#ifdef CONFIG_EVM_MODULE_ADC
#include "evm_module.h"

void *evm_adc_open(evm_t *e, evm_val_t v) {
	return NULL;
}

int evm_adc_read(evm_t *e, void *dev) {
	return 0;
}

void evm_adc_close(evm_t *e, void *dev) {
	
}

void evm_adc_destroy(evm_t *e, void *dev) {

}

#endif
