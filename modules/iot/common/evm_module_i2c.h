/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_I2C_H
#define EVM_MODULE_I2C_H

#include "evm_module_periph_common.h"

evm_val_t iot_i2c_set_platform_config(evm_t *e, iot_i2c_t* i2c, const evm_val_t jconfig);
bool iot_i2c_open(iot_i2c_t* i2c);
bool iot_i2c_write(iot_i2c_t* i2c);
bool iot_i2c_read(iot_i2c_t* i2c);
bool iot_i2c_close(iot_i2c_t* i2c);

void iot_i2c_create_platform_data(iot_i2c_t* i2c);
void iot_i2c_destroy_platform_data(iot_i2c_platform_data_t* pdata);

#endif
