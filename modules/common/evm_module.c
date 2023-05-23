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

EVM_FUNCTION( native_print ){
    EVM_EPCV
    char *s = evm_2_string(e, v[0]);
    printf("%s\r\n", s);
    evm_string_free(e, s);
    EVM_RETURN(evm_mk_undefined(e))
}

EVM_FUNCTION(native_require) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[0]);
    evm_val_t res = evm_module_get(e, s);
    evm_string_free(e, s);
    EVM_RETURN( res );
}

EVM_FUNCTION(native_compile) {
    EVM_EPCV;
    char *s = evm_2_string(e, v[1]);
    if( evm_run_bytecode_file(e, s) ){
        evm_string_free(e, s);
        EVM_RETURN(  evm_mk_boolean(e, 1) )
    }
    evm_string_free(e, s);
    EVM_RETURN(evm_mk_boolean(e, 0));
}

static void evm_native_init(evm_t *e) {
    evm_global_set(e, "print", evm_mk_native(e, native_print, "print", 1));
    evm_global_set(e, "__require__", evm_mk_native(e, native_require, "__require__", 1));
    evm_global_set(e, "__compile__", evm_mk_native(e, native_compile, "__compile__", 2));
}

void evm_module_init(evm_t *env)
{
    evm_native_init(env);

    extern void evm_module_process(evm_t *e);
    evm_module_process(env);

    extern void evm_module_console(evm_t *e);
    evm_module_console(env);

#ifdef EVM_USE_MODULE_LVGL
    extern void evm_module_lvgl_event(evm_t *e);
    extern void evm_module_lvgl(evm_t *e);
    extern void evm_module_lvgl_misc(evm_t *e);
    extern void evm_module_lvgl_style(evm_t *e);
    extern void evm_module_lvgl_image(evm_t *e);
    evm_module_lvgl(env);
    evm_module_lvgl_event(env);
    
    evm_module_lvgl_misc(env);
    evm_module_lvgl_style(env);
    evm_module_lvgl_image(env);
#endif
}
