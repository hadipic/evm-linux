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
#include "evm_module.h"
#include "iotjs.h"
#include "jerryscript.h"

static evm_t *_runtime;

evm_t *evm_runtime(void) {
   return  _runtime;
}

EVM_FUNCTION(native_require_module) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[0]);
    evm_val_t res = evm_module_get(e, s);
    evm_string_free(e, s);
    EVM_RETURN( res );
}

EVM_FUNCTION(native_require_js) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[1]);
    if( evm_run_file(e, EVM_UNDEFINED, s) ){
        evm_string_free(e, s);
        EVM_RETURN(  evm_mk_boolean(e, 1) )
    }
    evm_string_free(e, s);
    EVM_RETURN(evm_mk_boolean(e, 0));
}

EVM_FUNCTION(native_require_bc) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[1]);
    if( evm_run_bytecode_file(e, s) ){
        evm_string_free(e, s);
        EVM_RETURN(  evm_mk_boolean(e, 1) )
    }
    evm_string_free(e, s);
    EVM_RETURN(evm_mk_boolean(e, 0));
}

EVM_FUNCTION(native_gc) {
    EVM_EPCV;
    evm_heap_gc(e);
    EVM_RETURN(evm_mk_boolean(e, 0));
}

static void evm_native_init(evm_t *e) {
    evm_global_set(e, "gc", evm_mk_native(e, native_gc, "gc", 0));
    evm_global_set(e, "__require_module__", evm_mk_native(e, native_require_module, "__require_module__", EVM_VARARGS));
    evm_global_set(e, "__require_js__", evm_mk_native(e, native_require_js, "__require_js__", EVM_VARARGS));
    evm_global_set(e, "__require_bc__", evm_mk_native(e, native_require_bc, "__require_bc__", EVM_VARARGS));
}

void evm_module_init(evm_t *env)
{
    jerry_value_t res;
    jerry_set_runtime(env);
    evm_native_init(env);

    EVM_LOG("module process init\r\n");
    extern void evm_module_process(evm_t *e);
    evm_module_process(env);

    EVM_LOG("module console init\r\n");
    extern void evm_module_console(evm_t *e);
    evm_module_console(env);

    extern jerry_value_t iotjs_init_buffer(void);
    res = iotjs_init_buffer();
    evm_global_set(env, "@native.buffer", res);
    evm_val_free(env, res);

#ifdef EVM_USE_MODULE_ADC
    EVM_LOG("module adc init\r\n");
    extern jerry_value_t iotjs_init_adc(void);
    res = iotjs_init_adc();
    evm_global_set(env, "@native.adc", res);
    evm_val_free(env, res);
#endif

#ifdef EVM_USE_MODULE_GPIO
    EVM_LOG("module gpio init\r\n");
    extern jerry_value_t iotjs_init_gpio(void);
    res = iotjs_init_gpio();
    evm_global_set(env, "@native.gpio", res);
    evm_val_free(env, res);
#endif

#ifdef EVM_USE_MODULE_FS
    EVM_LOG("module fs init\r\n");
    extern jerry_value_t iotjs_init_fs(void);
    res = iotjs_init_fs();
    evm_global_set(env, "@native.fs", res);
    evm_val_free(env, res);
#endif

#ifdef EVM_USE_MODULE_CJSON
    EVM_LOG("module cjson init\r\n");
    extern void evm_module_cjson(evm_t *e);
    evm_module_cjson(env);
#endif

#ifdef EVM_USE_MODULE_HEATSHRINK
    EVM_LOG("module heatshrink init\r\n");
    extern void evm_module_heatshrink(evm_t *e);
    evm_module_heatshrink(env);
#endif

#ifdef EVM_USE_MODULE_BASE64
    EVM_LOG("module base64 init\r\n");
    extern void evm_module_base64(evm_t *e);
    evm_module_base64(env);
#endif

#ifdef EVM_USE_MODULE_LVGL
    extern void evm_module_lvgl_event(evm_t *e);
    extern void evm_module_lvgl(evm_t *e);
    extern void evm_module_lvgl_misc(evm_t *e);
    extern void evm_module_lvgl_style(evm_t *e);
    extern void evm_module_lvgl_image(evm_t *e);
    extern void evm_module_lvgl_timeout(evm_t *e);
    EVM_LOG("module lvgl init\r\n");
    evm_module_lvgl(env);
    EVM_LOG("module lvgl event init\r\n");
    evm_module_lvgl_event(env);
    
    EVM_LOG("module lvgl misc init\r\n");
    evm_module_lvgl_misc(env);
    EVM_LOG("module lvgl style init\r\n");
    evm_module_lvgl_style(env);
    EVM_LOG("module lvgl image init\r\n");
    evm_module_lvgl_image(env);
    EVM_LOG("module lvgl timeout init\r\n");
    evm_module_lvgl_timeout(env);
#endif

#ifdef EVM_USE_MODULE_EX
    evm_module_init_ex(env);
#endif
}

