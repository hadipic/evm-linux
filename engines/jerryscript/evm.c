/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm.h"
#include "jcontext.h"

int (*evm_print)(const char *fmt, ...) = printf;

void evm_register_print(int (*fn)(const char *fmt, ...)) {
    evm_print = fn;
}

evm_val_t evm_string_create(evm_t *e, const char *str) {
    return jerry_string_sz(str);
}

int evm_string_len(evm_t *e, evm_val_t o) {
    return (int)jerry_string_length(o);
}

/*** 字节数组对象操作函数 ***/
evm_val_t evm_buffer_create(evm_t *e, uint8_t *buf, int len) {
    jerry_value_t buffer = jerry_arraybuffer(len);
    jerry_arraybuffer_write(buffer, 0, buf, len);
    return jerry_typedarray_with_buffer(JERRY_TYPEDARRAY_INT8, buffer);
}

uint8_t *evm_buffer_addr(evm_t *e, evm_val_t o) {
    jerry_length_t byteLength = 0;
    jerry_length_t byteOffset = 0;
    jerry_value_t buffer = jerry_typedarray_buffer(o, &byteOffset, &byteLength);
    return jerry_arraybuffer_data(buffer);
}

int evm_buffer_len(evm_t *e, evm_val_t o) {
    jerry_length_t byteLength = 0;
    jerry_length_t byteOffset = 0;
    jerry_value_t buffer = jerry_typedarray_buffer(o, &byteOffset, &byteLength);
    return (int)byteLength;
}

/*** 列表对象操作函数 ***/
evm_val_t evm_list_create(evm_t *e) {
    return jerry_array(0);
}

int evm_list_len(evm_t *e, evm_val_t o) {
    return (int)jerry_array_length(o);
}

evm_err_t evm_list_set(evm_t *e, evm_val_t o, int i, evm_val_t v) {
    jerry_value_t ret_val = jerry_object_set_index(o, i, v);
    jerry_value_free(ret_val);
    return ec_ok;
}

evm_val_t evm_list_get(evm_t *e, evm_val_t o, int i) {
    return jerry_object_get_index(o, i);
}

/*** 对象操作函数 ***/
evm_val_t evm_object_create(evm_t *e) {
    jerry_value_t obj = jerry_object();
    return obj;
}

evm_val_t evm_object_create_user_data(evm_t *e, void *data) {
    jerry_value_t obj = jerry_object();
    jerry_object_set_native_ptr(obj, NULL, data);
    return obj;
}

void evm_object_set_user_data(evm_t *e, evm_val_t o, void *data) {
    jerry_object_set_native_ptr(o, NULL, data);
}

void *evm_object_get_user_data(evm_t *e, evm_val_t o) {
    return jerry_object_get_native_ptr(o, NULL);
}

evm_val_t evm_global_get(evm_t *e, const char* key) {
    jerry_value_t global_object = jerry_current_realm ();
    jerry_value_t value = jerry_object_get_sz(global_object, key);
    jerry_value_free (global_object);
    return value;
}

evm_err_t evm_global_set(evm_t *e, const char *key, evm_val_t v) {
    jerry_value_t global_object = jerry_current_realm ();
    jerry_object_set_sz(global_object, key, v);
    jerry_value_free (global_object);
    return ec_ok;
}

void evm_global_delete(evm_t *e, const char *key) {
    jerry_value_t global_object = jerry_current_realm ();
    jerry_object_delete_sz(global_object, key);
    jerry_value_free (global_object);
}

/*** 成员操作函数 ***/
evm_val_t evm_prop_get(evm_t *e, evm_val_t o, const char* key) {
    return jerry_object_get_sz(o, key);
}

evm_err_t evm_prop_set(evm_t *e, evm_val_t o, const char *key, evm_val_t v) {
    jerry_object_set_sz(o, key, v);
    return ec_ok;
}

void evm_prop_delete(evm_t *e, evm_val_t o, const char *key){
    jerry_object_delete_sz(o, key);
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
    jerry_heap_gc(JERRY_GC_PRESSURE_LOW);
}

