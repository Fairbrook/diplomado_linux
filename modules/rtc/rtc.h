#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/rtc.h>
#define SECONDS_REGISTER 0x00
#define move_to_first_register(client) \
    u8 _tmp_buf[] = {SECONDS_REGISTER}; \
    i2c_master_send(client, _tmp_buf, 1);

struct external_rtc_device_data {
  char label[20];
  struct rtc_device *rtc;
};

struct parallel_driver_data {
  struct class *driv_class;
};
