/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
****************************************************************************/
#ifndef EVM_TYPE_H
#define EVM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>

#define EVM_FILENAME_LEN        128
#define EVM_ERR_ATOM            0xFFFF
#define EVM_STRINGPOOL_SIZE     256U
#define EVM_LIST_EXPAND_SIZE    8
#define EVM_CODE_BUF_SIZE       256

typedef uint16_t evm_atom_t;
typedef uint64_t evm_val_t;
typedef int evm_err_t;

typedef struct evm_string_pool_t{
    int count;
    evm_val_t *values;
    struct evm_string_pool_t * next;
} evm_string_pool_t;

typedef struct evm_gc_object_t {
    void *obj;
    struct evm_gc_object_t *next;
} evm_gc_object_t;

typedef struct evm_t{
    evm_err_t err;
    int line;
    char file_name[EVM_FILENAME_LEN];
    evm_val_t *sp;
    evm_val_t *sp_base;
    int stack_size;
    evm_val_t global;
    evm_string_pool_t * string_pool;
    evm_gc_object_t *gcroot;
    evm_gc_object_t *gcnext;
} evm_t;

#define OBJECT_SECTION \
    uint16_t type;\
    uint16_t mark;\
    int32_t size;\
    evm_atom_t *keys;\
    evm_val_t  *vals;\
    struct qvm_object_t *proto;\
    void *data;\

typedef struct evm_buffer_t {
    OBJECT_SECTION
    int32_t count;
    uint8_t *buf;
} evm_buffer_t;

typedef struct evm_object_t {
    OBJECT_SECTION
} evm_object_t;

typedef struct evm_function_t {
    OBJECT_SECTION
    uint8_t *codes;
    size_t code_idx;
    size_t code_size;
    evm_atom_t *var_names;
    int16_t var_count;
    int16_t var_size;
    int16_t param_len;
    evm_object_t *scope;
} evm_function_t;

typedef struct evm_list_t {
    OBJECT_SECTION
    int count;
} evm_list_t;

typedef struct evm_string_t {
    OBJECT_SECTION
    char *str;
    int len;
} evm_string_t;

typedef evm_val_t (*evm_native_t)(evm_t *e, evm_val_t pthis, int argc, evm_val_t *v);

typedef union {
    evm_val_t   v;
    double      d;
} evm_valnum_t;

#define EVM_API     extern
#define double_2_val(d) (((evm_valnum_t*)&(d))->v)

enum EVM_TYPE
{
    TYPE_NUMBER = 0,
    TYPE_STRING,
    TYPE_CONST_STRING,
    TYPE_BOOLEAN,
    TYPE_FUNCTION,
    TYPE_NATIVE,
    TYPE_NULL,
    TYPE_UNDEFINED,
    TYPE_NAN,
    TYPE_LIST,
    TYPE_BUFFER,
    TYPE_OBJECT,
    TYPE_INVOKE,
};

