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

#ifdef EVM_USE_MODULE_ADC
#if !defined(__linux__)
#error "Module __FILE__ is for Linux only"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "evm_module_adc.h"

#define ADC_PIN_FORMAT ADC_INTERFACE ADC_PIN_INTERFACE
#define ADC_PATH_BUFFER_SIZE DEVICE_IO_PATH_BUFFER_SIZE
#define ADC_PIN_BUFFER_SIZE DEVICE_IO_PIN_BUFFER_SIZE
#define ADC_VALUE_BUFFER_SIZE 64

struct iot_adc_platform_data_s {
  char *device;
};


void iot_adc_create_platform_data(iot_adc_t* adc) {
  adc->platform_data = evm_malloc( sizeof(iot_adc_platform_data_t) );
}


void iot_adc_destroy_platform_data(iot_adc_platform_data_t* platform_data) {
  evm_free(platform_data->device);
  evm_free(platform_data);
}


evm_val_t iot_adc_set_platform_config(evm_t *e, iot_adc_t* adc,
                                            const evm_val_t jconfig) {

  iot_adc_platform_data_t* platform_data = adc->platform_data;

  evm_val_t str = evm_prop_get(e, jconfig, IOT_MAGIC_STRING_DEVICE);
  int len = evm_string_len(e, str);
  platform_data->device = evm_malloc(len + 1);
  memcpy(platform_data->device, evm_2_string(e, str), len);

  return EVM_UNDEFINED;
}


// Implementation used here are based on:
//  https://www.kernel.org/doc/Documentation/adc/sysfs.txt

bool iot_adc_read(iot_adc_t* adc) {
  iot_adc_platform_data_t* platform_data = adc->platform_data;

  const char* device_path = platform_data->device;
  char buffer[ADC_VALUE_BUFFER_SIZE];

  if (!system_open_read_close(device_path, buffer, sizeof(buffer))) {
    return false;
  }

  adc->value = atoi(buffer) != 0;

  return true;
}


bool iot_adc_close(iot_adc_t* adc) {
  return true;
}

bool iot_adc_open(iot_adc_t* adc) {
  iot_adc_platform_data_t* platform_data = adc->platform_data;

  EVM_LOG("%s()", __func__);
  const char* device_path = platform_data->device;

  // Check if ADC interface exists.
  if (!system_check_path(device_path)) {
    return false;
  }

  return true;
}
#endif
