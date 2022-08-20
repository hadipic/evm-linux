#include "evm_module.h"

evm_t *evm_runtime;


void evm_module_registry_init(evm_t *e) {
    evm_runtime = e;
    evm_val_t registry = evm_list_create(e);
    evm_global_set(e, "@registry", registry);
}

int evm_module_registry_add(evm_t *e, evm_val_t v) {
    evm_val_t registry = evm_global_get(e, "@registry");
    int size = evm_list_len(e, registry);
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

evm_val_t evm_module_registry_get(evm_t *e, int id) {
    evm_val_t registry = evm_global_get(e, "@registry");
    int size = evm_list_len(e, registry);
    evm_val_free(e, registry);
    if( id < 0 || id >= size ) {
        return evm_mk_undefined(e);
    }
    return evm_list_get(e, registry, id);
}

void evm_module_registry_remove(evm_t *e, int id) {
    evm_val_t registry = evm_global_get(e, "@registry");
    int size = evm_list_len(e, registry);
    evm_val_free(e, registry);
    if( id < 0 || id >= size )
        return;
    evm_list_set(e, registry, id, evm_mk_undefined(e));
}

void evm_module_next_tick(evm_t *e, int argc, evm_val_t *v) {
#ifdef CONFIG_EVM_MODULE_PROCESS
    evm_val_t undef = evm_mk_undefined(e);
    evm_val_free(e, undef);
    evm_module_process_nextTick(e, undef, argc, v);
#endif
}

evm_err_t evm_module_event_add_listener(evm_t *e, evm_val_t pthis, const char *type, evm_val_t listener) {
    if( !evm_is_callable(e, listener) ) {
        evm_throw(e, evm_mk_string(e,"Listener must be a function"));
    }
    evm_val_t prop = evm_prop_get(e, pthis, "events");
    if( evm_is_undefined(e, prop) ) {
        evm_val_free(e, prop);
        prop = evm_object_create(e);
        evm_prop_set(e, pthis, "events", prop);
    }
    evm_prop_set(e, prop, type, listener);
    return ec_ok;
}

void evm_module_event_remove_listener(evm_t *e, evm_val_t pthis, const char *type) {
    evm_val_t prop = evm_prop_get(e, pthis, "events");
    if( evm_is_undefined(e, prop) ) {
        evm_val_free(e, prop);
        return;
    }
    evm_prop_delete(e, prop, type);
    evm_val_free(e, prop);
}

void evm_module_event_emit (evm_t *e, evm_val_t pthis, const char *type, int argc, evm_val_t *v) {
    evm_val_t prop = evm_prop_get(e, pthis, "events");
    evm_val_free(e, prop);
    if( evm_is_undefined(e, prop) ) {
        return;
    }
    evm_val_t listener = evm_prop_get(e, prop, type);
    evm_val_free(e, listener);
    if( evm_is_callable(e, listener)) {
        evm_val_t args[argc + 1];
        args[0] = listener;
        for(int i = 1; i < argc + 1; i++) {
            args[i] = *(v + i - 1);
        }
        evm_module_next_tick(e, argc + 1, args);
    }
}

static evm_val_t native_print(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    const char *s = evm_2_string(e, v[0]);
    printf("%s\r\n", s);
    return evm_mk_undefined(e);
}

static evm_val_t native_require(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    return evm_module_get(e, evm_2_string(e, v[0]));
}

static void evm_native_init(evm_t *e) {
    evm_global_set(e, "print", evm_mk_native(e, native_print, "print", 1));
    evm_global_set(e, "require", evm_mk_native(e, native_require, "require", 1));
}

evm_err_t evm_module_init(evm_t *env)
{
    evm_module_registry_init(env);
    evm_native_init(env);

    evm_err_t err;
#ifdef CONFIG_EVM_MODULE_ADC
    err = evm_module_adc(env);
    if (err != ec_ok)
    {
        evm_print("Failed to create adc module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_UART
    err = evm_module_uart(env);
    if (err != ec_ok)
    {
        evm_print("Failed to create uart module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_GPIO
    err = evm_module_gpio(env);
    if (err != ec_ok)
    {
        evm_print("Failed to create gpio module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_FS
    err = evm_module_fs(env);
    if (err != ec_ok)
    {
        printf("Failed to create fs module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_NET
    err = evm_module_net(env);
    if (err != ec_ok)
    {
        printf("Failed to create net module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_PROCESS
    err = evm_module_process(env);
    if (err != ec_ok)
    {
        printf("Failed to create process module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_EVENTS
    err = evm_module_events(env);
    if (err != ec_ok)
    {
        printf("Failed to create events module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_DNS
    err = evm_module_dns(env);
    if (err != ec_ok)
    {
        printf("Failed to create dns module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_TIMERS
    err = evm_module_timers(env);
    if (err != ec_ok)
    {
        printf("Failed to create timers module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_BUFFER
    err = evm_module_buffer(env);
    if (err != ec_ok)
    {
        printf("Failed to create buffer module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_ASSERT
    err = evm_module_assert(env);
    if (err != ec_ok)
    {
        printf("Failed to create assert module\r\n");
        return err;
    }
#endif

#ifdef CONFIG_EVM_MODULE_CFFI
    evm_module_cffi(env);
#endif
    return ec_ok;
}
