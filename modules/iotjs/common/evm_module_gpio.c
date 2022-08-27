#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_GPIO

static evm_val_t evm_module_gpio_class_instantiate(evm_t *e);

//gpio.open(configuration)
static evm_val_t evm_module_gpio_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 1)
        return EVM_UNDEFINED;

    evm_val_t ret_obj = evm_module_gpio_class_instantiate(e);
    void *dev = evm_gpio_open(e, v[0]);
    evm_object_set_user_data(e, ret_obj, dev);
    return ret_obj;
}

//gpiopin.setDirection(direction)
static evm_val_t evm_module_gpio_class_setDirection(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
	if( !dev )
		return EVM_UNDEFINED;

    if( argc < 1 || !evm_is_integer(e, v[0]) )
		return EVM_UNDEFINED;
	
    evm_gpio_set_direction(e, dev, evm_2_integer(e, v[0]));
	return EVM_UNDEFINED;
}

//gpiopin.write(value)
static evm_val_t evm_module_gpio_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;

    if( argc < 1 || !evm_is_integer(e, v[0]) )
		return EVM_UNDEFINED;
    evm_gpio_write(e, dev, evm_2_integer(e, v[0]));
	return EVM_UNDEFINED;
}

//gpiopin.read()
static evm_val_t evm_module_gpio_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    return evm_mk_number(e, evm_gpio_read(e, dev));
}

static evm_val_t evm_module_gpio_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_gpio_close(e, dev);
	return EVM_UNDEFINED;
}

//gpiopin.destroy()
static evm_val_t evm_module_gpio_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_gpio_destroy(e, dev);
	return EVM_UNDEFINED;
}


static evm_val_t evm_module_gpio_class_instantiate(evm_t *e)
{
    evm_val_t obj = evm_object_create_user_data(e, NULL);
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

    evm_val_t mode_prop = evm_object_create(e);
    evm_prop_set(e, mode_prop, "NONE", evm_mk_number(e, EVM_GPIO_MODE_NONE));
    evm_prop_set(e, mode_prop, "PULLUP", evm_mk_number(e, EVM_GPIO_MODE_PULLUP));
    evm_prop_set(e, mode_prop, "PULLDOWN", evm_mk_number(e, EVM_GPIO_MODE_PULLDOWN));
    evm_prop_set(e, mode_prop, "FLOAT", evm_mk_number(e, EVM_GPIO_MODE_FLOAT));
    evm_prop_set(e, mode_prop, "PUSHPULL", evm_mk_number(e, EVM_GPIO_MODE_PUSHPULL));
    evm_prop_set(e, mode_prop, "OPENDRAIN", evm_mk_number(e, EVM_GPIO_MODE_OPENDRAIN));

    evm_val_t edge_prop = evm_object_create(e);
    evm_prop_set(e, edge_prop, "NONE", evm_mk_number(e, EVM_GPIO_EDGE_NONE));
    evm_prop_set(e, edge_prop, "RISING", evm_mk_number(e, EVM_GPIO_EDGE_RISING));
    evm_prop_set(e, edge_prop, "FALLING", evm_mk_number(e, EVM_GPIO_EDGE_FALLING));
    evm_prop_set(e, edge_prop, "BOTH", evm_mk_number(e, EVM_GPIO_EDGE_BOTH));

	evm_val_t builtin = evm_object_create(e);
	evm_prop_set(e, builtin, "open", evm_mk_native(e, evm_module_gpio_open, "open", 0));
	evm_prop_set(e, builtin, "DIRECTION", dir_prop);
	evm_prop_set(e, builtin, "MODE", mode_prop);
	evm_prop_set(e, builtin, "EDGE", edge_prop);

	evm_module_add(e, "gpio", builtin);
}
#endif
