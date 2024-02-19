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
#ifndef JERRYSCRIPT_H
#define JERRYSCRIPT_H

/*
 * Jerryscript head at 8ba0d1b6
 */

#include "evm.h"

typedef enum
{
  JERRY_INIT_EMPTY = (0u), /**< empty flag set */
  JERRY_INIT_SHOW_OPCODES = (1u << 0), /**< dump byte-code to log after parse */
  JERRY_INIT_SHOW_REGEXP_OPCODES = (1u << 1), /**< dump regexp byte-code to log after compilation */
  JERRY_INIT_MEM_STATS = (1u << 2), /**< dump memory statistics */
} jerry_init_flag_t;


/**
 * Character type of JerryScript.
 */
typedef uint8_t jerry_char_t;

/**
 * Size type of JerryScript.
 */
typedef uint32_t jerry_size_t;

/**
 * Length type of JerryScript.
 */
typedef uint32_t jerry_length_t;

/**
 * Description of a JerryScript value.
 */
typedef evm_val_t jerry_value_t;

/**
 * JerryScript API Error object types.
 */
typedef enum
{
  JERRY_ERROR_NONE = 0,  /**< No Error */

  JERRY_ERROR_COMMON,    /**< Error */
  JERRY_ERROR_EVAL,      /**< EvalError */
  JERRY_ERROR_RANGE,     /**< RangeError */
  JERRY_ERROR_REFERENCE, /**< ReferenceError */
  JERRY_ERROR_SYNTAX,    /**< SyntaxError */
  JERRY_ERROR_TYPE,      /**< TypeError */
  JERRY_ERROR_URI        /**< URIError */
} jerry_error_t;

/**
 * Option flags for jerry_parse and jerry_parse_function functions.
 */
typedef enum
{
  JERRY_PARSE_NO_OPTS = 0, /**< no options passed */
  JERRY_PARSE_STRICT_MODE = (1 << 0), /**< enable strict mode */
  JERRY_PARSE_MODULE = (1 << 1) /**< parse source as an ECMAScript module */
} jerry_parse_opts_t;

/**
 * Native free callback of an object.
 */
typedef void (*jerry_object_native_free_callback_t) (void *native_p);

/**
 * Type information of a native pointer.
 */
typedef struct
{
  jerry_object_native_free_callback_t free_cb; /**< the free callback of the native pointer */
} jerry_object_native_info_t;

/**
 * Type of an external function handler.
 */
typedef evm_native_t jerry_external_handler_t;

evm_t *global_runtime;

static inline void jerry_init (jerry_init_flag_t flags) {
    global_runtime = evm_init();
}

static inline void jerry_cleanup (void) {
    evm_deinit(global_runtime);
}

static inline void jerry_release_value (jerry_value_t value) {
    evm_val_free(global_runtime, value);
}

static inline jerry_value_t jerry_get_global_object (void) {
    return evm_mk_global(global_runtime);
}

static inline void jerry_set_object_native_pointer (const jerry_value_t obj_val,
                                      void *native_pointer_p,
                                      const jerry_object_native_info_t *native_info_p) {
    evm_object_set_user_data(global_runtime, obj_val, native_pointer_p);
}

static inline int jerry_value_is_error (const jerry_value_t value) {
    return evm_is_exception(global_runtime, value);
}

static inline int jerry_is_valid_utf8_string (const jerry_char_t *utf8_buf_p, jerry_size_t buf_size) {
    return 1;
}

static inline jerry_value_t jerry_create_string_sz_from_utf8 (const jerry_char_t *str_p, jerry_size_t str_size) {
    return evm_mk_lstring(global_runtime, str_p, str_size);
}

static inline jerry_value_t jerry_create_error (jerry_error_t error_type, const jerry_char_t *message_p) {
    return evm_throw(global_runtime, evm_mk_string(global_runtime, message_p));
}

static inline jerry_value_t jerry_create_array (uint32_t size) {
    return evm_list_create(global_runtime);
}

static inline jerry_value_t jerry_create_number (double value) {
    return evm_mk_number(global_runtime, value);
}

static inline jerry_value_t jerry_set_property_by_index (const jerry_value_t obj_val, uint32_t index,
                                           const jerry_value_t value_to_set) {
    evm_list_set(global_runtime, obj_val, index, value_to_set);
    return value_to_set;
}

static inline jerry_value_t jerry_create_external_function (jerry_external_handler_t handler_p) {
    return evm_mk_native(global_runtime, handler_p, "", EVM_VARARGS);
}

static inline int jerry_value_is_object (const jerry_value_t value) {
    return evm_is_object(global_runtime, value);
}

static inline int jerry_value_is_array (const jerry_value_t value) {
    return evm_is_list(global_runtime, value);
}

static inline int jerry_value_is_function (const jerry_value_t value) {
    return evm_is_callable(global_runtime, value);
}

static inline int jerry_value_is_undefined (const jerry_value_t value) {
    return evm_is_undefined(global_runtime, value);
}

static inline int jerry_value_is_string (const jerry_value_t value) {
    return evm_is_string(global_runtime, value);
}

static inline jerry_size_t jerry_get_utf8_string_size (const jerry_value_t value) {
    return evm_string_len(global_runtime, value);
}

static inline jerry_size_t jerry_string_to_utf8_char_buffer (const jerry_value_t value,
                                               jerry_char_t *buffer_p,
                                               jerry_size_t buffer_size) {
    char *str = evm_2_string(global_runtime, value);
    memcpy(buffer_p, str, buffer_size);
    evm_string_free(global_runtime, str);
    return buffer_size;
}

