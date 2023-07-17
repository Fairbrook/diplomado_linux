#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/gpio/consumer.h>
#define PORT_LEN 4

static struct class *parallel_class;
static struct device *parallel_device;
struct parallel_private_data{
    char value;
    char label[20];
    struct gpio_desc *devices[4];
};

static void set_position(char *reg, unsigned pos, unsigned value ){
    unsigned mask = 0x1 << pos;
    if(value == 0) {
        *reg &= ~mask;
        return;
    }
    *reg |= mask;
}


static unsigned get_position(char *reg, unsigned pos){
    return ((*reg) & 0x1 << pos) >> pos;
}

static void apply_state(struct parallel_private_data *private_data){
    int i = 0;
    for(i = 0; i < PORT_LEN; i++){
         gpiod_set_value(private_data->devices[i], get_position(&private_data->value, i));
    }
}

static ssize_t parse_and_set_led(unsigned index, struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
    unsigned value;
    int ret;
    struct parallel_private_data *dev_data = dev_get_drvdata(dev);
    ret = kstrtouint(buf, 0, &value);
    if (ret) {
        dev_err(dev, "Bad formated input, expected number");
        return ret;
    }
    set_position(&dev_data->value, index, value);
    apply_state(dev_data);

    return count;
}

static ssize_t parse_and_get_led(unsigned index, struct device *dev, struct device_attribute *attr, char *buf){
    struct parallel_private_data *dev_data = dev_get_drvdata(dev);
    return snprintf(buf, PAGE_SIZE, "%u\n", get_position(&dev_data->value, index));
}

static ssize_t led0_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
    return parse_and_set_led(0, dev, attr, buf, count);
}
static ssize_t led0_show(struct device *dev, struct device_attribute *attr, char *buf){
    return parse_and_get_led(0, dev, attr, buf);
}


static ssize_t led1_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
    return parse_and_set_led(1, dev, attr, buf, count);
}
static ssize_t led1_show(struct device *dev, struct device_attribute *attr, char *buf){
    return parse_and_get_led(1, dev, attr, buf);
}

static ssize_t led2_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
    return parse_and_set_led(2, dev, attr, buf, count);
}
static ssize_t led2_show(struct device *dev, struct device_attribute *attr, char *buf){
    return parse_and_get_led(2, dev, attr, buf);
}

static ssize_t led3_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
    return parse_and_set_led(3, dev, attr, buf, count);
}
static ssize_t led3_show(struct device *dev, struct device_attribute *attr, char *buf){
    return parse_and_get_led(3, dev, attr, buf);
}

static ssize_t value_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count){
    unsigned value;
    int ret;
    struct parallel_private_data *dev_data = dev_get_drvdata(dev);
    ret = kstrtouint(buf, 0, &value);
    if (ret) {
        dev_err(dev, "Bad formated input, expected number");
        return ret;
    }
    dev_data->value = value;
    apply_state(dev_data);
    return count;
}

static ssize_t value_show(struct device *dev, struct device_attribute *attr, char *buf){
    struct parallel_private_data *dev_data = dev_get_drvdata(dev);
    return snprintf(buf, PAGE_SIZE, "%u\n", dev_data->value);
}

static DEVICE_ATTR_RW(led0);
static DEVICE_ATTR_RW(led1);
static DEVICE_ATTR_RW(led2);
static DEVICE_ATTR_RW(led3);
static DEVICE_ATTR_RW(value);


static struct attribute *dev_attrs[] = {
    &dev_attr_led0.attr,
    &dev_attr_led1.attr,
    &dev_attr_led2.attr,
    &dev_attr_led3.attr,
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

static int parallel_leds_device_probe(struct platform_device *pdev){
    struct parallel_private_data *dev_data;
    struct device *dev = &pdev->dev;
    const char *name;
    int i = 0, ret;
    pr_info("Probing parallel_leds device\n");

    dev_data = devm_kzalloc(dev, sizeof(*dev_data), GFP_KERNEL);
    if (!dev_data) {
        dev_err(dev, "Can't allocate memory\n");
        return -ENOMEM;
    }

     /* Get a lable device tree child node */
    if (of_property_read_string(dev->of_node, "label", &name)) {
        dev_warn(dev, "Missing label from device tree\n");
        snprintf(dev_data->label, sizeof(dev_data->label), "unknown_gpio");
    } 
    else {
        strcpy(dev_data->label, name);
        dev_info(dev, "Device label = %s", dev_data->label);
    }

    for(i = 0; i < PORT_LEN; i++){
        dev_data->devices[i] = devm_gpiod_get_index(dev, "led", i, GPIOD_OUT_HIGH);
        if(IS_ERR(dev_data->devices[i])){
            ret = PTR_ERR(dev_data->devices[i]);
            if (ret == -ENOENT)
                dev_err(dev, "Parallel driver is expecting 4 gpios in led-gpios attribute\n");
            return ret;
        }
    }

    parallel_device = device_create_with_groups(parallel_class, NULL, 0, dev_data, dev_attr_groups, dev_data->label);
    if (IS_ERR(parallel_device)) {
        dev_err(dev, "Create device error!\n");
        return PTR_ERR(parallel_device);
    }
    return 0;
}

static int parallel_leds_device_remove(struct platform_device *pdev){
    dev_info(&pdev->dev, "Remove call\n");
    device_unregister(parallel_device);

    return 0;
}

static const struct of_device_id of_parallel_leds_device_match[] = {
        { .compatible = "kamv,parallel-leds", },
        {},
};

MODULE_DEVICE_TABLE(of, of_parallel_leds_device_match);

static struct platform_driver parallel_leds_device_driver = {
        .probe          = parallel_leds_device_probe,
        .remove         = parallel_leds_device_remove,
        .driver         = {
                .name           = "parallel_leds_device",
                .of_match_table = of_parallel_leds_device_match 
        },
};

static int __init parallel_leds_init(void){
    int ret;
    pr_info("Parallel leds driver init\n");
    parallel_class = class_create(THIS_MODULE, "parallel_leds");
    if(IS_ERR(parallel_class)){
        pr_err("Could not create class\n");
        ret = PTR_ERR(parallel_class);
        return ret;
    }

    ret = platform_driver_register(&parallel_leds_device_driver);
    if(ret<0){
        class_destroy(parallel_class);
        return ret;
    }

    pr_info("Parallel leds driver loaded");
    return 0;
    
}

static void __exit parallel_leds_exit(void){
    platform_driver_unregister(&parallel_leds_device_driver);
    class_destroy(parallel_class);

    pr_info("Parallel leds driver unloaded\n");
}

module_init(parallel_leds_init);
module_exit(parallel_leds_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kevin Martinez");
