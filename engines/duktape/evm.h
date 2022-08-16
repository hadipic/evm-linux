/****************************************************************************
**
** Copyright (C) 2022 @武汉市凡迈科技有限公司
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  Version	: 3.2
**  Email	: scriptiot@aliyun.com
**  Website	: https://gitee.com/scriptiot
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_H
#define EVM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "duktape.h"

enum Errcode
{
    ec_ok = 0,
    ec_err,
    ec_no_file,
    ec_file_name_len,
    ec_name,
    ec_type,
    ec_memory,
    ec_zero_division,
    ec_syntax,
    ec_index,
    ec_import,
    ec_attribute,
    ec_key,
    ec_value,
    ec_system,
    ec_assertion,
    ec_overflow,
    ec_arithmetic,
    ec_indent,
    ec_gc,
    ec_exit,
};

typedef js_State evm_t;
typedef js_Value evm_val_t;

#define EVM_API     extern
typedef int     evm_err_t;
typedef evm_val_t (*evm_native_t)(evm_t *e, evm_val_t pthis, int argc, evm_val_t *v);

/*** 字符串对象操作函数 ***/
EVM_API evm_val_t evm_string_create(evm_t *e, const char *str);
EVM_API int evm_string_len(evm_t *e, evm_val_t o);

/*** 字节数组对象操作函数 ***/
EVM_API evm_val_t evm_buffer_create(evm_t *e, int len);
EVM_API uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o);
EVM_API int evm_buffer_len(evm_t *e, evm_val_t o);

/*** 列表对象操作函数 ***/
EVM_API evm_val_t evm_list_create(evm_t *e);
EVM_API int evm_list_len(evm_t *e, evm_val_t o);
EVM_API evm_err_t evm_list_set(evm_t *e, evm_val_t o, int index, evm_val_t v);
EVM_API evm_val_t evm_list_get(evm_t *e, evm_val_t o, int index);

/*** 对象操作函数 ***/
EVM_API evm_val_t evm_object_create(evm_t *e);
EVM_API evm_val_t evm_object_create_user_data(evm_t *e, void *user_data);
EVM_API void *evm_object_get_user_data(evm_t *e, evm_val_t o);
EVM_API evm_val_t evm_global_get(evm_t *e, const char* key);
EVM_API evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v);

/*** 成员操作函数 ***/
EVM_API evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key);
EVM_API evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v);

/*** 模块操作函数 ***/
EVM_API evm_err_t evm_module_add(evm_t *e, const char* name, evm_val_t v);
EVM_API evm_val_t evm_module_get(evm_t *e, const char* name);

/*** 其它操作函数 ***/
EVM_API void evm_heap_gc(evm_t *e);
EVM_API void evm_throw(evm_t *e, evm_val_t v);

/*** 虚拟机相关函数 ***/
EVM_API evm_t *evm_init(void);
EVM_API void evm_deinit(evm_t *e);
EVM_API evm_val_t evm_load_file(evm_t *e, const char *path);
EVM_API evm_val_t evm_load_string(evm_t *e, const char *source);
EVM_API evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v);
EVM_API evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v);

/*** value操作 ***/
EVM_API double evm_2_double(evm_t *e, evm_val_t v);
EVM_API int32_t evm_2_integer(evm_t *e, evm_val_t v);
EVM_API int evm_2_boolean(evm_t *e, evm_val_t v);
EVM_API const char *evm_2_string(evm_t *e, evm_val_t v);

EVM_API int evm_is_number(evm_t *e, evm_val_t v);
EVM_API int evm_is_integer(evm_t *e, evm_val_t v);
EVM_API int evm_is_string(evm_t *e, evm_val_t v);
EVM_API int evm_is_boolean(evm_t *e, evm_val_t v);
EVM_API int evm_is_buffer(evm_t *e, evm_val_t v);
EVM_API int evm_is_native(evm_t *e, evm_val_t v);
EVM_API int evm_is_callable(evm_t *e, evm_val_t v);
EVM_API int evm_is_list(evm_t *e, evm_val_t v);
EVM_API int evm_is_undefined(evm_t *e, evm_val_t v);
EVM_API int evm_is_null(evm_t *e, evm_val_t v);
EVM_API int evm_is_object(evm_t *e, evm_val_t v);
EVM_API evm_val_t evm_mk_number(evm_t *e, double d);
EVM_API evm_val_t evm_mk_string(evm_t *e, const char *s);
EVM_API evm_val_t evm_mk_boolean(evm_t *e, int v);
EVM_API evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len);
EVM_API evm_val_t evm_mk_null(evm_t *e);
EVM_API evm_val_t evm_mk_undefined(evm_t *e);
EVM_API void evm_val_free(evm_t *e, evm_val_t v);

static inline void evm_assert_fail (const char *assertion, const char *file, const char *function, const int line){
    evm_print ("AssertionError: '%s' failed at %s(%s):%lu.\n",
                       assertion,
                       file,
                       function,
                       (unsigned long) line);

    while(1);
}

#define EVM_ASSERT(x) \
  do \
  { \
    if (!x) \
    { \
      evm_assert_fail (#x, __FILE__, __func__, __LINE__); \
    } \
  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
