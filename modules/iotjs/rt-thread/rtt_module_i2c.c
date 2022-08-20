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

void *evm_i2c_open(evm_t *e, evm_val_t obj){
    evm_val_t device = evm_prop_get(e, obj, "device");
    rt_i2c_bus_device_t i2c_bus_name = (rt_i2c_bus_device_t)rt_device_find(evm_2_string(e, device));
    if (!i2c_bus_name)
        return NULL;

    evm_val_t address = evm_prop_get(e, obj, "address");
    rt_i2c_bus_device_t i2c_bus_addr = (rt_i2c_bus_device_t)rt_device_find(evm_2_integer(e, address));
    if (!i2c_bus_addr)
        return NULL;

    _i2c_bus *bus = evm_malloc(sizeof(_i2c_bus));
    EVM_ASSERT(bus);
    bus->bus = i2c_bus;
    bus->addr = i2c_bus_addr;
    return bus;
}

void evm_i2c_read(evm_t *e, void *dev, void *buf, int size){
    _i2c_bus *bus = dev;
    rt_device_read(bus->bus, 0, buffer, size);
}

void evm_i2c_write(evm_t *e, void *dev, void *buf, int size){
    _i2c_bus *bus = dev;
    rt_i2c_transfer(bus->bus, buf, size);
}

void evm_i2c_close(evm_t *e, void *dev){
    
}

void evm_i2c_destroy(evm_t *e, void *dev){
    evm_free(dev);
}

#endif
