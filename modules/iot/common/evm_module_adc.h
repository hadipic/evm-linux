/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_ADC_H
#define EVM_MODULE_ADC_H

#include "evm_module_periph_common.h"

bool iot_adc_read(iot_adc_t* adc);
bool iot_adc_close(iot_adc_t* adc);
bool iot_adc_open(iot_adc_t* adc);

void iot_adc_create_platform_data(iot_adc_t* gpio);
void iot_adc_destroy_platform_data (iot_adc_platform_data_t* platform_data);

evm_val_t iot_adc_set_platform_config(evm_t *e, iot_adc_t* adc,
                                            const evm_val_t jconfig);

#endif
