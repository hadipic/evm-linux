/****************************************************************************
**
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**
**  QuickVM是一款面向高性能的脚本引擎
**
**  Version	: 1.0
**  Email	: scriptiot@aliyun.com
**  Website	: https://gitee.com/scriptiot
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef QUICKVM_H
#define QUICKVM_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <limits.h>
#include <setjmp.h>
#include <ctype.h>
#include <stdbool.h>

#define QVM_INVALID_HASH           0xFFFF
#define QVM_API     extern
#define QVM_PROP_NON_C_W_E         0x07
#define QVM_PROP_C_W_E             0x00
#define QVM_PROP_NON_CONFIGURABLE  0x01
#define QVM_PROP_NON_WRITABLE      0x02
#define QVM_PROP_NON_ENUMERABLE    0x04
#define QVM_PROP_NON_PRINTABLE     0x08
#define QVM_PROP_HIDDEN            0x10

#define QVM_UNUSED(a)   (void)a
#define QVM_UNUSED2(a, b)   (void)a;(void)b;
#define QVM_UNUSED3(a, b, c)   (void)a;(void)b;(void)c;
#define QVM_UNUSED4(a, b, c, d)   (void)a;(void)b;(void)c;(void)d;

typedef uint16_t qvm_hash_t;
typedef int unicode_t;

enum QVM_TYPE {
    QVM_TYPE_INTEGER = 0,
    QVM_TYPE_STRING,
    QVM_TYPE_STRING_OBJECT,
    QVM_TYPE_NATIVE,
    QVM_TYPE_BOOLEAN,
    QVM_TYPE_NULL,
    QVM_TYPE_INVOKE,
    QVM_TYPE_UNDEFINED,
    QVM_TYPE_NAN,
    QVM_TYPE_OBJECT,
    QVM_TYPE_ARRAY,
    QVM_TYPE_BUFFER,
    QVM_TYPE_FUNCTION,
    QVM_TYPE_ENCLOSURE,
    QVM_TYPE_CLOSURE,
    QVM_TYPE_MAIN,
    QVM_TYPE_NUMBER,
    QVM_TYPE_NUMBER_OBJECT,
    QVM_TYPE_BOOLEAN_OBJECT,
    QVM_TYPE_NATIVE_OBJECT,
    QVM_TYPE_INVOKE_OBJECT,
    QVM_TYPE_VARREF,
    QVM_TYPE_FRAME,
};

#ifdef QVM_NAN_BOXING
typedef uint64_t qvm_value_t;

#define MAKE_TAG(s, t) \
  ((upy_val_t)(s) << 63 | (upy_val_t) 0x7ff0 <<48 | (upy_val_t)(t) <<48)

#else
typedef struct qvm_value_t {
    union {
        int boolean;
        double number;
        int32_t integer;
        const char *str;
        intptr_t native;
        intptr_t object;
        struct qvm_value_t *ref;
    } u;
    uint32_t type;
    uint32_t key;
} qvm_value_t;
#endif

typedef struct qvm_string_pool_t{
    int count;
    intptr_t *values;
    struct qvm_string_pool_t * next;
} qvm_string_pool_t;

typedef struct qvm_trybuf_t
{
    jmp_buf buf;
    qvm_value_t scope;
    qvm_value_t this;
    qvm_value_t *sp;
    qvm_value_t *values;
    uint16_t *pc;
} qvm_trybuf_t;

typedef struct qvm_state_t {
    /** vm **/
    const char *filename;
    void *gcclosure_root;
    void *gcclosure;
    int gc_threshold;
    void *gcroot;
    void *gcroot_right;
    uint16_t *pc;
    qvm_value_t extension;
    qvm_value_t root;
    qvm_value_t scope;
    qvm_value_t this;
    qvm_value_t modules;
    qvm_value_t *sp_base;
    qvm_value_t *sp_high;
    qvm_value_t *sp;
    qvm_value_t *values;
    int stack_size;
    qvm_value_t *refs;
    int ref_size;
    qvm_string_pool_t *string_pool;
    int trybuf_count;
    int trybuf_limit;
    qvm_trybuf_t *trybuf;
    int row;
    int gc_pause;
    struct qvm_ops_t *ops;
    /** parser **/
    char *name;
    int var_name_len;
    char *input;
    int input_len;
    int index;
    double num;
    int anonymous;
    /** user data **/
    void *user_data;
    /** grammar data **/
    qvm_value_t grammar;
    const char *multi_comment_pattern;
    const char *multi_comment_start;
    const char *single_comment_pattern;
    const char *single_comment_start;
} qvm_state_t;

