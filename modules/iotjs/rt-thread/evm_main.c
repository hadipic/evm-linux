#include "evm_module.h"
#include <rtthread.h>

void *evm_malloc(size_t size)
{
    void * m = rt_malloc(size);
    if( m ) 
        memset(m, 0 ,size);
    return m;
}

void evm_free(void * p)
{
    if(p) 
        rt_free (p);
}

void *evm_realloc(void *p, size_t size)
{
    void * m = rt_realloc(p, size);
    if( m ) 
        memset(m, 0 ,size);
    return m;
}

void evm_main (void) {
    evm_t *env = evm_init();
    evm_module_init(env);
#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_repl(env);
    printf("quit repl mode\r\n");
#else
    evm_run_file(env, "main.js");
#endif

    while(1){
    #ifdef CONFIG_EVM_MODULE_PROCESS
        evm_module_process_poll(env);
    #endif
    }
}
