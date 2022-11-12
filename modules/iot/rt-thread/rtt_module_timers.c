
#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_TIMER
#include <rtthread.h>

static evm_t *timer_e;

static void callback_handler(void *parameter)
{
    
}

void *evm_timer_open(evm_t *e, int tick, int flag) {
    rt_timer_t timer = rt_timer_create("timer",
                                       callback_handler,
                                       NULL,
                                       tick,
                                       flag == EVM_TIMER_ONE_SHOT ? RT_TIMER_FLAG_ONE_SHOT:RT_TIMER_FLAG_PERIODIC);

    rt_timer_start(timer);
    return timer;
}

void evm_timer_destroy(evm_t *e, void *dev) {
    rt_timer_t timer = dev;
    rt_timer_stop(timer);
    rt_timer_delete(timer);
}

#endif
