/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"
#include <time.h>

void *evm_malloc(size_t size)
{
    void * m = malloc(size);
    memset(m, 0, size);
    return m;
}

void evm_free(void * p)
{
    if(p)
        free(p);
}

void *evm_realloc(void * p, size_t size)
{
    return realloc(p, size);
}

evm_val_t native_clock(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    double clk = clock();
    return evm_mk_number(e,  clk / CLOCKS_PER_SEC);
}

void evm_main (char *filename) {
    evm_t *e = evm_init();
    evm_module_init(e);
    evm_global_set(e, "clock", evm_mk_native(e, native_clock, "clock", 1));

    extern const uint32_t common_js_bc_size;
    extern const uint8_t common_js_bc[];
    evm_run_bytecode(e, common_js_bc, common_js_bc_size);

#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_shell(env);
#else
    evm_run_file(e, EVM_UNDEFINED, filename);
#endif
}

void evm_loop() {

}
