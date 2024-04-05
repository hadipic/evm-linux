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
#include "evm.h"
#include "quickjs-libc.h"
#include "cutils.h"

#define PATH_MAX 256

int (*evm_print)(const char *fmt, ...) = printf;

evm_val_t evm_string_create(evm_t *e, const char *str) {
    return evm_val_duplicate(e, JS_NewString(e, str));
}

int evm_string_len(evm_t *e, evm_val_t o) {
    if( !evm_is_string(e, o) )
        return 0;
    size_t size;
    const char *s = JS_ToCStringLen(e, &size, o);
    JS_FreeCString(e, s);
    return size;
}

void evm_string_free(evm_t *e, char *str){
    JS_FreeCString(e, str);
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    return evm_val_duplicate(e, JS_NewArrayBufferCopy(e, buf, len));
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    size_t size;
    return JS_GetArrayBuffer(e, &size, o);
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    size_t size;
    JS_GetArrayBuffer(e, &size, o);
    return size;
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    return evm_val_duplicate(e, JS_NewArray(e));
}

int evm_list_len(evm_t *e, evm_val_t o) {
    JSContext *ctx = e;
    int32_t pres = 0;
    JSValue len_val;
    len_val = JS_GetPropertyStr(ctx, o, "length");
    if (JS_IsException(len_val)) {
        pres = 0;
        return -1;
    }
    JS_ToInt32(ctx, &pres, len_val);
    JS_FreeValue(ctx, len_val);
    return pres;
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    JS_SetPropertyUint32(e, o, i, v);
    return ec_ok;
}

evm_err_t evm_list_set_with_free(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    JS_SetPropertyUint32(e, o, i, v);
    evm_val_free(e, v);
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    if( !evm_is_list(e, o) ) {
        return JS_UNDEFINED;
    }
    return JS_GetPropertyUint32(e, o, i);
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    return evm_val_duplicate(e, JS_NewObject(e));
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    evm_val_t res = evm_object_create(e);
    JS_SetOpaque(res, data);
    return res;
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    JS_SetOpaque(o, data);
}

void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    return JS_GetOpaque(o, 1);
}

evm_val_t evm_object_keys(evm_t *e, evm_val_t o) {
    JSPropertyEnum *tab;
    uint32_t len, i;
    if (JS_GetOwnPropertyNames(e, &tab, &len, o, JS_GPN_STRING_MASK | JS_GPN_ENUM_ONLY) < 0)
        return EVM_UNDEFINED;
    const char *key;
    evm_val_t list = evm_list_create(e);
    for(i = 0; i < len; i++) {
        key = JS_AtomToCString(e, tab[i].atom);
        evm_val_t val = evm_string_create(e, key);
        evm_list_set(e, list, i, val);
        evm_string_free(e, key);
        evm_val_free(e, val);
    }
    return list;
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    JSContext *ctx = e;
    JSValue global_obj;
    global_obj = JS_GetGlobalObject(ctx);
    JSValue value = JS_GetPropertyStr(ctx, global_obj, key);
    evm_val_free(e, global_obj);
    return value;
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    JSContext *ctx = e;
    JSValue global_obj;
    global_obj = JS_GetGlobalObject(ctx);
    JS_SetPropertyStr(ctx, global_obj, key, v);
    evm_val_free(e, global_obj);
    return ec_ok;
}

evm_err_t evm_global_set_with_free(evm_t *e, const char *key, evm_val_t v) {
    JSContext *ctx = e;
    JSValue global_obj;
    global_obj = JS_GetGlobalObject(ctx);
    JS_SetPropertyStr(ctx, global_obj, key, v);
    evm_val_free(e, global_obj);
    evm_val_free(e, v);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {

}

/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    return JS_GetPropertyStr(e, o, key);
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    JS_SetPropertyStr(e, o, key, v);
    return ec_ok;
}

evm_err_t evm_prop_set_with_free(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    JS_SetPropertyStr(e, o, key, v);
    evm_val_free(e, v);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key){

}

/*** 模块操作函数 ***/
evm_err_t evm_module_add(evm_t *e, const char* name, evm_val_t v) {
    evm_global_set(e, name, v);
    return ec_ok;
}

evm_val_t evm_module_get(evm_t *e, const char* name) {
    return evm_global_get(e, name);
}

/*** 其它操作函数 ***/
void evm_heap_gc(evm_t *e) {
    JS_RunGC(JS_GetRuntime(e));
}

evm_val_t evm_throw(evm_t *e, evm_val_t v) {
    return JS_Throw(e, v);
}

