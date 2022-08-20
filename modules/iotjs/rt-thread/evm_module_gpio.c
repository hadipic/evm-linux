#ifdef CONFIG_EVM_MODULE_GPIO
#include "evm_module.h"
#include <rtthread.h>
#include <rtdevice.h>

evm_val_t *evm_module_gpio_class_instantiate(evm_t *e, evm_val_t p, int argc, evm_val_t *v);

typedef struct _gpio_dev_t {
	int pin;
    int rt_mode;
	int direction;
	int mode;
	int edge;
} _gpio_dev_t;

static void _gpio_set_mode(_gpio_dev_t *dev) {
	int mode = PIN_MODE_INPUT;
    switch (dev->direction)
    {
    case EVM_GPIO_DIRECTION_IN:
        mode = PIN_MODE_INPUT;
        break;
    case EVM_GPIO_DIRECTION_OUT:
        mode = PIN_MODE_OUTPUT;
        break;
    }

    switch (dev->mode)
    {
    case EVM_GPIO_MODE_PUSHPULL:
    case EVM_GPIO_MODE_FLOAT:
    case EVM_GPIO_MODE_NONE:
        break;
    case EVM_GPIO_MODE_PULLUP:
    {
        if (mode == PIN_MODE_INPUT)
            mode = PIN_MODE_INPUT_PULLUP;
        break;
    }
	case EVM_GPIO_MODE_PULLDOWN: {
		if( mode == PIN_MODE_INPUT )
			mode = PIN_MODE_INPUT_PULLDOWN;
		break;
	}
	case EVM_GPIO_MODE_OPENDRAIN: {
		if( mode == PIN_MODE_OUTPUT )
			mode = PIN_MODE_OUTPUT_OD;
		break;
	}
	}
    dev->rt_mode = mode;
}

void *evm_gpio_open(evm_t *e, evm_val_t v){
	evm_val_t val;
	_gpio_dev_t *dev;

	dev = evm_malloc(sizeof(_gpio_dev_t));
	if( !dev ) {
		evm_throw(e, evm_mk_string(e, "Insufficient external memory"));
	}

	val = evm_prop_get(e, v, "pin");
	if( !evm_is_integer(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'pin' member"));
	}
	dev->pin = evm_2_integer(e, val);
		
	val = evm_prop_get(e, v, "direction");
	if( !evm_is_integer(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'direction' member"));
	}
	dev->direction = evm_2_integer(e, val);
	
    val = evm_prop_get(e, v, "mode");
	if( !evm_is_integer(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'mode' member"));
	}
	dev->mode = evm_2_integer(e, val);
	_gpio_set_mode(dev);
	rt_pin_mode(dev->pin, dev->rt_mode);

	return dev;
}

void evm_gpio_set_direction(evm_t *e, void *dev, int value){
	_gpio_dev_t *gpio_dev = dev;
	gpio_dev->direction = value;
	_gpio_set_mode(dev);
	rt_pin_mode(gpio_dev->pin, gpio_dev->rt_mode);
}

void evm_gpio_write(evm_t *e, void *dev, int value){
	_gpio_dev_t *gpio_dev = dev;
	if( value == 0 ){
		rt_pin_write(gpio_dev->pin, PIN_LOW);
	} else {
		rt_pin_write(gpio_dev->pin, PIN_HIGH);
	}
}

int evm_gpio_read(evm_t *e, void *dev){
	_gpio_dev_t *gpio_dev = dev;
	return rt_pin_read(gpio_dev->pin)
}

void evm_gpio_close(evm_t *e, void *dev){

}

void evm_gpio_destroy(evm_t *e, void *dev){
	evm_free(dev);
}

#endif
