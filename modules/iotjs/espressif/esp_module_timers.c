#ifdef CONFIG_EVM_MODULE_TIMERS
#include "evm_module.h"
#include <FreeRTOS.h>
#include <timers.h>

static void callback_handler()
{
    
}

void *evm_timer_open(evm_t *e, int tick, int flag) {
    return NULL;
}

void evm_timer_destroy(evm_t *e, void *dev) {

}
#endif
