#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio/consumer.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/sched.h>

struct parallel_device_data {
  char label[20];
  unsigned long value;
  struct gpio_descs *gpio_array;
};

struct parallel_driver_data {
  struct class *driv_class;
};
