#ifdef EVM_USE_MODULE_LVGL

#include "lvgl.h"
#include "evm_module.h"

typedef struct _event_info_t {
    evm_val_t obj;
    evm_val_t cb;
    evm_t *e;
} _event_info_t;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    _event_info_t *info = lv_event_get_user_data(e);
    evm_val_t cb = info->cb;
    evm_val_t args[2];
    args[0] = info->obj;
    args[1] = evm_mk_number(info->e, code);
    evm_call_free(info->e, cb, EVM_UNDEFINED, 2, args);
    evm_val_free(info->e, args[1]);
}

//lv_obj_add_event_cb(obj, function, code)
EVM_FUNCTION(lvgl_event_lv_obj_add_event_cb) {
    EVM_EPCV;
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    _event_info_t *info = lv_obj_get_user_data(obj);
    info = lv_mem_alloc(sizeof (_event_info_t));
    EVM_ASSERT(info);
    info->obj = evm_val_duplicate(e, v[0]);
    info->e = e;
    info->cb = evm_val_duplicate(e, v[1]);
    lv_obj_set_user_data(obj, info);
    lv_obj_add_event_cb(obj, event_handler, evm_2_integer(e, v[2]), info);
    return EVM_UNDEFINED;
}

EVM_FUNCTION(lvgl_event_lv_obj_remove_event_cb) {

}

EVM_FUNCTION(indev_get_x){
    EVM_EPCV;
    lv_point_t point;
    lv_indev_t *indev = lv_indev_get_act();
    lv_indev_get_point(indev, &point);
    EVM_RETURN( evm_mk_number(e, point.x));
}

EVM_FUNCTION(indev_get_y){
    EVM_EPCV;
    lv_point_t point;
    lv_indev_t *indev = lv_indev_get_act();
    lv_indev_get_point(indev, &point);
    EVM_RETURN( evm_mk_number(e, point.y));
}

EVM_FUNCTION(get_gesture_dir){
    EVM_EPCV;
    int dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    EVM_RETURN( evm_mk_number(e, dir));
}

void evm_module_lvgl_event(evm_t *e) {
    evm_val_t obj = evm_module_get(e, "@native.lvgl");
    evm_prop_set(e, obj, "lv_obj_add_event_cb", evm_mk_native(e, lvgl_event_lv_obj_add_event_cb, "lv_obj_add_event_cb", EVM_VARARGS));
    evm_prop_set(e, obj, "lv_obj_remove_event_cb", evm_mk_native(e, lvgl_event_lv_obj_remove_event_cb, "lv_obj_remove_event_cb", EVM_VARARGS));
    evm_prop_set(e, obj, "indev_get_x", evm_mk_native(e, indev_get_x, "indev_get_x", EVM_VARARGS));
    evm_prop_set(e, obj, "indev_get_y", evm_mk_native(e, indev_get_y, "indev_get_y", EVM_VARARGS));
    evm_prop_set(e, obj, "get_gesture_dir", evm_mk_native(e, get_gesture_dir, "get_gesture_dir", EVM_VARARGS));
}
#endif
