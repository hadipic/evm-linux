/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
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
#include <stdarg.h>

#include "evm_type.h"

#define EVM_UNUSED(a)   (void)a
#define EVM_UNUSED2(a, b)   (void)a;(void)b;
#define EVM_UNUSED3(a, b, c)   (void)a;(void)b;(void)c;
#define EVM_UNUSED4(a, b, c, d)   (void)a;(void)b;(void)c;(void)d;

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

#define EVM_API     extern
typedef int     evm_err_t;

/*** 字符串对象操作函数 ***/
EVM_API evm_val_t evm_string_create(evm_t *e, const char *str);
EVM_API int evm_string_len(evm_t *e, evm_val_t o);

/*** 字节数组对象操作函数 ***/
EVM_API evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len);
EVM_API uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o);
EVM_API int evm_buffer_len(evm_t *e, evm_val_t o);

/*** 列表对象操作函数 ***/
EVM_API evm_val_t evm_list_create(evm_t *e);
EVM_API int evm_list_len(evm_t *e, evm_val_t o);
EVM_API evm_err_t evm_list_set(evm_t *e, evm_val_t o, int index, evm_val_t v);
EVM_API evm_err_t evm_list_set_with_free(evm_t *e, evm_val_t o, int i, evm_val_t v);
EVM_API evm_val_t evm_list_get(evm_t *e, evm_val_t o, int index);

/*** 对象操作函数 ***/
EVM_API evm_val_t evm_object_create(evm_t *e);
EVM_API evm_val_t evm_object_create_user_data(evm_t *e, void *data);
EVM_API void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data);
EVM_API void *evm_object_get_user_data(evm_t *e, evm_val_t o);
EVM_API evm_val_t evm_object_keys(evm_t *e, evm_val_t o);
EVM_API evm_val_t evm_global_get(evm_t *e, const char* key);
EVM_API evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v);
EVM_API evm_err_t evm_global_set_with_free(evm_t *e, const char *key, evm_val_t v);
EVM_API void evm_global_delete(evm_t *e, const char *key);

/*** 成员操作函数 ***/
EVM_API evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key);
EVM_API evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v);
EVM_API evm_err_t evm_prop_set_with_free(evm_t *e, evm_val_t o, const char *key, evm_val_t v);
EVM_API void evm_prop_delete(evm_t *e, evm_val_t o, const char *key);

/*** 模块操作函数 ***/
EVM_API evm_err_t evm_module_add(evm_t *e, const char* name, evm_val_t v);
EVM_API evm_val_t evm_module_get(evm_t *e, const char* name);

/*** 其它操作函数 ***/
EVM_API void evm_heap_gc(evm_t *e);
EVM_API void evm_set_prototype(evm_t *e, evm_val_t obj, evm_val_t proto);
EVM_API evm_val_t evm_throw(evm_t *e, evm_val_t v);
EVM_API evm_val_t evm_mk_global(evm_t *e);

/*** 虚拟机相关函数 ***/
EVM_API evm_t *evm_init(void);
EVM_API void evm_deinit(evm_t *e);
EVM_API int evm_run_file(evm_t *e, evm_val_t this_obj, const char *path);
EVM_API evm_val_t evm_run_string(evm_t *e, evm_val_t this_obj, const char *source);
EVM_API int evm_run_bytecode_file(evm_t *e, const char *path);
EVM_API evm_val_t evm_run_bytecode(evm_t *e, uint8_t *buf, size_t buf_len);
EVM_API void evm_run_shell(evm_t *e);
EVM_API evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v);
EVM_API evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v);
EVM_API void evm_register_print(int (*fn)(const char *fmt, ...));

/*** value操作 ***/
EVM_API double evm_2_double(evm_t *e, evm_val_t v);
EVM_API int32_t evm_2_integer(evm_t *e, evm_val_t v);
EVM_API int evm_2_boolean(evm_t *e, evm_val_t v);
EVM_API char *evm_2_string(evm_t *e, evm_val_t v);
EVM_API void evm_string_free(evm_t *e, char *str);
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
EVM_API int evm_is_invoke(evm_t *e, evm_val_t v);
EVM_API int evm_is_exception(evm_t *e, evm_val_t v);
EVM_API int evm_is_constructor(evm_t *e, evm_val_t obj);
EVM_API evm_val_t evm_mk_number(evm_t *e, double d);
EVM_API evm_val_t evm_mk_string(evm_t *e, const char *s);
EVM_API evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len);
EVM_API evm_val_t evm_mk_boolean(evm_t *e, int v);
EVM_API evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len);
EVM_API evm_val_t evm_mk_constructor(evm_t *e, evm_native_t v, const char *name, int len);
EVM_API evm_val_t evm_mk_null(evm_t *e);
EVM_API evm_val_t evm_mk_undefined(evm_t *e);
EVM_API evm_val_t evm_mk_invoke(evm_t *e, void *user_data);
EVM_API void *evm_2_invoke(evm_t *e, evm_val_t o);
EVM_API void evm_val_free(evm_t *e, evm_val_t v);
EVM_API evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v);

EVM_API uint8_t *evm_load_file(const char *filename, size_t *size);
EVM_API void *evm_malloc(size_t size);
EVM_API void *evm_realloc(void *p, size_t size);
EVM_API void evm_free(void *p);
EVM_API int (*evm_print)(const char *fmt, ...);

static inline void evm_assert_fail (const char *assertion, const char *file, const char *function, const int line){
    printf ("AssertionError: '%s' failed at %s(%s):%lu.\n",
                       assertion,
                       file,
                       function,
                       (unsigned long) line);

    while(1);
}

#define EVM_ASSERT(x) \
  do \
  { \
    if (!(x)) \
    { \
      evm_assert_fail (#x, __FILE__, __func__, __LINE__); \
    } \
  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
