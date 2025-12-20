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

// 🔥 لیست global برای track کردن تمام تایمرهای فعال
static timer_data_t *active_timers = NULL;

static void timer_callback(lv_timer_t *timer) {
    timer_data_t *timer_data = timer->user_data;
    if( timer_data ){
        evm_call_free(timer_data->e, timer_data->cb, EVM_UNDEFINED, 0, NULL);
    }
}

// 🔥 تابع برای اضافه کردن تایمر به لیست
static void add_timer_to_list(timer_data_t *timer_data) {
    timer_data->next = active_timers;
    active_timers = timer_data;
}

// 🔥 تابع برای حذف تایمر از لیست
static void remove_timer_from_list(timer_data_t *timer_data) {
    if (active_timers == timer_data) {
        active_timers = timer_data->next;
        return;
    }
    
    timer_data_t *prev = active_timers;
    while (prev && prev->next != timer_data) {
        prev = prev->next;
    }
    
    if (prev) {
        prev->next = timer_data->next;
    }
}

//setTimeout(callback, period)
EVM_FUNCTION(setTimeout) {
    EVM_EPCV;
    if( argc < 2 )
        return EVM_UNDEFINED;
    uint32_t period = (uint32_t)evm_2_double(e, v[1]);
    timer_data_t *timer_data = evm_malloc(sizeof (timer_data_t));
    EVM_ASSERT(timer_data);
    lv_timer_t *timer = lv_timer_create(timer_callback, period, timer_data);
    lv_timer_set_repeat_count(timer, 1);
    timer_data->e = e;
    timer_data->cb = evm_val_duplicate(e, v[0]);
    timer_data->timer = timer;
    timer_data->next = NULL;
    
    // 🔥 اضافه کردن به لیست تایمرهای فعال
    add_timer_to_list(timer_data);
    
    EVM_RETURN(evm_mk_invoke(e, timer_data));
}

//setInterval(callback, period)
EVM_FUNCTION(setInterval) {
    EVM_EPCV;
    if( argc < 2 )
        return EVM_UNDEFINED;
    uint32_t period = (uint32_t)evm_2_double(e, v[1]);
    timer_data_t *timer_data = evm_malloc(sizeof (timer_data_t));
    EVM_ASSERT(timer_data);
    lv_timer_t *timer = lv_timer_create(timer_callback, period, timer_data);
    lv_timer_set_repeat_count(timer, -1);
    timer_data->e = e;
    timer_data->cb = evm_val_duplicate(e, v[0]);
    timer_data->timer = timer;
    timer_data->next = NULL;
    
    // 🔥 اضافه کردن به لیست تایمرهای فعال
    add_timer_to_list(timer_data);
    
    EVM_RETURN(evm_mk_invoke(e, timer_data));
}

//clearTimeout(timer)
EVM_FUNCTION(clearTimeout) {
    EVM_EPCV;
    if( argc == 0 || !evm_is_invoke(e, v[0]) )
        return EVM_UNDEFINED;
    timer_data_t *timer_data = evm_2_invoke(e, v[0]);
    EVM_ASSERT(timer_data);
    
    // 🔥 حذف از لیست تایمرهای فعال
    remove_timer_from_list(timer_data);
    
    lv_timer_del(timer_data->timer);
    evm_val_free(e, timer_data->cb);
    evm_free(timer_data);
    
    // 🔥 حذف invoke از حافظه EVM
    evm_val_free(e, v[0]);
    
    EVM_RETURN(EVM_UNDEFINED);
}

// 🔥 تابع برای پاکسازی تمام تایمرهای فعال
void cleanup_all_timers(void) {
    printf("[LVGL_TIMEOUT] Cleaning up all active timers...\n");
    
    timer_data_t *current = active_timers;
    timer_data_t *next;
    int count = 0;
    
    while (current != NULL) {
        next = current->next;
        
        lv_timer_del(current->timer);
        evm_val_free(current->e, current->cb);
        evm_free(current);
        
        count++;
        current = next;
    }
    
    active_timers = NULL;
    printf("[LVGL_TIMEOUT] Cleared %d active timers\n", count);
}

// 🔥 تابع اصلی ماژول timeout
void evm_module_lvgl_timeout(evm_t *e) {
    evm_global_set(e, "setTimeout", evm_mk_native(e, setTimeout, "setTimeout", EVM_VARARGS));
    evm_global_set(e, "setInterval", evm_mk_native(e, setInterval, "setInterval", EVM_VARARGS));
    evm_global_set(e, "clearTimeout", evm_mk_native(e, clearTimeout, "clearTimeout", EVM_VARARGS));
    evm_global_set(e, "clearInterval", evm_mk_native(e, clearTimeout, "clearInterval", EVM_VARARGS));
    
    printf("[LVGL_TIMEOUT] Timeout module initialized successfully\n");
}
#endif