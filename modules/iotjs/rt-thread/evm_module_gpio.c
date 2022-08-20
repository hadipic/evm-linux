//#ifdef CONFIG_EVM_MODULE_GPIO
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

static evm_val_t _gpio_open_device(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
	evm_val_t val;
	evm_val_t ret_obj;
	_gpio_dev_t *dev;
	

	if( argc < 1)
		return EVM_UNDEFINED;
	
	if( argc > 1 && evm_is_script(v + 1) && !is_sync ) {
		cb = v + 1;
	} 

	dev = evm_malloc(sizeof(_gpio_dev_t));
	if( !dev ) {
		evm_throw(e, evm_mk_string(e, "Insufficient external memory"));
	}

	val = evm_prop_get(e, v[0], "pin");
	if( !evm_is_integer(val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'pin' member"));
	}
	dev->pin = evm_2_integer(val);
		
	val = evm_prop_get(e, v[0], "direction");
	if( !evm_is_integer(val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'direction' member"));
	}
	dev->direction = evm_2_integer(val);
	
    val = evm_prop_get(e, v[0], "mode");
	if( !evm_is_integer(val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'mode' member"));
	}
	dev->mode = evm_2_integer(val);
	_gpio_set_mode(dev);
	rt_pin_mode(dev->pin, dev->rt_mode);

    ret_obj = evm_module_gpio_class_instantiate(e, p, argc, v);
	evm_object_set_ext_data(e, ret_obj, dev);
    return *ret_obj;
}

//gpio.open(configuration)
static evm_val_t evm_module_gpio_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	return _gpio_open_device(e, p, argc, v, 1);
}

//gpiopin.setDirection(direction)
static evm_val_t evm_module_gpio_class_setDirection(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_gpio_dev_t *dev = (_gpio_dev_t *)evm_object_get_user_data(e, p);
	evm_val_t args[2];
	if( !dev )
		return EVM_UNDEFINED;

	if( argc < 1 || !evm_is_integer(v) )
		return EVM_UNDEFINED;
	
	dev->direction = evm_2_integer(v);
	_gpio_set_mode(dev);
	rt_pin_mode(dev->pin, dev->rt_mode);
	return EVM_UNDEFINED;
}

//gpiopin.write(value)
static evm_val_t evm_module_gpio_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_gpio_dev_t *dev = (_gpio_dev_t *)evm_object_get_user_data(e, p);
	evm_val_t args;
	if( !dev )
		return EVM_UNDEFINED;
	if( argc < 1 || !evm_is_integer(v) )
		return EVM_UNDEFINED;
	if( evm_2_integer(v) == 0 ){
		rt_pin_write(dev->pin, PIN_LOW);
	} else {
		rt_pin_write(dev->pin, PIN_HIGH);
	}
	return EVM_UNDEFINED;
}

//gpiopin.read()
static evm_val_t evm_module_gpio_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_gpio_dev_t *dev = (_gpio_dev_t *)evm_object_get_user_data(e, p);
	int status;
	if( !dev )
		return EVM_UNDEFINED;

	status = rt_pin_read(dev->pin);
	if( status ) {
		return evm_mk_boolean(e, 1);
	}
	return evm_mk_boolean(e, 0);
}

static evm_val_t evm_module_gpio_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	return EVM_UNDEFINED;
}

//gpiopin.destroy()
static evm_val_t evm_module_gpio_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_gpio_dev_t *dev = (_gpio_dev_t *)evm_object_get_user_data(e, p);
	if( !dev )
		return EVM_UNDEFINED;
	evm_free(dev);
	return EVM_UNDEFINED;
}


evm_val_t *evm_module_gpio_class_instantiate(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	evm_val_t obj = evm_object_create(e);
	evm_prop_set(e, obj, "setDirection", evm_mk_native(e, evm_module_gpio_class_setDirection, "setDirection", 0));
	evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_gpio_class_write, "write", 0));
	evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_gpio_class_read, "read", 0));
	evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_gpio_class_close, "close", 0));
	evm_prop_set(e, obj, "destroy", evm_mk_native(e, evm_module_gpio_class_destroy, "destroy", 0));
	return obj;
}

void evm_module_gpio(evm_t *e) {
	evm_val_t dir_prop = evm_object_create(e);
	evm_prop_set(e, dir_prop, "IN", evm_mk_number(e, EVM_GPIO_DIRECTION_IN));
	evm_prop_set(e, dir_prop, "OUT", evm_mk_number(e, EVM_GPIO_DIRECTION_OUT));

	evm_val_t mode_prop = evm_object_create(e, GC_OBJECT, 6, 0);
	evm_prop_set(e, mode_prop, "NONE", evm_mk_number(EVM_GPIO_MODE_NONE));
	evm_prop_set(e, mode_prop, "PULLUP", evm_mk_number(EVM_GPIO_MODE_PULLUP));
	evm_prop_set(e, mode_prop, "PULLDOWN", evm_mk_number(EVM_GPIO_MODE_PULLDOWN));
	evm_prop_set(e, mode_prop, "FLOAT", evm_mk_number(EVM_GPIO_MODE_FLOAT));
	evm_prop_set(e, mode_prop, "PUSHPULL", evm_mk_number(EVM_GPIO_MODE_PUSHPULL));
	evm_prop_set(e, mode_prop, "OPENDRAIN", evm_mk_number(EVM_GPIO_MODE_OPENDRAIN));

	evm_val_t edge_prop = evm_object_create(e, GC_OBJECT, 4, 0);
	evm_prop_set(e, edge_prop, "NONE", evm_mk_number(EVM_GPIO_EDGE_NONE));
	evm_prop_set(e, edge_prop, "RISING", evm_mk_number(EVM_GPIO_EDGE_RISING));
	evm_prop_set(e, edge_prop, "FALLING", evm_mk_number(EVM_GPIO_EDGE_FALLING));
	evm_prop_set(e, edge_prop, "BOTH", evm_mk_number(EVM_GPIO_EDGE_BOTH));

	evm_val_t builtin = evm_object_create(e);
	evm_prop_set(e, builtin, "open", evm_mk_native(e, evm_module_gpio_open, "open", 0));
	evm_prop_set(e, builtin, "DIRECTION", dir_prop);
	evm_prop_set(e, builtin, "MODE", mode_prop);
	evm_prop_set(e, builtin, "EDGE", edge_prop);

	evm_module_add(e, "gpio", builtin);
}
//#endif
