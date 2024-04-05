#include "evm_grammar.h"

extern void json_program(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_new_object(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_key(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_add_pair(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_new_array(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_add_arr(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_string_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_number_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_true_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_false_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
extern void json_null_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret);
static const evm_grm_rule_t grm_program;
static const evm_grm_rule_t grm_obj;
static const evm_grm_rule_t grm_pair;
static const evm_grm_rule_t grm_arr;
static const evm_grm_rule_t grm_value;
static const evm_grm_rule_t grm_grm_block0;
static const evm_grm_rule_t grm_grm_block1;
static const evm_grm_elem_t grm_grm_block0_alt0_elems[] = {
    {.token = 5, .suffix = 0, .u.text = ","},
    {.token = 7, .suffix = 0, .u.rule = &grm_pair},
};
static const evm_grm_elem_t grm_grm_block1_alt0_elems[] = {
    {.token = 5, .suffix = 0, .u.text = ","},
    {.token = 7, .suffix = 0, .u.rule = &grm_value},
    {.token = 18, .suffix = 0, .u.cfunc = json_add_arr},
};
static const evm_grm_alt_t grm_grm_block0_alt0 = {
    .size = 2,
    .elems = grm_grm_block0_alt0_elems,
};
static const evm_grm_alt_t grm_grm_block1_alt0 = {
    .size = 3,
    .elems = grm_grm_block1_alt0_elems,
};
static const evm_grm_alt_t *grm_grm_block0_alts[] = {
    &grm_grm_block0_alt0,
};
static const evm_grm_alt_t *grm_grm_block1_alts[] = {
    &grm_grm_block1_alt0,
};
static const evm_grm_rule_t grm_grm_block0 = {
    .size = 1,
    .alts = grm_grm_block0_alts,
};
static const evm_grm_rule_t grm_grm_block1 = {
    .size = 1,
    .alts = grm_grm_block1_alts,
};
static const evm_grm_elem_t grm_program_alt0_elems[] = {
    {.token = 7, .suffix = 0, .u.rule = &grm_value},
    {.token = 13, .suffix = 0,},
    {.token = 18, .suffix = 0, .u.cfunc = json_program},
};
static const evm_grm_elem_t grm_obj_alt0_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "{"},
    {.token = 18, .suffix = 0, .u.cfunc = json_new_object},
    {.token = 7, .suffix = 0, .u.rule = &grm_pair},
    {.token = 6, .suffix = 10, .u.rule = &grm_grm_block0},
    {.token = 5, .suffix = 0, .u.text = "}"},
};
static const evm_grm_elem_t grm_obj_alt1_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "{"},
    {.token = 18, .suffix = 0, .u.cfunc = json_new_object},
    {.token = 5, .suffix = 0, .u.text = "}"},
};
static const evm_grm_elem_t grm_pair_alt0_elems[] = {
    {.token = 14, .suffix = 0,},
    {.token = 18, .suffix = 0, .u.cfunc = json_key},
    {.token = 5, .suffix = 0, .u.text = ":"},
    {.token = 7, .suffix = 0, .u.rule = &grm_value},
    {.token = 18, .suffix = 0, .u.cfunc = json_add_pair},
};
static const evm_grm_elem_t grm_arr_alt0_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "["},
    {.token = 18, .suffix = 0, .u.cfunc = json_new_array},
    {.token = 7, .suffix = 0, .u.rule = &grm_value},
    {.token = 18, .suffix = 0, .u.cfunc = json_add_arr},
    {.token = 6, .suffix = 10, .u.rule = &grm_grm_block1},
    {.token = 5, .suffix = 0, .u.text = "]"},
};
static const evm_grm_elem_t grm_arr_alt1_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "["},
    {.token = 18, .suffix = 0, .u.cfunc = json_new_array},
    {.token = 5, .suffix = 0, .u.text = "]"},
};
static const evm_grm_elem_t grm_value_alt0_elems[] = {
    {.token = 14, .suffix = 0,},
    {.token = 18, .suffix = 0, .u.cfunc = json_string_value},
};
static const evm_grm_elem_t grm_value_alt1_elems[] = {
    {.token = 15, .suffix = 0,},
    {.token = 18, .suffix = 0, .u.cfunc = json_number_value},
};
static const evm_grm_elem_t grm_value_alt2_elems[] = {
    {.token = 7, .suffix = 0, .u.rule = &grm_obj},
};
static const evm_grm_elem_t grm_value_alt3_elems[] = {
    {.token = 7, .suffix = 0, .u.rule = &grm_arr},
};
static const evm_grm_elem_t grm_value_alt4_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "true"},
    {.token = 18, .suffix = 0, .u.cfunc = json_true_value},
};
static const evm_grm_elem_t grm_value_alt5_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "false"},
    {.token = 18, .suffix = 0, .u.cfunc = json_false_value},
};
static const evm_grm_elem_t grm_value_alt6_elems[] = {
    {.token = 5, .suffix = 0, .u.text = "null"},
    {.token = 18, .suffix = 0, .u.cfunc = json_null_value},
};
static const evm_grm_alt_t grm_program_alt0 = {
    .size = 3,
    .elems = grm_program_alt0_elems,
};
static const evm_grm_alt_t grm_obj_alt0 = {
    .size = 5,
    .elems = grm_obj_alt0_elems,
};
static const evm_grm_alt_t grm_obj_alt1 = {
    .size = 3,
    .elems = grm_obj_alt1_elems,
};
static const evm_grm_alt_t grm_pair_alt0 = {
    .size = 5,
    .elems = grm_pair_alt0_elems,
};
static const evm_grm_alt_t grm_arr_alt0 = {
    .size = 6,
    .elems = grm_arr_alt0_elems,
};
static const evm_grm_alt_t grm_arr_alt1 = {
    .size = 3,
    .elems = grm_arr_alt1_elems,
};
static const evm_grm_alt_t grm_value_alt0 = {
    .size = 2,
    .elems = grm_value_alt0_elems,
};
static const evm_grm_alt_t grm_value_alt1 = {
    .size = 2,
    .elems = grm_value_alt1_elems,
};
static const evm_grm_alt_t grm_value_alt2 = {
    .size = 1,
    .elems = grm_value_alt2_elems,
};
static const evm_grm_alt_t grm_value_alt3 = {
    .size = 1,
    .elems = grm_value_alt3_elems,
};
static const evm_grm_alt_t grm_value_alt4 = {
    .size = 2,
    .elems = grm_value_alt4_elems,
};
static const evm_grm_alt_t grm_value_alt5 = {
    .size = 2,
    .elems = grm_value_alt5_elems,
};
static const evm_grm_alt_t grm_value_alt6 = {
    .size = 2,
    .elems = grm_value_alt6_elems,
};
static const evm_grm_alt_t *grm_program_alts[] = {
    &grm_program_alt0,
};
static const evm_grm_alt_t *grm_obj_alts[] = {
    &grm_obj_alt0,
    &grm_obj_alt1,
};
static const evm_grm_alt_t *grm_pair_alts[] = {
    &grm_pair_alt0,
};
static const evm_grm_alt_t *grm_arr_alts[] = {
    &grm_arr_alt0,
    &grm_arr_alt1,
};
static const evm_grm_alt_t *grm_value_alts[] = {
    &grm_value_alt0,
    &grm_value_alt1,
    &grm_value_alt2,
    &grm_value_alt3,
    &grm_value_alt4,
    &grm_value_alt5,
    &grm_value_alt6,
};
static const evm_grm_rule_t grm_program = {
    .size = 1,
    .alts = grm_program_alts,
};
static const evm_grm_rule_t grm_obj = {
    .size = 2,
    .alts = grm_obj_alts,
};
static const evm_grm_rule_t grm_pair = {
    .size = 1,
    .alts = grm_pair_alts,
};
static const evm_grm_rule_t grm_arr = {
    .size = 2,
    .alts = grm_arr_alts,
};
static const evm_grm_rule_t grm_value = {
    .size = 7,
    .alts = grm_value_alts,
};
const evm_grm_t evm_grammar = {
    .size = 5,
    .rules = {
        &grm_program,
        &grm_obj,
        &grm_pair,
        &grm_arr,
        &grm_value,
    }
};