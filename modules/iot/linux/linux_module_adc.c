#ifdef CONFIG_EVM_MODULE_ADC
#include "evm_module.h"
#include "linux_systemio.h"

#define ADC_VALUE_BUFFER_SIZE 64

typedef struct _adc_dev_t {
    char dev[DEVICE_IO_NAME_LEN];
} _adc_dev_t; 

void *evm_adc_open(evm_t *e, evm_val_t v) {
	_adc_dev_t *dev;
	dev = evm_malloc(sizeof(_adc_dev_t));
	EVM_ASSERT(dev);
	evm_val_t val = evm_prop_get(e, v, "device");
	if( !evm_is_string(e, val) ) {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'device' member"));
	}
    const char *device_path = evm_2_string(e, val);
	if (!systemio_check_path(device_path)) {
		evm_throw(e, evm_mk_string(e, "Failed to open adc"));
	}
    sprintf(dev->dev, "%s", device_path);
	return dev;
}

int evm_adc_read(evm_t *e, void *dev) {
	_adc_dev_t *adc_dev = (_adc_dev_t*)dev;
	char buffer[ADC_VALUE_BUFFER_SIZE];
	if (!systemio_open_read_close(adc_dev->dev, buffer, sizeof(buffer))) {
		return 0;
	}
	return atoi(buffer) ;
}

void evm_adc_close(evm_t *e, void *dev) {
	EVM_UNUSED2(e, dev);
}

void evm_adc_destroy(evm_t *e, void *dev) {
	evm_free(dev);
}

#endif
