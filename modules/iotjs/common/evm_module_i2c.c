#ifdef CONFIG_EVM_MODULE_I2C
#include "evm_module.h"

static evm_val_t evm_module_i2c_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v);
static evm_val_t evm_module_i2c_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v);
static evm_val_t evm_module_i2c_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v);
static evm_val_t evm_module_i2c_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v);

//i2c.open(configuration)
static evm_val_t evm_module_i2c_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_object(e, v[0]))
        return EVM_UNDEFINED;

    void *dev = evm_i2c_open(e, v[0]);
    evm_val_t obj = evm_object_create_user_data(e, dev);
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_i2c_class_read, "read", 0));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_i2c_class_write, "write", 0));
    evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_i2c_class_close, "close", 0));
    evm_prop_set(e, obj, "destroy", evm_mk_native(e, evm_module_i2c_class_destroy, "destroy", 0));

    evm_object_set_user_data(e, obj, dev);
    return obj;
}

//i2cbus.read(length)
static evm_val_t evm_module_i2c_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;

    if (argc < 1 || !evm_is_integer(e, v[0]))
        return EVM_UNDEFINED;

    int size = evm_2_integer(e, v[0]);
    if ( size == 0 )
        return EVM_UNDEFINED;
    evm_val_t buffer = evm_buffer_create(e, NULL, evm_2_integer(e, v[0]));
    evm_i2c_read(e, dev, evm_buffer_addr(e, buffer), size);
    return buffer;
}

//i2cbus.write(bytes)
static evm_val_t evm_module_i2c_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;

    if (argc < 1 || !evm_is_buffer(e, v[0]))
        return EVM_UNDEFINED;

    evm_i2c_write(e, dev, evm_buffer_addr(e, v[0]), evm_buffer_len(e, v[0]));
    return EVM_UNDEFINED;
}

//i2cbus.close()
static evm_val_t evm_module_i2c_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_i2c_close(e, dev);
    return EVM_UNDEFINED;
}

//i2cbus.destroy()
static evm_val_t evm_module_i2c_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_i2c_destroy(e, dev);
    return EVM_UNDEFINED;
}

void evm_module_i2c(evm_t *e) {
    evm_val_t builtin = evm_object_create(e);
	evm_prop_set(e, builtin, "open", evm_mk_native(e, evm_module_i2c_open, "open", 0));
	evm_module_add(e, "i2c", builtin);
}
#endif
