#ifdef CONFIG_EVM_MODULE_LVGL

#include "evm_module.h"
#include "lvgl.h"

EVM_FUNCTION(destroy_obj) {
    EVM_EPCV;
    evm_val_t nativePtr = evm_prop_get(e, v[0], "nativePtr");
    evm_val_t stylePtr = evm_prop_get(e, v[0], "stylePtr");
    lv_obj_t *obj = evm_2_invoke(e, nativePtr);
    lv_style_t *style = evm_2_invoke(e, stylePtr);
    lv_obj_remove_style(obj, style, 0);
    lv_obj_del(obj);
    lv_mem_free(style);
    EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(get_screen_width) {
    EVM_EPCV;
    int width = lv_disp_get_hor_res(lv_disp_get_default());
    EVM_RETURN(evm_mk_number(e, width));
}

EVM_FUNCTION(get_screen_height) {
    EVM_EPCV;
    int width = lv_disp_get_ver_res(lv_disp_get_default());
    EVM_RETURN(evm_mk_number(e, width));
}

void evm_module_lvgl_misc(evm_t *e) {
    evm_val_t obj = evm_module_get(e, "@native.lvgl");
    evm_prop_set(e, obj, "destroy_obj", evm_mk_native(e, destroy_obj, "destroy_obj", EVM_VARARGS));
    evm_prop_set(e, obj, "get_screen_width", evm_mk_native(e, get_screen_width, "get_screen_width", EVM_VARARGS));
    evm_prop_set(e, obj, "get_screen_height", evm_mk_native(e, get_screen_height, "get_screen_height", EVM_VARARGS));
}
#endif
