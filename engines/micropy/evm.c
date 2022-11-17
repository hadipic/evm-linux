/*
 * This file is part of the Micropy project.
 *
 * Apache License
 *
 * Copyright (c) 2022 Zhe Wang zhewang_edmund@outlook.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "evm.h"

evm_val_t evm_string_create(evm_t *e, const char *str) {
    return upy_string_create(e, str);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    EVM_UNUSED(e);
    return upy_string_size(o);
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    return upy_buffer_create(e, buf, len);
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    EVM_UNUSED(e);
    return upy_2_buffer(o);
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    EVM_UNUSED(e);
    return upy_buffer_size(o);
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    return upy_array_create(e);
}

int evm_list_len(evm_t *e, evm_val_t o) {
    EVM_UNUSED(e);
    return upy_array_size(o);
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    upy_array_set(e, o, i, v);
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    return upy_array_get(e, o, i);
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    return upy_object_create(e);
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    evm_val_t o = upy_object_create(e);
    upy_object_set_user_data(o, data);
    return o;
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    upy_object_set_user_data(o, data);
}
void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    return upy_object_get_user_data(o);
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    return upy_global_get(e, key);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    upy_global_set(e, key, v);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {
    upy_global_delete(e, key);
}


/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    return upy_global_get_cs(e, key);
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    upy_object_set(e, o, key, v);
    evm_val_free(e, v);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key) {
    upy_object_delete(e, o, key);
}


/*** 模块操作函数 ***/
evm_err_t evm_module_add(evm_t *e, const char* name, evm_val_t v) {
    evm_val_t system = evm_global_get(e, "@system");
    evm_prop_set(e, system, name, v);
    evm_val_free(e, system);
    return ec_ok;
}

evm_val_t evm_module_get(evm_t *e, const char* name) {
    evm_val_t system = evm_global_get(e, "@system");
    evm_val_t res = evm_prop_get(e, system, name);
    evm_val_free(e, system);
    return res;
}

/*** 其它操作函数 ***/
void evm_heap_gc(evm_t *e) {
    upy_gc(e);
}

void evm_throw(evm_t *e, evm_val_t v) {
    upy_throw(e, v);
}

/*** 虚拟机相关函数 ***/
evm_t *evm_init(void) {
    evm_t *e = upy_init(1024);
    return e;
}

void evm_deinit(evm_t *e) {
    upy_deinit(e);
}

void evm_run_file(evm_t *e, const char *path) {
    evm_val_t o = upy_parse(e, path);
    upy_call(e, o, o, 0, NULL);
}

evm_val_t evm_run_string(evm_t *e, const char *source) {
    evm_val_t o = upy_parse_string(e, source);
    return upy_call(e, o, o, 0, NULL);
}

void evm_run_shell(evm_t *e) {
#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
    evm_run_repl(e);
#endif
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    return upy_call(e, obj, pthis, argc, v);
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t res = evm_call(e, obj, pthis, argc, v);
    return res;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    return upy_2_double(v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return upy_2_int32(v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return upy_2_boolean(v);
}

const char *evm_2_string(evm_t *e, evm_val_t v) {
    return upy_2_string(v);
}

int evm_is_number(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_number(v);
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_integer(v);
}

int evm_is_string(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_string(v);
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_boolean(v);
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    return upy_is_buffer(v);
}

int evm_is_native(evm_t *e, evm_val_t v) {
    return upy_is_buffer(v);
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_function(v) || upy_is_native(v);
}

int evm_is_list(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_array(v);
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_none(v);
}

int evm_is_null(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_none(v);
}

int evm_is_object(evm_t *e, evm_val_t v) {
    (void)e;
    return upy_is_object(v);
}

evm_val_t evm_mk_number(evm_t *e, double d){
    return evm_val_duplicate(e, upy_mk_number(d));
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    return evm_val_duplicate(e, upy_mk_string(s));
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    return upy_lstring_create(e, s, len);
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    return evm_val_duplicate(e, upy_mk_boolean(v));
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    return evm_val_duplicate(e, upy_mk_native(v));
}

evm_val_t evm_mk_null(evm_t *e){
    return evm_val_duplicate(e, upy_mk_none());
}

evm_val_t evm_mk_undefined(evm_t *e){
    return evm_val_duplicate(e, upy_mk_none());
}

void evm_val_free(evm_t *e, evm_val_t v) {
    EVM_UNUSED(v);
    upy_pop(e);
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    upy_push(e, v);
    return v;
}

evm_val_t evm_mk_global(evm_t *e) {
    return evm_val_duplicate(e, e->globals);
}


