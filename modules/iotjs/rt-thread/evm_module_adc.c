#ifdef CONFIG_EVM_MODULE_ADC
#include "evm_module.h"
#include <rtthread.h>
#include <rtdevice.h>

typedef struct _adc_dev_t {
	rt_adc_device_t dev;
	int channel;
} _adc_dev_t;

void *evm_adc_open(evm_t *e, evm_val_t v) {
	_adc_dev_t *adc_dev;
	adc_dev = evm_malloc(sizeof(_adc_dev_t));
	if( !adc_dev ) {
		evm_throw(e, evm_mk_string(e, "Insufficient external memory"));
	}

	evm_val_t val = evm_prop_get(e, v, "device");
	if( !evm_is_string(e, val) ) {
		evm_free(adc_dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'device' member"));
	}

	adc_dev->dev = (rt_adc_device_t)rt_device_find(evm_2_string(e, val));
    if ( adc_dev->dev == RT_NULL ) {
		evm_free(adc_dev);
        evm_throw(e, evm_mk_string(e, "Can't find adc device"));
    }

	val = evm_prop_get(e, v, "channel");
	if( !evm_is_integer(e, val) ) {
		evm_free(adc_dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'channel' member"));
	}

	adc_dev->channel = evm_2_integer(val);
	rt_adc_enable(adc_dev->dev, adc_dev->channel);
	return adc_dev;
}

int evm_adc_read(evm_t *e, void *dev) {
	_adc_dev_t *adc_dev = dev;
	return rt_adc_read(adc_dev->dev, adc_dev->channel);
}

void evm_adc_close(evm_t *e, void *dev) {
	_adc_dev_t *adc_dev = dev;
	rt_adc_disable(adc_dev->dev, adc_dev->channel);
}

void evm_adc_destroy(evm_t *e, void *dev) {
	_adc_dev_t *adc_dev = dev;
	rt_adc_disable(adc_dev->dev, adc_dev->channel);
	evm_free(dev);
}

#endif
