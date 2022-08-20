#ifdef CONFIG_EVM_MODULE_GPIO
#include "evm_module.h"

void *evm_gpio_open(evm_t *e, evm_val_t v){
	return NULL;
}

void evm_gpio_set_direction(evm_t *e, void *dev, int value){
	
}

void evm_gpio_write(evm_t *e, void *dev, int value){
	
}

int evm_gpio_read(evm_t *e, void *dev){
	return 0;
}

void evm_gpio_close(evm_t *e, void *dev){

}

void evm_gpio_destroy(evm_t *e, void *dev){

}
#endif
