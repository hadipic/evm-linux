#ifdef CONFIG_EVM_MODULE_EVENTS
#include "evm_module.h"

//emitter.addListener(event, listener)
static evm_val_t evm_module_events_emitter_addListener(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    if( argc < 2 || !evm_is_string(e, v[0]) || !evm_is_callable(e, v[1]) )
        return evm_mk_undefined(e);
    evm_val_t events = evm_prop_get(e, p, "events");
    evm_val_free(e, events);
    if( !evm_is_undefined(e, events) ) {
        evm_val_t listener = evm_val_duplicate(e, v[1]);
        evm_prop_set(e, events, evm_2_string(e, v[0]), listener);
    }
    return evm_mk_undefined(e);
}

//emitter.on(event, listener)
static evm_val_t evm_module_events_emitter_on(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    return evm_module_events_emitter_addListener(e, p, argc, v);
}

//emitter.emit(event[, args..])
static evm_val_t evm_module_events_emitter_emit(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    if( argc < 1 || !evm_is_string(e, v[0]) )
        return evm_mk_undefined(e);
    evm_module_event_emit(e, p, evm_2_string(e, v[0]), argc - 1, v + 1);
    return evm_mk_undefined(e);
}

//emitter.once(event, listener)
static evm_val_t evm_module_events_emitter_once(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    return evm_module_events_emitter_addListener(e, p, argc, v);
}

//emitter.removeListener(event, listener)
static evm_val_t evm_module_events_emitter_removeListener(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    evm_val_t events = evm_prop_get(e, p, "events");
    evm_val_free(e, events);
    if( !evm_is_undefined(e, events) ) {
        evm_prop_delete(e, events, evm_2_string(e, v[0]));
    }
    return evm_mk_undefined(e);
}

//emitter.removeAllListeners([event])
static evm_val_t evm_module_events_emitter_removeAllListeners(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    evm_val_t events = evm_object_create(e);
    evm_prop_set(e, p, "events", events);
    return evm_mk_undefined(e);
}

//emitter.EventEmitter
static evm_val_t evm_module_events_emitter_EventEmitter(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "addListener", evm_mk_native(e, evm_module_events_emitter_addListener, "addListener", 2));
    evm_prop_set(e, obj, "on", evm_mk_native(e, evm_module_events_emitter_on, "on", 2));
    evm_prop_set(e, obj, "emit", evm_mk_native(e, evm_module_events_emitter_emit, "emit", 2));
    evm_prop_set(e, obj, "once", evm_mk_native(e, evm_module_events_emitter_once, "once", 2));
    evm_prop_set(e, obj, "removeListener", evm_mk_native(e, evm_module_events_emitter_removeListener, "removeListener", 1));
    evm_prop_set(e, obj, "removeAllListeners", evm_mk_native(e, evm_module_events_emitter_removeAllListeners, "removeAllListeners", 0));
    evm_prop_set(e, obj, "events", evm_object_create(e));
    return obj;
}

evm_err_t evm_module_events(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "EventEmitter", evm_mk_native(e, evm_module_events_emitter_EventEmitter, "EventEmitter", 0));
    evm_module_add(e, "events", obj);
    return ec_ok;
}

#endif
