#include "evm_port_timer.h"


//start(timeout, repeat, callback)
EVM_FUNCTION(start) {
    EVM_EPCV;
    size_t timeout = (size_t)evm_2_integer(e, v[0]);
    int repeat = (size_t)evm_2_integer(e, v[1]);
    if (timeout < 1) {
        return evm_mk_boolean(e, 0);
    }
    evm_port_timer_t *timer = (evm_port_timer_t*)evm_malloc(sizeof(evm_port_timer_t));
    EVM_ASSERT(timer);
    timer->timeout = timeout;
    timer->repeat = repeat;
    timer->callback = v[2];

    int re = evm_port_timer_start(timer);
    if (re == 0) {
        return evm_object_create_user_data(e, timer);
    }
    else {
        return evm_mk_boolean(e, 0);
    }
}

//stop(obj)
EVM_FUNCTION(stop) {
    EVM_EPCV;
    evm_port_timer_t *timer = evm_object_get_user_data(e, v[0]);
    if (timer != NULL) {
        evm_port_timer_stop(timer);
        evm_free(timer);
    }
    return EVM_UNDEFINED;
}
