#ifdef EVM_USE_MODULE_LVGL

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

EVM_FUNCTION(rgba_to_color){
    EVM_EPCV;
    lv_color_t color;
    double r = evm_2_double(e, v[0]);
    double g = evm_2_double(e, v[1]);
    double b = evm_2_double(e, v[2]);
    double a = evm_2_double(e, v[3]);
    color.ch.red = r * 255;
    color.ch.green = g * 255;
    color.ch.blue = b * 255;
#if LV_COLOR_DEPTH == 32
    color.ch.alpha = a * 255;
#endif
    EVM_RETURN(evm_mk_number(e, color.full));
}

EVM_FUNCTION(disp_set_rotation){
    EVM_EPCV;
    int i = evm_2_integer(e, v[0]);
    lv_disp_rot_t rotation = i % 4;
    lv_disp_set_rotation(lv_disp_get_default(), rotation);
    EVM_RETURN(EVM_UNDEFINED)
}

EVM_FUNCTION(wrap_lv_img_set_pivot){
    EVM_EPCV;
    if( !evm_is_invoke(e, v[0]))
        EVM_RETURN(EVM_UNDEFINED);
    if( !evm_is_list(e, v[1]) )
        EVM_RETURN(EVM_UNDEFINED);
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    evm_val_t x = evm_list_get(e, v[1], 0);
    evm_val_t y = evm_list_get(e, v[1], 1);
    lv_img_set_pivot(obj, (lv_coord_t)evm_2_integer(e, x), (lv_coord_t)evm_2_integer(e, y));
    EVM_RETURN(EVM_UNDEFINED)
}

EVM_FUNCTION(wrap_lv_obj_get_abs_x){
    EVM_EPCV;
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    EVM_RETURN(evm_mk_number(e, obj->coords.x1));
}

EVM_FUNCTION(wrap_lv_obj_get_abs_y){
    EVM_EPCV;
    lv_obj_t *obj = evm_2_invoke(e, v[0]);
    EVM_RETURN(evm_mk_number(e, obj->coords.y1));
}

EVM_FUNCTION(init_style){
    EVM_EPCV;
    lv_style_t *style = evm_2_invoke(e, v[0]);
    lv_style_init(style);

    lv_style_set_pad_all(style, 0);
    lv_style_set_radius(style, 0);
    lv_style_set_border_width(style, 0);
    lv_style_set_border_color(style,  lv_color_make(0, 0, 0));
    lv_style_set_border_opa(style,  LV_OPA_COVER);
    lv_style_set_outline_width(style, 0);

    lv_style_set_bg_opa(style, LV_OPA_TRANSP);
    lv_style_set_bg_color(style, lv_color_make(0x55, 0x96, 0xd8));
    lv_style_set_bg_grad_color(style, lv_color_make(0x55, 0x96, 0xd8));
    lv_style_set_img_opa(style, LV_OPA_COVER);

    lv_style_set_line_opa(style, LV_OPA_COVER);
    lv_style_set_line_color(style, lv_color_make(0xf0, 0xf0, 0xf0));
    lv_style_set_line_width(style, 2);

    lv_style_set_text_align(style, LV_TEXT_ALIGN_RIGHT);
    lv_style_set_text_line_space(style, 2);
    lv_style_set_text_letter_space(style, 2);
}

void evm_module_lvgl_misc(evm_t *e) {
    evm_val_t obj = evm_module_get(e, "@native.lvgl");
    evm_prop_set(e, obj, "init_style", evm_mk_native(e, init_style, "init_style", EVM_VARARGS));
    evm_prop_set(e, obj, "destroy_obj", evm_mk_native(e, destroy_obj, "destroy_obj", EVM_VARARGS));
    evm_prop_set(e, obj, "get_screen_width", evm_mk_native(e, get_screen_width, "get_screen_width", EVM_VARARGS));
    evm_prop_set(e, obj, "get_screen_height", evm_mk_native(e, get_screen_height, "get_screen_height", EVM_VARARGS));
    evm_prop_set(e, obj, "rgba_to_color", evm_mk_native(e, rgba_to_color, "rgba_to_color", EVM_VARARGS));
    evm_prop_set(e, obj, "disp_set_rotation", evm_mk_native(e, disp_set_rotation, "disp_set_rotation", EVM_VARARGS));
    evm_prop_set(e, obj, "lv_img_set_pivot", evm_mk_native(e, wrap_lv_img_set_pivot, "lv_img_set_pivot", EVM_VARARGS));
    evm_prop_set(e, obj, "lv_obj_get_abs_x", evm_mk_native(e, wrap_lv_obj_get_abs_x, "lv_obj_get_abs_x", EVM_VARARGS));
    evm_prop_set(e, obj, "lv_obj_get_abs_y", evm_mk_native(e, wrap_lv_obj_get_abs_y, "lv_obj_get_abs_y", EVM_VARARGS));
}
#endif
