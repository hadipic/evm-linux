
#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_WLAN


//wlan.connect(ssid, password)
static evm_val_t evm_module_wlan_connect(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc > 1 )
        evm_wlan_connect(e, (char*)evm_2_string(e, v[0]), (char*)evm_2_string(e, v[1]));
    return EVM_UNDEFINED;
}

//wlan.disconnect()
static evm_val_t evm_module_wlan_disconnect(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_wlan_disconnect(e);
    return EVM_UNDEFINED;
}

//wlan.isConnected()
static evm_val_t evm_module_wlan_isConnected(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( evm_wlan_is_connectd(e) ) {
        return evm_mk_boolean(e, 1);
    }
    return evm_mk_boolean(e, 0);
}

void evm_module_wlan(evm_t *e) {
    evm_wlan_init(e);
	evm_val_t obj = evm_object_create(e);
	evm_prop_set(e, obj, "connect", evm_mk_native(e, evm_module_wlan_connect, "connect", 0));
	evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_wlan_disconnect, "close", 0));
	evm_prop_set(e, obj, "isConnected", evm_mk_native(e, evm_module_wlan_isConnected, "isConnected", 0));
	evm_module_add(e, "wlan", obj);
}

#endif
