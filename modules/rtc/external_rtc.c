#include "rtc.h"
/*
| Dirección | Nombre del Registro | Descripción                     |
|-----------|---------------------|---------------------------------|
| 0x00      | Segundos            | Segundos (00-59)                |
| 0x01      | Minutos             | Minutos (00-59)                 |
| 0x02      | Hora                | Hora (formato 24 horas) (1-23)  |
| 0x03      | Día de la semana    | Día de la semana (1-7)          |
| 0x04      | Día del mes         | Día del mes (01-31)             |
| 0x05      | Mes                 | Mes (01-12)                     |
| 0x06      | Año                 | Año (00-99)                     |
| 0x07      | Control             | Configuración de control        |
| 0x0E      | Estado              | Estado                          |
| 0x0F      | Aging Offset        | Ajuste de envejecimiento        |
| 0x10      | Temperatura MSB     | Parte alta de la temperatura    |
| 0x11      | Temperatura LSB     | Parte baja de la temperatura    |
*/

static int external_rtc_read_time(struct device *dev, struct rtc_time *time) {
  u8 buf[7], ret;
  struct i2c_client *client = to_i2c_client(dev);
  move_to_first_register(client);
  ret = i2c_master_recv(client, buf, sizeof(buf));
  if (ret < 0) {
    dev_err(dev, "Error while reading rtc time");
    return ret;
  }
  time->tm_sec = (buf[0] & 0xF) + ((buf[0] & 0xF0) >> 4) * 10;
  time->tm_min = (buf[1] & 0xF) + ((buf[1] & 0xF0) >> 4) * 10;
  time->tm_hour = buf[2];
  time->tm_wday = buf[3];
  time->tm_mday = (buf[4] & 0xF) + ((buf[4] & 0xF0) >> 4) * 10;
  time->tm_mon = (buf[5] & 0xF) + ((buf[5] & 0x10) >> 4) * 10;
  time->tm_year = (buf[6] & 0xF) + ((buf[6] & 0xF0) >> 4) * 10;
  time->tm_yday = 0;
  time->tm_isdst = 0;
  dev_info(dev, "%02x %02x %02x %02x %02x %02x %02x", time->tm_sec,
           time->tm_min, time->tm_hour, time->tm_wday, time->tm_mday,
           time->tm_mon, time->tm_year);
  return 0;
}

static int external_rtc_set_time(struct device *dev, struct rtc_time *time) {
  int ret;
  u8 buf[8] = {0,
               time->tm_sec,
               time->tm_min,
               time->tm_hour,
               time->tm_wday,
               time->tm_mday,
               time->tm_mon,
               time->tm_year};
  struct i2c_client *client = to_i2c_client(dev);
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
  const char *name;

  dev_data = devm_kzalloc(dev, sizeof(*dev_data), GFP_KERNEL);
  if (!dev_data) {
    dev_err(dev, "Cannot allocate memory for device data");
    return -ENOMEM;
  }

  //  if (of_property_read_string(dev->of_node, "label", &name)) {
  //    dev_err(dev, "Missing label from device tree");
  //    return -EINVAL;
  //  }
  //  strncpy(dev_data->label, name, sizeof(dev_data->label));
  dev_data->rtc = devm_rtc_allocate_device(dev);
  if (IS_ERR(dev_data->rtc)) {
    dev_err(dev, "Error while creating device");
    return PTR_ERR(dev_data->rtc);
  }
  dev_data->rtc->ops = &external_rtc_driver_ops;
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
