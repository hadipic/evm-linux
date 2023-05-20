#ifndef __EVM_PORT_TIMER_H__
#define __EVM_PORT_TIMER_H__

#include "evm_module.h"
#include "evm_port_msgbus.h"

typedef struct evm_port_timer_t
{
    void* os_timer;
    size_t timeout;
    int repeat;
    evm_msg_handler func;
    evm_val_t callback;
} evm_port_timer_t;

int evm_port_timer_start(evm_port_timer_t *timer);
int evm_port_timer_stop(evm_port_timer_t *timer);

#endif