enum Bytecode
{
    op_nop = 0,
    op_end,
    OP_getLocal2,
    OP_getLocal,
    OP_getGlobal,
    OP_getScope,
    OP_setScope,
    OP_number,
    OP_undefined,
    OP_null,
    OP_true,
    OP_false,
    OP_getString,
    OP_setLocal2,
    OP_setLocal,
    op_ia,
    OP_add,
    OP_sub,
    OP_mul,
    OP_div,
    OP_mod,
    OP_and,
    OP_or,
    OP_xor,
    op_neg,
    OP_not,
    op_inv,
    OP_leftShift,
    OP_rightShift,
    OP_unsignedRightShift,
    op_aadd, //aadd, hash, 2 bytes
    op_asub, //asub, hash, 2 bytes
    op_amul, //amul, hash, 2 bytes
    op_adiv, //adiv, hash, 2 bytes
    op_amod, //amod, hash, 2 bytes
    op_aand, //aand, hash, 2 bytes
    op_aor,  //aor, hash, 2 bytes
    op_axor, //axor, hash, 2 bytes
    op_alsh, //alsh, hash, 2 bytes
    op_arsh, //arsh, hash, 2 bytes
    OP_shortJump, //sjmp, short address, 2 bytes
    OP_shortJumpTrue,//sjmp, short address, 2 bytes
    OP_shortJumpFalse,//sjmp, short address, 2 bytes
    OP_jump,   //jmp, int address, 2 bytes
    OP_jumpTrue, //jmp, int address, 2 bytes
    OP_jumpFalse, //jmp, int address, 2 bytes
    OP_call,  //call, pos|pair, 2 bytes
    OP_callProp, //callp, pos|pair, 2 bytes
    op_call_pop,  //call_pop, pos|pair, 2 bytes
    op_callp_pop, //callp, pos|pair, 2 bytes
    OP_return,
    op_ret_pop,
    OP_lessThan,
    OP_greaterThan,
    OP_lessThanEqual,
    OP_greaterThanEqual,
    OP_equal,
    OP_notEqual,
    OP_typeEqual,
    OP_typeNotEqual,
    OP_stackDown,
    OP_stackDown2,
    OP_stackUp,
    op_swap,
    OP_pop,
    op_dup,
    OP_getProp, //lp, hash, 2 bytes
    OP_setProp, //ap, hash, 2 bytes
    op_aaddp, //aaddp, hash, 2 bytes
    op_asubp, //asubp, hash, 2 bytes
    op_amulp, //amulp, hash, 2 bytes
    op_adivp, //adivp, hash, 2 bytes
    op_amodp, //amodp, hash, 2 bytes
    op_aandp, //aandp, hash, 2 bytes
    op_aorp,  //aorp, hash, 2 bytes
    op_axorp, //axorp, hash, 2 bytes
    op_alshp, //alshp, hash, 2 bytes
    op_arshp, //arshp, hash, 2 bytes

    OP_getList,
    op_lr,
    OP_setList,
    op_assign_add_array,
    op_assign_sub_array,
    op_assign_mul_array,
    op_assign_div_array,
    op_assign_mod_array,
    op_assign_and_array,
    op_assign_or_array,
    op_assign_xor_array,
    op_assign_lsh_array,
    op_assign_rsh_array,
    op_array_suffix_inc,
    op_array_suffix_dec,
    op_array_prefix_inc,
    op_array_prefix_dec,

    op_suffix_inc, //pos, 4 bytes
    op_suffix_dec, //pos, 4 bytes
    op_suffix_incp,//hash, 2 bytes
    op_suffix_decp,//hash, 2 bytes
    op_prefix_inc, //pos, 4 bytes
    op_prefix_dec, //pos, 4 bytes
    op_prefix_incp,//hash, 2 bytes
    op_prefix_decp,//hash, 2 bytes

    op_br, //address, 2 bytes
    op_continue, //address, 2 bytes
    op_continue_end,
    op_import, //hash, 2 bytes
    OP_line8,
    OP_line16, //integer, 2 bytes
    OP_line32,
    op_seq, //integer, 2 bytes
    OP_newList,//integer, 2 bytes
    OP_newObject,//integer, 2 bytes
    op_iter,
    op_for, //address, 2 bytes
    op_try, //integer, 2 bytes
    OP_delProp,
    op_throw,
    op_inherit,
    OP_this,
    op_scope,
    op_init,
    OP_global,
    op_in,
    op_nin,
    OP_stop,
    op_sw,
    OP_nan,
    op_name, //hash, 2 bytes
    op_assign_name,//hash, 2 bytes
    OP_logicAnd,
    OP_logicOr,

    op_closure,
    op_super,
    op_select,
    op_br_if,
};

static inline int16_t __get_int16(uint8_t * buf){
    union{
        int16_t i;
        char buf[2];
    }u;
    memcpy(u.buf, buf, 2);
    return u.i;
}

static inline uint16_t __get_uint16(uint8_t * buf){
    union{
        uint16_t i;
        char buf[2];
    }u;
    memcpy(u.buf, buf, 2);
    return u.i;
}

static inline void __set_uint16(uint8_t * buf, uint16_t v){
    union{
        uint16_t i;
        char buf[2];
    }u;
    u.i = v;
    memcpy(buf, u.buf, 2);
}

