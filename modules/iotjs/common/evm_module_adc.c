#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_ADC

static evm_val_t evm_module_adc_class_instantiate(evm_t *e);

//adc.open(configuration)
static evm_val_t evm_module_adc_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 1)
        return EVM_UNDEFINED;

    evm_val_t ret_obj = evm_module_adc_class_instantiate(e);
    void *dev = evm_adc_open(e, v[0]);
    evm_object_set_user_data(e, ret_obj, dev);
    return ret_obj;
}

//adcpin.read()
static evm_val_t evm_module_adc_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
		return EVM_UNDEFINED;
    return evm_mk_number(e, evm_adc_read(e, dev) );
}

//adcpin.close()
static evm_val_t evm_module_adc_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_adc_close(e, dev);
	return EVM_UNDEFINED;
}

//adcpin.destroy()
static evm_val_t evm_module_adc_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_adc_destroy(e, dev);
	return EVM_UNDEFINED;
}

static evm_val_t evm_module_adc_class_instantiate(evm_t *e)
{
	evm_val_t obj = evm_object_create(e);
	evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_adc_class_read, "read", 0));
	evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_adc_class_close, "close", 0));
	evm_prop_set(e, obj, "destroy", evm_mk_native(e, evm_module_adc_class_destroy, "destroy", 0));
	return obj;
}

void evm_module_adc(evm_t *e) {
	evm_val_t obj = evm_object_create(e);
	evm_prop_set(e, obj, "open", evm_mk_native(e, evm_module_adc_open, "open", 0));
	evm_module_add(e, "adc", obj);
}

#endif