/*** 虚拟机相关函数 ***/
uint8_t *js_load_file(JSContext *ctx, size_t *pbuf_len, const char *filename)
{
    FILE *f;
    uint8_t *buf;
    size_t buf_len;
    long lret;

    f = fopen(filename, "rb");
    if (!f)
        return NULL;
    if (fseek(f, 0, SEEK_END) < 0)
        goto fail;
    lret = ftell(f);
    if (lret < 0)
        goto fail;

    buf_len = lret;
    if (fseek(f, 0, SEEK_SET) < 0)
        goto fail;
    if (ctx)
        buf = js_malloc(ctx, buf_len + 1);
    else
        buf = malloc(buf_len + 1);
    if (!buf)
        goto fail;
    if (fread(buf, 1, buf_len, f) != buf_len) {
        if (ctx)
            js_free(ctx, buf);
        else
            free(buf);
    fail:
        fclose(f);
        return NULL;
    }
    buf[buf_len] = '\0';
    fclose(f);
    *pbuf_len = buf_len;
    return buf;
}

int js_module_set_import_meta(JSContext *ctx, JSValueConst func_val,
                              JS_BOOL use_realpath, JS_BOOL is_main)
{
    JSModuleDef *m;
    char buf[PATH_MAX + 16];
    JSValue meta_obj;
    JSAtom module_name_atom;
    const char *module_name;

    EVM_ASSERT(JS_VALUE_GET_TAG(func_val) == JS_TAG_MODULE);
    m = JS_VALUE_GET_PTR(func_val);

    module_name_atom = JS_GetModuleName(ctx, m);
    module_name = JS_AtomToCString(ctx, module_name_atom);
    JS_FreeAtom(ctx, module_name_atom);
    if (!module_name)
        return -1;
    if (!strchr(module_name, ':')) {
        strcpy(buf, "file://");
#if !defined(_WIN32)
        /* realpath() cannot be used with modules compiled with qjsc
           because the corresponding module source code is not
           necessarily present */
        if (use_realpath) {
            char *res = realpath(module_name, buf + strlen(buf));
            if (!res) {
                JS_ThrowTypeError(ctx, "realpath failure");
                JS_FreeCString(ctx, module_name);
                return -1;
            }
        } else
#endif
        {
            pstrcat(buf, sizeof(buf), module_name);
        }
    } else {
        pstrcpy(buf, sizeof(buf), module_name);
    }
    JS_FreeCString(ctx, module_name);

    meta_obj = JS_GetImportMeta(ctx, m);
    if (JS_IsException(meta_obj))
        return -1;
    JS_DefinePropertyValueStr(ctx, meta_obj, "url",
                              JS_NewString(ctx, buf),
                              JS_PROP_C_W_E);
    JS_DefinePropertyValueStr(ctx, meta_obj, "main",
                              JS_NewBool(ctx, is_main),
                              JS_PROP_C_W_E);
    JS_FreeValue(ctx, meta_obj);
    return 0;
}

