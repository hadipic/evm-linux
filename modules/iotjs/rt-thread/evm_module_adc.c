#ifdef CONFIG_EVM_MODULE_ADC
#include "evm_module.h"
#include <rtthread.h>
#include <rtdevice.h>

typedef struct _adc_dev_t {
	rt_adc_device_t dev;
	int channel;
} _adc_dev_t;

static evm_val_t evm_module_adc_class_instantiate(evm_t *e);

static evm_val_t _adc_open_device(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
	evm_val_t val;
	evm_val_t *ret_obj;
	_adc_dev_t *adc_dev;

	if( argc < 1)
		return EVM_UNDEFINED;

	adc_dev = evm_malloc(sizeof(_adc_dev_t));
	if( !adc_dev ) {
		evm_throw(e, evm_mk_string(e, "Insufficient external memory"));
	}

	val = evm_prop_get(e, v, "device");
	if( !evm_is_string(e, val) ) {
		evm_free(adc_dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'device' member"));
	}

	adc_dev->dev = (rt_adc_device_t)rt_device_find(evm_2_string(val));
    if ( adc_dev->dev == RT_NULL ) {
		evm_free(adc_dev);
        evm_throw(e, evm_mk_string(e, "Can't find adc device"));
    }

	val = evm_prop_get(e, v, "channel", 0);
	if( !evm_is_integer(e, val) ) {
		evm_free(adc_dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'channel' member"));
	}

	adc_dev->channel = evm_2_integer(val);

	ret_obj = evm_module_adc_class_instantiate(e);
	rt_adc_enable(adc_dev->dev, adc_dev->channel);
	evm_object_set_user_data(e, ret_obj, adc_dev);
}

//adc.openSync(configuration)
static evm_val_t evm_module_adc_openSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	return _adc_open_device(e, p, argc, v);
}

//adcpin.read()
static evm_val_t evm_module_adc_class_readSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_adc_dev_t *adc_dev = (_adc_dev_t *)evm_object_get_user_data(e, p);
	if( !adc_dev )
		return EVM_UNDEFINED;
	return evm_mk_number( rt_adc_read(adc_dev->dev, adc_dev->channel) );
}

//adcpin.close()
static evm_val_t evm_module_adc_class_closeSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_adc_dev_t *adc_dev = (_adc_dev_t *)evm_object_get_user_data(e, p);
	if( !adc_dev )
		return EVM_UNDEFINED;
	rt_adc_disable(adc_dev->dev, adc_dev->channel) ;
	return EVM_UNDEFINED;
}

//adcpin.destroy()
static evm_val_t evm_module_adc_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_adc_dev_t *adc_dev = (_adc_dev_t *)evm_object_get_user_data(e, p);
	rt_err_t err;
	if( !adc_dev )
		return EVM_UNDEFINED;
	err = rt_adc_disable(adc_dev->dev, adc_dev->channel);
	evm_free(adc_dev);
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
