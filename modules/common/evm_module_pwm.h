/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
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
