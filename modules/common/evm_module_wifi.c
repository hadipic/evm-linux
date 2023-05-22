#include "evm_port_wifi.h"

EVM_FUNCTION(wifi_connect) {

}

EVM_FUNCTION(wifi_ip) {

}

EVM_FUNCTION(wifi_ssid) {

}

void evm_module_wifi(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "connect", evm_mk_native(e, wifi_connect, "connect", EVM_VARARGS));
    evm_prop_set(e, obj, "ip", evm_mk_native(e, wifi_ip, "ip", EVM_VARARGS));
    evm_prop_set(e, obj, "ssid", evm_mk_native(e, wifi_ssid, "ssid", EVM_VARARGS));
    evm_module_add(e, "@native.wifi", obj);
    evm_val_free(e, obj);
}