JSModuleDef *js_module_loader(JSContext *ctx,
                              const char *module_name, void *opaque)
{
    JSModuleDef *m;

    uint8_t *buf;
    JSValue func_val;
    size_t buf_len;
    buf = js_load_file(ctx, &buf_len, module_name);
    if (!buf) {
        JS_ThrowReferenceError(ctx, "could not load module filename '%s'",
                               module_name);
        return NULL;
    }
    /* compile the module */
    func_val = JS_Eval(ctx, (char *)buf, buf_len, module_name,
                       JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
    js_free(ctx, buf);
    if (JS_IsException(func_val))
        return NULL;
    /* XXX: could propagate the exception */
    js_module_set_import_meta(ctx, func_val, 1, 0);
    /* the module is already referenced, so we must free it */
    m = JS_VALUE_GET_PTR(func_val);
    JS_FreeValue(ctx, func_val);
    return m;
}

evm_val_t native_require(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    char *str = evm_2_string(e, v[0]);
    evm_val_t res = evm_module_get(e, str);
    evm_string_free(e, str);
    return res;
}

static void *js_trace_malloc(JSMallocState *s, size_t size)
{
    void *ptr;
    ptr = evm_malloc(size);
    if (ptr) {
        s->malloc_count++;
    }
    return ptr;
}

static void js_trace_free(JSMallocState *s, void *ptr)
{
    if (!ptr)
        return;
    s->malloc_count--;
    evm_free(ptr);
}

static void *js_trace_realloc(JSMallocState *s, void *ptr, size_t size)
{
    ptr = evm_realloc(ptr, size);
    return ptr;
}

static const JSMallocFunctions trace_mf = {
    js_trace_malloc,
    js_trace_free,
    js_trace_realloc,
    NULL
};

EVM_FUNCTION( native_print ){
    EVM_EPCV;
    for(int i = 0; i < argc;i++ ){
       char *s = evm_2_string(e, v[i]);
       printf("%s ", s);
       evm_string_free(e, s);
    }
    printf("\r\n");
    EVM_RETURN(evm_mk_undefined(e))
}

evm_t *evm_init(void) {
    JSRuntime *rt;
    JSContext *ctx;
    rt = JS_NewRuntime2(&trace_mf, NULL);
    ctx = JS_NewContext(rt);
    if (!ctx) {
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return NULL;
    }
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
    evm_val_t val = evm_object_create(ctx);
    evm_global_set(ctx, "@system", val);
    evm_val_free(ctx, val);
    evm_global_set(ctx, "require", evm_mk_native(ctx, native_require, "require", 1));
    evm_global_set(ctx, "print", evm_mk_native(ctx, native_print, "print", 1));
    return ctx;
}

void evm_deinit(evm_t *e) {
    if( e ) {
        JSContext *ctx = e;
        JSRuntime *rt = JS_GetRuntime(ctx);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
    }
}

static void js_dump_obj(JSContext *ctx, FILE *f, JSValueConst val)
{
    const char *str;

    str = JS_ToCString(ctx, val);
    if (str) {
        evm_print("%s\n", str);
        JS_FreeCString(ctx, str);
    } else {
        evm_print("[exception]\n");
    }
}

static void js_std_dump_error1(JSContext *ctx, JSValueConst exception_val)
{
    JSValue val;
    BOOL is_error;

    is_error = JS_IsError(ctx, exception_val);
    js_dump_obj(ctx, stderr, exception_val);
    if (is_error) {
        val = JS_GetPropertyStr(ctx, exception_val, "stack");
        if (!JS_IsUndefined(val)) {
            js_dump_obj(ctx, stderr, val);
        }
        JS_FreeValue(ctx, val);
    }
}

void js_std_dump_error(JSContext *ctx)
{
    JSValue exception_val;

    exception_val = JS_GetException(ctx);
    js_std_dump_error1(ctx, exception_val);
    JS_FreeValue(ctx, exception_val);
}

evm_val_t evm_run_bytecode(evm_t *e, uint8_t *buf, size_t buf_len) {
    JSValue obj, val;
    obj = JS_ReadObject(e, buf, buf_len, JS_READ_OBJ_BYTECODE);
    if (JS_IsException(obj))
        goto exception;
    if (JS_VALUE_GET_TAG(obj) == JS_TAG_MODULE) {
        if (JS_ResolveModule(e, obj) < 0) {
            JS_FreeValue(e, obj);
            goto exception;
        }
        js_module_set_import_meta(e, obj, FALSE, TRUE);
    }
    val = JS_EvalFunction(e, obj);
    if (JS_IsException(val)) {
    exception:
        js_std_dump_error(e);
        evm_print("eval bytecode failed!\n");
        return JS_UNDEFINED;
    }
    return val;
}

int evm_run_bytecode_file(evm_t *e, const char *path) {
    JSValue obj, val;
    size_t buf_len;
    uint8_t *buf = js_load_file(e, &buf_len, path);
    if (!buf) {
        return 0;
    }
    obj = JS_ReadObject(e, buf, buf_len, JS_READ_OBJ_BYTECODE);
    if (JS_IsException(obj))
        goto exception;
    if (JS_VALUE_GET_TAG(obj) == JS_TAG_MODULE) {
        if (JS_ResolveModule(e, obj) < 0) {
            JS_FreeValue(e, obj);
            goto exception;
        }
        js_module_set_import_meta(e, obj, FALSE, TRUE);
    }
    val = JS_EvalFunction(e, obj);
    if (JS_IsException(val)) {
    exception:
        js_std_dump_error(e);
        evm_print("eval bytecode failed!\n");
        return 0;
    }
    evm_val_free(e, val);
    return 1;
}

int evm_run_file(evm_t *e, evm_val_t this_obj, const char *path) {
    uint8_t *buf;
    size_t buf_len;
    int res = 1;
    buf = js_load_file(e, &buf_len, path);
    if (!buf) {
        return 0;
    }
    evm_val_t ret;
    if( evm_is_undefined(e, this_obj) )
        ret = JS_Eval(e, buf, buf_len, path, JS_EVAL_TYPE_GLOBAL);
    else
        ret = JS_EvalThis(e, this_obj, buf, buf_len, path, JS_EVAL_TYPE_GLOBAL);
    js_free(e, (void *)buf);
    if( JS_IsException(ret) ) {
        js_std_dump_error(e);
        res = 0;
    }
    evm_val_free(e, ret);
    return res;
}

evm_val_t evm_run_string(evm_t *e, evm_val_t this_obj, const char *source) {
    if( evm_is_undefined(e, this_obj) )
        return JS_Eval(e, source, strlen(source), "", JS_EVAL_TYPE_GLOBAL);
    else
        return JS_EvalThis(e, this_obj, source, strlen(source), "", JS_EVAL_TYPE_GLOBAL);
}

void evm_run_shell(evm_t *e) {
#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
    evm_run_repl(e);
#endif
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t ret =  JS_Call(e, obj, pthis, argc, v);
    if (JS_IsException(ret)){
        js_std_dump_error(e);
        return JS_UNDEFINED;
    }
    return ret;
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t res = evm_call(e, obj, pthis, argc, v);
    evm_val_free(e, res);
    return res;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    double ret;
    int flag = JS_ToFloat64(e, &ret, v);
    if (flag == 0){
        return ret;
    }
    return JS_VALUE_GET_FLOAT64(v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    int32_t ret;
    int flag = JS_ToInt32(e, &ret, v);
    if (flag == 0) {
        return ret;
    }
    return JS_VALUE_GET_INT(v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return JS_ToBool(e, v);
}

char *evm_2_string(evm_t *e, evm_val_t v) {
    char* ret = JS_ToCString(e, v);
    return ret;
}

int evm_is_number(evm_t *e, evm_val_t v) {
    (void)e;
    return JS_IsNumber(v);
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    (void)e;
    int tag = JS_VALUE_GET_TAG(v);
    return tag == JS_TAG_INT;
}

int evm_is_string(evm_t *e, evm_val_t v) {
    (void)e;
    return JS_IsString(v);
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    (void)e;
    return JS_IsBool(v);
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    size_t size;
    return JS_GetArrayBuffer(e, &size, v) != NULL;
}

int evm_is_native(evm_t *e, evm_val_t v) {
    return JS_IsFunction(e, v);
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    return JS_IsFunction(e, v);
}

int evm_is_invoke(evm_t *e, evm_val_t v) {
    if( !evm_is_object(e, v) )
        return 0;
    if( evm_object_get_user_data(e, v) == NULL )
        return 0;
    return 1;
}

int evm_is_list(evm_t *e, evm_val_t v) {
    return JS_IsArray(e, v);
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    (void)e;
    return JS_IsUndefined(v);
}

int evm_is_null(evm_t *e, evm_val_t v) {
    (void)e;
    return JS_IsNull(v);
}

int evm_is_object(evm_t *e, evm_val_t v) {
    (void)e;
    return JS_IsObject(v);
}

int evm_is_exception(evm_t *e, evm_val_t v) {
    JS_IsException(v);
}

evm_val_t evm_mk_number(evm_t *e, double d){
    return JS_NewFloat64(e, d);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    evm_val_t res;
    res = JS_NewString(e, s);
    return evm_val_duplicate(e, res);
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    evm_val_t res;
    res = JS_NewStringLen(e, s, len);
    return evm_val_duplicate(e, res);;
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    evm_val_t res;
    res = JS_MKVAL(JS_TAG_BOOL, v);
    return res;
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    JSContext *ctx = e;
    JSValue nfunc = JS_NewCFunction(ctx, v, name, len);
    return evm_val_duplicate(e, nfunc);
}

evm_val_t evm_mk_null(evm_t *e){
    return JS_NULL;
}

evm_val_t evm_mk_undefined(evm_t *e){
    return JS_UNDEFINED;
}

evm_val_t evm_mk_invoke(evm_t *e, void *user_data) {
    return evm_object_create_user_data(e, user_data);
}

void *evm_2_invoke(evm_t *e, evm_val_t o) {
    return evm_object_get_user_data(e, o);
}

void evm_val_free(evm_t *e, evm_val_t v) {
    JS_FreeValue(e, v);
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    return JS_DupValue(e, v);
}

evm_val_t evm_mk_global(evm_t *e) {
    JSContext *ctx = e;
    return JS_GetGlobalObject(ctx);
}

void evm_set_prototype(evm_t *e, evm_val_t obj, evm_val_t proto) {
    JS_SetPrototype(e, obj, proto);
}

int evm_is_constructor(evm_t *e, evm_val_t obj) {
    return JS_IsConstructor(e, obj);
}

evm_val_t evm_parse(evm_t *e) {

}