static inline jerry_value_t jerry_set_prototype (const jerry_value_t obj_val, const jerry_value_t proto_obj_val) {
    evm_set_prototype(global_runtime, obj_val, proto_obj_val);
    return EVM_UNDEFINED;
}

static inline jerry_value_t jerry_create_string (const jerry_char_t *str_p) {
    return evm_string_create(global_runtime, str_p);
}

static inline jerry_value_t jerry_create_null (void) {
    return evm_object_create(global_runtime);
}

static inline jerry_value_t jerry_set_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val,
                                  const jerry_value_t value_to_set) {
    char *name = evm_2_string(global_runtime, prop_name_val);
    evm_prop_set(global_runtime, obj_val, name, value_to_set);
    evm_string_free(global_runtime, name);
    return EVM_UNDEFINED;
}

static inline jerry_value_t jerry_get_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val) {
    char *name = evm_2_string(global_runtime, prop_name_val);
    evm_val_t res = evm_prop_get(global_runtime, obj_val, name);
    evm_string_free(global_runtime, name);
    return res;
}

static inline jerry_value_t jerry_create_undefined (void) {
    return EVM_UNDEFINED;
}

static inline jerry_value_t jerry_create_object (void) {
    return evm_object_create(global_runtime);
}

static inline jerry_value_t jerry_create_boolean (int value) {
    return evm_mk_boolean(global_runtime, value);
}

static inline jerry_value_t jerry_get_property_by_index (const jerry_value_t obj_val, uint32_t index) {
    return evm_list_get(global_runtime, obj_val, index);
}

static inline jerry_value_t jerry_parse (const jerry_char_t *resource_name_p, size_t resource_name_length,
                           const jerry_char_t *source_p, size_t source_size, uint32_t parse_opts) {

}

static inline jerry_value_t jerry_call_function (const jerry_value_t func_obj_val, const jerry_value_t this_val,
                                   const jerry_value_t args_p[], jerry_size_t args_count) {
    return evm_call(global_runtime, func_obj_val, this_val, args_count, args_p);
}

static inline jerry_value_t jerry_get_value_from_error (jerry_value_t value, int release) {
    return EVM_UNDEFINED;
}

static inline int jerry_value_to_boolean (const jerry_value_t value) {
    return evm_2_boolean(global_runtime, value);
}

static inline jerry_value_t jerry_value_to_number (const jerry_value_t value) {
    double d = evm_2_double(global_runtime, value);
    return evm_mk_number(global_runtime, d);
}

static inline jerry_value_t jerry_acquire_value (jerry_value_t value) {
    return evm_val_duplicate(global_runtime, value);
}

static inline jerry_value_t jerry_create_string_sz (const jerry_char_t *str_p, jerry_size_t str_size) {
    return evm_mk_lstring(global_runtime, str_p, str_size);
}

static inline int jerry_value_is_null (const jerry_value_t value) {
    return evm_is_null(global_runtime, value);
}

static inline int jerry_get_object_native_pointer (const jerry_value_t obj_val,
                                      void **out_native_pointer_p,
                                      const jerry_object_native_info_t *native_pointer_info_p) {
    void *user_data = evm_object_get_user_data(global_runtime, obj_val);
    if( !user_data )
        return 0;
    *out_native_pointer_p = user_data;
    return 1;
}

static inline jerry_value_t jerry_value_to_string (const jerry_value_t value) {
    char *str = evm_2_string(global_runtime, value);
    jerry_value_t res = evm_string_create(global_runtime, str);
    evm_string_free(global_runtime, str);
    return res;
}

static inline jerry_value_t jerry_create_string_from_utf8 (const jerry_char_t *str_p) {
    return evm_string_create(global_runtime, str_p);
}

static inline jerry_value_t jerry_create_error_from_value (jerry_value_t value, int release) {
    return evm_throw(global_runtime, value);
}

static inline int jerry_value_is_number (const jerry_value_t value) {
    return evm_is_number(global_runtime, value);
}

static inline double jerry_get_number_value (const jerry_value_t value) {
    return evm_2_double(global_runtime, value);
}

static inline jerry_length_t jerry_arraybuffer_read (const jerry_value_t value,
                                       jerry_length_t offset,
                                       uint8_t *buf_p,
                                       jerry_length_t buf_size) {

}

static inline int jerry_value_is_constructor (const jerry_value_t value) {
    return evm_is_constructor(global_runtime, value);
}

static inline int  jerry_value_is_boolean (const jerry_value_t value) {
    return evm_is_boolean(global_runtime, value);
}

static inline jerry_size_t jerry_get_string_size (const jerry_value_t value) {
    return evm_string_len(global_runtime, value);
}

static inline jerry_get_boolean_value (const jerry_value_t value) {
    return evm_2_boolean(global_runtime, value);
}

static inline jerry_size_t jerry_string_to_char_buffer (const jerry_value_t value, jerry_char_t *buffer_p, jerry_size_t buffer_size) {
    int size = evm_string_len(global_runtime, value);
    char *str = evm_2_string(global_runtime, value);
    int cpy_size = buffer_size >= size ? size : buffer_size;
    memcpy(buffer_p, str, cpy_size);
    return cpy_size;
}

static inline int jerry_value_is_arraybuffer (const jerry_value_t value) {
    return evm_is_buffer(global_runtime, value);
}

static inline jerry_length_t jerry_get_arraybuffer_byte_length (const jerry_value_t value) {
    return evm_buffer_len(global_runtime, value);
}

static inline uint32_t jerry_get_array_length (const jerry_value_t value) {
    return evm_list_len(global_runtime, value);
}

#endif
