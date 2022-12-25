#ifdef CONFIG_EVM_MODULE_TIMER

#include "linux_uv.h"

void iot_timer_object_init(evm_val_t jtimer) {
  uv_handle_t* handle = iot_uv_handle_create(sizeof(uv_timer_t), jtimer, 0);
  uv_timer_init(system_get_uv_loop(), (uv_timer_t*)handle);
}


static void timeout_handler(uv_timer_t* handle) {
  EVM_ASSERT(handle != NULL);

  evm_val_t jobject = IOT_UV_HANDLE_DATA(handle)->jobject;
  evm_val_t jcallback =
      evm_prop_get(evm_runtime(), jobject, IOT_MAGIC_STRING_HANDLETIMEOUT);
  evm_call_free(evm_runtime(), jcallback, jobject, 0, NULL);
  evm_val_free(evm_runtime(), jcallback);
}


EVM_FUNCTION(timer_start) {
  // Check parameters.
  uv_timer_t *timer_handle = evm_object_get_user_data(e, p);

  // parameters.
  uint64_t timeout = evm_2_double(e, v[0]);
  uint64_t repeat = evm_2_double(e, v[1]);

  // Start timer.
  int res = uv_timer_start(timer_handle, timeout_handler, timeout, repeat);

  return evm_mk_number(e, res);
}


EVM_FUNCTION(timer_stop) {
  uv_handle_t *timer_handle = evm_object_get_user_data(e, p);
  // Stop timer.

  if (!uv_is_closing(timer_handle)) {
    iot_uv_handle_close(timer_handle, NULL);
  }

  return evm_mk_number(e, 0);
}


EVM_FUNCTION(timer_constructor) {
  const evm_val_t jtimer = evm_object_create(e);
  iot_timer_object_init(jtimer);
  evm_prop_set(e, jtimer, IOT_MAGIC_STRING_START, evm_mk_native(e, timer_start, IOT_MAGIC_STRING_START, 0));
  evm_prop_set(e, jtimer, IOT_MAGIC_STRING_STOP, evm_mk_native(e, timer_stop, IOT_MAGIC_STRING_STOP, 0));
  return jtimer;
}

void evm_module_timer(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, timer_constructor, IOT_MAGIC_STRING_CREATE, 0));
    evm_module_add(e, "timer", obj);
}
#endif
