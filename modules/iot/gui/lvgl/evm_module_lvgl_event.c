#ifdef CONFIG_EVM_MODULE_LVGL

#include "lvgl.h"
#include "evm_module.h"

typedef struct _event_info_t {
    evm_val_t obj;
    evm_t *e;
} _event_info_t;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    _event_info_t *info = lv_obj_get_user_data(lv_event_get_target(e));
    evm_val_t cbs = evm_prop_get(info->e, info->obj, ".callbacks");
    int len = evm_list_len(info->e, cbs);
    for (int i = 0; i < len; i++) {
        evm_val_t cb = evm_list_get(info->e, cbs, i);
        evm_val_t this = evm_mk_global(info->e);
        evm_val_t args[2];
        args[0] = evm_val_duplicate(e, info->obj);
        args[1] = evm_mk_number(info->e, code);
        evm_call_free(info->e, cb, this, 2, args);
        evm_val_free(info->e, args[0]);
        evm_val_free(info->e, args[1]);
        evm_val_free(info->e, this);
        evm_val_free(info->e, cb);
    }
    evm_val_free(info->e, cbs);
}

//lv_obj_add_event_cb(obj, function, code)
static evm_val_t evm_module_lvgl_event_lv_obj_add_event_cb(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    lv_obj_t *obj = evm_object_get_user_data(e, v[0]);
    _event_info_t *info = lv_obj_get_user_data(obj);
    if( info == NULL ) {
        info = lv_mem_alloc(sizeof (_event_info_t));
        EVM_ASSERT(info);
        info->obj = evm_val_duplicate(e, v[0]);
        info->e = e;
        lv_obj_set_user_data(obj, info);
        lv_obj_add_event_cb(obj, event_handler, evm_2_integer(e, v[2]), NULL);
    }
    evm_val_t cbs = evm_prop_get(e, v[0], ".callbacks");
    if( evm_is_undefined(e, cbs) ) {
        cbs = evm_list_create(e);
        evm_prop_set(e, v[0], ".callbacks", evm_val_duplicate(e, cbs));
    }
    evm_list_set(e, cbs, evm_list_len(e, cbs), evm_val_duplicate(e, v[1]));
    evm_val_free(e, cbs);
    return EVM_UNDEFINED;
}

void evm_module_lvgl_event(evm_t *e) {
    evm_val_t obj = evm_module_get(e, "lvgl");
    evm_prop_set(e, obj, "lv_obj_add_event_cb", evm_mk_native(e, evm_module_lvgl_event_lv_obj_add_event_cb, "lv_obj_add_event_cb", 0));
}
#endif
