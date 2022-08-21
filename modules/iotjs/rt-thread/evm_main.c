#include "evm_module.h"
#include <rtthread.h>

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

void evm_main (void) {
    evm_t *env = evm_init();
    evm_module_init(env);
    evm_val_t res = evm_run_file(env, "main.js");
    evm_val_free(env, res);
}
