#include "evm.h"

static inline evm_atom_t hash_pjw(const void *key)
{
    const char *ptr = (const char *)key;
    uint32_t val = 0;
    uint32_t tmp;
    while (*ptr) {
        val = (val << 4) + (uint32_t)*ptr;
        tmp = val & 0xf0000000;
        if (tmp) {
            val = (val ^ (tmp >> 24)) ^ tmp;
        }
        ptr++;
    }
    return val;
}

static inline evm_atom_t htbl_key(evm_atom_t size, uint32_t hash, evm_atom_t i) {
    return (hash + i * (hash * 2 + 1)) % size;
}

static evm_atom_t evm_str_lookup(evm_t * e, const char *str)
{
    uint32_t hash;
    evm_atom_t pos;
    evm_atom_t i;
    evm_atom_t gen = 0;
    evm_string_pool_t *tbl = e->string_pool;
    if (tbl == 0) {
        return EVM_ERR_ATOM;
    }
    hash = hash_pjw(str);
    while(tbl){
        for (i = 0; i < EVM_STRINGPOOL_SIZE; i++) {
            pos = htbl_key(EVM_STRINGPOOL_SIZE, hash, i);
            evm_val_t v = tbl->values[pos];
            if( v == 0) break;
            if( evm_2_string(e, v) == str || !strcmp( evm_2_string(e, v), str ) ) {
                return pos + gen * EVM_STRINGPOOL_SIZE;
            }
        }
        tbl = tbl->next;
        gen++;
    }
    return EVM_ERR_ATOM;
}

static char *str_put(const char *str) {
    size_t size = strlen(str) + 1;
    char *sym = (char *)evm_malloc(size);
    if (sym) {
        memcpy(sym, str, size);
    }
    return sym;
}

evm_atom_t evm_str_insert(evm_t *e, const char *str, int alloc) {
    evm_atom_t i;
    evm_atom_t hash;
    evm_atom_t pos, gen = 0;
    evm_string_pool_t *tbl = e->string_pool;
    pos = evm_str_lookup(e, str);
    if( pos != EVM_ERR_ATOM )
        return pos;
    hash = hash_pjw(str);
    while(tbl){
        if( tbl->next != NULL) {
            tbl = tbl->next;
            gen++;
            continue;
        }
        for (i = 0; i < EVM_STRINGPOOL_SIZE; i++) {
            pos = htbl_key(EVM_STRINGPOOL_SIZE, hash, (evm_atom_t)i);
            evm_val_t v = tbl->values[pos];
            if( v == 0) {
                const char * res;
                if( alloc ) {
                    res = str_put(str);
                    EVM_ASSERT(res);
                    tbl->values[pos] = evm_string_create(e, res);
                } else {
                    res = str;
                    tbl->values[pos] = evm_mk_string(e, res);
                }
                tbl->count++;
                return pos + gen * EVM_STRINGPOOL_SIZE;
            }
        }
        if( tbl->next == NULL){
            tbl->next = (evm_string_pool_t*)evm_malloc(sizeof(evm_string_pool_t));
            if( !tbl->next ) {
                goto STR_INSERT_ERR;
            }
            memset(tbl->next, 0, sizeof(evm_string_pool_t));
            tbl->next->values = (evm_val_t*)evm_malloc(EVM_STRINGPOOL_SIZE * sizeof(evm_val_t));
            if( !tbl->next->values ) {
                goto STR_INSERT_ERR;
            }
            memset(tbl->next->values, 0, EVM_STRINGPOOL_SIZE * sizeof(evm_val_t));
        }
        tbl = tbl->next;
        gen++;
    }
STR_INSERT_ERR:
    return EVM_ERR_ATOM;
}

const char *evm_atom_to_string(evm_t * e, evm_atom_t key){
    evm_atom_t gen = key / EVM_STRINGPOOL_SIZE;
    evm_atom_t index = key - gen * EVM_STRINGPOOL_SIZE;
    evm_string_pool_t *tbl = e->string_pool;
    while(gen-- > 0) tbl = tbl->next;
    return evm_2_string(e, tbl->values[index]);
}

evm_val_t evm_atom_get(evm_t * e, evm_atom_t key) {
    evm_atom_t gen = key / EVM_STRINGPOOL_SIZE;
    evm_atom_t index = key - gen * EVM_STRINGPOOL_SIZE;
    evm_string_pool_t *tbl = e->string_pool;
    while(gen-- > 0) tbl = tbl->next;
    return tbl->values[index];
}

