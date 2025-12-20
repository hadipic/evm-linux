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
#include "evm_module_adc.h"

IOT_DEFINE_PERIPH_CREATE_FUNCTION(adc)

static void adc_worker(uv_work_t* work_req) {
  iot_periph_data_t* worker_data =
      (iot_periph_data_t*)IOT_UV_REQUEST_EXTRA_DATA(work_req);
  iot_adc_t* adc = (iot_adc_t*)worker_data->data;

  switch (worker_data->op) {
    case kAdcOpOpen:
      worker_data->result = iot_adc_open(adc);
      break;
    case kAdcOpRead:
      worker_data->result = iot_adc_read(adc);
      break;
    case kAdcOpClose:
      worker_data->result = iot_adc_close(adc);
      break;
    default:
      EVM_ASSERT(!"Invalid Adc Operation");
  }
}

EVM_FUNCTION(adc_read) {
    EVM_EPCV;
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  iot_periph_call_async(adc, v[0], kAdcOpRead,
                          adc_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(adc_read_sync) {
    EVM_EPCV;
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  if (!iot_adc_read(adc)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kAdcOpRead)));
  }

  EVM_RETURN(evm_mk_number(e, adc->value));
}

EVM_FUNCTION(adc_close) {
    EVM_EPCV;
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  iot_periph_call_async(adc, v[0], kAdcOpClose,
                          adc_worker);

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(adc_close_sync) {
    EVM_EPCV;
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  bool ret = iot_adc_close(adc);
  if (!ret) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kAdcOpClose)));
  }

  EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(adc_constructor) {
    EVM_EPCV;
  // Create ADC object
  const evm_val_t jadc = evm_object_create(e);
  iot_adc_t* adc = adc_create(e, jadc);

  evm_val_t jconfig = v[0];

  evm_val_t config_res = iot_adc_set_platform_config(e, adc, jconfig);
  EVM_ASSERT(evm_is_undefined(e, config_res));

  evm_val_t jcallback = v[1];

  // If the callback doesn't exist, it is completed synchronously.
  // Otherwise, it will be executed asynchronously.
  if (!evm_is_null(e, jcallback)) {
    iot_periph_call_async(adc, jcallback, kAdcOpOpen, adc_worker);
  } else if (!iot_adc_open(adc)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kAdcOpOpen)));
  }
  evm_prop_set(e, jadc, IOT_MAGIC_STRING_CLOSE, evm_mk_native(e, adc_close, IOT_MAGIC_STRING_CLOSE, 0));
  evm_prop_set(e, jadc, IOT_MAGIC_STRING_CLOSESYNC, evm_mk_native(e, adc_close_sync, IOT_MAGIC_STRING_CLOSESYNC, 0));
  evm_prop_set(e, jadc, IOT_MAGIC_STRING_READ, evm_mk_native(e, adc_read, IOT_MAGIC_STRING_READ, 0));
  evm_prop_set(e, jadc, IOT_MAGIC_STRING_READSYNC, evm_mk_native(e, adc_read_sync, IOT_MAGIC_STRING_READSYNC, 0));
  EVM_RETURN(jadc);
}

void evm_module_adc(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, adc_constructor, IOT_MAGIC_STRING_CREATE, 0));
    evm_module_add(e, "adc", obj);
}
#endif
