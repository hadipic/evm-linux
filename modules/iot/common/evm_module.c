#include "evm_module.h"

static evm_t *_runtime;

iot_console_out_t iot_console_out = NULL;

void iotjs_set_console_out(iot_console_out_t output) {
  iot_console_out = output;
}

#ifdef CONFIG_EVM_DEBUG_LOG
int iot_debug_level = DBGLEV_ERR;
FILE* iot_log_stream = NULL;
const char* iot_debug_prefix[4] = { "", "ERR", "WRN", "INF" };
#endif // ENABLE_DEBUG_LOG

evm_t *evm_runtime(void) {
   return  _runtime;
}

void evm_module_registry_init(evm_t *e) {
    _runtime = e;
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
    return size;
}

evm_val_t evm_module_registry_get(evm_t *e, int id) {
    evm_val_t registry = evm_global_get(e, "@registry");
    int size = evm_list_len(e, registry);

    if( id < 0 || id >= size ) {
        evm_val_free(e, registry);
        return evm_mk_undefined(e);
    }
    evm_val_t res = evm_list_get(e, registry, id);
    evm_val_free(e, registry);
    return res;
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

void evm_module_init(evm_t *env)
{
    evm_module_registry_init(env);
    evm_native_init(env);

#ifdef CONFIG_EVM_MODULE_ADC
    evm_module_adc(env);
#endif

#ifdef CONFIG_EVM_MODULE_UART
    evm_module_uart(env);
#endif

#ifdef CONFIG_EVM_MODULE_GPIO
    evm_module_gpio(env);
#endif

#ifdef CONFIG_EVM_MODULE_FS
    evm_module_fs(env);
#endif

#ifdef CONFIG_EVM_MODULE_NET
    evm_module_net(env);
#endif

#ifdef CONFIG_EVM_MODULE_PROCESS
    evm_module_process(env);
#endif

#ifdef CONFIG_EVM_MODULE_EVENT
    evm_module_events(env);
#endif

#ifdef CONFIG_EVM_MODULE_DNS
    evm_module_dns(env);
#endif

#ifdef CONFIG_EVM_MODULE_TIMER
    extern void evm_module_timer(evm_t *e);
    evm_module_timer(env);
#endif

#ifdef CONFIG_EVM_MODULE_BUFFER
    evm_module_buffer(env);
#endif

#ifdef CONFIG_EVM_MODULE_ASSERT
    evm_module_assert(env);
#endif

#ifdef CONFIG_EVM_MODULE_LIBC
    evm_module_libc(env);
#endif

#ifdef CONFIG_EVM_MODULE_SOCKET
    extern void evm_module_socket(evm_t *e);
    evm_module_socket(env);
#endif

#ifdef CONFIG_EVM_MODULE_WLAN
    evm_module_wlan(env);
#endif

#ifdef CONFIG_EVM_MODULE_LVGL
    extern void evm_module_lvgl_event(evm_t *e);
    extern void evm_module_lvgl(evm_t *e);
    extern void evm_module_lvgl_image(evm_t *e);
    evm_module_lvgl(env);
    evm_module_lvgl_event(env);
    evm_module_lvgl_image(env);
#endif

#ifdef CONFIG_EVM_MODULE_TCP
    extern void evm_module_tcp(evm_t *e);
    evm_module_tcp(env);
#endif

#ifdef CONFIG_EVM_MODULE_TLS
    extern void evm_module_tls(evm_t *e);
    evm_module_tls(env);
#endif

}

char* evm_buffer_allocate_from_number_array(evm_t *e, size_t size, const evm_val_t array) {
  char* buffer = evm_malloc(size);
  for (size_t i = 0; i < size; i++) {
    evm_val_t jdata = evm_list_get(e, array, i);
    buffer[i] = evm_2_integer(e, jdata);
    evm_val_free(e, jdata);
  }
  return buffer;
}

