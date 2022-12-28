#include "evm_module.h"
#include <pthread.h>
#include <unistd.h>
#include "linux_system.h"

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
    evm_t *env = evm_init();
    evm_module_init(env);

#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_shell(env);
#else
    evm_run_file(env, EVM_UNDEFINED, filename);
#endif
}

void evm_loop() {
    system_loop();
}
