/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm.h"

evm_val_t evm_string_create(evm_t *e, const char *str) {
    return ts_new_string(e, str);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    return ts_get_length(e, o);
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    return ts_new_bytes(e, buf, len);
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    return ts_to_bytes(e, o);
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    return ts_get_length(e, o);
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    return ts_new_array(e);
}

int evm_list_len(evm_t *e, evm_val_t o) {
    return ts_get_length(e, o);
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    ts_set_array(e, o, i, v);
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    return ts_get_array(e, o, i);
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    return ts_new_object(e);
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    ts_value_t res = ts_new_object(e);
    ts_add_property(e, res, ".user_data", ts_mk_invoke(data));
    return res;
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    ts_add_property(e, o, ".user_data", ts_mk_invoke(data));
}

void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    ts_value_t res = ts_get_property(e, o, ".user_data");
    return ts_to_invoke(e, res);
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    return ts_get_global(e, key);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    ts_add_global(e, key, v);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {

}

/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    return ts_get_property(e, o, key);
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    ts_add_property(e, o, key, v);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key){

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
    ts_gc(e);
}

void evm_throw(evm_t *e, evm_val_t v) {
    ts_throw(e, v);
}

/*** 虚拟机相关函数 ***/
int fs_size(void * handle)
{
    FILE *file = (void*)handle;
    fseek (file , 0 , SEEK_END);
    int lSize = ftell (file);
    rewind (file);
    return lSize;
}

char * open(char *filename){
    FILE *file;
    size_t result;
    uint32_t lSize;
    char *buffer = NULL;

    file = fopen(filename, "rb");
    if (file == NULL)
        return NULL;
    lSize = fs_size(file);
    buffer = ts_malloc(sizeof(uint8_t)*lSize + 1);
    memset(buffer, 0, lSize + 1);
    result = fread(buffer, 1, lSize, file);
    if (result != lSize ){
        fclose(file);
        return NULL;
    }
    buffer[lSize] = 0;
    fclose(file);
    return buffer;
}

void *ts_malloc(size_t size) {
    return malloc(size);
}

void *ts_realloc(void *ptr, size_t size) {
    return realloc(ptr, size);
}

void ts_free(void *ptr) {
    if(ptr)
        free(ptr);
}

ts_value_t native_show(evm_t *e, ts_value_t p, int argc, ts_value_t *v) {
    printf("stack usage: %ld B\r\n", ((intptr_t)e->sp - (intptr_t)e->sp_base));
    return EVM_UNDEFINED;
}

ts_value_t native_require(evm_t *e, ts_value_t p, int argc, ts_value_t *v) {
    return evm_module_get(e, ts_to_string(e, v[0]));
}

evm_t *evm_init(void) {
    evm_t *e = ts_malloc(sizeof (evm_t));
    ts_init(e, TS_STACK_SIZE);
    evm_global_set(e, "@system", evm_object_create(e));
    ts_add_native(e, "show", native_show);
    ts_add_native(e, "require", native_require);
    return e;
}

void evm_deinit(evm_t *e) {
    if( e ) {

    }
}

int evm_run_file(evm_t *e, evm_val_t this_obj, const char *path) {
    if( this_obj == EVM_UNDEFINED )
        this_obj = ts_new_object(e);
    uint8_t *buf = open(path);
    if( !buf )
        return 0;
    evm_val_t obj = ts_parse_executable(e, buf, this_obj);
    evm_free(buf);
    ts_call(e, obj, this_obj, 0, NULL);
    return 1;
}

evm_val_t evm_run_string(evm_t *e, evm_val_t this_obj, const char *source) {
    return EVM_UNDEFINED;
}

void evm_run_shell(evm_t *e) {
#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
    evm_run_repl(e);
#endif
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    return ts_call(e, obj, pthis, argc, v);
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t res = evm_call(e, obj, pthis, argc, v);
    evm_val_free(e, res);
    return res;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    return ts_to_number(e, v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return (int32_t)ts_to_number(e, v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return ts_to_boolean(e, v);
}

const char *evm_2_string(evm_t *e, evm_val_t v) {
    return ts_to_string(e, v);
}

int evm_is_number(evm_t *e, evm_val_t v) {
    return ts_is_number(&v);
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    return ts_is_integer(&v);
}

int evm_is_invoke(evm_t *e, evm_val_t v) {
    return ts_is_invoke(&v);
}

int evm_is_string(evm_t *e, evm_val_t v) {
    return ts_is_string(&v);
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    return ts_is_boolean(&v);
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    return ts_is_bytes(&v);
}

int evm_is_native(evm_t *e, evm_val_t v) {
    return ts_is_native(&v);
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    return ts_is_script(&v) || ts_is_native(&v);
}

int evm_is_list(evm_t *e, evm_val_t v) {
    return ts_is_array(&v);
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    return ts_is_undefined(&v);
}

int evm_is_null(evm_t *e, evm_val_t v) {
    return ts_is_null(&v);
}

int evm_is_object(evm_t *e, evm_val_t v) {
    return ts_is_object(&v);
}

evm_val_t evm_mk_number(evm_t *e, double d){
    return ts_mk_number(d);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    return ts_new_string(e, s);
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    return ts_new_lstring(e, s, len);
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    return ts_mk_boolean(v);
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    return ts_new_native(e, v);
}

evm_val_t evm_mk_null(evm_t *e){
    return ts_mk_null();
}

evm_val_t evm_mk_undefined(evm_t *e){
    return VAL_UNDEFINED;
}

void evm_val_free(evm_t *e, evm_val_t v) {

}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    return v;
}

evm_val_t evm_mk_global(evm_t *e) {
    return ts_mk_object(e->global);
}

void ts_assert(const char *assertion, const char *file, const char *function, const uint32_t line){
    printf ("AssertionError: '%s' failed at %s(%s):%lu.\n",
                       assertion,
                       file,
                       function,
                       (unsigned long) line);

    while(1);
}

evm_val_t evm_mk_invoke(evm_t *e, void *user_data) {
    return ts_mk_invoke(user_data);
}

void *evm_2_invoke(evm_t *e, evm_val_t o) {
    return ts_to_invoke(e, o);
}
