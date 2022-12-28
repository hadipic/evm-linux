#include "evm.h"
#include "quickvm_js_parse.h"
#include "bget.h"

evm_val_t evm_string_create(evm_t *e, const char *str) {
    return qvm_new_string(e, str);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    return qvm_string_length(e, o);
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    return qvm_new_buffer(e, buf, len);
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    return qvm_to_buffer(e, o);
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    return qvm_get_bufferlen(e, o);
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    return qvm_new_array(e);
}

int evm_list_len(evm_t *e, evm_val_t o) {
    return qvm_get_array_length(e, o);
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    qvm_set_array(e, o, i, v);
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    return qvm_get_array(e, o, i);
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    return qvm_new_object(e);
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    qvm_value_t res = qvm_new_object(e);
    qvm_add_property(e, res, ".user_data", qvm_mk_invoke(data));
    return res;
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    qvm_add_property(e, o, ".user_data", qvm_mk_invoke(data));
}

void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    qvm_value_t res = qvm_get_property(e, o, ".user_data");
    if( !qvm_is_invoke(res) )
        return NULL;
    return qvm_to_invoke(e, res);
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    return qvm_get_global(e, key);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    qvm_add_global(e, key, v);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {
    qvm_del_global(e, key);
}

/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    return qvm_get_property(e, o, key);
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    qvm_add_property(e, o, key, v);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key){
    qvm_del_property(e, o, key);
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
    qvm_gc(e);
}

void evm_throw(evm_t *e, evm_val_t v) {
    qvm_throw(e, v);
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
    buffer = qvm_malloc(NULL, sizeof(uint8_t)*lSize + 1);
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

const char *qvm_open_file(qvm_state_t *e, const char *path) {
    return open(path);
}

static void *local_malloc(qvm_state_t *e, size_t size) {
    return bgetz(size);
}

static void *local_realloc(qvm_state_t *e, void *ptr, size_t size) {
    return bgetr(ptr, size);
}

static void local_free(qvm_state_t *e, void *ptr) {
    if(ptr)
        brel(ptr);
}

qvm_value_t native_show(qvm_state_t *e, qvm_value_t p, int argc, qvm_value_t *v) {
    long curalloc, totfree, maxfree;
    unsigned long nget, nrel;
    bstats(&curalloc, &totfree, &maxfree, &nget, &nrel);
    printf("stack usage: %ld B\r\n", ((intptr_t)e->sp - (intptr_t)e->sp_base));
    printf("mem info: used = %ld B, max used = %ld B, total = %ld B\r\n", curalloc, bstatsmaxget() , (curalloc + totfree) );
    return qvm_undefined;
}

evm_t *evm_init(void) {
    qvm_register_malloc(local_malloc);
    qvm_register_realloc(local_realloc);
    qvm_register_free(local_free);
    qvm_register_file_load(qvm_open_file);

    void *buf = malloc(QVM_MEM_SIZE);
    memset(buf, 0, QVM_MEM_SIZE);
    bpool(buf, QVM_MEM_SIZE);
    qvm_state_t *e = qvm_malloc(NULL, sizeof (qvm_state_t));
    qvm_init(e, QVM_STACK_SIZE, QVM_REF_SIZE);
    evm_global_set(e, "@system", evm_object_create(e));
    qvm_add_native(e, "show", native_show);
    return e;
}

void evm_deinit(evm_t *e) {
    if( e ) {

    }
}

evm_val_t evm_run_file(evm_t *e, const char *path) {
    evm_val_t obj = qvm_js_parse(e, path);
    qvm_value_t this = qvm_new_object(e);
    qvm_set_parent(e, obj, this);
    return qvm_call(e, obj, qvm_get_parent(e, obj), 0, NULL);
}

evm_val_t evm_run_string(evm_t *e, const char *source) {
    qvm_value_t res = qvm_js_parse_string(e, source);
    qvm_set_parent(e, res, e->root);
    return qvm_call(e, res, e->root, 0, NULL);
}

void evm_run_shell(evm_t *e) {
#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
    evm_run_repl(e);
#endif
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    return qvm_call(e, obj, pthis, argc, v);
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t res = evm_call(e, obj, pthis, argc, v);
    evm_val_free(e, res);
    return res;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    return qvm_to_number(e, v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return qvm_to_int32(e, v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return qvm_to_boolean(e, v);
}

const char *evm_2_string(evm_t *e, evm_val_t v) {
    return qvm_to_string(e, v);
}

int evm_is_number(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_number(v);
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_integer(v);
}

int evm_is_string(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_string(v);
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_boolean(v);
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_buffer(v);
}

int evm_is_native(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_native(v);
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_callable(v);
}

int evm_is_list(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_array(v);
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_undefined(v);
}

int evm_is_null(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_null(v);
}

int evm_is_object(evm_t *e, evm_val_t v) {
    QVM_UNUSED(e);
    return qvm_is_object(v);
}

evm_val_t evm_mk_number(evm_t *e, double d){
    QVM_UNUSED(e);
    return qvm_mk_number(d);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    return qvm_new_string(e, s);
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    return qvm_new_lstring(e, s, len);
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    QVM_UNUSED(e);
    return qvm_mk_boolean(v);
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    return qvm_mk_native(v);
}

evm_val_t evm_mk_null(evm_t *e){
    QVM_UNUSED(e);
    return qvm_mk_null();
}

evm_val_t evm_mk_undefined(evm_t *e){
    QVM_UNUSED(e);
    return qvm_mk_undefined();
}

void evm_val_free(evm_t *e, evm_val_t v) {
    qvm_gc_deref(e, v);
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    qvm_gc_ref(e, v);
    return v;
}

evm_val_t evm_mk_global(evm_t *e) {
    return e->root;
}

void qvm_assert(const char *assertion, const char *file, const char *function, const uint32_t line){
    printf ("AssertionError: '%s' failed at %s(%s):%lu.\n",
                       assertion,
                       file,
                       function,
                       (unsigned long) line);

    while(1);
}

int qvm_check_memory(qvm_state_t *e) {
    return 0;
    long curalloc, totfree, maxfree;
    unsigned long nget, nrel;
    bstats(&curalloc, &totfree, &maxfree, &nget, &nrel);

    float res = curalloc;
    return 100 * res / (curalloc + totfree);
}
