#include "rtc.h"

/*
 * returns day of the week [0-6] 0=Sunday
 * This function belongs to the rtc efi driver
 */
static int compute_wday(int year, int yday) {
  int ndays = year * (365 % 7) + (year - 1) / 4 - (year - 1) / 100 +
              (year - 1) / 400 + yday;

  /*
   * 1/1/0000 may or may not have been a Sunday (if it ever existed at
   * all) but assuming it was makes this calculation work correctly.
   */
  return ndays % 7;
}

/*
 * Returns hour of the day [0-23]
 * Whether the mode is 12 or 24
 * */
static inline int calc_24_hours(struct custom_rtc_time *time) {
  if (time->is_12h) {
    return (time->hour % 12) + time->pm * 12;
  }
  return time->hour + time->pm * time->is_12h * 20;
}

/*
 * Sets the device pointer to the first register
 * */
static void move_to_first_reg(struct i2c_client *client) {
  u8 buf[1] = {SECONDS_REGISTER};
  i2c_master_send(client, buf, 1);
}

/*
 * Sets the device pointer to the date register
 * */
static void move_to_date_reg(struct i2c_client *client) {
  u8 buf[1] = {WEEKDAY_REGISTER};
  i2c_master_send(client, buf, 1);
}

/*
 * Assigns the time to the custom struct from the buffer
 * */
static void time_from_buf(u8 *buf, struct custom_rtc_time *time) {
  // The RTC module saves the values in binary coded decimal, so conversion is
  // needed
  time->sec = bcd2bin(buf[0]);
  time->min = bcd2bin(buf[1]);
  time->hour = bcd2bin(buf[2] & 0x1F);
  time->is_12h = is_12h_mode(buf[2]);
  time->pm = get_pm_or_10h(buf[2]);
  time->hour24 = calc_24_hours(time);
}

/*
 * Assigns the date to the custom struct from the buffer
 * */
static void date_from_buf(u8 *buf, struct custom_rtc_date *date) {
  date->wday = buf[0];
  date->mday = bcd2bin(buf[1]);
  date->mon = bcd2bin(buf[2] & MONTH_MASK);
  date->year = bcd2bin(buf[3]);
  date->century = is_year_overflowed(buf[2]);
}

/*
 * Transforms the customs struct to the standard rtc_time struct
 * */
static void custom2std(struct custom_rtc_date *c_date,
                       struct custom_rtc_time *c_time, struct rtc_time *time) {
  time->tm_sec = c_time->sec;
  time->tm_min = c_time->min;
  time->tm_hour = c_time->hour24;
  time->tm_wday = c_date->wday;
  time->tm_mday = c_date->mday;
  time->tm_mon = c_date->mon;
  time->tm_year = c_date->year + c_date->century * 100;
  time->tm_yday = rtc_year_days(c_date->mday, c_date->mon, c_date->year);
  time->tm_isdst = 0;
}

/*
 * Fills the standard rtc_time struct with the contents of a buffer
 * */
static void fill_time(u8 buf[7], struct rtc_time *time) {
  struct custom_rtc_date c_date;
  struct custom_rtc_time c_time;
  time_from_buf(buf, &c_time);
  date_from_buf(buf + 3, &c_date);
  custom2std(&c_date, &c_time, time);
}

/*
 * Fills a buffer with the contents of the standard rtc_time struct
 * */
static void fill_buf(u8 *buf, struct rtc_time *time) {
  buf[0] = bin2bcd(time->tm_sec);
  buf[1] = bin2bcd(time->tm_min);
  buf[2] = bin2bcd(time->tm_hour & 0x3F);
  buf[3] = time->tm_wday;
  buf[4] = bin2bcd(time->tm_mday);
  buf[5] = bin2bcd(time->tm_mon) + (time->tm_year >= 100 ? CENTURY_MASK : 0);
  buf[6] = bin2bcd(time->tm_year % 100);
}

/*
 * Reads the time from the device
 * */
static int read_time(struct i2c_client *client, struct custom_rtc_time *time) {
  u8 buf[3];
  int ret;
  struct external_rtc_device_data *data = i2c_get_clientdata(client);
  // Sets the pointer to the first register
  move_to_first_reg(client);
  // Reads 3 bytes from the devices (time registers)
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  // Saves the read time to the las recived buffer
  data->last_recv[0] = buf[0];
  data->last_recv[1] = buf[1];
  data->last_recv[2] = buf[2];
  // Fills the struct with the read time
  time_from_buf(buf, time);
  return 0;
}

