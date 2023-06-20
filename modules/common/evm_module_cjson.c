#include "evm_module.h"
#include "cJSON.h"

static evm_val_t cjson_object_parse(evm_t *e, cJSON *item);
static evm_val_t cjson_array_parse(evm_t *e, cJSON *item);
static cJSON *cjson_object_build(evm_t *e, evm_val_t obj);
static cJSON *cjson_array_build(evm_t *e, evm_val_t obj);

static void cjson_object_parse_children(evm_t *e, cJSON *item, evm_val_t parent){
    while (item != NULL) {
        char * key = item->string;
        if (cJSON_IsString(item)){
            evm_val_t val = evm_string_create(e, item->valuestring);
            evm_prop_set(e, parent, key, val);
            evm_val_free(e, val);
        } else if (cJSON_IsNumber(item)){
            evm_prop_set(e, parent, key, evm_mk_number(e, item->valuedouble));
        } else if (cJSON_IsBool(item)){
            evm_prop_set(e, parent, key, evm_mk_boolean(e, item->valueint));
        } else if (cJSON_IsArray(item)){
            evm_val_t val = cjson_array_parse(e, item);
            evm_prop_set(e, parent, key, val);
            evm_val_free(e, val);
        } else if (cJSON_IsNull(item)){
            evm_prop_set(e, parent, key, evm_mk_null(e));
        } else if (cJSON_IsObject(item)){
            evm_val_t obj = cjson_object_parse(e, item);
            evm_prop_set(e, parent, key, obj);
            evm_val_free(e, obj);
        }
        item = item->next;
    }
}

static void cjson_array_parse_children(evm_t * e, cJSON *item, evm_val_t parent){
    while (item != NULL) {
        int len = evm_list_len(e, parent);
        if (cJSON_IsString(item)){
            evm_val_t val = evm_string_create(e, item->valuestring);
            evm_list_set(e, parent, len, val);
            evm_val_free(e, val);
        } else if(cJSON_IsNumber(item)){
            evm_list_set(e, parent, len, evm_mk_number(e, item->valuedouble));
        } else if(cJSON_IsBool(item)){
            evm_list_set(e, parent, len, evm_mk_boolean(e, item->valueint));
        } else if(cJSON_IsArray(item)){
            evm_val_t val = cjson_array_parse(e, item);
            evm_list_set(e, parent, len, val);
            evm_val_free(e, val);
        } else if(cJSON_IsObject(item)){
            evm_val_t val = cjson_object_parse(e, item);
            evm_list_set(e, parent, len, val);
            evm_val_free(e, val);
        }
        item = item->next;
    }
}


static evm_val_t cjson_array_parse(evm_t *e, cJSON *item) {
    evm_val_t obj = evm_list_create(e);
    if (item->child != NULL){
        cjson_array_parse_children(e, item->child, obj);
    }
    return obj;
}

static evm_val_t cjson_object_parse(evm_t *e, cJSON *item) {
    evm_val_t obj = evm_object_create(e);
    cjson_object_parse_children(e, item->child, obj);
    return obj;
}

//parse(string)
EVM_FUNCTION(parse) {
    EVM_EPCV;
    char *str = evm_2_string(e, v[0]);
    cJSON* root = cJSON_Parse(str);
    evm_string_free(e, str);
    if( !root )
        EVM_RETURN(EVM_UNDEFINED);
    if( cJSON_IsArray(root) ){
        evm_val_t obj = cjson_array_parse(e, root);
        cJSON_Delete(root);
        return obj;
    } else if( cJSON_IsObject(root) ) {
        evm_val_t obj = cjson_object_parse(e, root);
        cJSON_Delete(root);
        return obj;
    }
    cJSON_Delete(root);
    EVM_RETURN(EVM_UNDEFINED);
}

