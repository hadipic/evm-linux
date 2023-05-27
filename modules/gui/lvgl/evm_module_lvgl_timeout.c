#ifdef EVM_USE_MODULE_LVGL

#include "evm_module.h"
#include "lvgl.h"

typedef struct timer_data_t {
    evm_t *e;
    evm_val_t cb;
    lv_timer_t *timer;
} timer_data_t;

static void timer_callback(lv_timer_t *timer) {
    timer_data_t *timer_data = timer->user_data;
    if( timer_data ){
        evm_call_free(timer_data->e, timer_data->cb, EVM_UNDEFINED, 0, NULL);
    }
}

//setTimeout(period, callback)
EVM_FUNCTION(setTimeout) {
    EVM_EPCV;
    if( argc < 2 )
        return EVM_UNDEFINED;
    uint32_t period = (uint32_t)evm_2_double(e, v[0]);
    timer_data_t *timer_data = evm_malloc(sizeof (timer_data_t));
    EVM_ASSERT(timer_data);
    lv_timer_t *timer = lv_timer_create(timer_callback, period, timer_data);
    lv_timer_set_repeat_count(timer, 1);
    timer_data->e = e;
    timer_data->cb = evm_val_duplicate(e, v[1]);
    timer_data->timer = timer;
    EVM_RETURN(evm_mk_invoke(e, timer_data));
}

//setInterval(period, callback)
EVM_FUNCTION(setInterval) {
    EVM_EPCV;
    if( argc < 2 )
        return EVM_UNDEFINED;
    uint32_t period = (uint32_t)evm_2_double(e, v[0]);
    timer_data_t *timer_data = evm_malloc(sizeof (timer_data_t));
    EVM_ASSERT(timer_data);
    lv_timer_t *timer = lv_timer_create(timer_callback, period, timer_data);
    lv_timer_set_repeat_count(timer, -1);
    timer_data->e = e;
    timer_data->cb = evm_val_duplicate(e, v[1]);
    timer_data->timer = timer;
    EVM_RETURN(evm_mk_invoke(e, timer_data));
}

//clearTimeout(timer)
EVM_FUNCTION(clearTimeout) {
    EVM_EPCV;
    if( argc == 0 || !evm_is_invoke(e, v[0]) )
        return EVM_UNDEFINED;
    timer_data_t *timer_data = evm_2_invoke(e, v[0]);
    EVM_ASSERT(timer_data);
    lv_timer_del(timer_data->timer);
    evm_val_free(e, timer_data->cb);
    evm_free(timer_data);
    EVM_RETURN(EVM_UNDEFINED);
}

void evm_module_lvgl_timeout(evm_t *e) {
    evm_global_set(e, "setTimeout", evm_mk_native(e, setTimeout, "setTimeout", EVM_VARARGS));
    evm_global_set(e, "setInterval", evm_mk_native(e, setInterval, "setInterval", EVM_VARARGS));
    evm_global_set(e, "clearTimeout", evm_mk_native(e, clearTimeout, "clearTimeout", EVM_VARARGS));
    evm_global_set(e, "clearInterval", evm_mk_native(e, clearTimeout, "clearInterval", EVM_VARARGS));
}
#endif
