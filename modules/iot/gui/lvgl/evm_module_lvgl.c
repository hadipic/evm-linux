//This is auto-generated file
#ifdef CONFIG_EVM_MODULE_LVGL

#include "lvgl.h"
#include "evm_module.h"

static evm_val_t evm_module_lvgl_lv_scr_act(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[1];
  evm_cffi_exec_param(e, cffi_args + 1, "", argc, v);
  cffi_args[0].p = lv_scr_act();
  return evm_cffi_exec_ret(e, cffi_args[0], "p");
}

static evm_val_t evm_module_lvgl_lv_color_hex(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "i", argc, v);
  return evm_mk_number(e, lv_color_hex(cffi_args[1].i32).full);
  return evm_cffi_exec_ret(e, cffi_args[0], "ii");
}

static evm_val_t evm_module_lvgl_lv_style_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[1];
  evm_cffi_exec_param(e, cffi_args + 1, "", argc, v);
  cffi_args[0].p = lv_mem_alloc(sizeof(lv_style_t));
  return evm_cffi_exec_ret(e, cffi_args[0], "p");
}

static evm_val_t evm_module_lvgl_lv_palette_main(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "i", argc, v);
  return evm_mk_number(e, lv_palette_main(cffi_args[1].i32).full);
  return evm_cffi_exec_ret(e, cffi_args[0], "ii");
}

