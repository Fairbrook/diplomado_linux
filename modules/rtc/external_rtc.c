#include "rtc.h"
#include <linux/rtc.h>

/*
 * returns day of the week [0-6] 0=Sunday
 */
static int compute_wday(rtc_time *time, int yday) {
  int ndays = time->tm_year * (365 % 7) + (time->tm_year - 1) / 4 -
              (time->tm_year - 1) / 100 + (time->tm_year - 1) / 400 + yday;

  /*
   * 1/1/0000 may or may not have been a Sunday (if it ever existed at
   * all) but assuming it was makes this calculation work correctly.
   */
  return ndays % 7;
}

static int calc_24_hours(u8 reg) {
  int h12 = bcd2bin(reg);
  u8 pm_or_h10 = get_pm_or_10h(reg);
  u8 is_12h = is_12h_mode(reg);
  return h12 + pm_or_h10 * (is_12h ? 12 : 20);
}

static void move_to_first_register(struct i2c_client *client) {
  u8 buf[1] = {SECONDS_REGISTER};
  i2c_master_send(client, buf, 1);
}

static void fill_time(u8 buf[7], struct rtc_time *time) {
  time->tm_sec = bcd2bin(buf[0]);
  time->tm_min = bcd2bin(buf[1]);
  time->tm_hour = calc_24_hours(buf[2]);
  time->tm_wday = buf[3];
  time->tm_mday = bcd2bin(buf[4]);
  time->tm_mon = bcd2bin(buf[5] & MONTH_MASK);
  time->tm_year = bcd2bin(buf[6]) + is_year_overflowed(buf[5]) * 100;
  time->tm_yday = rtc_year_days(time->tm_mday, time->tm_mon, time->tm_year);
  time->tm_isdst = 0;
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

static ssize_t atime_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  return 0;
}

static ssize_t atime_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  return count;
}

static ssize_t adate_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  return 0;
}

static ssize_t adate_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  return count;
}

static DEVICE_ATTR_RW(atime);
static DEVICE_ATTR_RW(adate);

static struct attribute *dev_attrs[] = {
    &dev_attr_atime.attr,
    &dev_attr_adate.attr,
    NULL,
};

static struct attribute_group dev_attr_group = {
    .attrs = dev_attrs,
};

static int external_rtc_read_time(struct device *dev, struct rtc_time *time) {
  u8 buf[7], ret;
  struct i2c_client *client = to_i2c_client(dev);
  move_to_first_register(client);
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
