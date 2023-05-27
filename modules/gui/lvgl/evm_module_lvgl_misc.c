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
    lv_style_set_text_font(style, &lv_font_montserrat_20);
    EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(lvgl_style_get_font){
    EVM_EPCV;
    int font_size = evm_2_integer(e, v[0]);
    switch (font_size) {
#if LV_FONT_MONTSERRAT_8
    case 8: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_8));
#endif
#if LV_FONT_MONTSERRAT_10
    case 10: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_10));
#endif
#if LV_FONT_MONTSERRAT_12
    case 12: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_12));
#endif
#if LV_FONT_MONTSERRAT_14
    case 14: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_14));
#endif
#if LV_FONT_MONTSERRAT_16
    case 16: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_16));
#endif
#if LV_FONT_MONTSERRAT_18
    case 18: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_18));
#endif
#if LV_FONT_MONTSERRAT_20
    case 20: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_20));
#endif
#if LV_FONT_MONTSERRAT_22
    case 22: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_22));
#endif
#if LV_FONT_MONTSERRAT_24
    case 24: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_24));
#endif
#if LV_FONT_MONTSERRAT_26
    case 26: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_26));
#endif
#if LV_FONT_MONTSERRAT_28
    case 28: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_28));
#endif
#if LV_FONT_MONTSERRAT_30
    case 30: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_30));
#endif
#if LV_FONT_MONTSERRAT_32
    case 32: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_32));
#endif
#if LV_FONT_MONTSERRAT_34
    case 34: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_34));
#endif
#if LV_FONT_MONTSERRAT_36
    case 36: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_36));
#endif
#if LV_FONT_MONTSERRAT_38
    case 38: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_38));
#endif
#if LV_FONT_MONTSERRAT_40
    case 40: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_40));
#endif
#if LV_FONT_MONTSERRAT_42
    case 42: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_42));
#endif
#if LV_FONT_MONTSERRAT_44
    case 44: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_44));
#endif
#if LV_FONT_MONTSERRAT_46
    case 46: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_46));
#endif
#if LV_FONT_MONTSERRAT_48
    case 48: EVM_RETURN_VAL(evm_mk_invoke(e, &lv_font_montserrat_48));
#endif
    }
    return evm_mk_invoke(e, &lv_font_montserrat_20);
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
    evm_prop_set(e, obj, "lvgl_style_get_font", evm_mk_native(e, lvgl_style_get_font, "lvgl_style_get_font", EVM_VARARGS));
}
#endif
