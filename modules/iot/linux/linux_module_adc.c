/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
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

  DDDLOG("%s()", __func__);
  const char* device_path = platform_data->device;

  // Check if ADC interface exists.
  if (!system_check_path(device_path)) {
    return false;
  }

  return true;
}
