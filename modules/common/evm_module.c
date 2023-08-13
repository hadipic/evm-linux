/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"

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
    evm_global_set(e, "__require_module__", evm_mk_native(e, native_require_module, "__require__", EVM_VARARGS));
    evm_global_set(e, "__require_js__", evm_mk_native(e, native_require_js, "__require_js__", EVM_VARARGS));
    evm_global_set(e, "__require_bc__", evm_mk_native(e, native_require_bc, "__require_bc__", EVM_VARARGS));
}

void evm_module_init(evm_t *env)
{
    evm_native_init(env);
    EVM_LOG("module process init\r\n");
    extern void evm_module_process(evm_t *e);
    evm_module_process(env);

    EVM_LOG("module console init\r\n");
    extern void evm_module_console(evm_t *e);
    evm_module_console(env);

#ifdef EVM_USE_MODULE_GPIO
    EVM_LOG("module gpio init\r\n");
    extern void evm_module_gpio(evm_t *e);
    evm_module_gpio(env);
#endif

#ifdef EVM_USE_MODULE_ADC
    EVM_LOG("module adc init\r\n");
    extern void evm_module_adc(evm_t *e);
    evm_module_adc(env);
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
