#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_GPIO
#include "bl_gpio.h"
#include <bl602_gpio.h>

typedef struct _gpio_dev_t
{
    int pin;
    int direction;
    int mode;
    int edge;
} _gpio_dev_t;

void *evm_gpio_open(evm_t *e, evm_val_t v){
    _gpio_dev_t *dev = evm_malloc(sizeof(_gpio_dev_t));
    EVM_ASSERT(dev);

    evm_val_t val;
    val = evm_prop_get(e, v, "pin");
    if (!evm_is_integer(e, val))
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'pin' member"));
    }
    dev->pin = evm_2_integer(e, val);

    val = evm_prop_get(e, v, "direction");
    if (!evm_is_integer(e, val))
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'direction' member"));
    }
    dev->direction = evm_2_integer(e, val);

    val = evm_prop_get(e, v, "mode");
    if (!evm_is_integer(e, val))
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'mode' member"));
    }
    dev->mode = evm_2_integer(e, val);

    if (dev->mode)
    {
        bl_gpio_enable_input(dev->pin, dev->direction ? 1 : 0, dev->direction ? 0 : 1);
    }
    else
    {
        bl_gpio_enable_output(dev->pin, dev->direction ? 1 : 0, dev->direction ? 0 : 1);
    }

    return dev;
}

void evm_gpio_set_direction(evm_t *e, void *dev, int value){
	_gpio_dev_t *gpio_dev = dev;
	gpio_dev->direction = value;
}

void evm_gpio_write(evm_t *e, void *dev, int value){
	_gpio_dev_t *gpio_dev = dev;
	bl_gpio_output_set(gpio_dev->pin, value);
}

int evm_gpio_read(evm_t *e, void *dev){
	_gpio_dev_t *gpio_dev = dev;
    uint8_t status;
    int ret = bl_gpio_input_get(gpio_dev->pin, &status);
    return ret == 0 ? 0:1;
}

void evm_gpio_close(evm_t *e, void *dev){
    
}

void evm_gpio_destroy(evm_t *e, void *dev){
	evm_free(dev);
}
#endif