static inline void add_gc_object(evm_t *e, evm_object_t *obj) {
    evm_gc_object_t *gc_obj = evm_malloc(sizeof (evm_gc_object_t));
    EVM_ASSERT(gc_obj);
    memset(gc_obj, 0, sizeof (evm_gc_object_t));
    if( e->gcroot == NULL ) {
        e->gcnext = e->gcroot = gc_obj;
        e->gcroot->obj = obj;
    } else {
        e->gcnext->next = gc_obj;
        e->gcnext->next->obj = obj;
        e->gcnext = e->gcnext->next;
    }
}

static inline void keys_init(evm_atom_t *keys, int size) {
    for(int i = 0; i < size; i++) {
        keys[i] = EVM_ERR_ATOM;
    }
}

static inline void value_init_as_undef(evm_val_t *value, int size) {
    for(int i = 0; i < size; i++) {
        value[i] = EVM_VAL_UNDEFINED;
    }
}

static inline void *to_object(evm_val_t v) {
    return (void*)(intptr_t)(v & EVM_VAL_MASK);
}

static void expand(evm_object_t *obj, evm_atom_t key, evm_val_t v) {
    if( obj->size == 0 ) {
        obj->vals = (evm_val_t*)evm_malloc(sizeof(evm_val_t) * EVM_LIST_EXPAND_SIZE);
        obj->keys = (evm_atom_t*)evm_malloc(sizeof(evm_atom_t) * EVM_LIST_EXPAND_SIZE);
        EVM_ASSERT(obj->vals);
        obj->size = EVM_LIST_EXPAND_SIZE;
        value_init_as_undef(obj->vals, EVM_LIST_EXPAND_SIZE);
        obj->vals[0] = v;
        obj->keys[0] = key;
        return;
    }

    for(int i = 0; i < obj->size; i++){
        if( obj->keys[i] == EVM_ERR_ATOM || key == obj->keys[i] ) {
            obj->vals[i] = v;
            return;
        }
    }
    int index = obj->size;
    int expand_size = obj->size + EVM_LIST_EXPAND_SIZE;
    evm_val_t *old_vals = obj->vals;
    evm_atom_t *old_keys = obj->keys;
    evm_val_t *new_vals = (evm_val_t*)evm_malloc(sizeof(evm_val_t) * expand_size);
    evm_atom_t *new_keys = (evm_atom_t*)evm_malloc(sizeof(evm_atom_t) * expand_size);
    EVM_ASSERT(new_vals);
    EVM_ASSERT(new_keys);
    keys_init(new_keys, expand_size);
    value_init_as_undef(new_vals, expand_size);
    for(int i = 0; i < obj->size; i++) {
        new_vals[i] = old_vals[i];
        new_keys[i] = old_keys[i];
    }
    evm_free(old_keys);
    evm_free(old_vals);
    obj->vals = new_vals;
    obj->keys = new_keys;
    obj->size = expand_size;
    obj->vals[index] = v;
}

#define NEW_OBJECT(type) \
    type* obj = evm_malloc(sizeof (type)); \
    EVM_ASSERT(obj); \
    memset(obj, 0, sizeof (type));\
    add_gc_object(e, (evm_object_t*)obj);\

evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    NEW_OBJECT(evm_buffer_t);
    obj->type = TYPE_BUFFER;
    obj->count = len;
    if(len > 0){
        obj->buf = evm_malloc(len);
        EVM_ASSERT(obj->buf);
        memcpy(obj->buf, buf, len);
    }
    return evm_val_duplicate(e, evm_mk_buffer(e, obj));
}

int evm_buffer_len(evm_t *e, evm_val_t v) {
    if( evm_is_buffer(e, v) ){
        evm_buffer_t * o = (evm_buffer_t*)to_object(v);
        return o->count;
    }
    return 0;
}

uint8_t* evm_buffer_addr(evm_t *e, evm_val_t v) {
    evm_buffer_t *b = (evm_buffer_t *)to_object(v);
    return b->buf;
}

