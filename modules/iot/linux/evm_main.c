/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"
#include <pthread.h>
#include <unistd.h>

#ifdef CONFIG_EVM_USE_UV
#include "linux_system.h"
#endif

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
#ifdef CONFIG_EVM_USE_UV
    system_loop();
#endif
    evm_t *e = evm_init();
    evm_module_init(e);

#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_shell(env);
#else
    evm_run_file(e, EVM_UNDEFINED, filename);
#endif
}

void evm_loop() {
#ifdef CONFIG_EVM_USE_UV
    system_loop();
#endif
}
