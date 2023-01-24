/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm.h"
#include "PikaStdData.h"
#include "PikaStdData_List.h"
#include "PikaStdData_Dict.h"
#include "PikaStdData_String.h"
#include "PikaStdLib_SysObj.h"
#include "PikaVM.h"
#include "pikaScript.h"

Arg _evm_pika_undefined;

evm_val_t evm_string_create(evm_t *e, const char *str) {

}

int evm_string_len(evm_t *e, evm_val_t o) {

}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {

}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {

}

int evm_buffer_len(evm_t *e, evm_val_t o) {

}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {

}

int evm_list_len(evm_t *e, evm_val_t o) {

}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {

}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {

}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {

}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {

}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {

}
void *evm_object_get_user_data(evm_t *e, evm_val_t o) {

}

evm_val_t evm_global_get(evm_t *e, const char* key) {

}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {

}

void evm_global_delete(evm_t *e, const char *key) {

}


/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {

}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key) {

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

}

void evm_throw(evm_t *e, evm_val_t v) {

}

/*** 虚拟机相关函数 ***/
volatile PikaObj *__pikaMain;
evm_t *evm_init(void) {
    PikaObj* pikaMain = newRootObj("pikaMain", New_PikaMain);
    __pikaMain = pikaMain;
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(pikaMain, pikaModules_py_a);
    return pikaMain;
}

void evm_deinit(evm_t *e) {

}

void evm_run_file(evm_t *e, const char *path) {
    size_t len = strlen(path);
    if(path[len - 2] == '.' && path[len - 1] == 'o') {
        pikaVM_runByteCodeFile(e, (char*)path);
    } else {
        pikaVM_runFile(e, (char*)path);
    }
}

evm_val_t evm_run_string(evm_t *e, const char *source) {
    pikaVM_run(e, (char*)source);
}

void evm_run_shell(evm_t *e) {
    pikaScriptShell(e);
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {

}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {

}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {

}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {

}

int evm_2_boolean(evm_t *e, evm_val_t v) {

}

const char *evm_2_string(evm_t *e, evm_val_t v) {

}

int evm_is_number(evm_t *e, evm_val_t v) {

}

int evm_is_integer(evm_t *e, evm_val_t v) {

}

int evm_is_string(evm_t *e, evm_val_t v) {

}

int evm_is_boolean(evm_t *e, evm_val_t v) {

}

int evm_is_buffer(evm_t *e, evm_val_t v) {

}

int evm_is_native(evm_t *e, evm_val_t v) {

}

int evm_is_callable(evm_t *e, evm_val_t v) {

}

int evm_is_list(evm_t *e, evm_val_t v) {

}

int evm_is_undefined(evm_t *e, evm_val_t v) {

}

int evm_is_null(evm_t *e, evm_val_t v) {

}

int evm_is_object(evm_t *e, evm_val_t v) {

}

evm_val_t evm_mk_number(evm_t *e, double d){

}

evm_val_t evm_mk_string(evm_t *e, const char *s){

}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {

}

evm_val_t evm_mk_boolean(evm_t *e, int v){

}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {

}

evm_val_t evm_mk_null(evm_t *e){

}

evm_val_t evm_mk_undefined(evm_t *e){

}

void evm_val_free(evm_t *e, evm_val_t v) {

}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {

}

evm_val_t evm_mk_global(evm_t *e) {

}