evm_err_t evm_list_set(evm_t * e, evm_val_t o, int index, evm_val_t v) {
    EVM_UNUSED(e);
    if( !evm_is_list(e, o) )
        return ec_type;
    evm_list_t *obj = (evm_list_t*)to_object(o);
    if( index < obj->count ){
        obj->vals[index] = v;
    }
    int expand_size = EVM_LIST_EXPAND_SIZE;
    int size = obj->size;
    if( size == 0 ) {
        obj->vals = (evm_val_t*)evm_malloc(sizeof(evm_val_t) * expand_size);
        EVM_ASSERT(obj->vals);
        size = obj->size = expand_size;
        value_init_as_undef(obj->vals, size);
    }
    expand_size = size;
    if( index >= size ) {
        expand_size += (index - size + 1) / EVM_LIST_EXPAND_SIZE * EVM_LIST_EXPAND_SIZE;
        if( (index - size + 1) % EVM_LIST_EXPAND_SIZE )
            expand_size += EVM_LIST_EXPAND_SIZE;
        evm_val_t *old = obj->vals;
        evm_val_t *new = (evm_val_t*)evm_malloc(sizeof(evm_val_t) * expand_size);
        EVM_ASSERT(new);
        value_init_as_undef(new, expand_size);
        for(int i = 0; i < size; i++) {
            new[i] = old[i];
        }
        evm_free(old);
        obj->vals = new;
        obj->size = expand_size;
    }
    if( index >= obj->count ){
        obj->count = index + 1;
    }
    obj->vals[index] = v;
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t obj, int index) {
    EVM_UNUSED(e);
    if( !evm_is_list(e, obj) )
        return evm_val_duplicate(e, EVM_VAL_UNDEFINED);
    evm_list_t * o = (evm_list_t*)to_object(obj);
    if( o->vals ){
        if(index < o->count){
            return evm_val_duplicate(e, o->vals[index]);
        }
    }
    return evm_val_duplicate(e, EVM_VAL_UNDEFINED);
}

evm_val_t evm_list_create(evm_t * e) {
    NEW_OBJECT(evm_list_t);
    obj->type = TYPE_LIST;
    return evm_val_duplicate(e, evm_mk_list(e, obj));
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    evm_atom_t atom = evm_str_insert(e, key, 1);
    evm_object_t *obj = to_object(o);
    expand(obj, atom, v);
    return ec_ok;
}

evm_err_t evm_prop_set_atom(evm_t *e, evm_val_t o, evm_atom_t atom, evm_val_t v) {
    evm_object_t *obj = to_object(o);
    expand(obj, atom, v);
    return ec_ok;
}

evm_val_t evm_prop_get_atom(evm_t *e, evm_val_t o, evm_atom_t atom) {
    if( !evm_is_object(e, o) )
        return evm_val_duplicate(e, EVM_VAL_UNDEFINED);
    evm_object_t *obj = to_object(o);
    for(int i = 0; i < obj->size; i++){
       if( obj->keys[i] == EVM_ERR_ATOM )
           return evm_val_duplicate(e, EVM_VAL_UNDEFINED);
       if( atom == obj->keys[i] ){
           return evm_val_duplicate(e, obj->vals[i]);
       }
    }
    return evm_val_duplicate(e, EVM_VAL_UNDEFINED);
}

evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    evm_atom_t atom = evm_str_insert(e, key, 1);
    return evm_prop_get_atom(e, o, atom);
}

evm_val_t evm_object_create(evm_t *e) {
    NEW_OBJECT(evm_object_t);
    return evm_val_duplicate(e, evm_mk_object(e, obj));
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data){
    NEW_OBJECT(evm_object_t);
    obj->data = data;
    return evm_val_duplicate(e, evm_mk_object(e, obj));
}

evm_val_t evm_string_create(evm_t *e, char *str) {
    NEW_OBJECT(evm_string_t);
    obj->type = TYPE_STRING;
    obj->len = strlen(str);
    obj->str = evm_malloc(obj->len + 1);
    memcpy(obj->str, str, obj->len);
    obj->str[obj->len] = 0;
    return evm_val_duplicate(e, evm_mk_string(e, obj));
}

evm_val_t evm_lstring_create(evm_t *e, char *str, int len) {
    NEW_OBJECT(evm_string_t);
    obj->type = TYPE_STRING;
    if( len >= strlen(str) ) {
        len = strlen(str);
    }
    obj->len = len;
    obj->str = evm_malloc(obj->len + 1);
    memcpy(obj->str, str, obj->len);
    obj->str[obj->len] = 0;
    return evm_val_duplicate(e, evm_mk_string(e, obj));
}

evm_val_t evm_cstring_create(evm_t *e, const char *str) {
    NEW_OBJECT(evm_string_t);
    obj->type = TYPE_CONST_STRING;
    obj->len = strlen(str);
    obj->str = evm_malloc(obj->len + 1);
    memcpy(obj->str, str, obj->len);
    obj->str[obj->len] = 0;
    return evm_val_duplicate(e, evm_mk_string(e, obj));
}