typedef struct qvm_accessor_t {
    qvm_value_t setter;
    qvm_value_t getter;
} qvm_accessor_t;

typedef struct qvm_builtin_t {
    qvm_value_t (*creator)(qvm_state_t * e, qvm_value_t self, int argc, qvm_value_t *v);
    qvm_value_t (*destroyer)(qvm_state_t * e, qvm_value_t self, int argc, qvm_value_t *v);
    qvm_value_t (*caller)(qvm_state_t * e, qvm_value_t self, int argc, qvm_value_t *v);
} qvm_builtin_t;

typedef struct qvm_ops_t {
    int (*instanceof)(qvm_state_t * e, qvm_value_t value1, qvm_value_t value2);
    qvm_value_t (*new_array)(qvm_state_t *e);
    void (*push_array)(qvm_state_t *e, qvm_value_t object, qvm_value_t value);
    qvm_value_t (*new_object)(qvm_state_t *e);
    qvm_value_t (*new_string)(qvm_state_t *e, const char *s);
} qvm_ops_t;

typedef struct qvm_value_t (*qvm_native_t)(qvm_state_t * e, struct qvm_value_t self, int argc, struct qvm_value_t *v);

/*** 外部实现接口注册 ***/
QVM_API void qvm_register_print(int (*fn)(const char *fmt, ...));
QVM_API void qvm_register_free(void (*fn)(qvm_state_t *e, void * mem));
QVM_API void qvm_register_malloc(void *(*fn)(qvm_state_t *e, size_t size));
QVM_API void qvm_register_realloc(void *(*fn)(qvm_state_t *e, void *ptr, size_t size));
QVM_API void qvm_register_file_load(const char *(*fn)(qvm_state_t *e, const char * path));
QVM_API void qvm_register_lock(void (*fn)(qvm_state_t *e));
QVM_API void qvm_register_unlock(void (*fn)(qvm_state_t *e));
QVM_API int (*qvm_print)(const char *fmt, ...);
QVM_API void *(*qvm_malloc)(qvm_state_t *e, size_t size);
QVM_API void *(*qvm_realloc)(qvm_state_t *e, void *ptr, size_t size);
QVM_API void (*qvm_free)(qvm_state_t *e, void * mem);
QVM_API void (*qvm_lock)(qvm_state_t *e);
QVM_API void (*qvm_unlock)(qvm_state_t *e);
QVM_API void (*qvm_gettime)(char *buffer);

/*** 外部实现接口实现 ***/
QVM_API int qvm_check_memory(qvm_state_t *e);
QVM_API void qvm_assert (const char *assertion, const char *file, const char *function, const uint32_t line);

static inline int qvm_is_object(qvm_value_t value) {
    switch (value.type) {
    case QVM_TYPE_ARRAY:
    case QVM_TYPE_BUFFER:
    case QVM_TYPE_BOOLEAN_OBJECT:
    case QVM_TYPE_NUMBER_OBJECT:
    case QVM_TYPE_STRING_OBJECT:
    case QVM_TYPE_NATIVE_OBJECT:
    case QVM_TYPE_INVOKE_OBJECT:
    case QVM_TYPE_OBJECT:
    case QVM_TYPE_FUNCTION:
    case QVM_TYPE_MAIN:
    case QVM_TYPE_ENCLOSURE:
    case QVM_TYPE_CLOSURE:
        return 1;
    }
    return 0;
}

static inline int qvm_is_invoke_object(qvm_value_t value) {
    return value.type == QVM_TYPE_INVOKE_OBJECT;
}

static inline int qvm_is_string(qvm_value_t value) {
    switch (value.type) {
    case QVM_TYPE_STRING:return 1;
    case QVM_TYPE_STRING_OBJECT:return 1;
    default:return 0;
    }
}

