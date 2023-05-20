#include "evm_port_gpio.h"
#include "evm_port_msgbus.h"

static int _gpio_handler(evm_t *e, void* ptr){
    evm_port_gpio_t* info = (evm_port_gpio_t*)ptr;
    evm_call_free(e, info->cb, EVM_UNDEFINED, 0, NULL);
    return 0;
}

int evm_port_gpio_setup(evm_port_gpio_t *info) {
    int pin = info->pin;
    int mode = info->mode;
    int pull = info->pull;
    int irq = info->irq;
    int pullup;
    int pulldown;

    if (info == NULL) {
        evm_print("setup gpio: info nullptr\n");
        return -1;
    }
    if (pin < 0) {
        evm_print("setup gpio: pin invalid\n");
        return -1;
    }

    switch (pull)
    {
    case EVM_PORT_GPIO_PULLUP:
        pullup = 1;
        pulldown = 0;
        break;
    case EVM_PORT_GPIO_PULLDOWN:
        pullup = 1;
        pulldown = 0;
        break;
    case EVM_PORT_GPIO_DEFAULT:
        pullup = 0;
        pulldown = 0;
        break;
    default:
        pullup = 0;
        pulldown = 0;
        break;
    }

    switch (mode)
    {
    case EVM_PORT_GPIO_INPUT:
        break;
    case EVM_PORT_GPIO_OUTPUT:
        break;
    case EVM_PORT_GPIO_IRQ: {
        switch (irq)
        {
        case EVM_PORT_GPIO_RISING:
            break;
        case EVM_PORT_GPIO_FALLING:
            break;
        case EVM_PORT_GPIO_BOTH:
            break;
        default:
            break;
        }
        break;
        }
    default:
        break;
    }

    evm_print("setup gpio ok: pin[%d], pull[%d], mode[%d]\n", pin, pull, mode);
    return 0;
}

int evm_port_gpio_set(evm_port_gpio_t *info, int level) {
    return 0;
}

int evm_port_gpio_get(evm_port_gpio_t *info) {
    return 0;
}

void evm_port_gpio_close(evm_port_gpio_t *info) {

}

