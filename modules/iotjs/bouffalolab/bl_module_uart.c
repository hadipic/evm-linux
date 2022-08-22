#ifdef CONFIG_EVM_MODULE_UART
#include "evm_module.h"
#include <bl_uart.h>
#include <hal_uart.h>
#include <hal_board.h>
#include <device/vfs_uart.h>
#include <bl602_uart.h>
#include <vfs.h>
#include <fdt.h>
#include <libfdt.h>


typedef struct _uart_dev_t {
    const char *dev;
    int baudrate;
    int databits;
    int fd;
} _uart_dev_t;

static int get_dts_addr(const char *name, uint32_t *start, uint32_t *off)
{
    uint32_t addr = hal_board_get_factory_addr();
    const void *fdt = (const void *)addr;
    uint32_t offset;

    if (!name || !start || !off)
    {
        return -1;
    }

    offset = fdt_subnode_offset(fdt, 0, name);
    if (offset <= 0)
    {
        return -1;
    }

    *start = (uint32_t)fdt;
    *off = offset;

    return 0;
}

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

    uint32_t fdt = 0, offset = 0;
    /* uart */
    if (0 == get_dts_addr("uart", &fdt, &offset))
    {
        vfs_uart_init(fdt, offset);
    }

    dev->fd = aos_open(dev->dev, 0);
    if (dev->fd < 0)
    {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Failed to open uart"));
    }
    aos_ioctl(dev->fd, IOCTL_UART_IOC_BAUD_MODE, dev->databits);
    aos_ioctl(dev->fd, IOCTL_UART_IOC_READ_NOBLOCK, 0); 
    return dev;
}

int evm_uart_write(evm_t *e, void *dev, void *buffer, int size){
    _uart_dev_t *uart_dev = dev;
    return aos_write(uart_dev->fd, buffer, size);
}

int evm_uart_read(evm_t *e, void *dev, void *buf, int size){
    _uart_dev_t *uart_dev = dev;
	return aos_read(uart_dev->fd, buf, size);
}

void evm_uart_close(evm_t *e, void *dev){
    _uart_dev_t *uart_dev = dev;
    aos_close(uart_dev->fd);
}

void evm_uart_destroy(evm_t *e, void *dev){
    evm_free(dev);
}
#endif
