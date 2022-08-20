#include "evm_module.h"
#include <rtthread.h>

void * evm_malloc(size_t size)
{
    void * m = malloc(size);
    if( m ) 
        memset(m, 0 ,size);
    return m;
}

void vm_free(void * p)
{
    if(mem) 
        free(p);
}

static void module_init(evm_t *env) {
#ifdef CONFIG_EVM_MODULE_ADC
    evm_module_adc(env);
#endif

#ifdef CONFIG_EVM_MODULE_UART
    evm_module_uart(env);
#endif

#ifdef CONFIG_EVM_MODULE_GPIO
    evm_module_gpio(env);
#endif
}

void evm_main (const char *file) {
    evm_t *env = evm_init();
    evm_module_init(env);
    module_init(env);

    evm_val_t res = evm_run_file(env, file);
    evm_val_free(env, res);
}
