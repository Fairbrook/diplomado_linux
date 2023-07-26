#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/rtc.h>
#include <linux/bcd.h>
#define SECONDS_REGISTER 0x00
#define WEEKDAY_REGISTER 0x03
#define DATE_REGISTER 0x04
#define MODE_12H_MASK 0x40
#define PM_OR_10H_MASK 0x20
#define MONTH_MASK 0x1F
#define CENTURY_MASK 0x80
#define is_12h_mode(reg) \
    (((reg) & MODE_12H_MASK) >> 6)
#define get_pm_or_10h(reg) \
    (((reg) & PM_OR_10H_MASK) >> 5)
#define is_year_overflowed(reg) \
    (((reg) & CENTURY_MASK) >> 7)

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

struct external_rtc_device_data {
  char label[20];
  struct rtc_device *rtc;
};

struct parallel_driver_data {
  struct class *driv_class;
};