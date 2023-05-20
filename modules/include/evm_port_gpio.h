#ifndef __EVM_PORT_GPIO_H__
#define __EVM_PORT_GPIO_H__

#include "evm.h"

#define EVM_PORT_GPIO_LOW            0x00
#define EVM_PORT_GPIO_HIGH           0x01

#define EVM_PORT_GPIO_OUTPUT         0x00
#define EVM_PORT_GPIO_INPUT          0x01
#define EVM_PORT_GPIO_IRQ            0x02

#define EVM_PORT_GPIO_DEFAULT        0x00
#define EVM_PORT_GPIO_PULLUP         0x01
#define EVM_PORT_GPIO_PULLDOWN       0x02

#define EVM_PORT_GPIO_RISING         0x00
#define EVM_PORT_GPIO_FALLING        0x01
#define EVM_PORT_GPIO_BOTH           0x02

typedef struct evm_port_gpio_t {
    int pin;
    int mode;
    int pull;
    int irq;
    evm_val_t cb;
} evm_port_gpio_t;

int evm_port_gpio_setup(evm_port_gpio_t *info);
int evm_port_gpio_set(evm_port_gpio_t *info, int level);
int evm_port_gpio_get(evm_port_gpio_t *info);
void evm_port_gpio_close(evm_port_gpio_t *info);

#endif
