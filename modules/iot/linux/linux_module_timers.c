#ifdef CONFIG_EVM_MODULE_TIMERS
#include "evm_module.h"
#include "linux_system.h"
#include "uv.h"

typedef struct _timer_dev_t {
    int id;
    uv_timer_t handle;
    evm_t *e;
    int refId;
} _timer_dev_t;

static void timeout_handler(uv_timer_t* handle) {
    _timer_dev_t *timer = handle->data;
    evm_t *e = timer->e;
    evm_val_t cb = evm_module_registry_get(e, timer->refId);
    evm_call_free(e, cb, EVM_UNDEFINED, 0, NULL);
    evm_val_free(e, cb);
}


void *evm_timer_open(evm_t *e, evm_val_t cb, int tick, int flag) {
    _timer_dev_t *dev = evm_malloc(sizeof (_timer_dev_t));
    uv_timer_init(system_get_uv_loop(), &dev->handle);
    if( flag == EVM_TIMER_PERIOD )
        dev->id = uv_timer_start(&dev->handle, timeout_handler, tick, tick);
    else
        dev->id = uv_timer_start(&dev->handle, timeout_handler, tick, 0);
    dev->handle.data = dev;
    dev->refId = evm_module_registry_add(e, evm_val_duplicate(e, cb));
    dev->e = e;
    return dev;
}

void evm_timer_destroy(evm_t *e, void *dev) {
    _timer_dev_t *timer = dev;
    if( !uv_is_closing(&timer->handle))
        uv_close(&timer->handle, NULL);
    evm_free(dev);
    evm_module_registry_remove(e, timer->refId);
}

#endif
