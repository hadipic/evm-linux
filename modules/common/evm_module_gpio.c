#include "evm_module.h"
#include "evm_port_gpio.h"

static void gpio_setup(evm_t *e, evm_port_gpio_t *gpio, evm_val_t obj) {
    evm_val_t val = evm_prop_get(e, obj, "pin");
    if( evm_is_number(e, val) ){
        gpio->pin = evm_2_integer(e, val);
    }
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "pull");
    if( evm_is_string(e, val) ){
        char *name = evm_2_string(e, val);
        if( !strcmp(name, "pullup") ) {
            gpio->pull = EVM_PORT_GPIO_PULLUP;
        } else if( !strcmp(name, "pulldown") ) {
            gpio->pull = EVM_PORT_GPIO_PULLDOWN;
        } else {
            gpio->pull = EVM_PORT_GPIO_DEFAULT;
        }
        evm_string_free(e, name);
    }
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "mode");
    if( evm_is_string(e, val) ) {
        char *name = evm_2_string(e, val);
        if( !strcmp(name, "output") ) {
            gpio->pull = EVM_PORT_GPIO_OUTPUT;
        } else if( !strcmp(name, "input") ) {
            gpio->pull = EVM_PORT_GPIO_INPUT;
        } else if( !strcmp(name, "irq") ) {
            gpio->pull = EVM_PORT_GPIO_IRQ;
        } else {
            gpio->pull = EVM_PORT_GPIO_OUTPUT;
        }
        evm_string_free(e, name);
    }
    evm_val_free(e, val);

    val = evm_prop_get(e, obj, "irq");
    if( evm_is_string(e, val) ) {
        char *name = evm_2_string(e, val);
        if( !strcmp(name, "rising") ) {
            gpio->pull = EVM_PORT_GPIO_RISING;
        } else if( !strcmp(name, "falling") ) {
            gpio->pull = EVM_PORT_GPIO_FALLING;
        } else if( !strcmp(name, "both") ) {
            gpio->pull = EVM_PORT_GPIO_BOTH;
        } else {
            gpio->pull = EVM_PORT_GPIO_FALLING;
        }
        evm_string_free(e, name);
    }
    evm_val_free(e, val);

    gpio->cb = evm_prop_get(e, obj, "callback");

    evm_port_gpio_setup(gpio);
}

//setup(obj, config)
static evm_val_t module_gpio_setup(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_port_gpio_t *gpio = evm_object_get_user_data(e, v[0]);
    if( !gpio )
        return EVM_UNDEFINED;

    gpio_setup(e, gpio, v[1]);
    return EVM_UNDEFINED;
}

static evm_val_t module_gpio_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_port_gpio_t *info = evm_object_get_user_data(e, v[0]);
    if( !info )
        return EVM_UNDEFINED;

    int level = evm_port_gpio_get(info);
    return evm_mk_number(e, level);
}

static evm_val_t module_gpio_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_port_gpio_t *info = evm_object_get_user_data(e, v[0]);
    if( !info )
        return EVM_UNDEFINED;

    if( argc == 0 || !evm_is_number(e, v[1]) )
        return EVM_UNDEFINED;

    int level = evm_2_integer(e, v[1]);

    evm_port_gpio_set(info, level);
    return EVM_UNDEFINED;
}

/**
 * @brief create({
 *  pin: 1,
 *  pull: "pullup",
 *  irq: "falling",
 *  mode: "irq",
 *  callback: <function>
 * })
 * @return
 */
static evm_val_t module_gpio_create(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_port_gpio_t *gpio = (evm_port_gpio_t *)evm_malloc(sizeof(evm_port_gpio_t));
    EVM_ASSERT(gpio);
    memset(gpio, 0, sizeof (evm_port_gpio_t));
    evm_val_t obj = evm_object_create_user_data(e, gpio);
    gpio_setup(e, gpio, v[0]);
    return obj;
}

void evm_module_gpio(evm_t * e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "create", evm_mk_native(e, module_gpio_create, "create", EVM_VARARGS));
    evm_prop_set(e, obj, "setup", evm_mk_native(e, module_gpio_setup, "setup", EVM_VARARGS));
    evm_prop_set(e, obj, "read", evm_mk_native(e, module_gpio_read, "read", EVM_VARARGS));
    evm_prop_set(e, obj, "write", evm_mk_native(e, module_gpio_write, "write", EVM_VARARGS));
    evm_module_add(e, "@native.gpio", obj);
    evm_val_free(e, obj);
}
