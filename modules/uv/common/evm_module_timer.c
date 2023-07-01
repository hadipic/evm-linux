/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifdef EVM_USE_MODULE_TIMER

#include "iot_uv.h"

void iot_timer_object_init(evm_t *e, evm_val_t jtimer) {
    uv_handle_t* handle = iot_uv_handle_create(sizeof(uv_timer_t), jtimer, 0);
    uv_timer_init(system_get_uv_loop(), (uv_timer_t*)handle);
    evm_object_set_user_data(e, jtimer, handle);
}


static void timeout_handler(uv_timer_t* handle) {
    EVM_ASSERT(handle != NULL);

    evm_val_t jobject = IOT_UV_HANDLE_DATA(handle)->jobject;
    evm_val_t jcallback = evm_prop_get(evm_runtime(), jobject, IOT_MAGIC_STRING_HANDLETIMEOUT);
    evm_call_free(evm_runtime(), jcallback, EVM_UNDEFINED, 0, NULL);
    evm_val_free(evm_runtime(), jcallback);
}


EVM_FUNCTION(timer_start) {
    EVM_EPCV;
    // Check parameters.
    uv_timer_t *timer_handle = evm_object_get_user_data(e, v[0]);

    // parameters.
    uint64_t timeout = evm_2_double(e, v[1]);
    uint64_t repeat = evm_2_double(e, v[2]);

    // Start timer.
    int res = uv_timer_start(timer_handle, timeout_handler, timeout, timeout);

    EVM_RETURN(evm_mk_number(e, res));
}


EVM_FUNCTION(timer_stop) {
    EVM_EPCV;
    uv_handle_t *timer_handle = evm_object_get_user_data(e, v[0]);
    // Stop timer.

    if (!uv_is_closing(timer_handle)) {
        iot_uv_handle_close(timer_handle, NULL);
    }

    EVM_RETURN(evm_mk_number(e, 0));
}


EVM_FUNCTION(timer_constructor) {
    EVM_EPCV;
    const evm_val_t jtimer = evm_object_create(e);
    iot_timer_object_init(e, jtimer);
    EVM_RETURN(jtimer);
}

void evm_module_timer(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, IOT_MAGIC_STRING_CREATE, evm_mk_native(e, timer_constructor, IOT_MAGIC_STRING_CREATE, 0));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_START, evm_mk_native(e, timer_start, IOT_MAGIC_STRING_START, 2));
    evm_prop_set(e, obj, IOT_MAGIC_STRING_STOP, evm_mk_native(e, timer_stop, IOT_MAGIC_STRING_STOP, 0));

    evm_module_add(e, "@native.timer", obj);
}
#endif
