#ifndef EVM_MODULE_PWM_H
#define EVM_MODULE_PWM_H

#include "evm_module_periph_common.h"

evm_val_t iot_pwm_set_platform_config(iot_pwm_t* pwm, evm_val_t jconfig);
bool iot_pwm_open(iot_pwm_t* pwm);
bool iot_pwm_set_period(iot_pwm_t* pwm);
bool iot_pwm_set_dutycycle(iot_pwm_t* pwm);
bool iot_pwm_set_enable(iot_pwm_t* pwm);
bool iot_pwm_close(iot_pwm_t* pwm);

void iot_pwm_create_platform_data(iot_pwm_t* pwm) ;
void iot_pwm_destroy_platform_data(iot_pwm_platform_data_t* pdata);

#endif
