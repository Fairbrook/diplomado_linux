#include "parallel.h"
static struct parallel_driver_data driver_data;

static ssize_t value_store(struct device *dev, struct device_attribute *attr,
                           const char *buf, size_t count) {
  struct parallel_device_data *dev_data = dev_get_drvdata(dev);
  struct gpio_descs *gpios = dev_data->gpio_array;
  unsigned long value;
  int ret;
  ret = kstrtoul(buf, 0, &value);
  if (ret) {
    dev_err(dev, "Bad input, expected number");
    return ret;
  }
  dev_data->value = value;
  ret = gpiod_set_array_value(gpios->ndescs, gpios->desc, gpios->info,
                              &dev_data->value);
  if (ret) {
    dev_err(dev, "Error while seting the gpios value");
    return ret;
  }
  return count;
}

static ssize_t value_show(struct device *dev, struct device_attribute *attr,
                          char *buf) {
  struct parallel_device_data *dev_data = dev_get_drvdata(dev);
  return snprintf(buf, PAGE_SIZE, "%lu\n", dev_data->value);
}

static DEVICE_ATTR_RW(value);

static struct attribute *dev_attrs[] = {
    &dev_attr_value.attr,
    NULL,
};

static struct attribute_group dev_attr_group = {
    .attrs = dev_attrs,
};

static const struct attribute_group *dev_attr_groups[] = {
    &dev_attr_group,
    NULL,
};

static int parallel_device_probe(struct platform_device *pdev) {
  struct device *dev = &pdev->dev, *child;
  struct parallel_device_data *dev_data;
  const char *name;
  dev_info(dev, "Probe new device");

  dev_data = devm_kzalloc(dev, sizeof(struct parallel_device_data), GFP_KERNEL);
  dev_data->value = 0;
  if (dev_data == NULL) {
    dev_err(dev, "Cannot allocate memory for device data");
    return -ENOMEM;
  }
  if (of_property_read_string(dev->of_node, "label", &name)) {
    dev_err(dev, "Missing label from device tree");
    return -EINVAL;
  }
  strncpy(dev_data->label, name, sizeof(dev_data->label));

  dev_data->gpio_array = devm_gpiod_get_array(dev, "led", GPIOD_OUT_HIGH);
  if (IS_ERR(dev_data->gpio_array)) {
    dev_err(dev, "GPIO pins not found");
    return PTR_ERR(dev_data->gpio_array);
  }
  dev_info(dev, "Found device with %d pins", dev_data->gpio_array->ndescs);

  child = device_create_with_groups(driver_data.driv_class, &pdev->dev, 0,
                                    dev_data, dev_attr_groups, dev_data->label);
  if (IS_ERR(child)) {
    dev_err(dev, "Error while creating device");
    return PTR_ERR(child);
  }

  platform_set_drvdata(pdev, child);
  return 0;
}

static int parallel_device_remove(struct platform_device *pdev) {
  struct device *child = platform_get_drvdata(pdev);
  dev_info(&pdev->dev, "Remove call\n");
  if (child != NULL)
    device_unregister(child);
  return 0;
}

static const struct of_device_id of_parallel_device_match[] = {
    {
        .compatible = "kamv,parallel",
    },
    {},
};

MODULE_DEVICE_TABLE(of, of_parallel_device_match);

static struct platform_driver parallel_device_driver = {
    .probe = parallel_device_probe,
    .remove = parallel_device_remove,
    .driver = {.name = "parallel_device",
               .of_match_table = of_parallel_device_match},
};

static int __init parallel_init(void) {
  int ret;
  pr_info("Parallel leds driver init\n");
  driver_data.driv_class = class_create(THIS_MODULE, "parallel");
  if (IS_ERR(driver_data.driv_class)) {
    pr_err("Could not create class\n");
    ret = PTR_ERR(driver_data.driv_class);
    return ret;
  }

  ret = platform_driver_register(&parallel_device_driver);
  if (ret < 0) {
    class_destroy(driver_data.driv_class);
    return ret;
  }

  pr_info("Parallel driver loaded");
  return 0;
}

static void __exit parallel_exit(void) {
  platform_driver_unregister(&parallel_device_driver);
  class_destroy(driver_data.driv_class);

  pr_info("Parallel driver unloaded\n");
}

module_init(parallel_init);
module_exit(parallel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Martinez");