int evm_string_len(evm_t *e, evm_val_t o) {
    if( !evm_is_string(e, o) )
        return 0;
    evm_string_t *obj = to_object(o);
    return obj->len;
}

evm_val_t evm_function_create(evm_t *e) {
    NEW_OBJECT(evm_function_t);
    obj->type = TYPE_FUNCTION;
    return evm_val_duplicate(e, evm_mk_function(e, obj));
}

evm_t *evm_init(int stack_size) {
    evm_t *e = evm_malloc(sizeof(evm_t));
    EVM_ASSERT(e);
    memset(e, 0, sizeof (evm_t));
    e->sp = e->sp_base = (evm_val_t *)evm_malloc(stack_size * sizeof (evm_val_t));
    EVM_ASSERT(e->sp);
    memset(e->sp, 0, stack_size * sizeof (evm_val_t));
    e->stack_size = stack_size;
    e->string_pool = (evm_string_pool_t*)evm_malloc(sizeof(evm_string_pool_t));
    EVM_ASSERT(e->string_pool);
    memset(e->string_pool, 0, sizeof(evm_string_pool_t));
    e->string_pool->values = (evm_val_t*)evm_malloc(EVM_STRINGPOOL_SIZE * sizeof(evm_val_t));
    EVM_ASSERT(e->string_pool->values);
    memset(e->string_pool->values, 0, EVM_STRINGPOOL_SIZE * sizeof(evm_val_t));
    e->global = evm_object_create(e);
    return e;
}

void evm_deinit(evm_t * e)
{

}

static inline evm_val_t concatString(evm_t *e, evm_val_t v1, evm_val_t v2) {
    const char *sa = evm_2_string(e, v1);
    const char *sb = evm_2_string(e, v2);
    char *sab = evm_malloc(strlen(sa) + strlen(sb) + 1);
    EVM_ASSERT(sab);
    strcpy(sab, sa);
    strcat(sab, sb);
    sab[strlen(sa) + strlen(sb)] = 0;
    evm_val_t res = evm_string_create(e, sab);
    evm_free(sab);
    evm_string_free(e, sa);
    evm_string_free(e, sb);
    return res;
}

static inline evm_val_t op_concat(evm_t *e, evm_val_t v1, evm_val_t v2) {
    if( evm_is_number(e, v1) && evm_is_number(e, v2) ) {
        double n = evm_2_double(e, v1) + evm_2_double(e, v2);
        return evm_mk_number(e, n);
    }
    return concatString(e, v1, v2);
}

static inline double op_2_number(evm_t *e, evm_val_t v) {
    switch (evm_type(&v)) {
    case TYPE_NUMBER: return evm_2_double(e, v);
    case TYPE_STRING:
    case TYPE_CONST_STRING:{
        evm_string_t *obj = to_object(v);
        return atof(obj->str);
    }
    case TYPE_NULL: return 0;
    case TYPE_BOOLEAN: return evm_2_boolean(e, v);
    }
    return NAN;
}

static inline int op_2_boolean(evm_t *e, evm_val_t v) {
    switch (evm_type(&v)) {
    case TYPE_BOOLEAN: return evm_2_boolean(e, v);
    case TYPE_STRING:
    case TYPE_CONST_STRING: {
        evm_string_t *obj = to_object(v);
        return obj->str[0] != 0;
    }
    case TYPE_UNDEFINED: return 0;
    case TYPE_NULL: return 0;
    case TYPE_NUMBER: return evm_2_double(e, v) != 0;
    default: return 1;
    }
}

static inline int op_compare(evm_t *e, evm_val_t v1, evm_val_t v2) {
    int other = 0;
    double x, y;
    switch (evm_type(&v1)) {
        case TYPE_NUMBER: x = evm_2_double(e, v1);break;
        default:other = 1;break;
    }
    switch (evm_type(&v2)) {
        case TYPE_NUMBER: y = evm_2_double(e, v2);break;
        default:other = 1;break;
    }
    if( !other ) {
        return x < y ? -1 : x > y ? 1 : 0;
    } else if (evm_is_string(e, v1) && evm_is_string(e, v2)) {
        return strcmp(((evm_string_t*)to_object(v1))->str, ((evm_string_t*)to_object(v2))->str);
    } else {
        double x = op_2_number(e, v1);
        double y = op_2_number(e, v2);
        return x < y ? -1 : x > y ? 1 : 0;
    }
}

