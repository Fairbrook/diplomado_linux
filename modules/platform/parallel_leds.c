#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio/consumer.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#define PORT_LEN 4
#define LED_LABEL "-led"
#define LED_LABEL_LEN 6
#define SLEEP_QUANTUM 10
#define DEMO_SEQUENCE_LEN 4

struct parallel_private_data {
  char value;
  char label[20];
  struct task_struct *task;
  struct gpio_desc *devices[4];
};
struct parallel_driver_data {
  size_t device_count;
  struct class *parallel_class;
  struct device **devices;
};
static struct parallel_driver_data driver_data;
char demo_sequence[] = {9, 15, 9, 0};

static void set_position(char *reg, unsigned pos, unsigned value) {
  unsigned mask = 0x1 << pos;
  if (value == 0) {
    *reg &= ~mask;
    return;
  }
  *reg |= mask;
}

static unsigned get_position(char *reg, unsigned pos) {
  return ((*reg) & 0x1 << pos) >> pos;
}

static void apply_state(struct parallel_private_data *private_data) {
  int i = 0;
  for (i = 0; i < PORT_LEN; i++) {
    gpiod_set_value(private_data->devices[i],
                    get_position(&private_data->value, i));
  }
}

int msleep_or_stop(unsigned ms) {
  int len = ms / SLEEP_QUANTUM;
  int i;
  for (i = 0; i < len; i++) {
    msleep(SLEEP_QUANTUM);
    if (kthread_should_stop())
      return 1;
  }
  return 0;
}

int parallel_leds_demo(void *pv) {
  struct parallel_private_data *dev_data = (struct parallel_private_data *)pv;
  int step = 0;
  while (!kthread_should_stop()) {
    for (step = 0; step < DEMO_SEQUENCE_LEN; step++) {
      dev_data->value = demo_sequence[step];
      apply_state(dev_data);
      if (msleep_or_stop(500))
        return 0;
    }
  }
  return 0;
}

void stop_demo(struct parallel_private_data *dev_data) {
  if (dev_data->task == NULL)
    return;
  kthread_stop(dev_data->task);
  dev_data->task = NULL;
}

static ssize_t parse_and_set_led(unsigned index, struct device *dev,
                                 struct device_attribute *attr, const char *buf,
                                 size_t count) {
  unsigned value;
  int ret;
  struct parallel_private_data *dev_data;
  ret = kstrtouint(buf, 0, &value);
  if (ret) {
    dev_err(dev, "Bad formated input, expected number");
    return ret;
  }
  // Should use locks
  dev_data = dev_get_drvdata(dev);
  stop_demo(dev_data);
  set_position(&dev_data->value, index, value);
  apply_state(dev_data);

  return count;
}

static ssize_t parse_and_get_led(unsigned index, struct device *dev,
                                 struct device_attribute *attr, char *buf) {
  struct parallel_private_data *dev_data = dev_get_drvdata(dev);
  return snprintf(buf, PAGE_SIZE, "%u\n",
                  get_position(&dev_data->value, index));
}

static ssize_t led0_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  return parse_and_set_led(0, dev, attr, buf, count);
}
static ssize_t led0_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  return parse_and_get_led(0, dev, attr, buf);
}

static ssize_t led1_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  return parse_and_set_led(1, dev, attr, buf, count);
}
static ssize_t led1_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  return parse_and_get_led(1, dev, attr, buf);
}

static ssize_t led2_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  return parse_and_set_led(2, dev, attr, buf, count);
}
static ssize_t led2_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  return parse_and_get_led(2, dev, attr, buf);
}

static ssize_t led3_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  return parse_and_set_led(3, dev, attr, buf, count);
}
static ssize_t led3_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  return parse_and_get_led(3, dev, attr, buf);
}

static ssize_t value_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  unsigned value;
  int ret;
  struct parallel_private_data *dev_data;
  ret = kstrtouint(buf, 0, &value);
  if (ret) {
    dev_err(dev, "Bad formated input, expected number");
    return ret;
  }
  // Should use locks
  dev_data = dev_get_drvdata(dev);
  stop_demo(dev_data);
  dev_data->value = value;
  apply_state(dev_data);
  return count;
}

static ssize_t value_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  struct parallel_private_data *dev_data = dev_get_drvdata(dev);
  return snprintf(buf, PAGE_SIZE, "%u\n", dev_data->value);
}

static ssize_t demo_store(struct device *dev, struct device_attribute *attr,
                          const char *buf, size_t count) {
  struct parallel_private_data *dev_data = dev_get_drvdata(dev);
  int ret;
  if (sysfs_streq(buf, "on")) {
    dev_data->task = kthread_run(parallel_leds_demo, dev_data, dev_data->label);
    if (IS_ERR(dev_data->task)) {
      dev_err(dev, "Error while starting thread");
      ret = PTR_ERR(dev_data->task);
      dev_data->task = NULL;
      return ret;
    }
    return count;
  }
  if (sysfs_streq(buf, "off")) {
    stop_demo(dev_data);
    return count;
  }
  return -EINVAL;
}

static ssize_t demo_show(struct device *dev, struct device_attribute *attr,
                         char *buf) {
  struct parallel_private_data *dev_data = dev_get_drvdata(dev);
  int ret;
  ret = snprintf(buf, 4, "%s", dev_data->task == NULL ? "off" : "on");
  return ret;
}

static DEVICE_ATTR_RW(led0);
static DEVICE_ATTR_RW(led1);
static DEVICE_ATTR_RW(led2);
static DEVICE_ATTR_RW(led3);
static DEVICE_ATTR_RW(demo);
static DEVICE_ATTR_RW(value);