static evm_val_t evm_module_lvgl_lv_style_init(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_style_init(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_min_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_min_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_max_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_max_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_height(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_min_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_min_height(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_max_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_max_height(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_x(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_y(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_align(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_transform_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_transform_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_transform_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_transform_height(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_translate_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_translate_x(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_translate_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_translate_y(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_transform_zoom(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_transform_zoom(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_transform_pivot_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_transform_pivot_x(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_transform_pivot_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_transform_pivot_y(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_pad_top(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_pad_top(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_pad_bottom(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_pad_bottom(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_pad_left(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_pad_left(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_pad_right(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_pad_right(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_pad_row(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_pad_row(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_pad_column(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_pad_column(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_bg_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_bg_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_grad_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_bg_grad_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_grad_dir(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_bg_grad_dir(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_main_stop(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_bg_main_stop(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_grad_stop(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_bg_grad_stop(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_bg_dither_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_bg_dither_mode(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_border_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_border_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_border_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_border_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_border_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_border_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_border_side(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_border_side(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_border_post(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pb", argc, v);
  lv_style_set_border_post(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_outline_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_outline_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_outline_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_outline_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_outline_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_outline_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_outline_pad(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_outline_pad(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_shadow_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_shadow_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_shadow_ofs_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_shadow_ofs_x(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_shadow_ofs_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_shadow_ofs_y(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_shadow_spread(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_shadow_spread(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_shadow_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_shadow_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_shadow_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_shadow_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_line_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_line_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_line_dash_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_line_dash_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_line_dash_gap(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_line_dash_gap(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_line_rounded(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pb", argc, v);
  lv_style_set_line_rounded(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_line_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_line_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_line_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_line_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_arc_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_arc_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_arc_rounded(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pb", argc, v);
  lv_style_set_arc_rounded(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_arc_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_arc_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_arc_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_arc_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_color(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_color_t color;
  color.full = cffi_args[2].i32;
  lv_style_set_text_color(cffi_args[1].p, color);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_opa(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_text_opa(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_font(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_text_font(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_letter_space(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_text_letter_space(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_line_space(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_text_line_space(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_decor(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_text_decor(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_text_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_text_align(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_style_set_radius(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_style_set_radius(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_obj_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_obj_add_style(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "ppi", argc, v);
  lv_obj_add_style(cffi_args[1].p, cffi_args[2].p, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_add_flag(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_add_flag(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_clear_flag(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_clear_flag(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_add_state(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_add_state(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_clear_state(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_clear_state(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_has_flag(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  cffi_args[0].i32 = lv_obj_has_flag(cffi_args[1].p, cffi_args[2].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "bpi");
}

static evm_val_t evm_module_lvgl_lv_obj_has_flag_any(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  cffi_args[0].i32 = lv_obj_has_flag_any(cffi_args[1].p, cffi_args[2].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "bpi");
}

static evm_val_t evm_module_lvgl_lv_obj_get_state(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_state(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_has_state(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  cffi_args[0].i32 = lv_obj_has_state(cffi_args[1].p, cffi_args[2].i32);
  return evm_cffi_exec_ret(e, cffi_args[0], "bpi");
}

static evm_val_t evm_module_lvgl_lv_obj_set_pos(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_obj_set_pos(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_x(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_y(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_size(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_obj_set_size(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_refr_size(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_refr_size(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "bp");
}

static evm_val_t evm_module_lvgl_lv_obj_set_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_height(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_content_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_content_width(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_content_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_content_height(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_layout(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_layout(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_is_layout_positioned(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_is_layout_positioned(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "bp");
}

static evm_val_t evm_module_lvgl_lv_obj_mark_layout_as_dirty(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_mark_layout_as_dirty(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_update_layout(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_update_layout(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_align(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "piii", argc, v);
  lv_obj_align(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32, cffi_args[4].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_align_to(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[6];
  evm_cffi_exec_param(e, cffi_args + 1, "ppiii", argc, v);
  lv_obj_align_to(cffi_args[1].p, cffi_args[2].p, cffi_args[3].i32, cffi_args[4].i32, cffi_args[5].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_center(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_center(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_get_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_x(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_x2(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_x2(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_y(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_y2(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_y2(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_width(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_height(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_content_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_content_width(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_content_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_content_height(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_self_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_self_width(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_get_self_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_get_self_height(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_obj_refresh_self_size(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_refresh_self_size(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "bp");
}

static evm_val_t evm_module_lvgl_lv_obj_refr_pos(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_refr_pos(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_move_to(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_obj_move_to(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_move_children_by(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "piib", argc, v);
  lv_obj_move_children_by(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32, cffi_args[4].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_transform_point(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "ppbb", argc, v);
  lv_obj_transform_point(cffi_args[1].p, cffi_args[2].p, cffi_args[3].i32, cffi_args[4].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_invalidate(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_invalidate(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_is_visible(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_obj_is_visible(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "bp");
}

static evm_val_t evm_module_lvgl_lv_obj_set_flex_flow(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_flex_flow(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_flex_grow(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_flex_grow(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_flex_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "piii", argc, v);
  lv_obj_set_flex_align(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32, cffi_args[4].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_arc_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_arc_set_start_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_start_angle(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_end_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_end_angle(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_angles(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_arc_set_angles(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_bg_start_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_bg_start_angle(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_bg_end_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_bg_end_angle(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_bg_angles(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_arc_set_bg_angles(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_rotation(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_rotation(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_mode(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_value(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_range(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_arc_set_range(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_change_rate(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_change_rate(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_get_angle_start(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_angle_start(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_angle_end(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_angle_end(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_bg_angle_start(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_bg_angle_start(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_bg_angle_end(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_bg_angle_end(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_min_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_min_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_max_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_max_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_arc_get_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_arc_get_mode(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_bar_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_bar_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_bar_set_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_bar_set_value(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_set_start_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_bar_set_start_value(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_set_range(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_bar_set_range(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_set_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_bar_set_mode(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_get_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_bar_get_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_bar_get_start_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_bar_get_start_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_bar_get_min_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_bar_get_min_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_bar_get_max_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_bar_get_max_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_bar_get_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_bar_get_mode(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_btn_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_btn_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_checkbox_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_checkbox_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_checkbox_set_text(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_checkbox_set_text(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_checkbox_set_text_static(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_checkbox_set_text_static(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_checkbox_get_text(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].s = lv_checkbox_get_text(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "sp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_dropdown_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_text(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_text(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_options(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_options(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_options_static(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_options_static(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_add_option(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "psi", argc, v);
  lv_dropdown_add_option(cffi_args[1].p, cffi_args[2].s, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_clear_options(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_dropdown_clear_options(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_selected(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_dropdown_set_selected(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_dir(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_dropdown_set_dir(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_symbol(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_symbol(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_selected_highlight(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pb", argc, v);
  lv_dropdown_set_selected_highlight(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_list(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_dropdown_get_list(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_text(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].s = lv_dropdown_get_text(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "sp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_options(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].s = lv_dropdown_get_options(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "sp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_selected(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_dropdown_get_selected(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_option_cnt(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_dropdown_get_option_cnt(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_option_index(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  cffi_args[0].i32 = lv_dropdown_get_option_index(cffi_args[1].p, cffi_args[2].s);
  return evm_cffi_exec_ret(e, cffi_args[0], "ips");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_symbol(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].s = lv_dropdown_get_symbol(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "sp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_selected_highlight(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_dropdown_get_selected_highlight(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "bp");
}

static evm_val_t evm_module_lvgl_lv_dropdown_get_dir(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_dropdown_get_dir(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_dropdown_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_dropdown_open(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_dropdown_close(cffi_args[1].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_is_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_dropdown_is_open(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "bp");
}

static evm_val_t evm_module_lvgl_lv_label_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_label_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_label_set_text(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_label_set_text(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_label_set_text_static(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_label_set_text_static(cffi_args[1].p, cffi_args[2].s);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_label_set_long_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_label_set_long_mode(cffi_args[1].p, cffi_args[2].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_label_get_text(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].s = lv_label_get_text(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "sp");
}

static evm_val_t evm_module_lvgl_lv_img_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_img_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_img_set_src(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pp", argc, v);
  lv_img_set_src(cffi_args[1].p, cffi_args[2].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_slider_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_slider_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_slider_set_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_slider_set_value(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_slider_set_range(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_slider_set_range(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_slider_get_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_slider_get_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_slider_get_min_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_slider_get_min_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}

static evm_val_t evm_module_lvgl_lv_slider_get_max_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].i32 = lv_slider_get_max_value(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "ip");
}


void evm_module_lvgl(evm_t *e) {
  evm_val_t obj = evm_object_create(e);
  evm_prop_set(e, obj, "lv_scr_act", evm_mk_native(e, evm_module_lvgl_lv_scr_act, "lv_scr_act", 0));
  evm_prop_set(e, obj, "lv_color_hex", evm_mk_native(e, evm_module_lvgl_lv_color_hex, "lv_color_hex", 1));
  evm_prop_set(e, obj, "lv_style_create", evm_mk_native(e, evm_module_lvgl_lv_style_create, "lv_style_create", 0));
  evm_prop_set(e, obj, "lv_palette_main", evm_mk_native(e, evm_module_lvgl_lv_palette_main, "lv_palette_main", 1));
  evm_prop_set(e, obj, "lv_style_init", evm_mk_native(e, evm_module_lvgl_lv_style_init, "lv_style_init", 1));
  evm_prop_set(e, obj, "lv_style_set_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_width, "lv_style_set_width", 2));
  evm_prop_set(e, obj, "lv_style_set_min_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_min_width, "lv_style_set_min_width", 2));
  evm_prop_set(e, obj, "lv_style_set_max_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_max_width, "lv_style_set_max_width", 2));
  evm_prop_set(e, obj, "lv_style_set_height", evm_mk_native(e, evm_module_lvgl_lv_style_set_height, "lv_style_set_height", 2));
  evm_prop_set(e, obj, "lv_style_set_min_height", evm_mk_native(e, evm_module_lvgl_lv_style_set_min_height, "lv_style_set_min_height", 2));
  evm_prop_set(e, obj, "lv_style_set_max_height", evm_mk_native(e, evm_module_lvgl_lv_style_set_max_height, "lv_style_set_max_height", 2));
  evm_prop_set(e, obj, "lv_style_set_x", evm_mk_native(e, evm_module_lvgl_lv_style_set_x, "lv_style_set_x", 2));
  evm_prop_set(e, obj, "lv_style_set_y", evm_mk_native(e, evm_module_lvgl_lv_style_set_y, "lv_style_set_y", 2));
  evm_prop_set(e, obj, "lv_style_set_align", evm_mk_native(e, evm_module_lvgl_lv_style_set_align, "lv_style_set_align", 2));
  evm_prop_set(e, obj, "lv_style_set_transform_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_transform_width, "lv_style_set_transform_width", 2));
  evm_prop_set(e, obj, "lv_style_set_transform_height", evm_mk_native(e, evm_module_lvgl_lv_style_set_transform_height, "lv_style_set_transform_height", 2));
  evm_prop_set(e, obj, "lv_style_set_translate_x", evm_mk_native(e, evm_module_lvgl_lv_style_set_translate_x, "lv_style_set_translate_x", 2));
  evm_prop_set(e, obj, "lv_style_set_translate_y", evm_mk_native(e, evm_module_lvgl_lv_style_set_translate_y, "lv_style_set_translate_y", 2));
  evm_prop_set(e, obj, "lv_style_set_transform_zoom", evm_mk_native(e, evm_module_lvgl_lv_style_set_transform_zoom, "lv_style_set_transform_zoom", 2));
  evm_prop_set(e, obj, "lv_style_set_transform_pivot_x", evm_mk_native(e, evm_module_lvgl_lv_style_set_transform_pivot_x, "lv_style_set_transform_pivot_x", 2));
  evm_prop_set(e, obj, "lv_style_set_transform_pivot_y", evm_mk_native(e, evm_module_lvgl_lv_style_set_transform_pivot_y, "lv_style_set_transform_pivot_y", 2));
  evm_prop_set(e, obj, "lv_style_set_pad_top", evm_mk_native(e, evm_module_lvgl_lv_style_set_pad_top, "lv_style_set_pad_top", 2));
  evm_prop_set(e, obj, "lv_style_set_pad_bottom", evm_mk_native(e, evm_module_lvgl_lv_style_set_pad_bottom, "lv_style_set_pad_bottom", 2));
  evm_prop_set(e, obj, "lv_style_set_pad_left", evm_mk_native(e, evm_module_lvgl_lv_style_set_pad_left, "lv_style_set_pad_left", 2));
  evm_prop_set(e, obj, "lv_style_set_pad_right", evm_mk_native(e, evm_module_lvgl_lv_style_set_pad_right, "lv_style_set_pad_right", 2));
  evm_prop_set(e, obj, "lv_style_set_pad_row", evm_mk_native(e, evm_module_lvgl_lv_style_set_pad_row, "lv_style_set_pad_row", 2));
  evm_prop_set(e, obj, "lv_style_set_pad_column", evm_mk_native(e, evm_module_lvgl_lv_style_set_pad_column, "lv_style_set_pad_column", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_color, "lv_style_set_bg_color", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_opa, "lv_style_set_bg_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_grad_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_grad_color, "lv_style_set_bg_grad_color", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_grad_dir", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_grad_dir, "lv_style_set_bg_grad_dir", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_main_stop", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_main_stop, "lv_style_set_bg_main_stop", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_grad_stop", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_grad_stop, "lv_style_set_bg_grad_stop", 2));
  evm_prop_set(e, obj, "lv_style_set_bg_dither_mode", evm_mk_native(e, evm_module_lvgl_lv_style_set_bg_dither_mode, "lv_style_set_bg_dither_mode", 2));
  evm_prop_set(e, obj, "lv_style_set_border_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_border_color, "lv_style_set_border_color", 2));
  evm_prop_set(e, obj, "lv_style_set_border_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_border_opa, "lv_style_set_border_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_border_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_border_width, "lv_style_set_border_width", 2));
  evm_prop_set(e, obj, "lv_style_set_border_side", evm_mk_native(e, evm_module_lvgl_lv_style_set_border_side, "lv_style_set_border_side", 2));
  evm_prop_set(e, obj, "lv_style_set_border_post", evm_mk_native(e, evm_module_lvgl_lv_style_set_border_post, "lv_style_set_border_post", 2));
  evm_prop_set(e, obj, "lv_style_set_outline_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_outline_width, "lv_style_set_outline_width", 2));
  evm_prop_set(e, obj, "lv_style_set_outline_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_outline_color, "lv_style_set_outline_color", 2));
  evm_prop_set(e, obj, "lv_style_set_outline_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_outline_opa, "lv_style_set_outline_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_outline_pad", evm_mk_native(e, evm_module_lvgl_lv_style_set_outline_pad, "lv_style_set_outline_pad", 2));
  evm_prop_set(e, obj, "lv_style_set_shadow_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_shadow_width, "lv_style_set_shadow_width", 2));
  evm_prop_set(e, obj, "lv_style_set_shadow_ofs_x", evm_mk_native(e, evm_module_lvgl_lv_style_set_shadow_ofs_x, "lv_style_set_shadow_ofs_x", 2));
  evm_prop_set(e, obj, "lv_style_set_shadow_ofs_y", evm_mk_native(e, evm_module_lvgl_lv_style_set_shadow_ofs_y, "lv_style_set_shadow_ofs_y", 2));
  evm_prop_set(e, obj, "lv_style_set_shadow_spread", evm_mk_native(e, evm_module_lvgl_lv_style_set_shadow_spread, "lv_style_set_shadow_spread", 2));
  evm_prop_set(e, obj, "lv_style_set_shadow_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_shadow_color, "lv_style_set_shadow_color", 2));
  evm_prop_set(e, obj, "lv_style_set_shadow_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_shadow_opa, "lv_style_set_shadow_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_line_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_line_width, "lv_style_set_line_width", 2));
  evm_prop_set(e, obj, "lv_style_set_line_dash_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_line_dash_width, "lv_style_set_line_dash_width", 2));
  evm_prop_set(e, obj, "lv_style_set_line_dash_gap", evm_mk_native(e, evm_module_lvgl_lv_style_set_line_dash_gap, "lv_style_set_line_dash_gap", 2));
  evm_prop_set(e, obj, "lv_style_set_line_rounded", evm_mk_native(e, evm_module_lvgl_lv_style_set_line_rounded, "lv_style_set_line_rounded", 2));
  evm_prop_set(e, obj, "lv_style_set_line_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_line_color, "lv_style_set_line_color", 2));
  evm_prop_set(e, obj, "lv_style_set_line_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_line_opa, "lv_style_set_line_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_arc_width", evm_mk_native(e, evm_module_lvgl_lv_style_set_arc_width, "lv_style_set_arc_width", 2));
  evm_prop_set(e, obj, "lv_style_set_arc_rounded", evm_mk_native(e, evm_module_lvgl_lv_style_set_arc_rounded, "lv_style_set_arc_rounded", 2));
  evm_prop_set(e, obj, "lv_style_set_arc_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_arc_color, "lv_style_set_arc_color", 2));
  evm_prop_set(e, obj, "lv_style_set_arc_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_arc_opa, "lv_style_set_arc_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_text_color", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_color, "lv_style_set_text_color", 2));
  evm_prop_set(e, obj, "lv_style_set_text_opa", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_opa, "lv_style_set_text_opa", 2));
  evm_prop_set(e, obj, "lv_style_set_text_font", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_font, "lv_style_set_text_font", 2));
  evm_prop_set(e, obj, "lv_style_set_text_letter_space", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_letter_space, "lv_style_set_text_letter_space", 2));
  evm_prop_set(e, obj, "lv_style_set_text_line_space", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_line_space, "lv_style_set_text_line_space", 2));
  evm_prop_set(e, obj, "lv_style_set_text_decor", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_decor, "lv_style_set_text_decor", 2));
  evm_prop_set(e, obj, "lv_style_set_text_align", evm_mk_native(e, evm_module_lvgl_lv_style_set_text_align, "lv_style_set_text_align", 2));
  evm_prop_set(e, obj, "lv_style_set_radius", evm_mk_native(e, evm_module_lvgl_lv_style_set_radius, "lv_style_set_radius", 2));
  evm_prop_set(e, obj, "lv_obj_create", evm_mk_native(e, evm_module_lvgl_lv_obj_create, "lv_obj_create", 1));
  evm_prop_set(e, obj, "lv_obj_add_style", evm_mk_native(e, evm_module_lvgl_lv_obj_add_style, "lv_obj_add_style", 3));
  evm_prop_set(e, obj, "lv_obj_add_flag", evm_mk_native(e, evm_module_lvgl_lv_obj_add_flag, "lv_obj_add_flag", 2));
  evm_prop_set(e, obj, "lv_obj_clear_flag", evm_mk_native(e, evm_module_lvgl_lv_obj_clear_flag, "lv_obj_clear_flag", 2));
  evm_prop_set(e, obj, "lv_obj_add_state", evm_mk_native(e, evm_module_lvgl_lv_obj_add_state, "lv_obj_add_state", 2));
  evm_prop_set(e, obj, "lv_obj_clear_state", evm_mk_native(e, evm_module_lvgl_lv_obj_clear_state, "lv_obj_clear_state", 2));
  evm_prop_set(e, obj, "lv_obj_has_flag", evm_mk_native(e, evm_module_lvgl_lv_obj_has_flag, "lv_obj_has_flag", 2));
  evm_prop_set(e, obj, "lv_obj_has_flag_any", evm_mk_native(e, evm_module_lvgl_lv_obj_has_flag_any, "lv_obj_has_flag_any", 2));
  evm_prop_set(e, obj, "lv_obj_get_state", evm_mk_native(e, evm_module_lvgl_lv_obj_get_state, "lv_obj_get_state", 1));
  evm_prop_set(e, obj, "lv_obj_has_state", evm_mk_native(e, evm_module_lvgl_lv_obj_has_state, "lv_obj_has_state", 2));
  evm_prop_set(e, obj, "lv_obj_set_pos", evm_mk_native(e, evm_module_lvgl_lv_obj_set_pos, "lv_obj_set_pos", 3));
  evm_prop_set(e, obj, "lv_obj_set_x", evm_mk_native(e, evm_module_lvgl_lv_obj_set_x, "lv_obj_set_x", 2));
  evm_prop_set(e, obj, "lv_obj_set_y", evm_mk_native(e, evm_module_lvgl_lv_obj_set_y, "lv_obj_set_y", 2));
  evm_prop_set(e, obj, "lv_obj_set_size", evm_mk_native(e, evm_module_lvgl_lv_obj_set_size, "lv_obj_set_size", 3));
  evm_prop_set(e, obj, "lv_obj_refr_size", evm_mk_native(e, evm_module_lvgl_lv_obj_refr_size, "lv_obj_refr_size", 1));
  evm_prop_set(e, obj, "lv_obj_set_width", evm_mk_native(e, evm_module_lvgl_lv_obj_set_width, "lv_obj_set_width", 2));
  evm_prop_set(e, obj, "lv_obj_set_height", evm_mk_native(e, evm_module_lvgl_lv_obj_set_height, "lv_obj_set_height", 2));
  evm_prop_set(e, obj, "lv_obj_set_content_width", evm_mk_native(e, evm_module_lvgl_lv_obj_set_content_width, "lv_obj_set_content_width", 2));
  evm_prop_set(e, obj, "lv_obj_set_content_height", evm_mk_native(e, evm_module_lvgl_lv_obj_set_content_height, "lv_obj_set_content_height", 2));
  evm_prop_set(e, obj, "lv_obj_set_layout", evm_mk_native(e, evm_module_lvgl_lv_obj_set_layout, "lv_obj_set_layout", 2));
  evm_prop_set(e, obj, "lv_obj_is_layout_positioned", evm_mk_native(e, evm_module_lvgl_lv_obj_is_layout_positioned, "lv_obj_is_layout_positioned", 1));
  evm_prop_set(e, obj, "lv_obj_mark_layout_as_dirty", evm_mk_native(e, evm_module_lvgl_lv_obj_mark_layout_as_dirty, "lv_obj_mark_layout_as_dirty", 1));
  evm_prop_set(e, obj, "lv_obj_update_layout", evm_mk_native(e, evm_module_lvgl_lv_obj_update_layout, "lv_obj_update_layout", 1));
  evm_prop_set(e, obj, "lv_obj_set_align", evm_mk_native(e, evm_module_lvgl_lv_obj_set_align, "lv_obj_set_align", 2));
  evm_prop_set(e, obj, "lv_obj_align", evm_mk_native(e, evm_module_lvgl_lv_obj_align, "lv_obj_align", 4));
  evm_prop_set(e, obj, "lv_obj_align_to", evm_mk_native(e, evm_module_lvgl_lv_obj_align_to, "lv_obj_align_to", 5));
  evm_prop_set(e, obj, "lv_obj_center", evm_mk_native(e, evm_module_lvgl_lv_obj_center, "lv_obj_center", 1));
  evm_prop_set(e, obj, "lv_obj_get_x", evm_mk_native(e, evm_module_lvgl_lv_obj_get_x, "lv_obj_get_x", 1));
  evm_prop_set(e, obj, "lv_obj_get_x2", evm_mk_native(e, evm_module_lvgl_lv_obj_get_x2, "lv_obj_get_x2", 1));
  evm_prop_set(e, obj, "lv_obj_get_y", evm_mk_native(e, evm_module_lvgl_lv_obj_get_y, "lv_obj_get_y", 1));
  evm_prop_set(e, obj, "lv_obj_get_y2", evm_mk_native(e, evm_module_lvgl_lv_obj_get_y2, "lv_obj_get_y2", 1));
  evm_prop_set(e, obj, "lv_obj_get_width", evm_mk_native(e, evm_module_lvgl_lv_obj_get_width, "lv_obj_get_width", 1));
  evm_prop_set(e, obj, "lv_obj_get_height", evm_mk_native(e, evm_module_lvgl_lv_obj_get_height, "lv_obj_get_height", 1));
  evm_prop_set(e, obj, "lv_obj_get_content_width", evm_mk_native(e, evm_module_lvgl_lv_obj_get_content_width, "lv_obj_get_content_width", 1));
  evm_prop_set(e, obj, "lv_obj_get_content_height", evm_mk_native(e, evm_module_lvgl_lv_obj_get_content_height, "lv_obj_get_content_height", 1));
  evm_prop_set(e, obj, "lv_obj_get_self_width", evm_mk_native(e, evm_module_lvgl_lv_obj_get_self_width, "lv_obj_get_self_width", 1));
  evm_prop_set(e, obj, "lv_obj_get_self_height", evm_mk_native(e, evm_module_lvgl_lv_obj_get_self_height, "lv_obj_get_self_height", 1));
  evm_prop_set(e, obj, "lv_obj_refresh_self_size", evm_mk_native(e, evm_module_lvgl_lv_obj_refresh_self_size, "lv_obj_refresh_self_size", 1));
  evm_prop_set(e, obj, "lv_obj_refr_pos", evm_mk_native(e, evm_module_lvgl_lv_obj_refr_pos, "lv_obj_refr_pos", 1));
  evm_prop_set(e, obj, "lv_obj_move_to", evm_mk_native(e, evm_module_lvgl_lv_obj_move_to, "lv_obj_move_to", 3));
  evm_prop_set(e, obj, "lv_obj_move_children_by", evm_mk_native(e, evm_module_lvgl_lv_obj_move_children_by, "lv_obj_move_children_by", 4));
  evm_prop_set(e, obj, "lv_obj_transform_point", evm_mk_native(e, evm_module_lvgl_lv_obj_transform_point, "lv_obj_transform_point", 4));
  evm_prop_set(e, obj, "lv_obj_invalidate", evm_mk_native(e, evm_module_lvgl_lv_obj_invalidate, "lv_obj_invalidate", 1));
  evm_prop_set(e, obj, "lv_obj_is_visible", evm_mk_native(e, evm_module_lvgl_lv_obj_is_visible, "lv_obj_is_visible", 1));
  evm_prop_set(e, obj, "lv_obj_set_flex_flow", evm_mk_native(e, evm_module_lvgl_lv_obj_set_flex_flow, "lv_obj_set_flex_flow", 2));
  evm_prop_set(e, obj, "lv_obj_set_flex_grow", evm_mk_native(e, evm_module_lvgl_lv_obj_set_flex_grow, "lv_obj_set_flex_grow", 2));
  evm_prop_set(e, obj, "lv_obj_set_flex_align", evm_mk_native(e, evm_module_lvgl_lv_obj_set_flex_align, "lv_obj_set_flex_align", 4));
  evm_prop_set(e, obj, "lv_arc_create", evm_mk_native(e, evm_module_lvgl_lv_arc_create, "lv_arc_create", 1));
  evm_prop_set(e, obj, "lv_arc_set_start_angle", evm_mk_native(e, evm_module_lvgl_lv_arc_set_start_angle, "lv_arc_set_start_angle", 2));
  evm_prop_set(e, obj, "lv_arc_set_end_angle", evm_mk_native(e, evm_module_lvgl_lv_arc_set_end_angle, "lv_arc_set_end_angle", 2));
  evm_prop_set(e, obj, "lv_arc_set_angles", evm_mk_native(e, evm_module_lvgl_lv_arc_set_angles, "lv_arc_set_angles", 3));
  evm_prop_set(e, obj, "lv_arc_set_bg_start_angle", evm_mk_native(e, evm_module_lvgl_lv_arc_set_bg_start_angle, "lv_arc_set_bg_start_angle", 2));
  evm_prop_set(e, obj, "lv_arc_set_bg_end_angle", evm_mk_native(e, evm_module_lvgl_lv_arc_set_bg_end_angle, "lv_arc_set_bg_end_angle", 2));
  evm_prop_set(e, obj, "lv_arc_set_bg_angles", evm_mk_native(e, evm_module_lvgl_lv_arc_set_bg_angles, "lv_arc_set_bg_angles", 3));
  evm_prop_set(e, obj, "lv_arc_set_rotation", evm_mk_native(e, evm_module_lvgl_lv_arc_set_rotation, "lv_arc_set_rotation", 2));
  evm_prop_set(e, obj, "lv_arc_set_mode", evm_mk_native(e, evm_module_lvgl_lv_arc_set_mode, "lv_arc_set_mode", 2));
  evm_prop_set(e, obj, "lv_arc_set_value", evm_mk_native(e, evm_module_lvgl_lv_arc_set_value, "lv_arc_set_value", 2));
  evm_prop_set(e, obj, "lv_arc_set_range", evm_mk_native(e, evm_module_lvgl_lv_arc_set_range, "lv_arc_set_range", 3));
  evm_prop_set(e, obj, "lv_arc_set_change_rate", evm_mk_native(e, evm_module_lvgl_lv_arc_set_change_rate, "lv_arc_set_change_rate", 2));
  evm_prop_set(e, obj, "lv_arc_get_angle_start", evm_mk_native(e, evm_module_lvgl_lv_arc_get_angle_start, "lv_arc_get_angle_start", 1));
  evm_prop_set(e, obj, "lv_arc_get_angle_end", evm_mk_native(e, evm_module_lvgl_lv_arc_get_angle_end, "lv_arc_get_angle_end", 1));
  evm_prop_set(e, obj, "lv_arc_get_bg_angle_start", evm_mk_native(e, evm_module_lvgl_lv_arc_get_bg_angle_start, "lv_arc_get_bg_angle_start", 1));
  evm_prop_set(e, obj, "lv_arc_get_bg_angle_end", evm_mk_native(e, evm_module_lvgl_lv_arc_get_bg_angle_end, "lv_arc_get_bg_angle_end", 1));
  evm_prop_set(e, obj, "lv_arc_get_value", evm_mk_native(e, evm_module_lvgl_lv_arc_get_value, "lv_arc_get_value", 1));
  evm_prop_set(e, obj, "lv_arc_get_min_value", evm_mk_native(e, evm_module_lvgl_lv_arc_get_min_value, "lv_arc_get_min_value", 1));
  evm_prop_set(e, obj, "lv_arc_get_max_value", evm_mk_native(e, evm_module_lvgl_lv_arc_get_max_value, "lv_arc_get_max_value", 1));
  evm_prop_set(e, obj, "lv_arc_get_mode", evm_mk_native(e, evm_module_lvgl_lv_arc_get_mode, "lv_arc_get_mode", 1));
  evm_prop_set(e, obj, "lv_bar_create", evm_mk_native(e, evm_module_lvgl_lv_bar_create, "lv_bar_create", 1));
  evm_prop_set(e, obj, "lv_bar_set_value", evm_mk_native(e, evm_module_lvgl_lv_bar_set_value, "lv_bar_set_value", 3));
  evm_prop_set(e, obj, "lv_bar_set_start_value", evm_mk_native(e, evm_module_lvgl_lv_bar_set_start_value, "lv_bar_set_start_value", 3));
  evm_prop_set(e, obj, "lv_bar_set_range", evm_mk_native(e, evm_module_lvgl_lv_bar_set_range, "lv_bar_set_range", 3));
  evm_prop_set(e, obj, "lv_bar_set_mode", evm_mk_native(e, evm_module_lvgl_lv_bar_set_mode, "lv_bar_set_mode", 2));
  evm_prop_set(e, obj, "lv_bar_get_value", evm_mk_native(e, evm_module_lvgl_lv_bar_get_value, "lv_bar_get_value", 1));
  evm_prop_set(e, obj, "lv_bar_get_start_value", evm_mk_native(e, evm_module_lvgl_lv_bar_get_start_value, "lv_bar_get_start_value", 1));
  evm_prop_set(e, obj, "lv_bar_get_min_value", evm_mk_native(e, evm_module_lvgl_lv_bar_get_min_value, "lv_bar_get_min_value", 1));
  evm_prop_set(e, obj, "lv_bar_get_max_value", evm_mk_native(e, evm_module_lvgl_lv_bar_get_max_value, "lv_bar_get_max_value", 1));
  evm_prop_set(e, obj, "lv_bar_get_mode", evm_mk_native(e, evm_module_lvgl_lv_bar_get_mode, "lv_bar_get_mode", 1));
  evm_prop_set(e, obj, "lv_btn_create", evm_mk_native(e, evm_module_lvgl_lv_btn_create, "lv_btn_create", 1));
  evm_prop_set(e, obj, "lv_checkbox_create", evm_mk_native(e, evm_module_lvgl_lv_checkbox_create, "lv_checkbox_create", 1));
  evm_prop_set(e, obj, "lv_checkbox_set_text", evm_mk_native(e, evm_module_lvgl_lv_checkbox_set_text, "lv_checkbox_set_text", 2));
  evm_prop_set(e, obj, "lv_checkbox_set_text_static", evm_mk_native(e, evm_module_lvgl_lv_checkbox_set_text_static, "lv_checkbox_set_text_static", 2));
  evm_prop_set(e, obj, "lv_checkbox_get_text", evm_mk_native(e, evm_module_lvgl_lv_checkbox_get_text, "lv_checkbox_get_text", 1));
  evm_prop_set(e, obj, "lv_dropdown_create", evm_mk_native(e, evm_module_lvgl_lv_dropdown_create, "lv_dropdown_create", 1));
  evm_prop_set(e, obj, "lv_dropdown_set_text", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_text, "lv_dropdown_set_text", 2));
  evm_prop_set(e, obj, "lv_dropdown_set_options", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_options, "lv_dropdown_set_options", 2));
  evm_prop_set(e, obj, "lv_dropdown_set_options_static", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_options_static, "lv_dropdown_set_options_static", 2));
  evm_prop_set(e, obj, "lv_dropdown_add_option", evm_mk_native(e, evm_module_lvgl_lv_dropdown_add_option, "lv_dropdown_add_option", 3));
  evm_prop_set(e, obj, "lv_dropdown_clear_options", evm_mk_native(e, evm_module_lvgl_lv_dropdown_clear_options, "lv_dropdown_clear_options", 1));
  evm_prop_set(e, obj, "lv_dropdown_set_selected", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_selected, "lv_dropdown_set_selected", 2));
  evm_prop_set(e, obj, "lv_dropdown_set_dir", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_dir, "lv_dropdown_set_dir", 2));
  evm_prop_set(e, obj, "lv_dropdown_set_symbol", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_symbol, "lv_dropdown_set_symbol", 2));
  evm_prop_set(e, obj, "lv_dropdown_set_selected_highlight", evm_mk_native(e, evm_module_lvgl_lv_dropdown_set_selected_highlight, "lv_dropdown_set_selected_highlight", 2));
  evm_prop_set(e, obj, "lv_dropdown_get_list", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_list, "lv_dropdown_get_list", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_text", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_text, "lv_dropdown_get_text", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_options", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_options, "lv_dropdown_get_options", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_selected", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_selected, "lv_dropdown_get_selected", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_option_cnt", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_option_cnt, "lv_dropdown_get_option_cnt", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_option_index", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_option_index, "lv_dropdown_get_option_index", 2));
  evm_prop_set(e, obj, "lv_dropdown_get_symbol", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_symbol, "lv_dropdown_get_symbol", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_selected_highlight", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_selected_highlight, "lv_dropdown_get_selected_highlight", 1));
  evm_prop_set(e, obj, "lv_dropdown_get_dir", evm_mk_native(e, evm_module_lvgl_lv_dropdown_get_dir, "lv_dropdown_get_dir", 1));
  evm_prop_set(e, obj, "lv_dropdown_open", evm_mk_native(e, evm_module_lvgl_lv_dropdown_open, "lv_dropdown_open", 1));
  evm_prop_set(e, obj, "lv_dropdown_close", evm_mk_native(e, evm_module_lvgl_lv_dropdown_close, "lv_dropdown_close", 1));
  evm_prop_set(e, obj, "lv_dropdown_is_open", evm_mk_native(e, evm_module_lvgl_lv_dropdown_is_open, "lv_dropdown_is_open", 1));
  evm_prop_set(e, obj, "lv_label_create", evm_mk_native(e, evm_module_lvgl_lv_label_create, "lv_label_create", 1));
  evm_prop_set(e, obj, "lv_label_set_text", evm_mk_native(e, evm_module_lvgl_lv_label_set_text, "lv_label_set_text", 2));
  evm_prop_set(e, obj, "lv_label_set_text_static", evm_mk_native(e, evm_module_lvgl_lv_label_set_text_static, "lv_label_set_text_static", 2));
  evm_prop_set(e, obj, "lv_label_set_long_mode", evm_mk_native(e, evm_module_lvgl_lv_label_set_long_mode, "lv_label_set_long_mode", 2));
  evm_prop_set(e, obj, "lv_label_get_text", evm_mk_native(e, evm_module_lvgl_lv_label_get_text, "lv_label_get_text", 1));
  evm_prop_set(e, obj, "lv_img_create", evm_mk_native(e, evm_module_lvgl_lv_img_create, "lv_img_create", 1));
  evm_prop_set(e, obj, "lv_img_set_src", evm_mk_native(e, evm_module_lvgl_lv_img_set_src, "lv_img_set_src", 2));
  evm_prop_set(e, obj, "lv_slider_create", evm_mk_native(e, evm_module_lvgl_lv_slider_create, "lv_slider_create", 1));
  evm_prop_set(e, obj, "lv_slider_set_value", evm_mk_native(e, evm_module_lvgl_lv_slider_set_value, "lv_slider_set_value", 3));
  evm_prop_set(e, obj, "lv_slider_set_range", evm_mk_native(e, evm_module_lvgl_lv_slider_set_range, "lv_slider_set_range", 3));
  evm_prop_set(e, obj, "lv_slider_get_value", evm_mk_native(e, evm_module_lvgl_lv_slider_get_value, "lv_slider_get_value", 1));
  evm_prop_set(e, obj, "lv_slider_get_min_value", evm_mk_native(e, evm_module_lvgl_lv_slider_get_min_value, "lv_slider_get_min_value", 1));
  evm_prop_set(e, obj, "lv_slider_get_max_value", evm_mk_native(e, evm_module_lvgl_lv_slider_get_max_value, "lv_slider_get_max_value", 1));
  evm_prop_set(e, obj, "LV_OPA_TRANSP", evm_mk_number(e, LV_OPA_TRANSP));
  evm_prop_set(e, obj, "LV_PALETTE_RED", evm_mk_number(e, LV_PALETTE_RED));
  evm_prop_set(e, obj, "LV_PALETTE_PINK", evm_mk_number(e, LV_PALETTE_PINK));
  evm_prop_set(e, obj, "LV_PALETTE_PURPLE", evm_mk_number(e, LV_PALETTE_PURPLE));
  evm_prop_set(e, obj, "LV_PALETTE_DEEP_PURPLE", evm_mk_number(e, LV_PALETTE_DEEP_PURPLE));
  evm_prop_set(e, obj, "LV_PALETTE_INDIGO", evm_mk_number(e, LV_PALETTE_INDIGO));
  evm_prop_set(e, obj, "LV_PALETTE_BLUE", evm_mk_number(e, LV_PALETTE_BLUE));
  evm_prop_set(e, obj, "LV_PALETTE_LIGHT_BLUE", evm_mk_number(e, LV_PALETTE_LIGHT_BLUE));
  evm_prop_set(e, obj, "LV_PALETTE_CYAN", evm_mk_number(e, LV_PALETTE_CYAN));
  evm_prop_set(e, obj, "LV_PALETTE_TEAL", evm_mk_number(e, LV_PALETTE_TEAL));
  evm_prop_set(e, obj, "LV_PALETTE_GREEN", evm_mk_number(e, LV_PALETTE_GREEN));
  evm_prop_set(e, obj, "LV_PALETTE_LIGHT_GREEN", evm_mk_number(e, LV_PALETTE_LIGHT_GREEN));
  evm_prop_set(e, obj, "LV_PALETTE_LIME", evm_mk_number(e, LV_PALETTE_LIME));
  evm_prop_set(e, obj, "LV_PALETTE_YELLOW", evm_mk_number(e, LV_PALETTE_YELLOW));
  evm_prop_set(e, obj, "LV_PALETTE_AMBER", evm_mk_number(e, LV_PALETTE_AMBER));
  evm_prop_set(e, obj, "LV_PALETTE_ORANGE", evm_mk_number(e, LV_PALETTE_ORANGE));
  evm_prop_set(e, obj, "LV_PALETTE_DEEP_ORANGE", evm_mk_number(e, LV_PALETTE_DEEP_ORANGE));
  evm_prop_set(e, obj, "LV_PALETTE_BROWN", evm_mk_number(e, LV_PALETTE_BROWN));
  evm_prop_set(e, obj, "LV_PALETTE_BLUE_GREY", evm_mk_number(e, LV_PALETTE_BLUE_GREY));
  evm_prop_set(e, obj, "LV_PALETTE_GREY", evm_mk_number(e, LV_PALETTE_GREY));
  evm_prop_set(e, obj, "LV_ALIGN_DEFAULT", evm_mk_number(e, LV_ALIGN_DEFAULT));
  evm_prop_set(e, obj, "LV_ALIGN_TOP_LEFT", evm_mk_number(e, LV_ALIGN_TOP_LEFT));
  evm_prop_set(e, obj, "LV_ALIGN_TOP_MID", evm_mk_number(e, LV_ALIGN_TOP_MID));
  evm_prop_set(e, obj, "LV_ALIGN_TOP_RIGHT", evm_mk_number(e, LV_ALIGN_TOP_RIGHT));
  evm_prop_set(e, obj, "LV_ALIGN_BOTTOM_LEFT", evm_mk_number(e, LV_ALIGN_BOTTOM_LEFT));
  evm_prop_set(e, obj, "LV_ALIGN_BOTTOM_MID", evm_mk_number(e, LV_ALIGN_BOTTOM_MID));
  evm_prop_set(e, obj, "LV_ALIGN_BOTTOM_RIGHT", evm_mk_number(e, LV_ALIGN_BOTTOM_RIGHT));
  evm_prop_set(e, obj, "LV_ALIGN_LEFT_MID", evm_mk_number(e, LV_ALIGN_LEFT_MID));
  evm_prop_set(e, obj, "LV_ALIGN_RIGHT_MID", evm_mk_number(e, LV_ALIGN_RIGHT_MID));
  evm_prop_set(e, obj, "LV_ALIGN_CENTER", evm_mk_number(e, LV_ALIGN_CENTER));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_TOP_LEFT", evm_mk_number(e, LV_ALIGN_OUT_TOP_LEFT));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_TOP_MID", evm_mk_number(e, LV_ALIGN_OUT_TOP_MID));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_TOP_RIGHT", evm_mk_number(e, LV_ALIGN_OUT_TOP_RIGHT));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_BOTTOM_LEFT", evm_mk_number(e, LV_ALIGN_OUT_BOTTOM_LEFT));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_BOTTOM_MID", evm_mk_number(e, LV_ALIGN_OUT_BOTTOM_MID));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_BOTTOM_RIGHT", evm_mk_number(e, LV_ALIGN_OUT_BOTTOM_RIGHT));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_LEFT_TOP", evm_mk_number(e, LV_ALIGN_OUT_LEFT_TOP));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_LEFT_MID", evm_mk_number(e, LV_ALIGN_OUT_LEFT_MID));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_LEFT_BOTTOM", evm_mk_number(e, LV_ALIGN_OUT_LEFT_BOTTOM));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_RIGHT_TOP", evm_mk_number(e, LV_ALIGN_OUT_RIGHT_TOP));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_RIGHT_MID", evm_mk_number(e, LV_ALIGN_OUT_RIGHT_MID));
  evm_prop_set(e, obj, "LV_ALIGN_OUT_RIGHT_BOTTOM", evm_mk_number(e, LV_ALIGN_OUT_RIGHT_BOTTOM));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_ROW", evm_mk_number(e, LV_FLEX_FLOW_ROW));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_COLUMN", evm_mk_number(e, LV_FLEX_FLOW_COLUMN));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_ROW_WRAP", evm_mk_number(e, LV_FLEX_FLOW_ROW_WRAP));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_ROW_REVERSE", evm_mk_number(e, LV_FLEX_FLOW_ROW_REVERSE));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_ROW_WRAP_REVERSE", evm_mk_number(e, LV_FLEX_FLOW_ROW_WRAP_REVERSE));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_COLUMN_WRAP", evm_mk_number(e, LV_FLEX_FLOW_COLUMN_WRAP));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_COLUMN_REVERSE", evm_mk_number(e, LV_FLEX_FLOW_COLUMN_REVERSE));
  evm_prop_set(e, obj, "LV_FLEX_FLOW_COLUMN_WRAP_REVERSE", evm_mk_number(e, LV_FLEX_FLOW_COLUMN_WRAP_REVERSE));
  evm_prop_set(e, obj, "LV_EVENT_ALL", evm_mk_number(e, LV_EVENT_ALL));
  evm_prop_set(e, obj, "LV_EVENT_PRESSED", evm_mk_number(e, LV_EVENT_PRESSED));
  evm_prop_set(e, obj, "LV_EVENT_PRESSING", evm_mk_number(e, LV_EVENT_PRESSING));
  evm_prop_set(e, obj, "LV_EVENT_LONG_PRESSED", evm_mk_number(e, LV_EVENT_LONG_PRESSED));
  evm_prop_set(e, obj, "LV_EVENT_CLICKED", evm_mk_number(e, LV_EVENT_CLICKED));
  evm_prop_set(e, obj, "LV_EVENT_RELEASED", evm_mk_number(e, LV_EVENT_RELEASED));
  evm_module_add(e, "lvgl", obj);
}
#endif