static inline int op_equal(evm_t *e, evm_val_t v1, evm_val_t v2) {
    int x_type = evm_type(&v1);
    int y_type = evm_type(&v2);
    switch (x_type) {
    case TYPE_NULL:
    case TYPE_UNDEFINED: {
        switch (y_type) {
        case TYPE_UNDEFINED: return 1;
        case TYPE_NULL: return 1;
        default:
            return 0;
        }
    }
    case TYPE_NUMBER:{
        switch (y_type) {
        case TYPE_NUMBER:
            return evm_2_double(e, v1) == evm_2_double(e, v2);
        default:
            return evm_2_double(e, v1) == op_2_number(e, v2);
        }
    }break;
    case TYPE_STRING:
    case TYPE_CONST_STRING:
        if (evm_is_string(e, v2) )
            return !strcmp(evm_2_string(e, v1), evm_2_string(e, v2));
        else{
            return 0;
        }
    case TYPE_BOOLEAN:{
        return evm_2_boolean(e, v1) == op_2_number(e, v2);
    }
    }
    return v1 == v2;
}

static inline int op_strictequal(evm_t *e, evm_val_t x, evm_val_t y)
{
    int x_type = evm_type(&x);
    int y_type = evm_type(&y);
    switch (x_type) {
    case TYPE_NUMBER:{
        switch (y_type) {
        case TYPE_NUMBER:
            return evm_2_double(e, x) == evm_2_double(e, y);
        default:
            return 0;
        }
    }break;
    case TYPE_STRING:
    case TYPE_CONST_STRING:
        if (evm_is_string(e, y) )
            return !strcmp(evm_2_string(e, x), evm_2_string(e, y));
        else{
            return 0;
        }
    }
    if (x_type != y_type) return 0;
    if (x_type == TYPE_UNDEFINED) return 1;
    if (x_type == TYPE_NULL) return 1;
    if (x_type == TYPE_BOOLEAN) return evm_2_boolean(e, x) == evm_2_boolean(e, y);
    return x == y;
}

