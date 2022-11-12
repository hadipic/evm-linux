#ifdef CONFIG_EVM_MODULE_GPIO
#include "evm_module.h"
#include "driver/gpio.h"

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

    gpio_intr_disable(dev->pin);
    if( dev->direction == EVM_GPIO_DIRECTION_IN ) 
        gpio_set_direction(dev->pin, GPIO_MODE_INPUT);
    else
        gpio_set_direction(dev->pin, GPIO_MODE_OUTPUT);

    return dev;
}

void evm_gpio_set_direction(evm_t *e, void *dev, int value){
	_gpio_dev_t *gpio_dev = dev;
	gpio_dev->direction = value;
}

void evm_gpio_write(evm_t *e, void *dev, int value){
	_gpio_dev_t *gpio_dev = dev;
	gpio_set_level(gpio_dev->pin, value);
}

int evm_gpio_read(evm_t *e, void *dev){
	_gpio_dev_t *gpio_dev = dev;
    return gpio_get_level(gpio_dev->pin);
}

void evm_gpio_close(evm_t *e, void *dev){
    
}

void evm_gpio_destroy(evm_t *e, void *dev){
	evm_free(dev);
}
#endif
