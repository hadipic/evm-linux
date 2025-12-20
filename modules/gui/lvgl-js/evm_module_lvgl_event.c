#ifdef EVM_USE_MODULE_LVGL

#include "lvgl.h"
#include "evm_module.h"
#include <stdio.h>

typedef struct _event_info_t {
    evm_val_t obj;
    evm_val_t cb;
    evm_t *e;
    struct _event_info_t *next;
} _event_info_t;

// 🔥 لیست global برای track کردن تمام eventهای فعال
static _event_info_t *active_events = NULL;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    _event_info_t *info = lv_event_get_user_data(e);
    
    // 🔥 روش ساده‌تر: فقط بررسی اینکه info معتبر است
    if (info) {
        evm_val_t args[2];
        args[0] = info->obj;
        args[1] = evm_mk_number(info->e, code);
        evm_call_free(info->e, info->cb, EVM_UNDEFINED, 2, args);
    }
}
// 🔥 تابع برای اضافه کردن event به لیست
static void add_event_to_list(_event_info_t *event_info) {
    event_info->next = active_events;
    active_events = event_info;
}

// 🔥 تابع برای حذف event از لیست
static void remove_event_from_list(_event_info_t *event_info) {
    if (active_events == event_info) {
        active_events = event_info->next;
        return;
    }
    
    _event_info_t *prev = active_events;
    while (prev && prev->next != event_info) {
        prev = prev->next;
    }
    
    if (prev) {
        prev->next = event_info->next;
    }
}