evm_val_t evm_throw(evm_t *e, evm_val_t v) {
    evm_val_t value = jerry_throw_value(v, true);
    jerry_value_free(value);
}

EVM_FUNCTION(native_require) {
    EVM_EPCV;
    return evm_module_get(e, evm_2_string(e, v[0]));
}

evm_t *evm_init(void) {
    jerry_init (JERRY_INIT_EMPTY);
    evm_global_set(&JERRY_CONTEXT_STRUCT, "@system", evm_object_create(&JERRY_CONTEXT_STRUCT));
    evm_global_set(&JERRY_CONTEXT_STRUCT, "require", evm_mk_native(&JERRY_CONTEXT_STRUCT, native_require, "require", 1));
    return &JERRY_CONTEXT_STRUCT;
}

void evm_deinit(evm_t *e) {
    jerry_cleanup ();
}

evm_val_t evm_run_bytecode(evm_t *e, uint8_t *buf, size_t buf_len) {
    jerry_value_t func = jerry_exec_snapshot(buf, buf_len, 0, 0, NULL);
    return func;
}

int evm_run_bytecode_file(evm_t *e, const char *path) {
    uint8_t *buf;
    size_t buf_len;
    int res = 1;
    buf = evm_load_file(path, &buf_len);
    if (!buf) {
        return 0;
    }

    jerry_value_t func = jerry_exec_snapshot(buf, buf_len, 0, JERRY_SNAPSHOT_EXEC_COPY_DATA, NULL);

    jerry_value_free (func);
    evm_free(buf);
    return res;
}

int evm_run_file(evm_t *e, evm_val_t this_obj, const char *path) {
    uint8_t *buf;
    size_t buf_len;
    int res = 1;
    buf = evm_load_file(path, &buf_len);
    if (!buf) {
        return 0;
    }

    jerry_parse_options_t parse_options;
    parse_options.options = JERRY_PARSE_HAS_SOURCE_NAME | JERRY_PARSE_HAS_START;
    parse_options.source_name = jerry_string_sz (path);
    parse_options.start_line = 1;
    parse_options.start_column = 1;

    jerry_value_t parsed_code = jerry_parse (buf, buf_len, &parse_options);
    if (!jerry_value_is_exception (parsed_code))
    {
        evm_print("parse: ok\r\n");
        jerry_value_free (jerry_run (parsed_code));
    } else {
        evm_print("parse: exception\r\n");
    }
    jerry_value_free (parsed_code);
    jerry_value_free (parse_options.source_name);
    evm_free(buf);
    return res;
}

evm_val_t evm_run_string(evm_t *e, evm_val_t this_obj, const char *source) {
    return jerry_eval (source, strlen(source), JERRY_PARSE_NO_OPTS);
}

void evm_run_shell(evm_t *e) {
#ifdef EVM_USE_MODULE_REPL
#include "evm_module.h"
    evm_run_repl(e);
#endif
}

evm_val_t evm_call(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t ret =  jerry_call(obj, pthis, v, (jerry_size_t)argc);
    return ret;
}

evm_val_t evm_call_free(evm_t *e, evm_val_t obj, evm_val_t pthis, int argc, evm_val_t *v) {
    evm_val_t ret =  jerry_call(obj, pthis, v, (jerry_size_t)argc);
    jerry_value_free(ret);
    return ret;
}

/*** value操作 ***/
double evm_2_double(evm_t *e, evm_val_t v) {
    return jerry_value_as_number(v);
}

int32_t evm_2_integer(evm_t *e, evm_val_t v) {
    return jerry_value_as_int32(v);
}

int evm_2_boolean(evm_t *e, evm_val_t v) {
    return jerry_value_is_true(v);
}

char *evm_2_string(evm_t *e, evm_val_t v) {
    v = jerry_value_to_string (v);
    jerry_size_t size = jerry_string_size(v, JERRY_ENCODING_UTF8);
    char *buf = evm_malloc(size + 1);
    buf[size] = 0;
    jerry_string_to_buffer(v, JERRY_ENCODING_UTF8, buf, size);
    evm_val_free(e, v);
    return buf;
}