static evm_val_t vm_run(evm_t * e, evm_val_t *local, evm_function_t *func, evm_val_t this_val)
{
    int pc = 0;
    uint8_t *code = func->codes;
    uint8_t opcode;
    int line = e->line;
    evm_val_t ret_val = EVM_VAL_UNDEFINED;
    evm_val_t *sp = e->sp;
    evm_val_t scope_val = evm_mk_object(e, func->scope);
    for(;;)
    {
        opcode = code[pc++];
        switch(opcode){
        case OP_getScope:{
            evm_prop_get_atom(e, scope_val, __get_uint16(code+ pc));
            pc+=2;
        } break;
        case OP_setScope: {
            evm_prop_get_atom(e, scope_val, __get_uint16(code+ pc));
            pc+=2;
        } break;
        case OP_getLocal2: {
            e->sp++;
            *e->sp = local[__get_uint16(code+ pc)];
            pc += 2;
        } break;
        case OP_getLocal: {
            e->sp++;
            *e->sp = local[*(uint8_t*)(code + pc)];
            pc++;
        } break;
        case OP_setLocal2: {
            local[__get_uint16(code+ pc)] = *e->sp;
            pc += 2;
        } break;
        case OP_setLocal: {
            local[*(uint8_t*)(code + pc)] = *e->sp;
            pc += 1;
        } break;
        case OP_getGlobal: {
            evm_prop_get_atom(e, e->global, __get_uint16(code+ pc));
            pc+=2;
        } break;
        case OP_number:*(++e->sp) = evm_mk_number(e, __get_double(code+ pc));pc+=8;break;
        case OP_undefined:*(++e->sp) = evm_mk_undefined(e);break;
        case OP_null:*(++e->sp) = evm_mk_null(e);break;
        case OP_true:*(++e->sp) = evm_mk_boolean(e, 1);break;
        case OP_false:*(++e->sp) = evm_mk_boolean(e, 0);break;
        case OP_string: {
            evm_atom_get(e, __get_int16(code+ pc));
            pc+=2;
        } break;
        case OP_add: e->sp--; *e->sp = op_concat(e, *e->sp, *(e->sp + 1));break;
        case OP_sub: e->sp--; *e->sp = evm_mk_number(e, op_2_number(e, *e->sp) - op_2_number(e, *(e->sp + 1))); break;
        case OP_mul: e->sp--; *e->sp = evm_mk_number(e, op_2_number(e, *e->sp) * op_2_number(e, *(e->sp + 1))); break;
        case OP_div: e->sp--; *e->sp = evm_mk_number(e, op_2_number(e, *e->sp) / op_2_number(e, *(e->sp + 1))); break;
        case OP_mod: e->sp--; *e->sp = evm_mk_number(e, fmod(op_2_number(e, *e->sp), op_2_number(e, *(e->sp + 1)))); break;
        case OP_and: e->sp--; *e->sp = evm_mk_number(e, (int32_t)op_2_number(e, *e->sp) & (int32_t)op_2_number(e, *(e->sp + 1))); break;
        case OP_or:  e->sp--; *e->sp = evm_mk_number(e, (int32_t)op_2_number(e, *e->sp) | (int32_t)op_2_number(e, *(e->sp + 1))); break;
        case OP_xor: e->sp--; *e->sp = evm_mk_number(e, (int32_t)op_2_number(e, *e->sp) ^ (int32_t)op_2_number(e, *(e->sp + 1))); break;
        case OP_leftShift: e->sp--; *e->sp = evm_mk_number(e, (int32_t)op_2_number(e, *e->sp) << (uint32_t)op_2_number(e, *(e->sp + 1))); break;
        case OP_rightShift: e->sp--; *e->sp = evm_mk_number(e, (int32_t)op_2_number(e, *e->sp) >> (uint32_t)op_2_number(e, *(e->sp + 1))); break;
        case OP_unsignedRightShift:
            e->sp--; *e->sp = evm_mk_number(e, (uint32_t)op_2_number(e, *e->sp) >> (uint32_t)op_2_number(e, *(e->sp + 1))); break;
        case OP_not: *e->sp = evm_mk_boolean(e, evm_2_boolean(e, *e->sp)); break;
        case OP_shortJump:
            pc = __get_uint16(code + pc);
            break;
        case OP_shortJumpTrue:{
            if( op_2_boolean(e, *e->sp) ) {
                pc = __get_uint16(code + pc);
            } else
                pc+=2;
            e->sp--;
        } break;
        case OP_shortJumpFalse:{
            if( !op_2_boolean(e, *e->sp) ) {
                pc = __get_uint16(code + pc);
            } else
                pc+=2;
            e->sp--;
        } break;
        case OP_jump:
            pc = __get_uint32(code+ pc);
            break;
        case OP_jumpTrue: {
            if( op_2_boolean(e, *e->sp) ){
                pc = __get_uint32(code+ pc);
            } else
                pc+=4;
            e->sp--;
        } break;
        case OP_jumpFalse: {
            if( !op_2_boolean(e, *e->sp) ){
                pc = __get_uint32(code+ pc);
            } else
                pc+=4;
            e->sp--;
        } break;
        case OP_call: {
            int argc = code[pc++];
            evm_val_t *top_sp = e->sp - argc;
            evm_val_t *func = e->sp - argc;
            evm_val_t *args = e->sp - argc + 1;
            evm_val_t ret_val = evm_call_free(e, *func, this_val, argc, args);
            e->sp = top_sp;
            *top_sp = ret_val;
        } break;
        case OP_callProp: {

        } break;
        case OP_return:{

        } break;
        case OP_negative: {
            *e->sp = evm_mk_number(e, -op_2_number(e, *e->sp));
        }break;
        case OP_invert: {
            *e->sp = evm_mk_number(e, -(int32_t)op_2_number(e, *e->sp));
        } break;
        case OP_lessThan: e->sp--; *e->sp = evm_mk_boolean(e, op_compare(e, *e->sp, *(e->sp + 1)) < 0);break;
        case OP_greaterThan: e->sp--; *e->sp = evm_mk_boolean(e, op_compare(e, *e->sp, *(e->sp + 1)) > 0);break;
        case OP_lessThanEqual: e->sp--; *e->sp = evm_mk_boolean(e, op_compare(e, *e->sp, *(e->sp + 1)) <= 0);break;
        case OP_greaterThanEqual: e->sp--; *e->sp = evm_mk_boolean(e, op_compare(e, *e->sp, *(e->sp + 1)) >= 0);break;
        case OP_equal: e->sp--; *e->sp = evm_mk_boolean(e, op_equal(e, *e->sp, *(e->sp + 1) == 0 ) == 0);break;
        case OP_notEqual: e->sp--; *e->sp = evm_mk_boolean(e, op_equal(e, *e->sp, *(e->sp + 1) != 0) == 0);break;
        case OP_typeEqual: e->sp--; *e->sp = evm_mk_boolean(e, op_strictequal(e, *e->sp, *(e->sp + 1) == 0 ) == 0);break;
        case OP_typeNotEqual: e->sp--; *e->sp = evm_mk_boolean(e, op_strictequal(e, *e->sp, *(e->sp + 1) != 0) == 0);break;
        case OP_stackDown: e->sp--;break;
        case OP_stackDown2: e->sp-=2;break;
        case OP_stackUp: e->sp++;break;
        case OP_nan: e->sp++;*e->sp = NAN; break;
        case OP_pop: *(e->sp - 1) = *e->sp;e->sp--; break;
        case OP_dup: e->sp++; *e->sp = *(e->sp - 1); break;
        case OP_swap: {
            evm_val_t val = *e->sp;
            *e->sp = *(e->sp - 1);
            *(e->sp - 1) = val;
        }break;
        case OP_getProp: {
            evm_atom_t atom = __get_int16(code+ pc);
            evm_val_t obj = *e->sp;
            evm_val_t val = evm_prop_get_atom(e, obj, atom);
            evm_val_free(e, val);
            *(e->sp + 1) = obj;
            *e->sp = val;
            pc+=2;
        }break;
        case OP_setProp: {
            evm_val_t *top_sp = e->sp;
            evm_atom_t atom = __get_int16(code+ pc);
            evm_val_t obj = *e->sp;
            evm_val_t val = *(e->sp - 1);
            evm_prop_set_atom(e, obj, atom, val);
            e->sp = top_sp;
            e->sp--;
            pc+=2;
        } break;
        case OP_getList:{
            evm_val_t *top_sp = e->sp - 1;
            evm_val_t obj = *(e->sp - 1);
            evm_val_t index = *e->sp;
            evm_val_t val = evm_list_get(e, obj, (int)op_2_number(e, index));
            evm_val_free(e, val);
            e->sp = top_sp;
            *e->sp = val;
            pc+=2;
        }break;
        case OP_setList:
        {
            evm_val_t *top_sp = e->sp - 2;
            evm_val_t obj = *(e->sp - 1);
            evm_val_t index = *e->sp;
            evm_val_t val = *(e->sp - 2);
            evm_list_set(e, obj, (int)op_2_number(e, index), val);
            e->sp = top_sp;
        }break;
        case OP_stop: {
            *sp = *e->sp;
            e->sp = sp;
            goto VM_END;
        }
        case OP_newList:{
            evm_list_create(e);
        }break;
        case OP_line8:e->line = line = code[pc];pc++; break;
        case OP_line32:e->line = line = __get_uint32(code+ pc);pc+=4;break;
        case OP_line16:e->line = line = __get_uint16(code+ pc);pc+=2;break;
        case OP_newObject:{
            evm_object_create(e);
        }break;
        case OP_this:{
            e->sp++;
            *e->sp = this_val;
        }break;
        case OP_global:{
            e->sp++;
            *e->sp = e->global;
        }break;
        default:
            e->err = ec_system;
            goto VM_END;
        }
    }
    VM_END:
    return ret_val;
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t this_val, int argc, evm_val_t *v) {
    if( !evm_is_callable(e, obj) )
        return EVM_VAL_UNDEFINED;
    if( !evm_is_object(e, this_val) )
        return EVM_VAL_UNDEFINED;
    evm_val_t *top_sp = e->sp;
    evm_val_duplicate(e, obj);
    evm_val_duplicate(e, this_val);
    evm_val_t ret_val = EVM_VAL_UNDEFINED;
    evm_val_t *local = ++e->sp;
    switch (evm_type(&obj)) {
    case TYPE_FUNCTION: {
        evm_function_t *func_obj = evm_2_ptr(e, obj);
        if( argc ) {
            int size = func_obj->var_count - func_obj->param_len;
            e->sp += size;
            for(int i = 0; i < argc; i++) {
                local[i] = v[i];
            }

            for(int i = 0; i < size; i++) {
                local[i + argc] = EVM_VAL_UNDEFINED;
            }
        }
        ret_val = vm_run(e, local, func_obj, this_val);
    }break;
    case TYPE_NATIVE:{
        if( argc ) {
            e->sp += argc;
            for(int i = 0; i < argc; i++) {
                local[i] = v[i];
            }
        }
        evm_native_t native = evm_2_ptr(e, obj);
        ret_val = native(e, this_val, argc, local);
    }break;
    }
    e->sp = top_sp;
    return ret_val;
}

