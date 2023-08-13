#ifdef EVM_USE_MODULE_ADC
#include "evm_module.h"
#include "evm_port_adc.h"


//open(pin)
EVM_FUNCTION(open)
{
    EVM_EPCV;
    evm_port_adc_t *dev = (evm_port_adc_t*)evm_2_invoke(e, v[0]);
    printf("dev = %x\r\n", dev);
    if( !dev )
        EVM_RETURN(EVM_UNDEFINED);
    evm_port_adc_open(dev, evm_2_integer(e, v[1]));
    EVM_RETURN(EVM_UNDEFINED);
}

EVM_FUNCTION(read)
{
    EVM_EPCV;
    evm_port_adc_t *dev = evm_2_invoke(e, v[0]);
    if( !dev )
        return EVM_UNDEFINED;

    int level = evm_port_adc_read(dev);
    return evm_mk_number(e, level);
}

EVM_FUNCTION(create)
{
    EVM_EPCV;
    evm_port_adc_t *dev = evm_port_adc_init();
    EVM_ASSERT(dev);
    evm_val_t obj = evm_mk_invoke(e, dev);
    return obj;
}

void evm_module_adc(evm_t * e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "create", evm_mk_native(e, create, "create", EVM_VARARGS));
    evm_prop_set(e, obj, "open", evm_mk_native(e, open, "open", EVM_VARARGS));
    evm_prop_set(e, obj, "read", evm_mk_native(e, read, "read", EVM_VARARGS));
    evm_module_add(e, "@native.adc", obj);
    evm_val_free(e, obj);
}
#endif