static inline int qvm_is_array(qvm_value_t value) {
    return value.type == QVM_TYPE_ARRAY;
}

static inline int qvm_is_number(qvm_value_t value) {
    return value.type == QVM_TYPE_NUMBER || value.type == QVM_TYPE_INTEGER;
}

QVM_API int qvm_is_boolean(qvm_value_t value);
QVM_API int qvm_is_undefined(qvm_value_t value);
QVM_API int qvm_is_null(qvm_value_t value);
QVM_API int qvm_is_script(qvm_value_t value);
QVM_API int qvm_is_string_object(qvm_value_t value);
QVM_API int qvm_is_buffer(qvm_value_t value);
QVM_API int qvm_is_defined(qvm_value_t value);
QVM_API int qvm_is_integer(qvm_value_t value);
QVM_API int qvm_is_invoke(qvm_value_t value);
QVM_API int qvm_is_callable(qvm_value_t value);
QVM_API int qvm_is_function(qvm_value_t value);
QVM_API int qvm_is_primitive(qvm_value_t value);
QVM_API int qvm_is_invoke_object(qvm_value_t value);
QVM_API int qvm_is_native(qvm_value_t value);

/*** 属性判断 ***/
QVM_API const char *qvm_get_propertyname(qvm_state_t *e, qvm_value_t value);
QVM_API int qvm_has_next(qvm_state_t *e, qvm_value_t object, int *index);
QVM_API qvm_value_t qvm_next_property(qvm_state_t *e, qvm_value_t object, int *index);
QVM_API int qvm_has_property(qvm_state_t *e, qvm_value_t object, const char *name);
QVM_API void qvm_del_property(qvm_state_t *e, qvm_value_t object, const char *name);
QVM_API qvm_value_t qvm_add_property(qvm_state_t *e, qvm_value_t object, const char *name, qvm_value_t value);
QVM_API qvm_value_t qvm_get_property(qvm_state_t *e, qvm_value_t object, const char *name);
QVM_API qvm_value_t qvm_get_property_by_key(qvm_state_t *e, qvm_value_t object, qvm_hash_t key);
QVM_API qvm_value_t qvm_add_property_by_key(qvm_state_t *e, qvm_value_t object, qvm_hash_t key, qvm_value_t value);
QVM_API int qvm_get_property_flag(qvm_state_t *e, qvm_value_t object, const char *name);
QVM_API qvm_value_t qvm_def_property(qvm_state_t *e, qvm_value_t object, const char *name, qvm_value_t value, uint8_t flag);

/*** 类型操作 ***/
QVM_API qvm_value_t qvm_concat(qvm_state_t *e, qvm_value_t value1, qvm_value_t value2);
QVM_API int qvm_to_boolean(qvm_state_t *e, qvm_value_t value);
QVM_API int qvm_compare(qvm_state_t *e, qvm_value_t value1, qvm_value_t value2, int *ok);
QVM_API int qvm_strictequal(qvm_state_t *e, qvm_value_t x, qvm_value_t y);
QVM_API int qvm_equal(qvm_state_t *e, qvm_value_t x, qvm_value_t y);
QVM_API const char *qvm_to_string(qvm_state_t *e, qvm_value_t value);
QVM_API double qvm_to_number(qvm_state_t *e, qvm_value_t value);
QVM_API uint32_t qvm_to_uint32(qvm_state_t *e, qvm_value_t value);
QVM_API int32_t qvm_to_int32(qvm_state_t *e, qvm_value_t value);
QVM_API qvm_value_t qvm_ecma_to_primitive(qvm_state_t *e, qvm_value_t object, int type);
QVM_API qvm_value_t qvm_to_primitive(qvm_state_t *e, qvm_value_t value, const char *choice);
QVM_API qvm_value_t qvm_mk_boolean(int v);
QVM_API qvm_value_t qvm_mk_number(double n);
QVM_API qvm_value_t qvm_mk_int32(int32_t n);
QVM_API qvm_value_t qvm_mk_null(void);
QVM_API qvm_value_t qvm_mk_native(qvm_native_t native);
QVM_API qvm_value_t qvm_mk_string(const char *str);
QVM_API qvm_value_t qvm_mk_undefined(void);
QVM_API qvm_value_t qvm_mk_nan(void);
QVM_API qvm_value_t qvm_mk_invoke(void *ptr);
QVM_API qvm_value_t qvm_mk_function(intptr_t func);
QVM_API void *qvm_to_invoke(qvm_state_t *e, qvm_value_t value);
QVM_API qvm_native_t qvm_to_native(qvm_state_t *e, qvm_value_t value);
QVM_API void qvm_print_value(qvm_state_t * e, qvm_value_t value);

