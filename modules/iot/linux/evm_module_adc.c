#ifdef CONFIG_EVM_MODULE_ADC

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
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  iot_periph_call_async(adc, v[0], kAdcOpRead,
                          adc_worker);

  return EVM_UNDEFINED;
}

EVM_FUNCTION(adc_read_sync) {
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  if (!iot_adc_read(adc)) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kAdcOpRead)));
  }

  return evm_mk_number(e, adc->value);
}

EVM_FUNCTION(adc_close) {
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  iot_periph_call_async(adc, v[0], kAdcOpClose,
                          adc_worker);

  return EVM_UNDEFINED;
}

EVM_FUNCTION(adc_close_sync) {
  iot_adc_t *adc = evm_object_get_user_data(e, p);

  bool ret = iot_adc_close(adc);
  if (!ret) {
    evm_throw(e, evm_mk_string(e, iot_periph_error_str(kAdcOpClose)));
  }

  return EVM_UNDEFINED;
}

EVM_FUNCTION(adc_constructor) {
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
  return jadc;
}

void evm_module_adc(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, adc_constructor, IOT_MAGIC_STRING_CREATE, 0));
    evm_module_add(e, "adc", obj);
}
#endif
