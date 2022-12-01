#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_TIMER

//setTimeout(callback, delay[, args..])
static evm_val_t evm_module_timers_setTimeout(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 2 || !evm_is_callable(e, v[0]) || !evm_is_integer(e, v[1]))
        return EVM_UNDEFINED;

    int tick = evm_2_integer(e, v[1]);
    void *dev = evm_timer_open(e, v[0], tick, EVM_TIMER_ONE_SHOT);
    evm_val_t obj = evm_object_create_user_data(e, dev);
    int id = evm_module_registry_add(e, obj);
    return evm_mk_number(e, id);
}

//clearTimeout(timeout)
static evm_val_t evm_module_timers_clearTimeout(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    int id = evm_2_integer(e, v[0]);
    p = evm_module_registry_get(e, id);
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_module_registry_remove(e, id);
    evm_timer_destroy(e, dev);
    return EVM_UNDEFINED;
}

//setInterval(callback, delay[, args..])
static evm_val_t evm_module_timers_setInterval(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 2 || !evm_is_callable(e, v[0]) || !evm_is_integer(e, v[1]))
        return EVM_UNDEFINED;

    int tick = evm_2_integer(e, v[1]);
    void *dev = evm_timer_open(e, v[0], tick, EVM_TIMER_PERIOD);
    evm_val_t obj = evm_object_create_user_data(e, dev);
    int id = evm_module_registry_add(e, obj);
    return evm_mk_number(e, id);
}

//clearInterval(timeout)
static evm_val_t evm_module_timers_clearInterval(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return evm_module_timers_clearTimeout(e, p, argc, v);
}

void evm_module_timers(evm_t *e) {
    evm_global_set(e, "setTimeout", evm_mk_native(e, evm_module_timers_setTimeout, "setTimeout", 0));
    evm_global_set(e, "clearTimeout", evm_mk_native(e, evm_module_timers_clearTimeout, "clearTimeout", 0));
    evm_global_set(e, "setInterval", evm_mk_native(e, evm_module_timers_setInterval, "setInterval", 0));
    evm_global_set(e, "clearInterval", evm_mk_native(e, evm_module_timers_clearInterval, "clearInterval", 0));
}
#endif
