#ifdef CONFIG_EVM_MODULE_TIMERS
#include "evm_module.h"
#include <time.h>
#include <signal.h>
#include <errno.h>

#define NUM_OF_TIMERS   16

static evm_t *timer_e;
static timer_t timers[NUM_OF_TIMERS];

static void timer_init(evm_t *e) {
    timer_e = e;
    evm_val_t registry = evm_list_create(e);
    evm_global_set(e, "@timers", registry);
}

static int timer_add(evm_t *e, evm_val_t v) {
    evm_val_t registry = evm_global_get(e, "@timers");
    int size = evm_list_len(e, registry);
    if( size >= NUM_OF_TIMERS )
        return -1;
    for(int i = 0; i < size; i++) {
        evm_val_t item = evm_list_get(e, registry, i);
        if( evm_is_undefined(e, item) ) {
            evm_val_free(e, item);
            evm_list_set(e, registry, i, v);
            return i;
        }
        evm_val_free(e, item);
    }
    evm_list_set(e, registry, size, v);
    return -1;
}

evm_val_t timer_get(evm_t *e, int id) {
    evm_val_t registry = evm_global_get(e, "@timers");
    int size = evm_list_len(e, registry);
    evm_val_free(e, registry);
    if( id < 0 || id >= size ) {
        return evm_mk_undefined(e);
    }
    return evm_list_get(e, registry, id);
}

void timer_remove(evm_t *e, int id) {
    evm_val_t registry = evm_global_get(e, "@timers");
    int size = evm_list_len(e, registry);
    evm_val_free(e, registry);
    if( id < 0 || id >= size )
        return;
    evm_list_set(e, registry, id, evm_mk_undefined(e));
}

static void callback_handler(union sigval v)
{
    evm_val_t callback = timer_get(timer_e, v.sival_int);
    evm_module_next_tick(timer_e, 1, &callback);
}

static timer_t timer(int id, int delay, int once)
{
    timer_t timerid;
    int ret;

    struct sigevent sev;

    // handle in thread when timeout
    memset(&sev, 0, sizeof(struct sigevent));
    sev.sigev_value.sival_ptr = &timerid;
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = callback_handler;
    sev.sigev_value.sival_int = id;

    struct itimerspec its; // duration settings

    ret = timer_create(CLOCK_REALTIME, &sev, &timerid);
    if (ret == -1)
    {
        return NULL;
    }

    // set timeout, only once
    // it_value the first timeout duration
    // it_interval the next timeout duration
    if (delay >= 1000)
    {
        its.it_value.tv_sec = delay / 1000;
        its.it_value.tv_nsec = (delay % 1000) * 1000000;
    }
    else
    {
        its.it_value.tv_sec = 0;
        its.it_value.tv_nsec = delay * 1000000;
    }
    if( !once ) {
        its.it_interval.tv_sec = its.it_value.tv_sec;
        its.it_interval.tv_nsec = its.it_value.tv_nsec;
    }

    ret = timer_settime(timerid, TIMER_ABSTIME, &its, NULL);
    if (ret == -1)
    {
        return NULL;
    }

    return timerid;
}

//setTimeout(callback, delay[, args..])
static evm_val_t evm_module_timers_setTimeout(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 2 || !evm_is_callable(e, v[0]) || !evm_is_integer(e, v[1]))
    {
        return evm_mk_undefined(e);
    }
    int id = timer_add(e, v[0]);
    if (id < 0)
        return evm_mk_undefined(e);
    timer_t timerid = timer(id, evm_2_integer(e, v[1]), 1);
    if (timerid == NULL)
        return evm_mk_undefined(e);
    timers[id] = timerid;
    return evm_mk_undefined(e);
}

//clearTimeout(timeout)
static evm_val_t evm_module_timers_clearTimeout(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_integer(e, v[0]))
    {
        return evm_mk_undefined(e);
    }
    int id = evm_2_integer(e, v[0]);
    evm_val_t callback = evm_module_registry_get(e, id);
    if ( evm_is_undefined(e, callback) )
        return evm_mk_undefined(e);
    timer_t timerid = timers[id];
    if (timerid == NULL)
        return evm_mk_undefined(e);
    timer_delete(timerid);
    timer_remove(e, id);
    timers[id] = NULL;
    return evm_mk_undefined(e);
}

//setInterval(callback, delay[, args..])
static evm_val_t evm_module_timers_setInterval(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 2 || !evm_is_callable(e, v[0]) || !evm_is_integer(e, v[1]))
    {
        return evm_mk_undefined(e);
    }
    int id = timer_add(e, v[0]);
    if (id < 0)
        return evm_mk_undefined(e);
    timer_t timerid = timer(id, evm_2_integer(e, v[1]), 0);
    if (timerid == NULL)
        return evm_mk_undefined(e);
    timers[id] = timerid;
    return evm_mk_number(e, id);
}

//clearInterval(timeout)
static evm_val_t evm_module_timers_clearInterval(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_integer(e, v[0]))
    {
        return evm_mk_undefined(e);
    }
    evm_module_timers_clearTimeout(e, p, argc, v);
    return evm_mk_undefined(e);
}

evm_err_t evm_module_timers(evm_t *e) {
    timer_init(e);
    evm_global_set(e, "setTimeout", evm_mk_native(e, evm_module_timers_setTimeout, "setTimeout", 3));
    evm_global_set(e, "clearTimeout", evm_mk_native(e, evm_module_timers_clearTimeout, "setTimeout", 1));
    evm_global_set(e, "setInterval", evm_mk_native(e, evm_module_timers_setInterval, "setInterval", 3));
    evm_global_set(e, "clearInterval", evm_mk_native(e, evm_module_timers_clearInterval, "clearInterval", 1));
    return ec_ok;
}
#endif