void evm_string_free(evm_t *e, char *str){
    evm_free(str);
}

int evm_is_number(evm_t *e, evm_val_t v) {
    (void)e;
    return jerry_value_is_number(v);
}

int evm_is_integer(evm_t *e, evm_val_t v) {
    (void)e;
    return evm_is_number(e, v);
}

int evm_is_string(evm_t *e, evm_val_t v) {
    (void)e;
    return jerry_value_is_string(v);
}

int evm_is_boolean(evm_t *e, evm_val_t v) {
    (void)e;
    return jerry_value_is_boolean(v);
}

int evm_is_buffer(evm_t *e, evm_val_t v) {
    return jerry_value_is_typedarray(v) && jerry_typedarray_type(v) == JERRY_TYPEDARRAY_INT8;
}

int evm_is_native(evm_t *e, evm_val_t v) {
    return jerry_value_is_function(v);
}

int evm_is_callable(evm_t *e, evm_val_t v) {
    return jerry_value_is_function(v);
}

int evm_is_invoke(evm_t *e, evm_val_t v) {
    if( !evm_is_object(e, v) )
        return 0;
    if( evm_object_get_user_data(e, v) == NULL )
        return 0;
    return 1;
}

int evm_is_list(evm_t *e, evm_val_t v) {
    return jerry_value_is_array(v);
}

int evm_is_undefined(evm_t *e, evm_val_t v) {
    (void)e;
    return jerry_value_is_undefined(v);
}

int evm_is_null(evm_t *e, evm_val_t v) {
    (void)e;
    return jerry_value_is_null(v);
}

int evm_is_object(evm_t *e, evm_val_t v) {
    (void)e;
    return jerry_value_is_object(v);
}

evm_val_t evm_mk_number(evm_t *e, double d){
    return jerry_number(d);
}

evm_val_t evm_mk_string(evm_t *e, const char *s){
    evm_val_t res;
    res = jerry_string_sz(s);
    return res;
}

evm_val_t evm_mk_lstring(evm_t *e, const char *s, int len) {
    evm_val_t res;
    res = jerry_string(s, len, JERRY_ENCODING_UTF8);
    return res;
}

evm_val_t evm_mk_boolean(evm_t *e, int v){
    return jerry_boolean(v);
}

evm_val_t evm_mk_native(evm_t *e, evm_native_t v, const char *name, int len) {
    return jerry_function_external(v);
}

evm_val_t evm_mk_null(evm_t *e){
    return jerry_null();
}

evm_val_t evm_mk_undefined(evm_t *e){
    return jerry_undefined();
}

evm_val_t evm_mk_invoke(evm_t *e, void *user_data) {
    return evm_object_create_user_data(e, user_data);
}

void *evm_2_invoke(evm_t *e, evm_val_t o) {
    return evm_object_get_user_data(e, o);
}

void evm_val_free(evm_t *e, evm_val_t v) {
    jerry_value_free(v);
}

evm_val_t evm_val_duplicate(evm_t *e, evm_val_t v) {
    return jerry_value_copy(v);
}

evm_val_t evm_mk_global(evm_t *e) {
    return jerry_current_realm();
}

jerry_char_t *JERRY_ATTR_WEAK
jerry_port_path_normalize (const jerry_char_t *path_p, /**< input path */
                           jerry_size_t path_size) /**< size of the path */
{
  jerry_char_t *buffer_p = (jerry_char_t *) evm_malloc (path_size + 1);

  if (buffer_p == NULL)
  {
    return NULL;
  }

  /* Also copy terminating zero byte. */
  memcpy (buffer_p, path_p, path_size + 1);

  return buffer_p;
} /* jerry_port_normalize_path */

void
jerry_port_path_free (jerry_char_t *path_p)
{
  evm_free (path_p);
} /* jerry_port_path_free */

jerry_size_t JERRY_ATTR_WEAK
jerry_port_path_base (const jerry_char_t *path_p) /**< path */
{
  const jerry_char_t *basename_p = (jerry_char_t *) strrchr ((char *) path_p, '/') + 1;

  if (basename_p == NULL)
  {
    return 0;
  }

  return (jerry_size_t) (basename_p - path_p);
} /* jerry_port_get_directory_end */

