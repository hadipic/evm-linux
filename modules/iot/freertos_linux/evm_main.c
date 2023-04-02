/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"
#include "iot_system.h"

void *evm_malloc(size_t size)
{
    void * m = malloc(size);
    if( m )
        memset(m, 0 ,size);
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

void evm_main (char *filename) {
    system_loop();
    evm_t *e = evm_init();
    evm_module_init(e);

#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_shell(env);
#else
    evm_run_file(e, EVM_UNDEFINED, filename);
#endif
}

void evm_loop() {
    system_loop();
}
