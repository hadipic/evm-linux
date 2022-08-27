
#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_UART


static evm_val_t evm_module_uart_class_instantiate(evm_t *e);

//uart.open(configuration)
static evm_val_t evm_module_uart_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 1)
        return EVM_UNDEFINED;

    evm_val_t ret_obj = evm_module_uart_class_instantiate(e);
    void *dev = evm_uart_open(e, v[0]);
    evm_object_set_user_data(e, ret_obj, dev);
    return ret_obj;
}

//uartport.write(data)
static evm_val_t evm_module_uart_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;

    if( argc < 1 || !( evm_is_buffer(e, v[0]) || evm_is_string(e, v[0]) ) ) {
        return EVM_UNDEFINED;
    }
    void *buffer;
    int size;
    if( evm_is_string(e, v[0]) ) {
        buffer = (void*)evm_2_string(e, v[0]);
        size = evm_string_len(e, v[0]);
    } else {
        buffer = evm_buffer_addr(e, v[0]);
        size = evm_buffer_len(e, v[0]);
    }
    evm_uart_write(e, dev, buffer, size);
    return EVM_UNDEFINED;
}

//uartport.read(size)
static evm_val_t evm_module_uart_class_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
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
    evm_uart_read(e, dev, evm_buffer_addr(e, buffer), size);
    return buffer;
}

//uartport.close()
static evm_val_t evm_module_uart_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_uart_close(e, dev);
    return EVM_UNDEFINED;
}

//uartport.destroy()
static evm_val_t evm_module_uart_class_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    void *dev = evm_object_get_user_data(e, p);
    if( !dev )
        return EVM_UNDEFINED;
    evm_uart_destroy(e, dev);
    return EVM_UNDEFINED;
}

evm_val_t evm_module_uart_class_instantiate(evm_t *e)
{
	evm_val_t obj = evm_object_create_user_data(e, NULL);
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_uart_class_write, "write", 0));
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_uart_class_read, "read", 0));
    evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_uart_class_close, "close", 0));
    evm_prop_set(e, obj, "destroy", evm_mk_native(e, evm_module_uart_class_destroy, "destroy", 0));
	return obj;
}

void evm_module_uart(evm_t *e) {
	evm_val_t obj = evm_object_create(e);
	evm_prop_set(e, obj, "open", evm_mk_native(e, evm_module_uart_open, "open", 0));
	evm_module_add(e, "uart", obj);
}
#endif
