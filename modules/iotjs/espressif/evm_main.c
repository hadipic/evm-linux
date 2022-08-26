#include "evm_module.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


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

evm_val_t native_print(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    for( int i = 0; i < argc; i++)
        printf("%s ", evm_2_string(e, v[i]));
    printf("\r\n");
    return EVM_UNDEFINED;
}

void evm_main (void) {
    evm_t *env = evm_init();
    
    evm_global_set(env, "print", evm_mk_native(env, native_print, "print", 0));
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