/*** 字符串对象操作 ***/
QVM_API qvm_value_t qvm_new_string(qvm_state_t *e, const char *s);
QVM_API qvm_value_t qvm_new_lstring(qvm_state_t *e, const char *s, int n);
QVM_API int qvm_string_length(qvm_state_t *e, qvm_value_t value);
QVM_API const char * qvm_key_to_str(qvm_state_t *e, qvm_hash_t key);

/*** 对象操作 ***/
QVM_API qvm_value_t qvm_copy(qvm_state_t *e, qvm_value_t object);
QVM_API qvm_value_t qvm_new_object(qvm_state_t *e);
QVM_API qvm_value_t qvm_new_invoke_object(qvm_state_t *e);
QVM_API qvm_value_t qvm_new_boolean(qvm_state_t *e, int v);
QVM_API qvm_value_t qvm_new_number(qvm_state_t *e, double v);
QVM_API qvm_value_t qvm_new_native(qvm_state_t *e, qvm_native_t native, int length);

/*** 对象属性劫持操作 ***/
QVM_API qvm_accessor_t *qvm_get_accessor(qvm_state_t *e, qvm_value_t object, const char *name);
QVM_API void qvm_def_accessor(qvm_state_t *e,
                            qvm_value_t object,
                            const char *name,
                            qvm_value_t getter,
                            qvm_value_t setter,
                            qvm_value_t value,
                            uint8_t flag);
/*** 对象内置方法操作 ***/
QVM_API void qvm_set_builtin(qvm_state_t *e, qvm_value_t value, qvm_builtin_t *builtin);
QVM_API qvm_builtin_t *qvm_get_builtin(qvm_state_t *e, qvm_value_t value);

/*** 对象继承操作 ***/
QVM_API void qvm_set_parent(qvm_state_t *e, qvm_value_t value, qvm_value_t parent);
QVM_API qvm_value_t qvm_get_parent(qvm_state_t *e, qvm_value_t value);

/*** 模块操作 ***/
QVM_API void qvm_add_module(qvm_state_t *e, const char *name, qvm_value_t value);
QVM_API qvm_value_t qvm_get_module(qvm_state_t *e, const char *name);
QVM_API void qvm_del_module(qvm_state_t *e, const char *name);

/*** 数组对象操作 ***/
QVM_API void qvm_del_array(qvm_state_t *e, qvm_value_t object, int index);
QVM_API void qvm_set_array(qvm_state_t *e, qvm_value_t object, int index, qvm_value_t value);
QVM_API int qvm_has_array(qvm_state_t *e, qvm_value_t object, int i);
QVM_API qvm_value_t qvm_get_array(qvm_state_t *e, qvm_value_t object, int index);
QVM_API qvm_value_t qvm_new_array(qvm_state_t *e);
QVM_API int qvm_get_array_length(qvm_state_t *e, qvm_value_t object);
QVM_API void qvm_set_array_length(qvm_state_t *e, qvm_value_t object, int length);

