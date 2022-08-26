#ifdef CONFIG_EVM_MODULE_UART
#include "evm_module.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>


typedef struct _uart_dev_t {
    const char *dev;
    int baudrate;
    int databits;
    int fd;
} _uart_dev_t;



void *evm_uart_open(evm_t *e, evm_val_t v){
    evm_val_t val ;
	_uart_dev_t *dev;

	dev = evm_malloc(sizeof(_uart_dev_t));
	EVM_ASSERT(dev);

	val = evm_prop_get(e, v, "device");
	if( !evm_is_string(e, val) ) {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'device' member"));
	}
    dev->dev = evm_2_string(e, val);

    val = evm_prop_get(e, v, "baudRate");
	if( !evm_is_integer(e, val) ) {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'baudRate' member"));
	}
	dev->baudrate = evm_2_integer(e, val);

    val = evm_prop_get(e, v, "dataBits");
	if( !evm_is_integer(e, val) ) {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Configuration has no 'dataBits' member"));
	}
	dev->databits = evm_2_integer(e, val);
    dev->fd = open(dev->dev, 0);
    if (dev->fd < 0)
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Failed to open uart"));
    }
    return dev;
}

int evm_uart_write(evm_t *e, void *dev, void *buffer, int size){
    _uart_dev_t *uart_dev = dev;
    return write(uart_dev->fd, buffer, size);
}

int evm_uart_read(evm_t *e, void *dev, void *buf, int size){
    _uart_dev_t *uart_dev = dev;
	return read(uart_dev->fd, buf, size);
}

void evm_uart_close(evm_t *e, void *dev){
    _uart_dev_t *uart_dev = dev;
    close(uart_dev->fd);
}

void evm_uart_destroy(evm_t *e, void *dev){
    evm_free(dev);
}
#endif
