#include "evm_module.h"

static void process_handler(evm_t *e, void* ptr) {
    evm_val_t queue = evm_global_get(e, "@processQueue");
    evm_val_free(e, queue);
    int len = evm_list_len(e, queue);
    for(int i = 0; i < len; i++) {
        evm_val_t obj = evm_list_get(e, queue, i);
        evm_val_free(e, obj);
        if( evm_is_object(e, obj) ) {
            evm_val_t callback = evm_prop_get(e, obj, "callback");
            evm_val_free(e, callback);
            evm_val_t arguments = evm_prop_get(e, obj, "arguments");
            evm_val_free(e, arguments);
            if( evm_is_list(e, arguments) ) {
                int argc = evm_list_len(e, arguments);
                evm_val_t args[ argc ];
                for(int i = 0; i < argc; i++){
                    args[i] = evm_list_get(e, arguments, i);
                }
                evm_call_free(e, callback, EVM_UNDEFINED, argc, args);
            } else {
                evm_call_free(e, callback, EVM_UNDEFINED, 0, NULL);
            }
            evm_list_set(e, queue, i, evm_mk_undefined(e));
        }
    }
}

static void queue_push(evm_t *e, evm_val_t queue, evm_val_t obj) {
    int len = evm_list_len(e, queue);
    for(int i = 0; i < len; i++) {
        evm_val_t item = evm_list_get(e, queue, i);
        if( evm_is_undefined(e, item) ) {
            evm_list_set(e, queue, i, obj);
            evm_eventbus_t event;
            event.handler = process_handler;
            evm_eventbus_set(&event);
            return;
        }
    }
    evm_list_set(e, queue, len, obj);
    evm_eventbus_t event;
    event.handler = process_handler;
    evm_eventbus_set(&event);
}

//process.nextTick(callback, [...args]);
evm_val_t evm_module_process_nextTick(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    if (argc > 0 && evm_is_callable(e, v[0]))
    {
        evm_val_t queue = evm_global_get(e, "@processQueue");
        evm_val_free(e, queue);
        evm_val_t obj = evm_object_create(e);
        evm_prop_set(e, obj, "callback", evm_val_duplicate(e, v[0]));
        if( argc > 1 ) {
            evm_val_t arguments = evm_list_create(e);
            for(int i = 0; i < argc - 1; i++){
                evm_list_set(e, arguments, i, evm_val_duplicate(e, v[i + 1]));
            }
            evm_prop_set(e, obj, "arguments", arguments);
        }
        queue_push(e, queue, obj);
    }
    return evm_mk_undefined(e);
}

void evm_module_process_poll(evm_t *e) {
    evm_eventbus_t event;
    int re;
    re = evm_eventbus_get(&event);
    if (!re) {
        event.handler(e, event.ptr);
    }
}

evm_err_t evm_module_process(evm_t *e) {
    evm_eventbus_init();
    
    evm_val_t queue = evm_list_create(e);
    evm_global_set(e, "@processQueue", queue);
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "nextTick", evm_mk_native(e, evm_module_process_nextTick, "nextTick", 2));
    evm_module_add(e, "process", obj);
    return ec_ok;
}
