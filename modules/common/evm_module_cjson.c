#include "evm_module.h"
#include "cJSON.h"

static evm_val_t cjson_object_parse(evm_t *e, cJSON *item);
static evm_val_t cjson_array_parse(evm_t *e, cJSON *item);

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
}

//stringify(object)
EVM_FUNCTION(stringify) {
    EVM_EPCV;

    EVM_RETURN(EVM_UNDEFINED);
}

void evm_module_cjson(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "parse", evm_mk_native(e, parse, "parse", EVM_VARARGS));
    evm_prop_set(e, obj, "stringify", evm_mk_native(e, stringify, "stringify", EVM_VARARGS));
    evm_module_add(e, "@native.cjson", obj);
    evm_val_free(e, obj);
}
