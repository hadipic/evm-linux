
#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_UART

#include <rtthread.h>
#include <rtdevice.h>

typedef struct _uart_dev_t {
    rt_device_t dev;
    int baudrate;
    int databits;
} _uart_dev_t;

void *evm_uart_open(evm_t *e, evm_val_t obj){
	evm_val_t val;
	_uart_dev_t *dev;
	dev = evm_malloc(sizeof(_uart_dev_t));
	EVM_ASSERT(dev);

	val = evm_prop_get(e, obj, "device");
	if( !evm_is_string(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'device' member"));
	}
		
	dev->dev = rt_device_find(evm_2_string(e, val));
    if ( dev->dev == RT_NULL ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Can't find uart device"));
    }

	val = evm_prop_get(e, obj, "baudRate");
	if( !evm_is_integer(e, val) ) {
		evm_free(dev);
		evm_throw(e, evm_mk_string(e, "Configuration has no 'baudRate' member"));
	}
	dev->baudrate = evm_2_integer(e, val);

    val = evm_prop_get(e, obj, "dataBits");
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
	return dev;
}

int evm_uart_write(evm_t *e, void *dev, void *buffer, int size){
	_uart_dev_t *uart_dev = dev;
    if( !dev ) 
        return 0;
    return rt_device_write(uart_dev->dev, 0, buffer, size);
}

int evm_uart_read(evm_t *e, void *dev, void *buf, int size){
	return 0;
}

void evm_uart_close(evm_t *e, void *dev){
	_uart_dev_t *uart_dev = dev;
	rt_device_close(uart_dev->dev);
}

void evm_uart_destroy(evm_t *e, void *dev){
	_uart_dev_t *uart_dev = dev;
	rt_device_close(uart_dev->dev);
	evm_free(dev);
}

#endif
