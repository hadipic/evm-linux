#ifdef EVM_USE_MODULE_LVGL

#include "evm_module.h"
#include "lvgl.h"
#include <stdio.h>

typedef struct timer_data_t {
    evm_t *e;
    evm_val_t cb;
    lv_timer_t *timer;
    struct timer_data_t *next;
} timer_data_t;

static timer_data_t *active_timers = NULL;

static void timer_callback(lv_timer_t *timer) {
    timer_data_t *data = (timer_data_t*)timer->user_data;
    if (!data || !data->e) return;

    // فقط اگر callback معتبر باشه اجرا کن
    if (evm_is_callable(data->e, data->cb)) {
        evm_call_free(data->e, data->cb, EVM_UNDEFINED, 0, NULL);
    }
}

// اضافه کردن به لیست
static void add_timer(timer_data_t *data) {
    data->next = active_timers;
    active_timers = data;
}

// حذف از لیست
static void remove_timer(timer_data_t *data) {
    if (!active_timers) return;
    if (active_timers == data) {
        active_timers = data->next;
        return;
    }
    timer_data_t *prev = active_timers;
    while (prev->next && prev->next != data) prev = prev->next;
    if (prev->next == data) prev->next = data->next;
}

// setTimeout
EVM_FUNCTION(setTimeout) {
    EVM_EPCV;
    if (argc < 2) return EVM_UNDEFINED;

    uint32_t ms = (uint32_t)evm_2_double(e, v[1]);
    timer_data_t *data = evm_malloc(sizeof(timer_data_t));
    if (!data) return EVM_UNDEFINED;

    lv_timer_t *timer = lv_timer_create(timer_callback, ms, data);
    lv_timer_set_repeat_count(timer, 1);

    data->e = e;
    data->cb = evm_val_duplicate(e, v[0]);
    data->timer = timer;
    data->next = NULL;

    add_timer(data);
    EVM_RETURN(evm_mk_invoke(e, data));
}

// setInterval
EVM_FUNCTION(setInterval) {
    EVM_EPCV;
    if (argc < 2) return EVM_UNDEFINED;

    uint32_t ms = (uint32_t)evm_2_double(e, v[1]);
    timer_data_t *data = evm_malloc(sizeof(timer_data_t));
    if (!data) return EVM_UNDEFINED;

    lv_timer_t *timer = lv_timer_create(timer_callback, ms, data);
    lv_timer_set_repeat_count(timer, -1);  // تکرار دائمی

    data->e = e;
    data->cb = evm_val_duplicate(e, v[0]);
    data->timer = timer;
    data->next = NULL;

    add_timer(data);
    EVM_RETURN(evm_mk_invoke(e, data));
}

// clearTimeout / clearInterval
EVM_FUNCTION(clearTimeout) {
    EVM_EPCV;
    if (argc == 0 || !evm_is_invoke(e, v[0])) return EVM_UNDEFINED;

    timer_data_t *data = evm_2_invoke(e, v[0]);
    if (!data || !data->timer) return EVM_UNDEFINED;

    // حذف تایمر از LVGL
    lv_timer_del(data->timer);

    // حذف از لیست
    remove_timer(data);

    // آزاد کردن حافظه
    evm_val_free(e, data->cb);
    evm_free(data);

    EVM_RETURN(EVM_UNDEFINED);
}

// پاکسازی تمام تایمرها در زمان خروج
void cleanup_all_timers(void) {
    printf("[LVGL_TIMEOUT] Cleaning up all timers...\n");
    while (active_timers) {
        timer_data_t *data = active_timers;
        active_timers = data->next;

        if (data->timer) lv_timer_del(data->timer);
        evm_val_free(data->e, data->cb);
        evm_free(data);
    }
    printf("[LVGL_TIMEOUT] All timers cleaned up\n");
}

void evm_module_lvgl_timeout(evm_t *e) {
    evm_global_set(e, "setTimeout", evm_mk_native(e, setTimeout, "setTimeout", EVM_VARARGS));
    evm_global_set(e, "setInterval", evm_mk_native(e, setInterval, "setInterval", EVM_VARARGS));
    evm_global_set(e, "clearTimeout", evm_mk_native(e, clearTimeout, "clearTimeout", EVM_VARARGS));
    evm_global_set(e, "clearInterval", evm_mk_native(e, clearTimeout, "clearInterval", EVM_VARARGS));
    printf("[LVGL_TIMEOUT] LVGL-based Timer module initialized (safe)\n");
}

#endif