const char *evm_2_string(evm_t *e, evm_val_t v) {
    static char buf[32];
        switch (evm_type(&v)) {
        case TYPE_STRING:
        case TYPE_CONST_STRING:
            return ((evm_string_t*)to_object(v))->str;
        case TYPE_BOOLEAN:
            return evm_2_boolean(e, v) == 0 ? "false" : "true";
        case TYPE_UNDEFINED:
            return "undefined";
        case TYPE_NULL:
            return "null";
        case TYPE_NUMBER:
            sprintf(buf, "%f", evm_2_double(e, v));
            return buf;
        case TYPE_NAN:
            return "NaN";
        case TYPE_OBJECT:
            return "object";
        case TYPE_LIST:
            return "array";
        case TYPE_INVOKE:
            return "invoke";
        case TYPE_FUNCTION:
            return "function";
        case TYPE_NATIVE:
            return "native";
        case TYPE_BUFFER:
            return (char *)((evm_buffer_t*)to_object(v))->buf;
        }
        return "";
}

double evm_2_double(evm_t *e, evm_val_t v) {
    return ((evm_valnum_t*)&v)->d;
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return (int32_t)((evm_valnum_t*)&v)->d;
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return (int)(v & EVM_VAL_MASK);
}

void evm_string_free(evm_t *e, char *str) {

}