/*
 * Writes the time to the device
 * */
static int write_time(struct i2c_client *client, struct custom_rtc_time *time) {
  u8 buf[4];
  int ret;
  // The direction to the seconds register (is the first register)
  buf[0] = SECONDS_REGISTER;
  buf[1] = bin2bcd(time->sec);
  buf[2] = bin2bcd(time->min);
  buf[3] = bin2bcd(time->hour) | (time->pm << 5) | (time->is_12h << 6);
  // Sends the contents to save
  ret = i2c_master_send(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  return 0;
}

/*
 * Reads the date from the device
 * */
static int read_date(struct i2c_client *client, struct custom_rtc_date *date) {
  u8 buf[4];
  int ret;
  struct external_rtc_device_data *data = i2c_get_clientdata(client);
  // Sets the pointer to the date register
  move_to_date_reg(client);
  // Reads 4 bytes from the devices (date registers)
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  // Fills the las recived buffer with the read date
  data->last_recv[3] = buf[0];
  data->last_recv[4] = buf[1];
  data->last_recv[5] = buf[2];
  data->last_recv[6] = buf[3];
  // Fills the struct with the read date
  date_from_buf(buf, date);
  return 0;
}

/*
 * Writes the date to the device
 * */
static int write_date(struct i2c_client *client, struct custom_rtc_date *date) {
  u8 buf[5];
  int ret;
  // The direction to the date register
  buf[0] = WEEKDAY_REGISTER;
  buf[1] = date->wday;
  buf[2] = bin2bcd(date->mday);
  buf[3] = bin2bcd(date->mon) | (date->century << 7);
  buf[4] = bin2bcd(date->year);
  // Sends the contents to save
  ret = i2c_master_send(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  return 0;
}

/*
 * Returns a string with the time hh:mm:ss (am/pm)
 * */
static ssize_t ctime_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  int ret;
  char *pm_label = "";
  // !! Since the device points to the RTC with need to get the parent device
  // And get the full i2c estructure from the dev property. This is done in the
  // rest of the handlers
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  // Reads the current time
  ret = read_time(client, &time);
  if (ret) {
    return ret;
  }
  // Assing the pm or am label if necessary
  if (time.is_12h) {
    if (time.pm)
      pm_label = "PM";
    else
      pm_label = "AM";
  }
  // Returns the formated string
  return snprintf(buf, PAGE_SIZE, "%02d:%02d:%02d %s\n",
                  time.is_12h ? time.hour : time.hour24, time.min, time.sec,
                  pm_label);
}

/*
 * Writes the time to the devices. The required format is hh:mm:ss
 * */
static ssize_t ctime_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  struct custom_rtc_time time;
  int hour, min, sec;
  // Retrieves each of the values from the input
  int ret = sscanf(buf, "%02d:%02d:%02d", &hour, &min, &sec);
  if (ret != 3) {
    dev_err(dev, "Invalid time format");
    return -EINVAL;
  }
  // Read the current time
  read_time(to_i2c_client(dev->parent), &time);
  // Limits the read values to the valid maximum
  // !! Further validation is required for better error handeling
  min %= 60;
  sec %= 60;
  hour %= 24;
  time.min = min;
  time.sec = sec;
  // Formats the time to the appropiet registers
  if (time.is_12h) {
    time.pm = hour > 12 ? 1 : 0;
    time.hour = hour > 12 ? hour - 12 : hour;
  } else {
    time.pm = (hour / 20) & 1;
    time.hour = hour % 20;
  }
  time.hour = time.hour;
  // Writes the time to the device
  ret = write_time(to_i2c_client(dev->parent), &time);
  if (ret) {
    dev_err(dev, "Error while writing time");
    return ret;
  }
  return count;
}

/*
 * Returns a string with the date
 * */
static ssize_t cdate_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  struct custom_rtc_date date;
  int ret;
  // Reads the current date
  ret = read_date(to_i2c_client(dev->parent), &date);
  if (ret) {
    dev_err(dev, "Error while reading date");
    return ret;
  }
  // Returns the formated string
  // *Note: 1900 is the minimun year allowed thats why we add 1900
  return snprintf(buf, PAGE_SIZE, "%02d/%02d/%04d\n", date.mday, date.mon + 1,
                  date.year + 1900 + (date.century * 100));
}

/*
 * Writes the date to the device
 * */
