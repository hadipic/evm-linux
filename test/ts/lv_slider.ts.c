
#include "tinyscript.h"
#include "tinyscript_p.h"

extern ts_value_t *__get_dict_const(ts_obj_object_t *obj, uint16_t key);
extern ts_obj_object_t *__key_to_str(ts_runtime_t *e, uint16_t key);
extern double __to_number(ts_value_t *v);
extern int __to_boolean(ts_value_t *v);
extern void __set_dict_const(ts_obj_object_t *obj, uint16_t key, ts_value_t *v);
extern ts_value_t ts_new_function(ts_runtime_t *e);


ts_value_t slider_changed(ts_runtime_t *e, ts_obj_object_t *this, ts_obj_object_t *func, ts_value_t *local){
    ts_value_t *funcs = func->u.func->func_list->u.list->values;
    ts_obj_object_t *scope = func->u.func->scope_obj;

    local[2] = ts_Op_getScopeVar(e, scope, "print");

    local[4] = ts_Op_getScopeVar(e, scope, "lv");

    if( ts_is_callable(local + 3) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 3);
        ts_obj_object_t *local_this = ts_2_ptr(local + 4);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[0];

        local[5] = ts_op_call(e, obj, local_this, 1, args);
        e->sp = args;
    }

    if( ts_is_callable(local + 2) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 2);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 
        args[0] = local[5]; 
        local[6] = ts_op_call(e, obj, this, 1, args);
        e->sp = args;
    }
    return VAL_UNDEFINED}

ts_value_t __main__(ts_runtime_t *e, ts_obj_object_t *this){
    ts_value_t *local = e->sp;
    e->sp += 7;

    ts_value_t main =  ts_new_function(e);
    ts_obj_object_t *func = ts_2_ptr(&main);
    ts_value_t func_list = ts_new_array(e);
    func->proto = ts_2_ptr(&func_list);
    func->u.func->scope_obj = this;
    func->u.func->func_list = func->proto;

    ts_value_t local_func;
    ts_obj_object_t *local_func_obj;

    local_func = ts_new_function(e);
    local_func_obj = ts_2_ptr(&local_func);
    local_func_obj->u.func->scope_obj = ts_2_ptr(&this);
    local_func_obj->u.func->func_list = func->proto;
    local_func_obj->u.func->cfunc = slider_changed;
    local_func_obj->u.func->nvar = 5;
    local_func_obj->u.func->nparam = 2;
    ts_set_array(e, func_list, ts_get_length(e, func_list), local_func);
    ts_value_t *funcs = func->u.func->func_list->u.list->values;
    ts_obj_object_t *scope = func->u.func->scope_obj;

    local[0] = ts_Op_getScopeVar(e, scope, "clock");

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar;  
        local[1] = ts_op_call(e, obj, this, 0, args);
        e->sp = args;
    }

{
    uint16_t key = ts_strpool_append(e, "t1", 0);
    __set_dict_const(scope, key, local + 1);
} 

    local[0] = ts_Op_getScopeVar(e, scope, "require");

    {
        uint16_t key = ts_strpool_append(e, "@native.lvgl", 0);
        ts_set_foreign_string(local + 1, key_to_str(e, key));
    }

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 
        args[0] = local[1]; 
        local[2] = ts_op_call(e, obj, this, 1, args);
        e->sp = args;
    }

{
    uint16_t key = ts_strpool_append(e, "lv", 0);
    __set_dict_const(scope, key, local + 2);
} 

    local[1] = ts_Op_getScopeVar(e, scope, "lv");

    local[3] = ts_Op_getScopeVar(e, scope, "lv");

    if( ts_is_callable(local + 2) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 2);
        ts_obj_object_t *local_this = ts_2_ptr(local + 3);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        local[4] = ts_op_call(e, obj, local_this, 0, args);
        e->sp = args;
    }

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_obj_object_t *local_this = ts_2_ptr(local + 1);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[4];

        local[5] = ts_op_call(e, obj, local_this, 1, args);
        e->sp = args;
    }

{
    uint16_t key = ts_strpool_append(e, "slider", 0);
    __set_dict_const(scope, key, local + 5);
} 

    local[1] = ts_Op_getScopeVar(e, scope, "lv");

    local[2] = ts_Op_getScopeVar(e, scope, "slider");

    ts_set_integer(local + 3, 50);

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_obj_object_t *local_this = ts_2_ptr(local + 1);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[2];

        args[1] = local[3];

        local[4] = ts_op_call(e, obj, local_this, 2, args);
        e->sp = args;
    }

    local[1] = ts_Op_getScopeVar(e, scope, "lv");

    local[2] = ts_Op_getScopeVar(e, scope, "slider");

    ts_set_integer(local + 3, 50);

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_obj_object_t *local_this = ts_2_ptr(local + 1);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[2];

        args[1] = local[3];

        local[4] = ts_op_call(e, obj, local_this, 2, args);
        e->sp = args;
    }

    ts_set_integer(local + 0, 0);

{
    uint16_t key = ts_strpool_append(e, "i", 0);
    __set_dict_const(scope, key, local + 0);
} 

    ts_set_integer(local + 0, 0);

{
    uint16_t key = ts_strpool_append(e, "i", 0);
    __set_dict_const(scope, key, local + 0);
} 

loop_0_begin:

    local[1] = ts_Op_getScopeVar(e, scope, "i");

    ts_set_integer(local + 2, 1000000);

    if( !(__to_number(local + 1) < __to_number(local + 2)) ) {
        goto loop_0_start;
    } 

    local[4] = ts_Op_getScopeVar(e, scope, "i");

    ts_set_integer(local + 5, 1);

    local[3] = ts_mk_number(__to_number(local + 4) + __to_number(local + 5));

{
    uint16_t key = ts_strpool_append(e, "i", 0);
    __set_dict_const(scope, key, local + 3);
} 
goto loop_0_begin;
loop_0_start;

    local[1] = ts_Op_getScopeVar(e, scope, "lv");

    local[2] = ts_Op_getScopeVar(e, scope, "slider");

    local[3] = funcs[0];

    local[5] = ts_Op_getScopeVar(e, scope, "lv");

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_obj_object_t *local_this = ts_2_ptr(local + 1);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[2];

        args[1] = local[3];

        args[2] = local[4];

        local[6] = ts_op_call(e, obj, local_this, 3, args);
        e->sp = args;
    }

    local[0] = ts_Op_getScopeVar(e, scope, "print");

    local[2] = ts_Op_getScopeVar(e, scope, "clock");

    if( ts_is_callable(local + 2) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 2);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar;  
        local[3] = ts_op_call(e, obj, this, 0, args);
        e->sp = args;
    }

    local[4] = ts_Op_getScopeVar(e, scope, "t1");

    local[1] = ts_mk_number(__to_number(local + 3) - __to_number(local + 4));

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 
        args[0] = local[1]; 
        local[5] = ts_op_call(e, obj, this, 1, args);
        e->sp = args;
    }

    return VAL_UNDEFINED;
    }
