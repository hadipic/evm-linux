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

static evm_val_t evm_module_lvgl_lv_obj_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  cffi_args[0].p = lv_obj_create(cffi_args[1].p);
  return evm_cffi_exec_ret(e, cffi_args[0], "pp");
}

static evm_val_t evm_module_lvgl_lv_obj_add_flag(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_add_flag(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_clear_flag(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_clear_flag(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_add_state(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_add_state(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_clear_state(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_clear_state(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_x(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_x(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_y(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_y(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_size(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_obj_set_size(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_height(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_content_width(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_content_width(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_content_height(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_content_height(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_layout(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_layout(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_update_layout(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_update_layout(cffi_args[1].p);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_align(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "piii", argc, v);
  lv_obj_align(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32, cffi_args[4].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_align_to(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[6];
  evm_cffi_exec_param(e, cffi_args + 1, "ppiii", argc, v);
  lv_obj_align_to(cffi_args[1].p, cffi_args[2].p, cffi_args[3].i32, cffi_args[4].i32, cffi_args[5].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_center(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_center(cffi_args[1].p);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_move_to(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_obj_move_to(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_move_children_by(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "piib", argc, v);
  lv_obj_move_children_by(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32, cffi_args[4].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_transform_point(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "ppbb", argc, v);
  lv_obj_transform_point(cffi_args[1].p, cffi_args[2].p, cffi_args[3].i32, cffi_args[4].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_invalidate(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_obj_invalidate(cffi_args[1].p);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_flex_grow(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_obj_set_flex_grow(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_obj_set_flex_align(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[5];
  evm_cffi_exec_param(e, cffi_args + 1, "piii", argc, v);
  lv_obj_set_flex_align(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32, cffi_args[4].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_end_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_end_angle(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_angles(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_arc_set_angles(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_bg_start_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_bg_start_angle(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_bg_end_angle(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_bg_end_angle(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_bg_angles(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_arc_set_bg_angles(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_rotation(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_rotation(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_mode(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_value(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_range(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_arc_set_range(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_arc_set_change_rate(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_arc_set_change_rate(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_set_start_value(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_bar_set_start_value(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_set_range(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_bar_set_range(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_bar_set_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_bar_set_mode(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_checkbox_set_text_static(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_checkbox_set_text_static(cffi_args[1].p, cffi_args[2].s);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_options(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_options(cffi_args[1].p, cffi_args[2].s);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_options_static(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_options_static(cffi_args[1].p, cffi_args[2].s);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_add_option(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "psi", argc, v);
  lv_dropdown_add_option(cffi_args[1].p, cffi_args[2].s, cffi_args[3].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_clear_options(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_dropdown_clear_options(cffi_args[1].p);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_selected(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_dropdown_set_selected(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_dir(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_dropdown_set_dir(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_symbol(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_dropdown_set_symbol(cffi_args[1].p, cffi_args[2].s);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_set_selected_highlight(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pb", argc, v);
  lv_dropdown_set_selected_highlight(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_dropdown_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args + 1, "p", argc, v);
  lv_dropdown_close(cffi_args[1].p);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_label_set_text_static(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "ps", argc, v);
  lv_label_set_text_static(cffi_args[1].p, cffi_args[2].s);
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_label_set_long_mode(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args + 1, "pi", argc, v);
  lv_label_set_long_mode(cffi_args[1].p, cffi_args[2].i32);
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
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
  EVM_UNDEFINED;
}

static evm_val_t evm_module_lvgl_lv_slider_set_range(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args + 1, "pii", argc, v);
  lv_slider_set_range(cffi_args[1].p, cffi_args[2].i32, cffi_args[3].i32);
  EVM_UNDEFINED;
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
  evm_prop_set(e, obj, "lv_obj_create", evm_mk_native(e, evm_module_lvgl_lv_obj_create, "lv_obj_create", 1));
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
  evm_module_add(e, "lvgl", obj);
}
#endif
