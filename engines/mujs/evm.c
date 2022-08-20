#include "evm.h"

evm_val_t evm_string_create(evm_t *e, const char *str) {
    js_pushstring(e, str);
    return *js_tovalue(e, -1);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    if( !evm_is_string(e, o) )
        return 0;
    return strlen(jsV_tostring(e, &o));
}

/*** 字节数组对象操作函数 ***/
typedef struct js_buffer_t {
    uint8_t *buf;
    int size;
} js_buffer_t;

static void buffer_Finalize(evm_t *e, void *p) {
    js_buffer_t *js_buf = p;
    js_free(e, js_buf->buf);
    js_free(e, js_buf);
}

evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    if( len == 0 )
        return evm_mk_undefined(e);
    js_newobject(e);
    js_buffer_t *js_buf = js_malloc(e, sizeof (js_buffer_t));
    EVM_ASSERT(js_buf);
    js_buf->buf = js_malloc(e, len);
    js_buf->size = len;
    if( buf != NULL )
        memcpy(js_buf->buf , buf, len);
    js_newuserdata(e, "", js_buf, buffer_Finalize);
    evm_val_t res = *js_tovalue(e, -1);
    evm_prop_set(e, res, "$isbuffer", evm_mk_boolean(e, 1));
    return res;
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    js_buffer_t *js_buf = evm_object_get_user_data(e, o);
    return js_buf->buf;
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    js_buffer_t *js_buf = evm_object_get_user_data(e, o);
    return js_buf->size;
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    js_newarray(e);
    evm_val_t obj = *js_tovalue(e, -1);
    evm_prop_set(e, obj, "length", evm_mk_number(e, 0));
    return obj;
}

int evm_list_len(evm_t *e, evm_val_t o) {
    int len = 0;
    js_Property *prop = jsV_getproperty(e, jsV_toobject(e, &o), "length");
    if( prop ) {
        len = (int)jsV_tointeger(e, &prop->value);
    }
	return len;
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    char buf[32];
    int len = evm_list_len(e, o);
    if( i >= len ) {
        evm_prop_set(e, o, "length", evm_mk_number(e, i + 1));
    }
    return evm_prop_set(e, o, js_itoa(buf, i), v);
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    if( !evm_is_list(e, o) ) {
        js_pushundefined(e);
        return *js_tovalue(e, -1);
    }
    char buf[32];
    js_Property *ref;
    ref = jsV_getproperty(e, jsV_toobject(e, &o), js_itoa(buf, i));
	if (ref) {
		js_pushvalue(e, ref->value);
        return ref->value;
	} else {
        js_pushundefined(e);
        return *js_tovalue(e, -1);
    }
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    js_newobject(e);
    return *js_tovalue(e, -1);
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    js_newobject(e);
    js_newuserdata(e, "", data, NULL);
    return *js_tovalue(e, -1);
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    js_Value *v = &o;
    if (v->type == JS_TOBJECT && v->u.object->type == JS_CUSERDATA)
        v->u.object->u.user.data = data;
}
void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    js_Value *v = &o;
    if (v->type == JS_TOBJECT && v->u.object->type == JS_CUSERDATA)
        return v->u.object->u.user.data;
    return NULL;
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    js_getglobal(e, key);
    return *js_tovalue(e, -1);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    EVM_UNUSED(v);
    js_setglobal(e, key);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {
    js_delglobal(e, key);
}


/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    if( !evm_is_object(e, o) ) {
        js_pushundefined(e);
        return *js_tovalue(e, -1);
    }
    js_Property *ref;
    ref = jsV_getproperty(e, jsV_toobject(e, &o), key);
    if (ref) {
        js_pushvalue(e, ref->value);
        return ref->value;
    } else {
        js_pushundefined(e);
        return *js_tovalue(e, -1);
    }
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    if( !evm_is_object(e, o) ) {
        evm_val_free(e, v);
        return ec_err;
    }
    js_Property *ref;
    ref = jsV_getproperty(e, jsV_toobject(e, &o), key);
	if (ref) {
        ref->value = v;
	} else {
        ref = jsV_setproperty(e, jsV_toobject(e, &o), key);
    }
    ref->value = v;
    evm_val_free(e, v);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key) {
    if( !evm_is_object(e, o) ) {
        return;
    }
    jsV_delproperty(e, jsV_toobject(e, &o), key);
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
    js_gc(e, 0);
}

