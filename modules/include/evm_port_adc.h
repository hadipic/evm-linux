#ifndef __EVM_PORT_GPIO_H__
#define __EVM_PORT_GPIO_H__

#include "evm.h"

typedef struct evm_port_adc_t {
    int pin;
    void *data;
} evm_port_adc_t;

int evm_port_adc_read(evm_port_adc_t *info);
int evm_port_adc_close(evm_port_adc_t *info);
int evm_port_adc_open(evm_port_adc_t *info, int pin);
evm_port_adc_t *evm_port_adc_init(void);

#endif
