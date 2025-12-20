#include <stdio.h>

#include "evm_grammar.h"
#include "cJSON.h"

void json_program(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj = evm_pop_arg(p);
    if( obj.u.ptr ){
        char *str = cJSON_Print(obj.u.ptr);
        printf("%s\r\n", str);
        cJSON_free(str);
    }
}

void json_new_object(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_CreateObject();
    evm_push_arg(p, obj);
}

void json_new_array(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_CreateArray();
    evm_push_arg(p, obj);
}

void json_key(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_malloc(p->str_len);
    memcpy(obj.u.ptr, p->str, p->str_len);
    evm_push_arg(p, obj);
}

void json_string_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = p->str;
    evm_push_arg(p, obj);
}

void json_number_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_CreateNumber(p->num);
    evm_push_arg(p, obj);
}

void json_true_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_CreateTrue();
    evm_push_arg(p, obj);
}

void json_false_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_CreateFalse();
    evm_push_arg(p, obj);
}

void json_null_value(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj;
    obj.u.ptr = cJSON_CreateNull();
    evm_push_arg(p, obj);
}

void json_add_pair(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj_v = evm_pop_arg(p);
    evm_grm_arg_t obj_k = evm_pop_arg(p);
    evm_grm_arg_t obj = evm_get_arg(p, 0);
    cJSON_AddItemToObject(obj.u.ptr, obj_k.u.ptr, obj_v.u.ptr);
}

void json_add_arr(evm_parser_t *p, evm_grm_arg_t *args, evm_grm_ret_t *ret) {
    evm_grm_arg_t obj_v = evm_pop_arg(p);
    evm_grm_arg_t obj = evm_get_arg(p, 0);
    cJSON_AddItemToArray(obj.u.ptr, obj_v.u.ptr);
}

static size_t fs_size(void * handle)
{
    FILE *file = (void*)handle;
    fseek (file , 0 , SEEK_END);
    size_t lSize = ftell (file);
    rewind (file);
    return lSize;
}

static char *load_file(const char *filename, size_t *size){
    FILE *file;
    size_t result;
    uint8_t *buffer = NULL;

    file = fopen(filename, "rb");
    if (file == NULL)
        return NULL;
    *size = fs_size(file);
    buffer = malloc(sizeof(uint8_t)*(*size) + 1);
    memset(buffer, 0, *size + 1);
    result = fread(buffer, 1, *size, file);
    if (result != *size ){
        fclose(file);
        return NULL;
    }
    buffer[*size] = 0;
    fclose(file);
    return buffer;
}

int main(int argc, char *argv[])
{
    size_t size;
    char *content = load_file(argv[1], &size);
    evm_parse(content);
    free(content);
    return 0;
}
