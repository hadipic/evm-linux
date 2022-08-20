#ifdef CONFIG_EVM_MODULE_UART
#include "evm_module.h"

#include <rtthread.h>
#include <rtdevice.h>

typedef struct _uart_dev_t {
    rt_device_t dev;
    int baudrate;
    int databits;
} _uart_dev_t;

evm_val_t evm_module_uart_class_instantiate(evm_t *e);

static evm_val_t _uart_open_device(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
	evm_val_t val;
	evm_val_t ret_obj;
	evm_val_t args;
	_uart_dev_t *dev;

	if( argc < 1)
		return EVM_VAL_UNDEFINED;

	dev = evm_malloc(sizeof(_uart_dev_t));
	EVM_ASSERT(dev);

	val = evm_prop_get(e, v[0], "device", 0);
	if( !evm_is_string(val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'device' member"));
	}
		
	dev->dev = rt_device_find(evm_2_string(e, val));
    if ( dev->dev == RT_NULL ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Can't find uart device"));
    }

	val = evm_prop_get(e, v[0], "baudRate", 0);
	if( !evm_is_integer(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'baudRate' member"));
	}
	dev->baudrate = evm_2_integer(e, val);

    val = evm_prop_get(e, v[0], "dataBits", 0);
	if( !evm_is_integer(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'dataBits' member"));
	}
	dev->databits = evm_2_integer(e, val);

    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = dev->baudrate;
    config.data_bits = dev->databits;
    config.bufsz     = 512;
    rt_device_control(dev->dev, RT_DEVICE_CTRL_CONFIG, &config);
    rt_err_t re = rt_device_open(dev->dev, RT_DEVICE_FLAG_INT_RX);
    if(re != RT_EOK) {
        evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Failed to open uart"));
    }

    ret_obj = evm_module_uart_class_instantiate(e);
	evm_object_set_ext_data(e, ret_obj, dev);
    return *ret_obj;
}

//uart.open(configuration)
static evm_val_t evm_module_uart_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	return _uart_open_device(e, p, argc, v);
}

static rt_err_t _uart_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    _uart_dev_t *dev = (_uart_dev_t*)evm_object_get_ext_data(p);
    if( !dev ) 
        return EVM_VAL_UNDEFINED;

    if( argc < 1 || !( evm_is_buffer(v) || evm_is_string(v) ) ) {
        return EVM_VAL_UNDEFINED;
    }

    void *buffer;
    rt_size_t size;

    if( evm_is_string(v) ) {
        buffer = evm_2_string(v);
        size = evm_string_len(v);
    } else {
        buffer = evm_buffer_addr(v);
        size = evm_buffer_len(v);
    }
    return rt_device_write(dev->dev, 0, buffer, size);
}

//uartport.write(data)
static evm_val_t evm_module_uart_class_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_uart_class_write(e, p, argc, v);
    return EVM_VAL_UNDEFINED;
}

static rt_err_t _uart_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    _uart_dev_t *dev = (_uart_dev_t*)evm_object_get_ext_data(p);
    if( !dev ) 
        return EVM_VAL_UNDEFINED;
    return rt_device_close(dev->dev);
}

//uartport.close()
static evm_val_t evm_module_uart_class_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
	_uart_class_close(e, p, argc, v);
    return EVM_VAL_UNDEFINED;
}

evm_val_t evm_module_uart_class_instantiate(evm_t *e)
{
	evm_val_t obj = evm_object_create_user_data(e, NULL);
	evm_prop_append(e, obj, "write", evm_mk_native(e, evm_module_uart_class_write, "write", 0));
	evm_prop_append(e, obj, "close", evm_mk_native(e, evm_module_uart_class_close, "close", 0));
	return obj;
}

void evm_module_uart(evm_t *e) {
	evm_val_t obj = evm_object_create(e);
	evm_prop_set(e, obj, "open", evm_mk_native(e, evm_module_uart_open, "open", 0));
	evm_module_add(e, "uart", obj);
}
#endif
