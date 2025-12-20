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
#ifdef EVM_USE_MODULE_PWM

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evm_module_pwm.h"


// Generic PWM implementation for linux.


#define PWM_INTERFACE "/sys/class/pwm/pwmchip%d/"
#define PWM_PIN_INTERFACE "pwm%d/"
#define PWM_PIN_FORMAT PWM_INTERFACE PWM_PIN_INTERFACE
#define PWM_EXPORT PWM_INTERFACE "export"
#define PWM_UNEXPORT PWM_INTERFACE "unexport"
#define PWM_PIN_DUTYCYCLE "duty_cycle"
#define PWM_PIN_PERIOD "period"
#define PWM_PIN_ENABlE "enable"

#define PWM_PATH_BUFFER_SIZE 64
#define PWM_VALUE_BUFFER_SIZE 32

struct iot_pwm_platform_data_s {
  int chip;
  char *device;
};

void iot_pwm_create_platform_data(iot_pwm_t* pwm) {
  pwm->platform_data = evm_malloc(sizeof (iot_pwm_platform_data_t) );
  pwm->platform_data->chip = 0;
}

void iot_pwm_destroy_platform_data(iot_pwm_platform_data_t* pdata) {
  evm_free(pdata->device);
  evm_free(pdata);
}

evm_val_t iot_pwm_set_platform_config(iot_pwm_t* pwm, evm_val_t jconfig) {
    evm_t *e = evm_runtime();
    iot_pwm_platform_data_t* platform_data = pwm->platform_data;
    evm_val_t jchip = evm_prop_get(e, jconfig, "chip");

    if (evm_is_undefined(e, jchip)) {
        return jchip;
    }

    if (evm_is_number(e, jchip)) {
        platform_data->chip = evm_2_integer(e, jchip);
    } else {
        platform_data->chip = 0;
    }

    evm_val_free(e, jchip);

    return EVM_UNDEFINED;
}

// Generate device path for specified PWM device.
// The path may include node suffix if passed ('enable', 'period', 'duty_cycle')
// Pointer to a allocated string is returned, or null in case of error.
// If PWM_PIN_FORMAT format results in an empty string,
// NULL is returned (and fileName is ignored).
static char* generate_device_subpath(char* device,
                                     const char* fileName) {
  char* devicePath = NULL;
  // Do not print anything, only calculate resulting string length.
  size_t prefixSize = strlen(device);
  if (prefixSize > 0) {
    size_t suffixSize = fileName ? strlen(fileName) : 0;
    devicePath = evm_malloc(prefixSize + suffixSize + 1);
    if (devicePath) {
      // Do not need to check bounds, the buffer is of exact required size.
      memcpy(devicePath, device, prefixSize);
      memcpy(devicePath + prefixSize, fileName, suffixSize);
      devicePath[prefixSize + suffixSize] = 0;
    }
  }
  return devicePath;
}

// Limit period to [0..1]s
static double adjust_period(double period) {
  if (period < 0) {
    return 0.0;
  } else if (period > 1) {
    return 1.0;
  } else {
    return period;
  }
}


bool iot_pwm_open(iot_pwm_t* pwm) {
  iot_pwm_platform_data_t* platform_data = pwm->platform_data;

  char path[PWM_PATH_BUFFER_SIZE] = { 0 };
  if (snprintf(path, PWM_PATH_BUFFER_SIZE, PWM_PIN_FORMAT, platform_data->chip,
               pwm->pin) < 0) {
    return false;
  }

  platform_data->device = evm_malloc(strlen(path));
  memcpy(platform_data->device, path, strlen(path));

  // See if the PWM is already opened.
  if (!system_check_path(path)) {
    // Write exporting PWM path
    char export_path[PWM_PATH_BUFFER_SIZE] = { 0 };
    snprintf(export_path, PWM_PATH_BUFFER_SIZE, PWM_EXPORT,
             platform_data->chip);

    const char* created_files[] = { PWM_PIN_DUTYCYCLE, PWM_PIN_PERIOD,
                                    PWM_PIN_ENABlE };
    int created_files_length = sizeof(created_files) / sizeof(created_files[0]);
    if (!system_device_open(export_path, pwm->pin, path, created_files,
                                    created_files_length)) {
      return false;
    }
  }

  // Set options.
  if (pwm->period >= 0) {
    if (!iot_pwm_set_period(pwm)) {
      return false;
    }
    if (pwm->duty_cycle >= 0) {
      if (!iot_pwm_set_dutycycle(pwm)) {
        return false;
      }
    }
  }

  return true;
}


