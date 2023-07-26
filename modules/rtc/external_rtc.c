#include "rtc.h"
#include <linux/rtc.h>

struct custom_rtc_time {
  int sec;
  int min;
  int hour;
  int is_12h;
  int pm;
};

struct custom_rtc_date {
  int wday;
  int mday;
  int mon;
  int year;
  int century;
};

/*
 * returns day of the week [0-6] 0=Sunday
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

static inline int calc_24_hours(struct custom_rtc_time *time) {
  return time->hour + time->pm * (time->is_12h ? 12 : 20);
}

static void move_to_first_reg(struct i2c_client *client) {
  u8 buf[1] = {SECONDS_REGISTER};
  i2c_master_send(client, buf, 1);
}

static void move_to_date_reg(struct i2c_client *client) {
  u8 buf[1] = {SECONDS_REGISTER};
  i2c_master_send(client, buf, 1);
}

static void time_from_buf(u8 *buf, struct custom_rtc_time *time) {
  time->sec = bcd2bin(buf[0]);
  time->min = bcd2bin(buf[1]);
  time->hour = bcd2bin(buf[2]);
  time->is_12h = is_12h_mode(buf[2]);
  time->pm = get_pm_or_10h(buf[2]);
}

static void date_from_buf(u8 *buf, struct custom_rtc_date *date) {
  date->wday = buf[0];
  date->mday = bcd2bin(buf[1]);
  date->mon = bcd2bin(buf[2] & MONTH_MASK);
  date->year = bcd2bin(buf[3]);
  date->century = is_year_overflowed(buf[2]);
}

static void custom2std(struct custom_rtc_date *c_date,
                       struct custom_rtc_time *c_time, struct rtc_time *time) {
  time->tm_sec = c_time->sec;
  time->tm_min = c_time->min;
  time->tm_hour = calc_24_hours(c_time);
  time->tm_wday = c_date->wday;
  time->tm_mday = c_date->mday;
  time->tm_mon = c_date->mon;
  time->tm_year = c_date->year + c_date->century * 100;
  time->tm_yday = rtc_year_days(c_date->mday, c_date->mon, c_date->year);
  time->tm_isdst = 0;
}

static void fill_time(u8 buf[7], struct rtc_time *time) {
  struct custom_rtc_date c_date;
  struct custom_rtc_time c_time;
  date_from_buf(buf, &c_date);
  time_from_buf(buf, &c_time);
  custom2std(&c_date, &c_time, time);
}

static void fill_buf(u8 *buf, struct rtc_time *time) {
  buf[0] = bin2bcd(time->tm_sec);
  buf[1] = bin2bcd(time->tm_min);
  buf[2] = bin2bcd(time->tm_hour & 0x3F);
  buf[3] = time->tm_wday;
  buf[4] = bin2bcd(time->tm_mday);
  buf[5] = bin2bcd(time->tm_mon) + (time->tm_year >= 100 ? CENTURY_MASK : 0);
  buf[6] = bin2bcd(time->tm_year % 100);
}

static int read_time(struct i2c_client *client, struct custom_rtc_time *time) {
  u8 buf[3];
  int ret;
  move_to_first_reg(client);
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  time_from_buf(buf, time);
  return 0;
}

static int write_time(struct i2c_client *client, struct custom_rtc_time *time) {
  u8 buf[4];
  buf[0] = SECONDS_REGISTER;
  buf[1] = bin2bcd(time->sec);
  buf[2] = bin2bcd(time->hour) | (time->pm << 5) | (time->is_12h << 6);
  int ret;
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  return 0;
}

static int read_date(struct i2c_client *client, struct custom_rtc_date *date) {
  u8 buf[4];
  int ret;
  move_to_date_reg(client);
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  date_from_buf(buf, time);
  return 0;
}

static int write_date(struct i2c_client *client, struct custom_rtc_date *date) {
  u8 buf[5];
  buf[0] = WEEKDAY_REGISTER;
  buf[1] = bin2bcd(date->wday);
  buf[2] = bin2bcd(date->mday);
  buf[3] = bin2bcd(date->mon);
  buf[4] = bin2bcd(date->year);
  int ret;
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    return ret;
  }
  return 0;
}

static ssize_t wtime_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  int ret, hour_offset = 0;
  char *pm_label = "";
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  ret = read_time(client, &time);
  if (ret) {
    return ret;
  }
  if (time.is_12h) {
    if (time.pm)
      pm_label = "PM";
    else
      pm_label = "AM";
  } else {
    hour_offset = time.pm * 20;
  }
  return snprintf(buf, PAGE_SIZE, "%02d:%02d:%02d %s\n",
                  time.hour + hour_offset, time.min, time.sec, pm_label);
}

static ssize_t wtime_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  struct custom_rtc_time time;
  int pm = 0, hour, min, sec, ret;
  int ret = sscanf(buf, "%02d:%02d:%02d", &hour, &min, &sec);
  if (ret != 3) {
    dev_err(dev, "Invalid time format");
    return -EINVAL;
  }
  read_time(to_i2c_client(dev->parent), &time);
  time.min = min;
  time.sec = sec;
  if (time.is_12h) {
    time.pm = hour > 12 ? 1 : 0;
    time.hour = hour > 12 ? hour - 12 : hour;
  } else {
    time.pm = (time.hour / 20) & 1;
    time.hour = time.hour % 20;
  }
  ret = write_time(to_i2c_client(dev->parent), &time);
  if (ret) {
    dev_err(dev, "Error while writing time");
    return ret;
  }
  return count;
}

static ssize_t wdate_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  struct custom_rtc_date date;
  int ret;
  ret = read_date(to_i2c_client(dev->parent), &date);
  if (ret) {
    dev_err(dev, "Error while reading date");
    return ret;
  }
  return snprintf(buf, PAGE_SIZE, "%02d/%02d/%04d\n", date.mday, date.mon + 1,
                  date.year + 1900 + (date.century * 100));
}

static ssize_t wdate_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  struct custom_rtc_date date;
  int day, month, year, ret, yday;
  ret = sscanf(buf, "%02d/%02d/%04d", &day, &month, &year);
  if (ret != 3) {
    dev_err(dev, "Invalid date format");
    return -EINVAL;
  }
  year -= 1900;
  yday = rtc_year_days(day, month - 1, year);
  date.century = (year / 100) & 1;
  date.year = year % 100;
  date.mday = day;
  date.mon = month - 1;
  date.wday = compute_wday(year, yday);
  ret = write_date(to_i2c_client(dev->parent), &date);
  if (ret) {
    dev_err(dev, "Error while writing date");
    return ret;
  }
  return count;
}

static ssize_t mode_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  int ret;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  ret = read_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  return snprintf(buf, PAGE_SIZE, "%s\n", time.is_12h ? "12h" : "24h");
}

static ssize_t mode_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  int ret;
  struct i2c_client *client = to_i2c_client(dev->parent);
  struct custom_rtc_time time;
  ret = read_time(client, &time);
  if (ret) {
    dev_err(dev, "Error while reading time");
    return ret;
  }
  if (sysfs_streq(buf, "12h")) {
    if (time.is_12h)
      return count;
    time.pm = time.hour > 12;
    time.hour = time.hour > 12 ? time.hour - 12 : time.hour;
    ret = write_time(client, &time);
    if (ret) {
      dev_err(dev, "Error while writing time");
      return ret;
    }
  }
  if (sysfs_streq(buf, "12h")) {
    if (time.is_12h)
      return count;
    time.pm = time.hour > 12;
    time.hour = time.hour > 12 ? time.hour - 12 : time.hour;
    ret = write_time(client, &time);
    if (ret) {
      dev_err(dev, "Error while writing time");
      return ret;
    }
  }
}

static DEVICE_ATTR_RW(wtime);
static DEVICE_ATTR_RW(wdate);
static DEVICE_ATTR_RW(mode);
static DEVICE_ATTR_RW(meridiem);

static struct attribute *dev_attrs[] = {
    &dev_attr_wtime.attr,
    &dev_attr_wdate.attr,
    NULL,
};

static struct attribute_group dev_attr_group = {
    .attrs = dev_attrs,
};

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

static int external_rtc_driver_probe(struct i2c_client *client,
                                     const struct i2c_device_id *id) {
  struct external_rtc_device_data *dev_data;
  struct device *dev = &client->dev;
  int ret = 0;

  dev_data = devm_kzalloc(dev, sizeof(*dev_data), GFP_KERNEL);
  if (!dev_data) {
    dev_err(dev, "Cannot allocate memory for device data");
    return -ENOMEM;
  }

  dev_data->rtc = devm_rtc_allocate_device(dev);
  if (IS_ERR(dev_data->rtc)) {
    dev_err(dev, "Error while creating device");
    return PTR_ERR(dev_data->rtc);
  }
  dev_data->rtc->ops = &external_rtc_driver_ops;
  rtc_add_group(dev_data->rtc, &dev_attr_group);
  ret = rtc_register_device(dev_data->rtc);
  if (ret) {
    dev_err(dev, "Error while registering device");
    return ret;
  }
  return 0;
}

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