static inline int32_t __get_int32(uint8_t * buf){
    union{
        int32_t i;
        char buf[4];
    }u;
    memcpy(u.buf, buf, 4);
    return u.i;
}

static inline int32_t __get_int64(uint8_t * buf){
    union{
        int64_t i;
        char buf[8];
    }u;
    memcpy(u.buf, buf, 8);
    return u.i;
}

static inline uint32_t __get_uint32(uint8_t * buf){
    union{
        uint32_t i;
        char buf[4];
    }u;
    memcpy(u.buf, buf, 4);
    return u.i;
}

static inline void __set_uint32(uint8_t * buf, uint32_t v){
    union{
        uint32_t i;
        char buf[4];
    }u;
    u.i = v;
    memcpy(buf, u.buf, 4);
}

static inline uint64_t __get_uint64(uint8_t * buf){
    union{
        uint64_t i;
        char buf[8];
    }u;
    memcpy(u.buf, buf, 8);
    return u.i;
}

static inline float __get_float(uint8_t * buf){
    union{
        float i;
        char buf[4];
    }u;
    memcpy(u.buf, buf, 4);
    return u.i;
}

static inline double __get_double(uint8_t * buf){
    union{
        double i;
        char buf[8];
    }u;
    memcpy(u.buf, buf, 8);
    return u.i;
}

#define MAKE_TYPE(s, t) \
  ((evm_val_t)(s) << 63 | (evm_val_t) 0x7ff0 <<48 | (evm_val_t)(t) <<48)
#define INNER_TYPE_INFINITE        MAKE_TYPE(0, TYPE_NUMBER)
#define INNER_TYPE_FRAME           MAKE_TYPE(1, TYPE_FRAME)
#define INNER_TYPE_BUFFER          MAKE_TYPE(1, TYPE_BUFFER)
#define INNER_TYPE_STRING          MAKE_TYPE(1, TYPE_STRING)
#define INNER_TYPE_CONST_STRING    MAKE_TYPE(1, TYPE_CONST_STRING)
#define INNER_TYPE_BOOLEAN         MAKE_TYPE(1, TYPE_BOOLEAN)
#define INNER_TYPE_FUNC_SCRIPT     MAKE_TYPE(1, TYPE_FUNCTION)
#define INNER_TYPE_FUNC_NATIVE     MAKE_TYPE(1, TYPE_NATIVE)
#define INNER_TYPE_NAN             MAKE_TYPE(1, TYPE_NAN)
#define INNER_TYPE_LIST            MAKE_TYPE(1, TYPE_LIST)
#define INNER_TYPE_UNDEFINED       MAKE_TYPE(1, TYPE_UNDEFINED)
#define INNER_TYPE_NULL            MAKE_TYPE(1, TYPE_NULL)
#define INNER_TYPE_OBJECT          MAKE_TYPE(1, TYPE_OBJECT)
#define INNER_TYPE_INVOKE          MAKE_TYPE(0, TYPE_INVOKE)
#define INNER_TYPE_MASK            MAKE_TYPE(1, 0xF)
#define EVM_ADDR_MASK              0x0000FFFFFFFFFFFFL
#define EVM_VAL_MASK               (~MAKE_TYPE(1, 0xF))
#define EVM_VAL_UNDEFINED       INNER_TYPE_UNDEFINED
#define EVM_VAL_NULL            INNER_TYPE_NULL
#define EVM_VAL_INFINITE        INNER_TYPE_INFINITE
#define EVM_VAL_TRUE            (INNER_TYPE_BOOLEAN | 1)
#define EVM_VAL_FALSE           (INNER_TYPE_BOOLEAN)

static inline int evm_type(evm_val_t *v) {
    int type = (*v) >> 48;
    if ((type & 0x7ff0) != 0x7ff0) {
        return 0;
    } else {
        return type & 0xf;
    }
}

#define EVM_FUNCTION(name)                                \
  static evm_val_t name(evm_t *e,   \
                            evm_val_t p,   \
                            int argc, \
                            evm_val_t *v)

#define EVM_EPCV
#define EVM_RETURN(x)   return x;
#define EVM_RETURN_VAL(x)   return x;
#define EVM_VARARGS 0

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