// 🔥 تابع برای پیدا کردن event info مربوط به یک object
static _event_info_t *find_event_info(lv_obj_t *obj) {
    _event_info_t *current = active_events;
    while (current) {
        lv_obj_t *current_obj = evm_2_invoke(current->e, current->obj);
        if (current_obj == obj) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

EVM_FUNCTION(lvgl_event_lv_obj_add_event_cb) {
    EVM_EPCV;
    if( argc < 3 ) {
        printf("[LVGL_EVENT] Error: lv_obj_add_event_cb requires 3 arguments\n");
        return EVM_UNDEFINED;
    }
    
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    if (!obj) {
        printf("[LVGL_EVENT] Error: Invalid object\n");
        return EVM_UNDEFINED;
    }
    
    // 🔥 اول بررسی کن که قبلاً event برای این object ثبت نشده
    _event_info_t *existing_info = find_event_info(obj);
    if (existing_info) {
        printf("[LVGL_EVENT] Warning: Event already registered for this object, removing old one\n");
        lv_obj_remove_event_cb_with_user_data(obj, event_handler, existing_info);
        remove_event_from_list(existing_info);
        evm_val_free(existing_info->e, existing_info->obj);
        evm_val_free(existing_info->e, existing_info->cb);
        lv_mem_free(existing_info);
    }
    
    _event_info_t *info = lv_mem_alloc(sizeof(_event_info_t));
    if (!info) {
        printf("[LVGL_EVENT] Error: Memory allocation failed\n");
        return EVM_UNDEFINED;
    }
    
    info->obj = evm_val_duplicate(e, v[0]);
    info->e = e;
    info->cb = evm_val_duplicate(e, v[1]);
    info->next = NULL;
    
    lv_event_code_t event_code = (lv_event_code_t)evm_2_integer(e, v[2]);
    lv_obj_add_event_cb(obj, event_handler, event_code, info);
    
    // 🔥 اضافه کردن به لیست eventهای فعال
    add_event_to_list(info);
    
    printf("[LVGL_EVENT] Event registered successfully for event code: %d\n", event_code);
    return EVM_UNDEFINED;
}

EVM_FUNCTION(lvgl_event_lv_obj_remove_event_cb) {
    EVM_EPCV;
    if( argc < 1 ) {
        printf("[LVGL_EVENT] Error: lv_obj_remove_event_cb requires at least 1 argument\n");
        return EVM_UNDEFINED;
    }
    
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    if (!obj) {
        printf("[LVGL_EVENT] Error: Invalid object\n");
        return EVM_UNDEFINED;
    }
    
    // 🔥 پیدا کردن event info مربوط به این object
    _event_info_t *info = find_event_info(obj);
    if (info) {
        // حذف event callback
        lv_obj_remove_event_cb_with_user_data(obj, event_handler, info);
        
        // حذف از لیست
        remove_event_from_list(info);
        
        // آزاد کردن حافظه
        evm_val_free(info->e, info->obj);
        evm_val_free(info->e, info->cb);
        lv_mem_free(info);
        
        printf("[LVGL_EVENT] Event removed successfully\n");
    } else {
        printf("[LVGL_EVENT] Warning: No event found for this object\n");
    }
    
    return EVM_UNDEFINED;
}

// 🔥 تابع برای پاکسازی تمام eventهای یک object خاص
EVM_FUNCTION(lvgl_event_lv_obj_remove_all_event_cb) {
    EVM_EPCV;
    if( argc < 1 ) {
        return EVM_UNDEFINED;
    }
    
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    if (!obj) {
        return EVM_UNDEFINED;
    }
    
    // حذف تمام event callbacks با user data مربوطه
    _event_info_t *current = active_events;
    _event_info_t *prev = NULL;
    int count = 0;
    
    while (current) {
        lv_obj_t *current_obj = evm_2_invoke(current->e, current->obj);
        if (current_obj == obj) {
            // حذف از لیست
            if (prev) {
                prev->next = current->next;
            } else {
                active_events = current->next;
            }
            
            // حذف event callback
            lv_obj_remove_event_cb_with_user_data(obj, event_handler, current);
            
            // آزاد کردن حافظه
            evm_val_free(current->e, current->obj);
            evm_val_free(current->e, current->cb);
            lv_mem_free(current);
            
            count++;
            current = prev ? prev->next : active_events;
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    printf("[LVGL_EVENT] Removed %d events from object\n", count);
    return EVM_UNDEFINED;
}

// 🔥 تابع برای پاکسازی تمام eventهای فعال
void cleanup_all_events(void) {
    printf("[LVGL_EVENT] Cleaning up all active events...\n");
    
    _event_info_t *current = active_events;
    _event_info_t *next;
    int count = 0;
    
    while (current != NULL) {
        next = current->next;
        
        lv_obj_t *obj = evm_2_invoke(current->e, current->obj);
        if (obj && lv_obj_is_valid(obj)) {
            lv_obj_remove_event_cb_with_user_data(obj, event_handler, current);
        }
        
        evm_val_free(current->e, current->obj);
        evm_val_free(current->e, current->cb);
        lv_mem_free(current);
        
        count++;
        current = next;
    }
    
    active_events = NULL;
    printf("[LVGL_EVENT] Cleared %d active events\n", count);
}

EVM_FUNCTION(indev_get_x){
    EVM_EPCV;
    lv_point_t point;
    lv_indev_t *indev = lv_indev_get_act();
    if (indev) {
        lv_indev_get_point(indev, &point);
        EVM_RETURN(evm_mk_number(e, point.x));
    }
    EVM_RETURN(evm_mk_number(e, 0));
}

EVM_FUNCTION(indev_get_y){
    EVM_EPCV;
    lv_point_t point;
    lv_indev_t *indev = lv_indev_get_act();
    if (indev) {
        lv_indev_get_point(indev, &point);
        EVM_RETURN(evm_mk_number(e, point.y));
    }
    EVM_RETURN(evm_mk_number(e, 0));
}

EVM_FUNCTION(get_gesture_dir){
    EVM_EPCV;
    lv_indev_t *indev = lv_indev_get_act();
    if (indev) {
        int dir = lv_indev_get_gesture_dir(indev);
        EVM_RETURN(evm_mk_number(e, dir));
    }
    EVM_RETURN(evm_mk_number(e, 0));
}

// 🔥 تابع برای گرفتن اطلاعات eventهای فعال
EVM_FUNCTION(get_active_events_info) {
    EVM_EPCV;
    evm_val_t info = evm_object_create(e);
    int count = 0;
    
    _event_info_t *current = active_events;
    while (current) {
        count++;
        current = current->next;
    }
    
    evm_prop_set(e, info, "count", evm_mk_number(e, count));
    evm_prop_set(e, info, "max_events", evm_mk_number(e, 50)); // محدودیت اختیاری
    
    return info;
}

void evm_module_lvgl_event(evm_t *e) {
    evm_val_t obj = evm_module_get(e, "@native.lvgl");
    
    // توابع اصلی event
    evm_prop_set(e, obj, "lv_obj_add_event_cb", evm_mk_native(e, lvgl_event_lv_obj_add_event_cb, "lv_obj_add_event_cb", EVM_VARARGS));
    evm_prop_set(e, obj, "lv_obj_remove_event_cb", evm_mk_native(e, lvgl_event_lv_obj_remove_event_cb, "lv_obj_remove_event_cb", EVM_VARARGS));
    evm_prop_set(e, obj, "lv_obj_remove_all_event_cb", evm_mk_native(e, lvgl_event_lv_obj_remove_all_event_cb, "lv_obj_remove_all_event_cb", EVM_VARARGS));
    
    // توابع input device
    evm_prop_set(e, obj, "indev_get_x", evm_mk_native(e, indev_get_x, "indev_get_x", EVM_VARARGS));
    evm_prop_set(e, obj, "indev_get_y", evm_mk_native(e, indev_get_y, "indev_get_y", EVM_VARARGS));
    evm_prop_set(e, obj, "get_gesture_dir", evm_mk_native(e, get_gesture_dir, "get_gesture_dir", EVM_VARARGS));
    
    // 🔥 تابع برای مدیریت eventها
    evm_prop_set(e, obj, "get_active_events_info", evm_mk_native(e, get_active_events_info, "get_active_events_info", EVM_VARARGS));
    
    printf("[LVGL_EVENT] Event module initialized successfully\n");
}
#endif