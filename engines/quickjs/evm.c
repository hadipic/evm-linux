/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm.h"
#include "quickjs-libc.h"
#include "cutils.h"

#define PATH_MAX 256

evm_val_t evm_string_create(evm_t *e, const char *str) {
    return JS_NewString(e, str);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    if( !evm_is_string(e, o) )
        return 0;
    const char *s = JS_ToCString(e, o);
    return strlen(s);
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    return JS_NewArrayBufferCopy(e, buf, len);
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
    return JS_NewArray(e);
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

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    if( !evm_is_list(e, o) ) {
        return JS_UNDEFINED;
    }
    return JS_GetPropertyUint32(e, o, i);
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    return JS_NewObject(e);
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

void evm_throw(evm_t *e, evm_val_t v) {
    JS_Throw(e, v);
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

evm_t *evm_init(void) {
    JSRuntime *rt;
    JSContext *ctx;
    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);
    if (!ctx) {
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return NULL;
    }
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
    evm_global_set(ctx, "@system", evm_object_create(ctx));
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
        ret = JS_Eval(e, buf, buf_len, path, JS_EVAL_TYPE_MODULE);
    else
        ret = JS_EvalThis(e, this_obj, buf, buf_len, path, JS_EVAL_TYPE_GLOBAL);
    js_free(e, (void *)buf);
    if( JS_IsException(ret) ) {
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

const char *evm_2_string(evm_t *e, evm_val_t v) {
    const char* ret = JS_ToCString(e, v);
    JS_FreeCString(e, ret);
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

evm_val_t evm_mk_number(evm_t *e, double d){
    return JS_NewFloat64(e, d);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    evm_val_t res;
    res = JS_NewString(e, s);
    return res;
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    evm_val_t res;
    res = JS_NewStringLen(e, s, len);
    return res;
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    evm_val_t res;
    res = JS_MKVAL(JS_TAG_BOOL, v);
    return res;
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    JSContext *ctx = e;
    JSValue nfunc = JS_NewCFunction(ctx, v, name, len);
    return nfunc;
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