int evm_is_number(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_INFINITE) != INNER_TYPE_INFINITE;
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    if(!evm_is_number(e, v))
        return 0;
    if(evm_2_double(e, v) - evm_2_integer(e, v) == 0)
        return 1;
    return 0;
}

int evm_is_string(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_STRING || (v & INNER_TYPE_MASK) == INNER_TYPE_CONST_STRING;
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_BOOLEAN;
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_BUFFER;
}

int evm_is_native(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_FUNC_NATIVE;
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    return evm_is_native(e, v) || (v & INNER_TYPE_MASK) == INNER_TYPE_FUNC_SCRIPT;
}

int evm_is_list(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_LIST;
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_UNDEFINED;
}

int evm_is_null(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_NULL;
}

int evm_is_object(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_OBJECT;
}

int evm_is_invoke(evm_t *e, evm_val_t v) {
    return (v & INNER_TYPE_MASK) == INNER_TYPE_INVOKE;
}

evm_val_t evm_mk_number(evm_t *e, double d) {
    return double_2_val(d);
}

evm_val_t evm_mk_boolean(evm_t *e, int v) {
    return INNER_TYPE_BOOLEAN | (!!v);
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    return INNER_TYPE_FUNC_NATIVE | ((intptr_t)v & EVM_ADDR_MASK);
}

evm_val_t evm_mk_null(evm_t *e) {
    return EVM_VAL_NULL;
}

evm_val_t evm_mk_undefined(evm_t *e) {
    return EVM_VAL_UNDEFINED;
}

evm_val_t evm_mk_invoke(evm_t *e, void *v) {
    return INNER_TYPE_INVOKE | ((intptr_t)v & EVM_ADDR_MASK);
}

evm_val_t evm_mk_buffer(evm_t *e, void *v) {
    return INNER_TYPE_BUFFER | ((intptr_t)v & EVM_ADDR_MASK);
}

evm_val_t evm_mk_list(evm_t *e, void *v) {
    return INNER_TYPE_LIST | ((intptr_t)v & EVM_ADDR_MASK);
}

evm_val_t evm_mk_object(evm_t *e, void *v) {
    return INNER_TYPE_OBJECT | ((intptr_t)v & EVM_ADDR_MASK);
}

evm_val_t evm_mk_string(evm_t *e, void *v) {
    return INNER_TYPE_STRING | ((intptr_t)v & EVM_ADDR_MASK);
}

evm_val_t evm_mk_function(evm_t *e, void *v) {
    return INNER_TYPE_FUNC_SCRIPT | ((intptr_t)v & EVM_ADDR_MASK);
}

void *evm_2_ptr(evm_t *e, evm_val_t v) {
    return (void*)(intptr_t)(v & EVM_VAL_MASK);
}

void evm_val_free(evm_t *e, evm_val_t v) {
    --e->sp;
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    ++e->sp;
    *e->sp = v;
    return v;
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    return evm_prop_get(e, e->global, key);
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    return evm_prop_set(e, e->global, key, v);
}

