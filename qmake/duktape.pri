INCLUDEPATH += $$PWD/../engines/duktape
INCLUDEPATH += $$PWD/../engines/duktape/duktape/src-separate

HEADERS += \
    $$PWD/../engines/duktape/evm_type.h

SOURCES += \
    $$PWD/../engines/duktape/evm.c

SOURCES += \
    $$PWD/../engines/duktape/duktape/src-separate/duk_alloc_default.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_buffer.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_bytecode.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_call.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_codec.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_compile.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_debug.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_heap.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_inspect.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_memory.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_object.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_random.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_stack.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_string.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_api_time.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_array.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_boolean.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_buffer.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_cbor.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_date.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_date_unix.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_date_windows.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_duktape.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_encoding.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_error.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_function.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_global.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_json.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_math.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_number.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_object.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_performance.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_pointer.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_promise.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_proxy.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_reflect.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_regexp.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_string.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_symbol.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_thread.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_bi_thrower.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_builtins.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_debug_fixedbuffer.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_debug_macros.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_debug_vsnprintf.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_debugger.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_error_augment.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_error_longjmp.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_error_macros.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_error_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_error_throw.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hbuffer_alloc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hbuffer_assert.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hbuffer_ops.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hbufobj_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_alloc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_finalize.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_hashstring.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_markandsweep.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_memory.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_refcount.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_stringcache.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heap_stringtable.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_heaphdr_assert.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_alloc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_assert.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_class.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_enum.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_pc2line.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hobject_props.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hstring_assert.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hstring_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hthread_alloc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hthread_builtins.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hthread_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_hthread_stacks.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_js_arith.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_js_call.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_js_compiler.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_js_executor.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_js_ops.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_js_var.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_lexer.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_numconv.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_regexp_compiler.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_regexp_executor.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_replacements.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_selftest.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_tval.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_unicode_support.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_unicode_tables.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_bitdecoder.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_bitencoder.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_bufwriter.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_cast.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_double.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_hashbytes.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_memory.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_memrw.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_misc.c \
    $$PWD/../engines/duktape/duktape/src-separate/duk_util_tinyrandom.c





