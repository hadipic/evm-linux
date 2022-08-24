#include "evm_module.h"
#include <pthread.h>
#include <unistd.h>


void evm_main (void) {
    evm_t *env = evm_init();
    evm_module_init(env);

#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_repl(env);
#endif

    evm_run_file(env, "./main.js");

    while(1){
    #ifdef CONFIG_EVM_MODULE_PROCESS
        evm_module_process_poll(env);
    #endif
        usleep(10);
    }
}
