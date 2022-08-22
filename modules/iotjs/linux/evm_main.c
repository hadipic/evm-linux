#include "evm_module.h"
#include <pthread.h>
#include <unistd.h>


void evm_main (void) {
    evm_t *env = evm_init();
    evm_module_init(env);

    evm_val_t res = evm_run_file(env, "./main.js");
    evm_val_free(env, res);

    while(1){
    #ifdef CONFIG_EVM_MODULE_PROCESS
        evm_module_process_poll(env);
    #endif
        usleep(10);
    }
}