/**
 * Determines the size of the given file.
 * @return size of the file
 */
static jerry_size_t
jerry_port_get_file_size (FILE *file_p) /**< opened file */
{
  fseek (file_p, 0, SEEK_END);
  long size = ftell (file_p);
  fseek (file_p, 0, SEEK_SET);

  return (jerry_size_t) size;
} /* jerry_port_get_file_size */

/**
 * Opens file with the given path and reads its source.
 * @return the source of the file
 */
jerry_char_t *JERRY_ATTR_WEAK
jerry_port_source_read (const char *file_name_p, /**< file name */
                        jerry_size_t *out_size_p) /**< [out] read bytes */
{
  FILE *file_p = fopen (file_name_p, "rb");

  if (file_p == NULL)
  {
    return NULL;
  }

  jerry_size_t file_size = jerry_port_get_file_size (file_p);
  jerry_char_t *buffer_p = (jerry_char_t *) malloc (file_size);

  if (buffer_p == NULL)
  {
    fclose (file_p);
    return NULL;
  }

  size_t bytes_read = fread (buffer_p, 1u, file_size, file_p);

  if (bytes_read != file_size)
  {
    fclose (file_p);
    free (buffer_p);
    return NULL;
  }

  fclose (file_p);
  *out_size_p = (jerry_size_t) bytes_read;

  return buffer_p;
} /* jerry_port_source_read */

/**
 * Release the previously opened file's content.
 */
void JERRY_ATTR_WEAK
jerry_port_source_free (uint8_t *buffer_p) /**< buffer to free */
{
  evm_free (buffer_p);
} /* jerry_port_source_free */

void
jerry_port_log (const char *message_p) /**< message */
{
  evm_print("%s", message_p);
} /* jerry_port_log */

/**
 * Read a line from standard input as a zero-terminated string.
 *
 * @param out_size_p: length of the string
 *
 * @return pointer to the buffer storing the string,
 *         or NULL if end of input
 */
jerry_char_t *
jerry_port_line_read (jerry_size_t *out_size_p)
{
  (void) out_size_p;
  return NULL;
} /* jerry_port_line_read */

/**
 * Aborts the program.
 */
void
jerry_port_fatal (jerry_fatal_code_t code)
{
  exit ((int) code);
} /* jerry_port_fatal */

/**
 * Dummy function to get the time zone adjustment.
 *
 * @return 0
 */
int32_t
jerry_port_local_tza (double unix_ms)
{
  (void) unix_ms;

  /* We live in UTC. */
  return 0;
} /* jerry_port_local_tza */

/**
 * Dummy function to get the current time.
 *
 * @return 0
 */
double
jerry_port_current_time (void)
{
  return 0;
} /* jerry_port_current_time */

#include "jerryscript-port.h"

#ifndef JERRY_GLOBAL_HEAP_SIZE
#define JERRY_GLOBAL_HEAP_SIZE 512
#endif /* JERRY_GLOBAL_HEAP_SIZE */

/**
 * Pointer to the current context.
 * Note that it is a global variable, and is not a thread safe implementation.
 */
static jerry_context_t *current_context_p = NULL;

/**
 * Allocate a new external context.
 *
 * @param context_size: requested context size
 *
 * @return total allcoated size
 */
size_t JERRY_ATTR_WEAK
jerry_port_context_alloc (size_t context_size)
{
  size_t total_size = context_size + JERRY_GLOBAL_HEAP_SIZE * 1024;
  current_context_p = evm_malloc(total_size);

  return total_size;
} /* jerry_port_context_alloc */

/**
 * Get the current context.
 *
 * @return the pointer to the current context
 */
jerry_context_t *JERRY_ATTR_WEAK
jerry_port_context_get (void)
{
  return current_context_p;
} /* jerry_port_context_get */

/**
 * Free the currently allocated external context.
 */
void JERRY_ATTR_WEAK
jerry_port_context_free (void)
{
  evm_free(current_context_p);
} /* jerry_port_context_free */