static cJSON *cjson_array_build(evm_t *e, evm_val_t obj) {
    cJSON *parent = cJSON_CreateArray();
    int size = evm_list_len(e, obj);
    for(int i = 0; i < size; i++) {
        evm_val_t val = evm_list_get(e, obj, i);
        if( evm_is_null(e, val) ){
            cJSON *item = cJSON_CreateNull();
            cJSON_AddItemToArray(parent, item);
        } else if( evm_is_string(e, val) ) {
            char *str = evm_2_string(e, val);
            cJSON *item = cJSON_CreateString(str);
            cJSON_AddItemToArray(parent, item);
            evm_string_free(e, str);
        } else if( evm_is_number(e, val) ) {
            cJSON *item = cJSON_CreateNumber(evm_2_double(e, val));
            cJSON_AddItemToArray(parent, item);
        } else if( evm_is_boolean(e, val) ) {
            cJSON *item = cJSON_CreateBool(evm_2_boolean(e, val));
            cJSON_AddItemToArray(parent, item);
        } else if( evm_is_list(e, val) ) {
            cJSON *item = cjson_array_build(e, val);
            cJSON_AddItemToArray(parent, item);
        } else if( evm_is_object(e, val) ) {
            cJSON *item = cjson_object_build(e, val);
            cJSON_AddItemToArray(parent, item);
        }
        evm_val_free(e, val);
    }
    return parent;
}

static cJSON *cjson_object_build(evm_t *e, evm_val_t obj) {
     cJSON *parent = cJSON_CreateObject();
     evm_val_t keys = evm_object_keys(e, obj);
     int size = evm_list_len(e, keys);
     for(int i = 0; i < size; i++) {
         evm_val_t key = evm_list_get(e, keys, i);
         char *key_s = evm_2_string(e, key);
         evm_val_t val = evm_prop_get(e, obj, key_s);
         if( evm_is_null(e, val) ){
             cJSON *item = cJSON_CreateNull();
             cJSON_AddItemToObject(parent, key_s, item);
         } else if( evm_is_string(e, val) ) {
             char *str = evm_2_string(e, val);
             cJSON *item = cJSON_CreateString(str);
             cJSON_AddItemToObject(parent, key_s, item);
             evm_string_free(e, str);
         } else if( evm_is_number(e, val) ) {
             cJSON *item = cJSON_CreateNumber(evm_2_double(e, val));
             cJSON_AddItemToObject(parent, key_s, item);
         } else if( evm_is_boolean(e, val) ) {
             cJSON *item = cJSON_CreateBool(evm_2_boolean(e, val));
             cJSON_AddItemToObject(parent, key_s, item);
         } else if( evm_is_list(e, val) ) {
             cJSON *item = cjson_array_build(e, val);
             cJSON_AddItemToObject(parent, key_s, item);
         } else if( evm_is_object(e, val) ) {
             cJSON *item = cjson_object_build(e, val);
             cJSON_AddItemToObject(parent, key_s, item);
         }
         evm_val_free(e, val);
         evm_string_free(e, key_s);
     }
     evm_val_free(e, keys);
     return parent;
}

//stringify(object)
EVM_FUNCTION(stringify) {
    EVM_EPCV;
    if( evm_is_list(e, v[0]) ){
        cJSON *root = cjson_array_build(e, v[0]);
        char *str = cJSON_PrintUnformatted(root);
        evm_val_t res = evm_string_create(e, str);
        cJSON_free(str);
        cJSON_Delete(root);
        return res;
    } else if( evm_is_object(e, v[0])) {
        cJSON *root = cjson_object_build(e, v[0]);
        char *str = cJSON_PrintUnformatted(root);
        evm_val_t res = evm_string_create(e, str);
        cJSON_free(str);
        cJSON_Delete(root);
        return res;
    }
    EVM_RETURN(EVM_UNDEFINED);
}

void evm_module_cjson(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "parse", evm_mk_native(e, parse, "parse", EVM_VARARGS));
    evm_prop_set(e, obj, "stringify", evm_mk_native(e, stringify, "stringify", EVM_VARARGS));
    evm_module_add(e, "@native.cjson", obj);
    evm_val_free(e, obj);
}