static struct attribute *dev_attrs[] = {
    &dev_attr_led0.attr,
    &dev_attr_led1.attr,
    &dev_attr_led2.attr,
    &dev_attr_led3.attr,
    &dev_attr_value.attr,
    &dev_attr_demo.attr,
    NULL,
};

static struct attribute_group dev_attr_group = {
    .attrs = dev_attrs,
};

static const struct attribute_group *dev_attr_groups[] = {
    &dev_attr_group,
    NULL,
};

static void
parallel_leds_node_label_assign(struct device *dev, struct device_node *node,
                                struct parallel_private_data *dev_data,
                                unsigned index) {
  const char *name;
  if (of_property_read_string(node, "label", &name)) {
    dev_warn(dev, "Missing label from device tree\n");
    snprintf(dev_data->label, sizeof(dev_data->label), "unknown_port%d", index);
  } else {
    strcpy(dev_data->label, name);
  }
  dev_info(dev, "Device label = %s", dev_data->label);
}

static int
parallel_leds_child_node_register(struct device *dev, struct device_node *child,
                                  struct parallel_private_data *dev_data,
                                  unsigned index) {
  size_t label_len;
  int pin_index = 0;
  char *pin_label = NULL;
  int ret;

  dev_data->value = 0;
  dev_data->task = NULL;
  /* Get a lable device tree child node */
  parallel_leds_node_label_assign(dev, child, dev_data, index);
  label_len = strnlen(dev_data->label, sizeof(dev_data->label)) + LED_LABEL_LEN;

  for (pin_index = 0; pin_index < PORT_LEN; pin_index++) {
    pin_label = devm_kzalloc(dev, label_len, GFP_KERNEL);
    if (pin_label == NULL) {
      dev_err(dev, "Can't allocate memory\n");
      return -ENOMEM;
    }
    snprintf(pin_label, label_len, "%s" LED_LABEL "%d", dev_data->label,
             pin_index);

    dev_data->devices[pin_index] = devm_fwnode_gpiod_get_index(
        dev, &child->fwnode, "led", pin_index, GPIOD_OUT_HIGH, pin_label);
    if (IS_ERR(dev_data->devices[pin_index])) {
      ret = PTR_ERR(dev_data->devices[pin_index]);
      if (ret == -ENOENT)
        dev_err(
            dev,
            "Parallel driver is expecting 4 gpios in led-gpios attribute\n");
      return ret;
    }
  }
  apply_state(dev_data);
  return 0;
}

static int parallel_leds_device_probe(struct platform_device *pdev) {
  struct device *dev = &pdev->dev;
  struct device_node *node = dev->of_node;
  struct device_node *child = NULL;
  struct parallel_private_data *dev_data;
  int child_index = 0, ret;
  pr_info("Probing parallel_leds device\n");

  driver_data.device_count = of_get_child_count(node);

  if (!driver_data.device_count) {
    dev_err(dev, "Child node not found");
    return -EINVAL;
  }

  dev_info(dev, "Found %d child nodes", driver_data.device_count);
  driver_data.devices = devm_kzalloc(
      dev, sizeof(struct device *) * driver_data.device_count, GFP_KERNEL);
  if (driver_data.devices == NULL) {
    dev_err(dev, "Cannot allocate memory for child nodes");
    return -ENOMEM;
  }

  for_each_available_child_of_node(node, child) {
    dev_data = devm_kzalloc(dev, sizeof(*dev_data), GFP_KERNEL);
    if (!dev_data) {
      dev_err(dev, "Can't allocate memory\n");
      return -ENOMEM;
    }
    ret = parallel_leds_child_node_register(dev, child, dev_data, child_index);
    if (ret)
      return ret;
    driver_data.devices[child_index] =
        device_create_with_groups(driver_data.parallel_class, NULL, 0, dev_data,
                                  dev_attr_groups, dev_data->label);
    if (IS_ERR(driver_data.devices[child_index])) {
      dev_err(dev, "Create device error!\n");
      return PTR_ERR(driver_data.devices[child_index]);
    }
    child_index++;
  }

  return 0;
}

static int parallel_leds_device_remove(struct platform_device *pdev) {
  int i = 0;
  struct parallel_private_data *dev_data;

  dev_info(&pdev->dev, "Remove call\n");

  for (i = 0; i < driver_data.device_count; i++) {
    dev_data = dev_get_drvdata(driver_data.devices[i]);
    stop_demo(dev_data);
    device_unregister(driver_data.devices[i]);
  }

  return 0;
}

static const struct of_device_id of_parallel_leds_device_match[] = {
    {
        .compatible = "kamv,parallel-leds",
    },
    {},
};

MODULE_DEVICE_TABLE(of, of_parallel_leds_device_match);

static struct platform_driver parallel_leds_device_driver = {
    .probe = parallel_leds_device_probe,
    .remove = parallel_leds_device_remove,
    .driver = {.name = "parallel_leds_device",
               .of_match_table = of_parallel_leds_device_match},
};

static int __init parallel_leds_init(void) {
  int ret;
  pr_info("Parallel leds driver init\n");
  driver_data.parallel_class = class_create(THIS_MODULE, "parallel_leds");
  if (IS_ERR(driver_data.parallel_class)) {
    pr_err("Could not create class\n");
    ret = PTR_ERR(driver_data.parallel_class);
    return ret;
  }

  ret = platform_driver_register(&parallel_leds_device_driver);
  if (ret < 0) {
    class_destroy(driver_data.parallel_class);
    return ret;
  }

  pr_info("Parallel leds driver loaded");
  return 0;
}

static void __exit parallel_leds_exit(void) {
  platform_driver_unregister(&parallel_leds_device_driver);
  class_destroy(driver_data.parallel_class);

  pr_info("Parallel leds driver unloaded\n");
}

module_init(parallel_leds_init);
module_exit(parallel_leds_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Martinez");
