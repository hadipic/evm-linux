#ifndef EVM_MODULE_GPIO_H
#define EVM_MODULE_GPIO_H

#include "evm_module_periph_common.h"

bool iot_gpio_open(iot_gpio_t* gpio);
bool iot_gpio_write(iot_gpio_t* gpio);
bool iot_gpio_read(iot_gpio_t* gpio);
bool iot_gpio_close(iot_gpio_t* gpio);
bool iot_gpio_set_direction(iot_gpio_t* gpio);

void iot_gpio_create_platform_data(iot_gpio_t* gpio);
void iot_gpio_destroy_platform_data (iot_gpio_platform_data_t* platform_data);

#endif