bool iot_pwm_set_period(iot_pwm_t* pwm) {
  iot_pwm_platform_data_t* platform_data = pwm->platform_data;

  bool result = false;
  if (isfinite(pwm->period) && pwm->period >= 0.0) {
    char* devicePath =
        generate_device_subpath(platform_data->device, PWM_PIN_PERIOD);
    if (devicePath) {
      // Linux API uses nanoseconds, thus 1E9
      unsigned int value = (unsigned)(adjust_period(pwm->period) * 1.E9);
      char buf[PWM_VALUE_BUFFER_SIZE];
      if (snprintf(buf, sizeof(buf), "%d", value) > 0) {
        result = system_open_write_close(devicePath, buf);
      }
      evm_free(devicePath);
    }
  }
  return result;
}


bool iot_pwm_set_dutycycle(iot_pwm_t* pwm) {
  iot_pwm_platform_data_t* platform_data = pwm->platform_data;

  bool result = false;
  double dutyCycle = pwm->duty_cycle;
  if (isfinite(pwm->period) && pwm->period >= 0.0 && isfinite(dutyCycle) &&
      0.0 <= dutyCycle && dutyCycle <= 1.0) {
    char* devicePath =
        generate_device_subpath(&platform_data->device, PWM_PIN_DUTYCYCLE);
    if (devicePath) {
      double period = adjust_period(pwm->period);
      // Linux API uses nanoseconds, thus 1E9
      unsigned dutyCycleValue = (unsigned)(period * pwm->duty_cycle * 1E9);

      char buf[PWM_VALUE_BUFFER_SIZE];
      if (snprintf(buf, sizeof(buf), "%d", dutyCycleValue) < 0) {
        return false;
      }

      result = system_open_write_close(devicePath, buf);
      evm_free(devicePath);
    }
  }
  return result;
}


bool iot_pwm_set_enable(iot_pwm_t* pwm) {
  iot_pwm_platform_data_t* platform_data = pwm->platform_data;

  bool result = false;
  char* devicePath =
      generate_device_subpath(platform_data->device, PWM_PIN_ENABlE);
  if (devicePath) {
    char value[4];
    if (snprintf(value, sizeof(value), "%d", pwm->enable) < 0) {
      return false;
    }

    char buf[PWM_VALUE_BUFFER_SIZE];
    if (snprintf(buf, sizeof(buf), "%d", pwm->enable) < 0) {
      return false;
    }

    result = system_open_write_close(devicePath, buf);
    evm_free(devicePath);
  }
  return result;
}


bool iot_pwm_close(iot_pwm_t* pwm) {
  iot_pwm_platform_data_t* platform_data = pwm->platform_data;

  char path[PWM_PATH_BUFFER_SIZE] = { 0 };
  if (snprintf(path, PWM_PATH_BUFFER_SIZE, PWM_PIN_FORMAT, platform_data->chip,
               pwm->pin) < 0) {
    return false;
  }

  if (system_check_path(path)) {
    // Write exporting pin path
    char unexport_path[PWM_PATH_BUFFER_SIZE] = { 0 };
    if (snprintf(unexport_path, PWM_PATH_BUFFER_SIZE, PWM_UNEXPORT,
                 platform_data->chip) < 0) {
      return false;
    }

    system_device_close(unexport_path, pwm->pin);
  }

  return true;
}
#endif
