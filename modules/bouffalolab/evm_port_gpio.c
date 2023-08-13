#include "evm_port_gpio.h"
#include "evm_port_msgbus.h"
#include "bflb_gpio.h"

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
    int cfgset = 0;

    if (info == NULL) {
        EVM_LOG("setup gpio: info nullptr\n");
        return -1;
    }
    if (pin < 0) {
        EVM_LOG("setup gpio: pin invalid\n");
        return -1;
    }

    switch (pull)
    {
    case EVM_PORT_GPIO_PULLUP:
        cfgset |= GPIO_PULLUP;
        break;
    case EVM_PORT_GPIO_PULLDOWN:
        cfgset |= GPIO_PULLDOWN;
        break;
    case EVM_PORT_GPIO_DEFAULT:
        cfgset |= GPIO_PULLUP;
        break;
    default:
        cfgset |= GPIO_PULLUP;
        break;
    }

    switch (mode)
    {
    case EVM_PORT_GPIO_INPUT:
        cfgset |= GPIO_INPUT;
        break;
    case EVM_PORT_GPIO_OUTPUT:
        cfgset |= GPIO_OUTPUT;
        break;
    case EVM_PORT_GPIO_IRQ: {
        switch (irq)
        {
        case EVM_PORT_GPIO_RISING:
            cfgset |= GPIO_INT_TRIG_MODE_SYNC_RISING_EDGE;
            break;
        case EVM_PORT_GPIO_FALLING:
            cfgset |= GPIO_INT_TRIG_MODE_SYNC_FALLING_EDGE;
            break;
        case EVM_PORT_GPIO_BOTH:
            cfgset |= GPIO_INT_TRIG_MODE_SYNC_FALLING_RISING_EDGE;
            break;
        default:
            break;
        }
        break;
        }
    default:
        break;
    }

    struct bflb_device_s *gpio;
    gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, pin, cfgset | GPIO_SMT_EN | GPIO_DRV_0);
    info->device = gpio;

    EVM_LOG("setup gpio ok: pin[%d], pull[%d], mode[%d]\n", pin, pull, mode);
    return 0;
}

int evm_port_gpio_set(evm_port_gpio_t *info, int level) {
    if( level )
        bflb_gpio_set(info->device, info->pin);
    else{
        bflb_gpio_reset(info->device, info->pin);
    }
    return 0;
}

int evm_port_gpio_get(evm_port_gpio_t *info) {
    return bflb_gpio_read(info->device, info->pin);
}

void evm_port_gpio_close(evm_port_gpio_t *info) {
    bflb_gpio_deinit(info->device, info->pin);
}

