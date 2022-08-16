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
evm_val_t evm_buffer_create(evm_t *e, int len) {

}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {

}

int evm_buffer_len(evm_t *e, evm_val_t o) {

}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    js_newarray(e);
    return *js_tovalue(e, -1);
}

int evm_list_len(evm_t *e, evm_val_t o) {
    int len;
	js_Value *res = jsV_getproperty(e, &o, "length");
	len = jsV_tointeger(e, res);
	return len;
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    char buf[32];
    jsV_setproperty(e, jsV_toobject(e, &o), js_itoa(buf, i));
    return ec_ok;
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

evm_val_t evm_object_create_user_data(evm_t *e, void *user_data) {
    js_newuserdata(e, "user", user_data, NULL);
    return *js_tovalue(e, -1); 
}

void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    (void)e;
    evm_val_t *v = &o;
    if (v->type == JS_TOBJECT && v->u.object->type == JS_CUSERDATA)
        return v->u.object->u.user.data;
    return NULL;
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    js_getglobal(e, key);
    return *js_tovalue(e, -1);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    js_pushvalue(e, v);
    js_setglobal(e, key);
    return ec_ok;
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
        js_pushundefined(e);
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
    return ec_ok;
}


/*** 模块操作函数 ***/
evm_err_t evm_module_add(evm_t *e, const char* name, evm_val_t v) {
    js_Property *ref;
    ref = jsV_getproperty(e, e->G, "@system");
    if (ref) {
        js_Property *local_ref = jsV_getproperty(e, jsV_toobject(e, &ref->value), name);
        if( local_ref ) {
            local_ref->value = v;
            return ec_ok;
        }
        local_ref = jsV_setproperty(e, jsV_toobject(e, &ref->value), name);
        local_ref->value = v;
    }
    return ec_err;
}

evm_val_t evm_module_get(evm_t *e, const char* name) {
    js_Property *ref;
    ref = jsV_getproperty(e, e->G, "@system");
    if (ref) {
        ref = jsV_getproperty(e, jsV_toobject(e, &ref->value), name);
        if( ref ) {
            js_pushvalue(e, ref->value);
            return ref->value;
        }
    }
    js_pushundefined(e);
    return *js_tovalue(e, -1);
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

evm_val_t evm_load_file(evm_t *e, const char *path) {
    js_loadfile(e, path);
    js_pushundefined(e);
    js_call(e, 0);
    return *js_tovalue(e, -1);
}

evm_val_t evm_load_string(evm_t *e, const char *source) {
    js_loadstring(e, "[string]", source);
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
    evm_val_free(e, res);
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
    js_pop(e, 1);
}
