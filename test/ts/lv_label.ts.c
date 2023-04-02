
#include "tinyscript.h"
#include "tinyscript_p.h"

extern ts_value_t *__get_dict_const(ts_obj_object_t *obj, uint16_t key);
extern ts_obj_object_t *__key_to_str(ts_runtime_t *e, uint16_t key);
extern double __to_number(ts_value_t *v);
extern int __to_boolean(ts_value_t *v);
extern void __set_dict_const(ts_obj_object_t *obj, uint16_t key, ts_value_t *v);
extern ts_value_t ts_new_function(ts_runtime_t *e);


ts_value_t timeout(ts_runtime_t *e, ts_obj_object_t *this, ts_obj_object_t *func, ts_value_t *local){
    ts_value_t *funcs = func->u.func->func_list->u.list->values;
    ts_obj_object_t *scope = func->u.func->scope_obj;

    local[0] = ts_Op_getScopeVar(e, scope, "a");

    ts_set_integer(local + 1, 0);

    if( !(__to_number(local + 0) == __to_number(local + 1)) ) {
        goto loop_undefined_start;
    } 

    local[3] = ts_Op_getScopeVar(e, scope, "lv");

    local[4] = ts_Op_getScopeVar(e, scope, "label1");

    {
        uint16_t key = ts_strpool_append(e, "hello", 0);
        ts_set_foreign_string(local + 5, key_to_str(e, key));
    }

    if( ts_is_callable(local + 2) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 2);
        ts_obj_object_t *local_this = ts_2_ptr(local + 3);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[4];

        args[1] = local[5];

        local[6] = ts_op_call(e, obj, local_this, 2, args);
        e->sp = args;
    }

    ts_set_integer(local + 2, 1);

{
    uint16_t key = ts_strpool_append(e, "a", 0);
    __set_dict_const(scope, key, local + 2);
} 
goto loop_undefined_start;

    local[3] = ts_Op_getScopeVar(e, scope, "lv");

    local[4] = ts_Op_getScopeVar(e, scope, "label1");

    {
        uint16_t key = ts_strpool_append(e, "EVM", 0);
        ts_set_foreign_string(local + 5, key_to_str(e, key));
    }

    if( ts_is_callable(local + 2) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 2);
        ts_obj_object_t *local_this = ts_2_ptr(local + 3);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        args[0] = local[4];

        args[1] = local[5];

        local[6] = ts_op_call(e, obj, local_this, 2, args);
        e->sp = args;
    }

    ts_set_integer(local + 2, 0);

{
    uint16_t key = ts_strpool_append(e, "a", 0);
    __set_dict_const(scope, key, local + 2);
} 
loop_undefined_end;
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
    local_func_obj->u.func->cfunc = timeout;
    local_func_obj->u.func->nvar = 7;
    local_func_obj->u.func->nparam = 0;
    ts_set_array(e, func_list, ts_get_length(e, func_list), local_func);
    ts_value_t *funcs = func->u.func->func_list->u.list->values;
    ts_obj_object_t *scope = func->u.func->scope_obj;

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

    local[0] = ts_Op_getScopeVar(e, scope, "require");

    {
        uint16_t key = ts_strpool_append(e, "@native.timer", 0);
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
    uint16_t key = ts_strpool_append(e, "timer", 0);
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
    uint16_t key = ts_strpool_append(e, "label1", 0);
    __set_dict_const(scope, key, local + 5);
} 

    local[1] = ts_Op_getScopeVar(e, scope, "lv");

    local[2] = ts_Op_getScopeVar(e, scope, "label1");

    {
        uint16_t key = ts_strpool_append(e, "hello", 0);
        ts_set_foreign_string(local + 3, key_to_str(e, key));
    }

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
    uint16_t key = ts_strpool_append(e, "a", 0);
    __set_dict_const(scope, key, local + 0);
} 

    local[1] = ts_Op_getScopeVar(e, scope, "timer");

    if( ts_is_callable(local + 0) ){
        ts_obj_object_t *obj = ts_2_ptr(local + 0);
        ts_obj_object_t *local_this = ts_2_ptr(local + 1);
        ts_value_t *args = e->sp;
        e->sp += obj->u.func->nvar; 

        local[2] = ts_op_call(e, obj, local_this, 0, args);
        e->sp = args;
    }

{
    uint16_t key = ts_strpool_append(e, "t", 0);
    __set_dict_const(scope, key, local + 2);
} 

    local[0] = ts_Op_getScopeVar(e, scope, "t");

    local[1] = funcs[0];

    local[1] = ts_Op_getScopeVar(e, scope, "t");

    ts_set_integer(local + 2, 100);

    ts_set_integer(local + 3, 500);

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

    return VAL_UNDEFINED;
    }
