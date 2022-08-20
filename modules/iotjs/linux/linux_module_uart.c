#ifdef CONFIG_EVM_MODULE_UART
#include "evm_module.h"


void *evm_uart_open(evm_t *e, evm_val_t obj){
	return NULL;
}

int evm_uart_write(evm_t *e, void *dev, void *buffer, int size){
	return 0;
}

int evm_uart_read(evm_t *e, void *dev, void *buf, int size){
	
}

void evm_uart_close(evm_t *e, void *dev){
	
}

void evm_uart_destroy(evm_t *e, void *dev){
	
}

#endif
