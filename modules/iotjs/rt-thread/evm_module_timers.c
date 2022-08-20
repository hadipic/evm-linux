#ifdef CONFIG_EVM_MODULE_TIMERS
#include "evm_module.h"
#include <rtthread.h>

static evm_t *timer_e;

static void *callback_handler(void *parameter)
{

}

//setTimeout(callback, delay[, args..])
static evm_val_t evm_module_timers_setTimeout(evm_t *e, evm_val_t *p, int argc, evm_val_t *v)
{
    if (argc < 2 || !evm_is_callable(e, v[0]) || !evm_is_integer(e, v[1]))
        return EVM_VAL_UNDEFINED;

    int tick = evm_2_integer(e, v[1]);
    rt_timer_t timer = rt_timer_create("timer",
                                       callback_handler,
                                       NULL,
                                       tick,
                                       RT_TIMER_FLAG_ONE_SHOT);

    rt_err_t rt_timer_start(timer);
    evm_val_t obj = evm_object_create_user_data(e, timer);
    evm_prop_set(e, obj, "callback", evm_val_duplicate(e, v[0]));
    return obj;
}

//clearTimeout(timeout)
static evm_val_t evm_module_timers_clearTimeout(evm_t *e, evm_val_t *p, int argc, evm_val_t *v)
{
    rt_timer_t timer = evm_object_get_ext_data(e, v[0]);
    rt_timer_stop(timer);
    rt_timer_delete(timer);
    return EVM_VAL_UNDEFINED;
}

//setInterval(callback, delay[, args..])
static evm_val_t evm_module_timers_setInterval(evm_t *e, evm_val_t *p, int argc, evm_val_t *v)
{
    if (argc < 2 || !evm_is_callable(e, v[0]) || !evm_is_integer(e, v[1]))
        return EVM_VAL_UNDEFINED;

    int tick = evm_2_integer(e, v[1]);

    rt_timer_t timer = rt_timer_create("timer",
                                       callback_handler,
                                       NULL,
                                       tick,
                                       RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
    rt_err_t rt_timer_start(timer);
    evm_val_t obj = evm_object_create_user_data(e, timer);
    evm_prop_set(e, obj, "callback", evm_val_duplicate(e, v[0]));
    return obj;
}

//clearInterval(timeout)
static evm_val_t evm_module_timers_clearInterval(evm_t *e, evm_val_t *p, int argc, evm_val_t *v)
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
