#ifdef CONFIG_EVM_MODULE_I2C
#include "evm_module.h"
#include <rtthread.h>
#include <rtdevice.h>

typedef struct rt_i2c_bus_device *rt_i2c_bus_device_t;

typedef struct _i2c_bus
{
    rt_uint16_t addr;
    rt_i2c_bus_device_t bus;
} _i2c_bus;

//i2c.open(configuration)
static evm_val_t evm_module_i2c_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_object(e, v[0]))
        return EVM_UNDEFINED;

    evm_val_t device = evm_prop_get(e, v[0], "device");
    rt_i2c_bus_device_t i2c_bus_name = (rt_i2c_bus_device_t)rt_device_find(evm_2_string(e, device));
    if (!i2c_bus_name)
        return EVM_UNDEFINED;

    evm_val_t address = evm_prop_get(e, v[0], "address");
    rt_i2c_bus_device_t i2c_bus_addr = (rt_i2c_bus_device_t)rt_device_find(evm_2_integer(e, address));
    if (!i2c_bus_addr)
        return EVM_UNDEFINED;

    evm_val_t obj = evm_object_create(e);
    _i2c_bus *bus = evm_malloc(sizeof(_i2c_bus));
    EVM_ASSERT(bus);
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_i2c_class_read, "", 0));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_i2c_class_write, "", 0));
    evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_i2c_class_close, "", 0));

    bus->bus = i2c_bus;
    bus->addr = i2c_bus_addr;
    evm_object_set_user_data(e, obj, bus);
    return obj;
}

//i2cbus.read(length)
static evm_val_t evm_module_i2c_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    _i2c_bus *bus = evm_object_get_user_date(e, p);
    if (!bus)
        return EVM_UNDEFINED;

    if (argc < 1 || !evm_is_integer(e, v[0]))
        return EVM_UNDEFINED;

    rt_size_t size = evm_2_integer(e, v[0]);
    if (!size)
        return EVM_UNDEFINED;
    evm_val_t buffer = evm_buffer_create(e, NULL, evm_2_integer(e, v[0]));
    rt_device_read(bus->bus, 0, evm_buffer_addr(e, buffer), size);
    return buffer;
}

//i2cbus.write(bytes)
static evm_val_t evm_module_i2c_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_buffer(e, v[0]))
        return EVM_UNDEFINED;

    _i2c_bus *bus = evm_object_get_user_date(e, p);
    if (!bus)
        return EVM_UNDEFINED;
    rt_i2c_transfer(bus->bus, evm_buffer_addr(e, v[0]), evm_buffer_len(e, v[0]));
    return EVM_UNDEFINED;
}

//i2cbus.close([callback])
static evm_val_t evm_module_i2c_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return EVM_UNDEFINED;
}

//i2cbus.destroy()
static evm_val_t evm_module_i2c_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    _i2c_bus *bus = evm_object_get_user_date(e, p);
    if (!bus)
        return EVM_UNDEFINED;
    evm_free(buf);
    return EVM_UNDEFINED;
}

void evm_module_i2c(evm_t *e) {
    evm_val_t builtin = evm_object_create(e);
	evm_prop_set(e, builtin, "open", evm_mk_native(e, evm_module_i2c_open, "open", 0));
	evm_module_add(e, "i2c", builtin);
}
#endif