static ssize_t cdate_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  struct custom_rtc_date date;
  int day, month, year, ret, yday;
  // Retrieves each of the values from the input buffer
  ret = sscanf(buf, "%02d/%02d/%04d", &day, &month, &year);
  if (ret != 3) {
    dev_err(dev, "Invalid date format");
    return -EINVAL;
  }
  // Limits the read values to the valid maximum
  // !! Further validation is required for better error handeling
  month -= 1;
  day %= 32;
  month %= 12;
  // Calculates the number of day in the year
  yday = rtc_year_days(day, month, year);
  // Calculates the day of week
  date.wday = compute_wday(year, yday);
  // 1900 is the minimun year allowed thats why we subtract 1900
  year -= 1900;
  // Check if year is bigger than 99 so that the century is set to 1
  date.century = (year / 100) & 1;
  date.year = year % 100;
  date.mday = day;
  date.mon = month;
  // Writes the date to the device
  ret = write_date(to_i2c_client(dev->parent), &date);
  if (ret) {
    dev_err(dev, "Error while writing date");
    return ret;
  }
  return count;
}

/*
 * Returns a string with the mode (24h or 12h)
 * */
static ssize_t mode_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  int ret;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  // Reads the current time
  ret = read_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  // Returns the formated string
  return snprintf(buf, PAGE_SIZE, "%s\n", time.is_12h ? "12h" : "24h");
}

/*
 * Writes the mode to the device
 * Makes the appropriate changes to the time value to make it equivalent
 * */
static ssize_t mode_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  int ret;
  int temphour;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  // Reads the current time
  ret = read_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  // Checks if the desired mode is 12h or 24h
  if (sysfs_streq(buf, "12h")) {
    // If the desired mode is the same as the current mode nothing is done
    if (time.is_12h)
      return count;
    // transforms 24h format to 12h
    time.pm = time.hour24 >= 12;
    time.hour = time.hour24 > 12 ? time.hour24 - 12 : time.hour24;
    time.is_12h = 1;
    // Writes the time
    ret = write_time(client, &time);
    if (ret) {
      dev_err(dev, "Error while writing time");
      return ret;
    }
    return count;
  }
  if (sysfs_streq(buf, "24h")) {
    // If the desired mode is the same as the current mode nothing is done
    if (!time.is_12h)
      return count;
    // transforms 12h format to 24h
    temphour = time.hour + (time.pm * 12);
    time.pm = (temphour / 20) & 1;
    time.hour = temphour % 20;
    time.is_12h = 0;
    // Writes the time
    ret = write_time(client, &time);
    if (ret) {
      dev_err(dev, "Error while writing time");
      return ret;
    }
    return count;
  }

  dev_err(dev, "Invalid mode");
  return -EINVAL;
}

/*
 * Returns a string with the meridiem (am/pm)
 * */
static ssize_t meridiem_show(struct device *dev, struct device_attribute *attr,
                             char *buf) {
  int ret;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  ret = read_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  // Returns the formated string (based in the calculated 24h time)
  return snprintf(buf, PAGE_SIZE, "%s\n", time.hour24 >= 12 ? "PM" : "AM");
}

/*
 * Writes the meridiem to the device
 * If device is in 24h mode and the user write the meridiem the time is
 * converted to 12h
 * */
static ssize_t meridiem_store(struct device *dev, struct device_attribute *attr,
                              const char *buf, size_t count) {
  int ret, meridiem = 0, valid_input = 0;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  ret = read_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  // Validates the input is either am or pm
  if (sysfs_streq(buf, "pm")) {
    meridiem = 1;
    valid_input = 1;
  }
  if (sysfs_streq(buf, "am")) {
    meridiem = 0;
    valid_input = 1;
  }
  if (!valid_input) {
    dev_err(dev, "Invalid meridiem");
    return -EINVAL;
  }
  // If mode is 24h the time is converted to 12h
  if (!time.is_12h) {
    time.hour = time.hour24 > 12 ? time.hour24 - 12 : time.hour24;
  }
  time.pm = meridiem;
  time.is_12h = true;
  // Writes the time
  ret = write_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while writing time");
    return ret;
  }
  return count;
}

/*
 * Returns a string with the day of the week
 * */
static ssize_t wday_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  int ret;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_date date;
  // Reads the current date
  ret = read_date(client, &date);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  // Returns the formated string
  return snprintf(buf, PAGE_SIZE, "%s\n", days[date.wday]);
}

/*
 * show the last recived date and time from the device
 * */
