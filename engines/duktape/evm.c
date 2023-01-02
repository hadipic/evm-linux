#include "evm.h"
#include "duk_api_internal.h"
#include "duk_js.h"


evm_val_t evm_string_create(evm_t *e, const char *str) {
    duk_push_string(e, str);
    return *duk_get_tval(e, -1);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    duk_push_tval(e, &o);
    duk_size_t len = duk_get_length(e, -1);
    duk_pop(e);
    return (int)len;
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    void *p = duk_push_fixed_buffer_zero(e, len);
    memcpy(p, buf, len);
    return *duk_get_tval(e, -1);
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    duk_size_t sz;
    duk_push_tval(e, &o);
    void *buf = duk_to_fixed_buffer(e, -1, &sz);
    duk_pop(e);
    return buf;
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    duk_size_t sz;
    duk_push_tval(e, &o);
    duk_to_fixed_buffer(e, -1, &sz);
    duk_pop(e);
    return (int)sz;
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    duk_push_array(e);
    return *duk_get_tval(e, -1);
}

int evm_list_len(evm_t *e, evm_val_t o) {
    duk_push_tval(e, &o);
    duk_size_t len = duk_get_length(e, -1);
    duk_pop(e);
    return (int)len;
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    duk_push_tval(e, &o);
    duk_idx_t idx = duk_get_top_index_unsafe(e);
    duk_push_tval(e, &v);
    duk_put_prop_index(e, idx, i);
    duk_pop(e);
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    duk_push_tval(e, &o);
    duk_idx_t idx = duk_get_top_index_unsafe(e);
    duk_get_prop_index(e, idx, i);
    evm_val_t res = *duk_get_tval(e, -1);
    duk_pop_2(e);
    duk_push_tval(e, &res);
    return res;
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    duk_push_object(e);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    duk_idx_t idx = duk_push_object(e);
    duk_push_pointer(e, data);
    duk_put_prop_string(e, idx, ".data");
    return *duk_get_tval(e, -1);
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    duk_push_tval(e, &o);
    duk_push_pointer(e, data);
    duk_put_prop_string(e, -2, ".data");
    duk_pop(e);
}

void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    duk_push_tval(e, &o);
    duk_get_prop_string(e, -1, ".data");
    void *res = duk_to_pointer(e, -1);
    duk_pop(e);
    return res;
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    duk_get_global_string(e, key);
    return *duk_get_tval(e, -1);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    duk_push_tval(e, &v);
    duk_put_global_string(e, key);
    duk_pop(e);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {
    duk_push_global_object(e);
    duk_del_prop_string(e, -1, key);
    duk_pop(e);
}

/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    duk_push_tval(e, &o);
    duk_get_prop_string(e, -1, key);
    evm_val_t res = *duk_get_tval(e, -1);
    duk_pop(e);
    duk_push_tval(e, &res);
    return *duk_get_tval(e, -1);
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    duk_push_tval(e, &o);
    duk_push_tval(e, &v);
    duk_put_prop_string(e, -2, key);
    duk_pop_2(e);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key){
    duk_push_tval(e, &o);
    duk_del_prop_string(e, -1, key);
    duk_pop(e);
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
    evm_val_free(e, system);
    evm_val_t res = evm_prop_get(e, system, name);
    return res;
}

/*** 其它操作函数 ***/
void evm_heap_gc(evm_t *e) {
    duk_gc(e, 0);
}

void evm_throw(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    duk_throw(e);
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
    buffer = evm_malloc(sizeof(uint8_t)*lSize + 1);
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

evm_t *evm_init(void) {
    duk_context *ctx = duk_create_heap_default();
    evm_global_set(ctx, "@system", evm_object_create(ctx));
    duk_push_undefined(ctx);
    return ctx;
}

void evm_deinit(evm_t *e) {
    if( e ) {
        duk_destroy_heap(e);
    }
}

int evm_run_file(evm_t *e, evm_val_t this_obj, const char *path) {
    char *buf = open(path);
    if( !buf )
        return 0;
    duk_eval_string_noresult(e, buf);
    evm_free(buf);
    return 1;
}

evm_val_t evm_run_string(evm_t *e, evm_val_t this_obj, const char *source) {
    void *buf = open(source);
    duk_eval_string(e, buf);
    evm_free(buf);
    return *duk_get_tval(e, -1);
}

void evm_run_shell(evm_t *e) {
#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
    evm_run_repl(e);
#endif
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    if(evm_is_undefined(e, pthis) ){
        duk_push_tval(e, &obj);
        for(int i = 0; i < argc; i++){
            duk_push_tval(e, v + i);
        }
        duk_call(e, argc);
        return *duk_get_tval(e, -1);
    } else {
        duk_push_tval(e, &obj);
        duk_push_tval(e, &pthis);
        for(int i = 0; i < argc; i++){
            duk_push_tval(e, v + i);
        }
        duk_call_method(e, argc);
        return *duk_get_tval(e, -1);
    }
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t res = evm_call(e, obj, pthis, argc, v);
    evm_val_free(e, res);
    return res;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    return duk_js_tonumber(e, &v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return duk_js_toint32(e, &v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    EVM_UNUSED(e);
    return (int)duk_js_toboolean(&v);
}

const char *evm_2_string(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    const char *str = duk_to_string(e, -1);
    duk_pop(e);
    return str;
}

int evm_is_number(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_number(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_number(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_string(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_string(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_boolean(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_buffer(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_native(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_c_function(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_callable(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_list(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_array(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_undefined(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_null(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_null(e, -1);
    duk_pop(e);
    return res;
}

int evm_is_object(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    int res = (int)duk_is_object(e, -1);
    duk_pop(e);
    return res;
}

evm_val_t evm_mk_number(evm_t *e, double d){
    duk_push_number(e, d);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    duk_push_string(e, s);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    duk_push_lstring(e, s, len);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    duk_push_boolean(e, v);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    duk_push_c_function(e, v, len);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_null(evm_t *e){
    duk_push_null(e);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_undefined(evm_t *e){
    duk_push_undefined(e);
    return *duk_get_tval(e, -1);
}

void evm_val_free(evm_t *e, evm_val_t v) {
    duk_pop(e);
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    duk_push_tval(e, &v);
    return *duk_get_tval(e, -1);
}

evm_val_t evm_mk_global(evm_t *e) {
    duk_push_global_object(e);
    return *duk_get_tval(e, -1);
}