/*** 虚拟机API ***/
QVM_API void qvm_set_ops(qvm_state_t *e, qvm_ops_t *ops);
QVM_API void qvm_gc_pause(qvm_state_t *e);
QVM_API void qvm_gc_resume(qvm_state_t *e);
QVM_API void qvm_gc_ref(qvm_state_t *e, qvm_value_t object);
QVM_API void qvm_gc_deref(qvm_state_t *e, qvm_value_t object);
QVM_API qvm_value_t qvm_get_current_scope(qvm_state_t *e);
QVM_API qvm_value_t qvm_call(qvm_state_t *e, qvm_value_t object, qvm_value_t pthis, int argc, qvm_value_t *v);
QVM_API int qvm_set_ref(qvm_state_t *e, qvm_value_t value);
QVM_API qvm_value_t qvm_get_ref(qvm_state_t *e, int idx);
QVM_API void qvm_clear_ref(qvm_state_t *e, int idx);
QVM_API qvm_value_t qvm_parse_bc(qvm_state_t *e, const char *path);
QVM_API int qvm_init(qvm_state_t *e, int stack_size, int ref_size);
QVM_API void qvm_deinit(qvm_state_t *e);
QVM_API void qvm_gc(qvm_state_t *e);
QVM_API qvm_value_t qvm_global(qvm_state_t *e);
QVM_API qvm_value_t qvm_get_global(qvm_state_t *e, const char *name);
QVM_API void qvm_del_global(qvm_state_t *e, const char *name);
QVM_API void qvm_add_global(qvm_state_t *e, const char *name, qvm_value_t value);
QVM_API void qvm_add_native(qvm_state_t *e, const char *name, qvm_native_t native);
QVM_API void qvm_def_global(qvm_state_t *e, const char *name, qvm_value_t value, int flag);
QVM_API uint8_t *qvm_read_file(qvm_state_t *e, const char *path);

/*** 添加扩展函数，用于实现不同语言内部语法功能 ***/
QVM_API void qvm_add_extension(qvm_state_t *e, const char *name, qvm_value_t value);

/*** 字符串常量操作 ***/
QVM_API qvm_hash_t qvm_strpool_append(qvm_state_t *e, const char *str, int alloc);

/*** 虚拟机栈操作 ***/
QVM_API qvm_value_t *qvm_save_sp(qvm_state_t *e);
QVM_API void qvm_restore_sp(qvm_state_t *e, qvm_value_t *sp);
QVM_API void qvm_push(qvm_state_t *e, qvm_value_t value);
QVM_API qvm_value_t qvm_pop(qvm_state_t *e);

/*** 字节数组对象操作 ***/
QVM_API int qvm_get_bufferlen(qvm_state_t *e, qvm_value_t value);
QVM_API uint8_t *qvm_to_buffer(qvm_state_t *e, qvm_value_t value);
QVM_API qvm_value_t qvm_new_buffer(qvm_state_t *e, uint8_t *buf, int len);

/*** 异常错误操作 ***/
QVM_API void qvm_throw(qvm_state_t *e, qvm_value_t value);
QVM_API void *qvm_savetrypc(qvm_state_t *e);
QVM_API qvm_value_t qvm_error(qvm_state_t *e, const char *message);
QVM_API void qvm_report(qvm_state_t *e, qvm_value_t error);

/*** 字符编码 ***/
QVM_API int	qvm_char_to_unicode(unicode_t *rune, const char *str);
QVM_API int	qvm_unicode_to_char(char *str, const unicode_t *rune);
QVM_API unicode_t qvm_to_lower_unicode(unicode_t c);
QVM_API unicode_t qvm_to_upper_unicode(unicode_t c);
QVM_API int	qvm_unicode_len(int c);

/*** utils ***/
double qvm_string_to_float(const char *s, char **p);
int	qvm_utf_len(const char *s);

#if defined (WIN32) || defined (WIN64)
#define qvm_setjmp __builtin_setjmp
#define qvm_longjmp __builtin_longjmp
#define qvm_try(e) __builtin_setjmp(qvm_savetrypc(e))
#else
#define qvm_try(e) setjmp(qvm_savetrypc(e))
#define qvm_setjmp setjmp
#define qvm_longjmp longjmp
#endif

#define QVM_ASSERT(x) \
  do \
  { \
    if (!(x)) \
    { \
      qvm_assert(#x, __FILE__, __func__, __LINE__); \
    } \
  } while (0)

extern qvm_value_t qvm_undefined;
#define QVM_TRUE        qvm_mk_boolean(1)
#define QVM_FALSE       qvm_mk_boolean(0)
#define QVM_NULL        qvm_mk_null()
#define QVM_UNDEFINED   qvm_mk_undefined()

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