static ssize_t last_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct external_rtc_device_data *data = i2c_get_clientdata(client);
  return snprintf(buf, PAGE_SIZE,
                  "00: %02x\n"
                  "01: %02x\n"
                  "01: %02x\n"
                  "03: %02x\n"
                  "04: %02x\n"
                  "05: %02x\n"
                  "06: %02x\n",
                  data->last_recv[0], data->last_recv[1], data->last_recv[2],
                  data->last_recv[3], data->last_recv[4], data->last_recv[5],
                  data->last_recv[6]);
}

// Extra attributes to be added to the rtc device
static DEVICE_ATTR_RW(ctime);
static DEVICE_ATTR_RW(cdate);
static DEVICE_ATTR_RO(wday);
static DEVICE_ATTR_RO(last);
static DEVICE_ATTR_RW(mode);
static DEVICE_ATTR_RW(meridiem);

static struct attribute *dev_attrs[] = {
    &dev_attr_ctime.attr,
    &dev_attr_cdate.attr,
    &dev_attr_mode.attr,
    &dev_attr_meridiem.attr,
    &dev_attr_wday.attr,
    &dev_attr_last.attr,
    NULL,
};

static struct attribute_group dev_attr_group = {
    .attrs = dev_attrs,
};

/*
 * Reads the current date and time fromt the device
 * This function is used byt the kernel utility hwclock
 * */
static int external_rtc_read_time(struct device *dev, struct rtc_time *time) {
  u8 buf[7], ret;
  struct i2c_client *client = to_i2c_client(dev);
  move_to_first_reg(client);
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    dev_err(dev, "Error while reading rtc time");
    return ret;
  }
  fill_time(buf, time);
  return 0;
}

/*
 * Writes the current date and time to the device
 * This function is used byt the kernel utility hwclock
 * */
static int external_rtc_set_time(struct device *dev, struct rtc_time *time) {
  int ret;
  u8 buf[8];
  struct i2c_client *client = to_i2c_client(dev);
  buf[0] = SECONDS_REGISTER;
  fill_buf(buf + 1, time);
  ret = i2c_master_send(client, buf, sizeof(buf));
  if (ret < 0) {
    dev_err(dev, "Error while setting rtc time");
    return ret;
  }
  return 0;
}

struct rtc_class_ops external_rtc_driver_ops = {
    .read_time = external_rtc_read_time,
    .set_time = external_rtc_set_time,
};

/*
 * Probe function run by the kernel when the driver is loaded
 * Register the rtc device
 * */
static int external_rtc_driver_probe(struct i2c_client *client,
                                     const struct i2c_device_id *id) {
  struct external_rtc_device_data *dev_data;
  struct device *dev = &client->dev;
  int ret = 0;

  // Allocates the new device data
  dev_data = devm_kzalloc(dev, sizeof(*dev_data), GFP_KERNEL);
  if (!dev_data) {
    dev_err(dev, "Cannot allocate memory for device data");
    return -ENOMEM;
  }
  // Sets the device data as the client data for the i2c client device
  i2c_set_clientdata(client, dev_data);

  // Allocates a new rtc device
  dev_data->rtc = devm_rtc_allocate_device(dev);
  if (IS_ERR(dev_data->rtc)) {
    dev_err(dev, "Error while creating device");
    return PTR_ERR(dev_data->rtc);
  }

  // Sets the ops fot he hwclock utility
  dev_data->rtc->ops = &external_rtc_driver_ops;
  // Ads the custom attributes to the rtc device
  rtc_add_group(dev_data->rtc, &dev_attr_group);
  // Register the device to the rtc class
  ret = rtc_register_device(dev_data->rtc);
  if (ret) {
    dev_err(dev, "Error while registering device");
    return ret;
  }
  return 0;
}

/*
 * Called when the driver is removed from the system
 * Since all the allocated objects are managed by the i2c device whe do not need
 * to free anything
 * */
static int external_rtc_driver_remove(struct i2c_client *client) { return 0; }

static const struct of_device_id external_rtc_of_match[] = {
    {.compatible = "kamv,rtc"},
    {},
};

MODULE_DEVICE_TABLE(of, external_rtc_of_match);

static struct i2c_driver external_rtc_driver = {
    .driver = {.name = "external_rtc", .of_match_table = external_rtc_of_match},
    .probe = external_rtc_driver_probe,
    .remove = external_rtc_driver_remove};

module_i2c_driver(external_rtc_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Martinez");