void evm_throw(evm_t *e, evm_val_t v) {
    js_pushvalue(e, v);
    js_throw(e);
}

/*** 虚拟机相关函数 ***/
evm_t *evm_init(void) {
    evm_t *e = js_newstate(NULL, NULL, 0);
    js_newobject(e);
	js_setglobal(e, "@system");
    return e;
}

void evm_deinit(evm_t *e) {
    js_freestate(e);
}

evm_val_t evm_run_file(evm_t *e, const char *path) {
    js_loadfile(e, path);
    js_pushundefined(e);
    js_call(e, 0);
    return *js_tovalue(e, -1);
}

evm_val_t evm_run_string(evm_t *e, const char *source) {
    js_loadstring(e, "[string]", source);
    js_pushundefined(e);
    js_call(e, 0);
    return *js_tovalue(e, -1);
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    js_pushvalue(e, obj);
    js_pushvalue(e, pthis);
    for(int i = 0; i < argc; i++ ) {
        js_pushvalue(e, *(v + 1));
    }
    js_call(e, argc);
    evm_val_t res = *js_tovalue(e, -1);
    js_pop(e, 1 + argc);
    js_pushvalue(e, res);
    return res;
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t res = evm_call(e, obj, pthis, argc, v);
    return res;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    return jsV_tonumber(e, &v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return (int32_t)jsV_tointeger(e, &v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return jsV_toboolean(e, &v);
}

const char *evm_2_string(evm_t *e, evm_val_t v) {
    return jsV_tostring(e, &v);
}

int evm_is_number(evm_t *e, evm_val_t v) {
    (void)e;
    return v.type == JS_TNUMBER;
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    (void)e;
    return v.type == JS_TNUMBER;
}

int evm_is_string(evm_t *e, evm_val_t v) {
    (void)e;
    enum js_Type t = v.type; 
    return t == JS_TSHRSTR || t == JS_TLITSTR || t == JS_TMEMSTR;
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    (void)e;
    return v.type == JS_TBOOLEAN;
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    if( v.type == JS_TOBJECT && v.u.object->type == JS_CUSERDATA){
        evm_val_t res = evm_prop_get(e, v, "$isbuffer");
        int b = evm_2_boolean(e, res);
        evm_val_free(e, res);
        return b;
    }
    return 0;
}

int evm_is_native(evm_t *e, evm_val_t v) {
    (void)e;
    if (v.type == JS_TOBJECT)
		return v.u.object->type == JS_CCFUNCTION;
	return 0;
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    (void)e;
	if (v.type == JS_TOBJECT)
		return v.u.object->type == JS_CFUNCTION ||
			v.u.object->type == JS_CSCRIPT ||
			v.u.object->type == JS_CCFUNCTION;
	return 0;
}

int evm_is_list(evm_t *e, evm_val_t v) {
    (void)e;
	return v.type == JS_TOBJECT && v.u.object->type == JS_CARRAY;
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    (void)e;
    return v.type == JS_TUNDEFINED;
}

int evm_is_null(evm_t *e, evm_val_t v) {
    (void)e;
    return v.type == JS_TNULL; 
}

int evm_is_object(evm_t *e, evm_val_t v) {
    (void)e;
    return v.type == JS_TOBJECT;
}

evm_val_t evm_mk_number(evm_t *e, double d){
    js_pushnumber(e, d);
    return *js_tovalue(e, -1);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    js_pushstring(e, s);
    return *js_tovalue(e, -1);
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    js_pushlstring(e, s, len);
    return *js_tovalue(e, -1);
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    js_pushboolean(e, v);
    return *js_tovalue(e, -1);
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    js_newcnative(e, v, name, len);
    return *js_tovalue(e, -1);
}

evm_val_t evm_mk_null(evm_t *e){
    js_pushnull(e);
    return *js_tovalue(e, -1);
}

evm_val_t evm_mk_undefined(evm_t *e){
    js_pushundefined(e);
    return *js_tovalue(e, -1);
}

void evm_val_free(evm_t *e, evm_val_t v) {
    EVM_UNUSED(v);
    js_pop(e, 1);
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    js_pushvalue(e, v);
    return v;
}

evm_val_t evm_mk_global(evm_t *e) {
    js_pushglobal(e);
    return *js_tovalue(e, -1);
}
