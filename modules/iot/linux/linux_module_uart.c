#ifdef CONFIG_EVM_MODULE_UART
#include "evm_module.h"
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include "linux_system.h"

typedef struct _uart_dev_t {
    char dev[DEVICE_IO_NAME_LEN];
    int baudrate;
    int databits;
    int fd;
    uv_poll_t uart_poll_handle;
    evm_t *e;
    evm_val_t this;
} _uart_dev_t;

static unsigned baud_to_constant(int baudRate) {
  switch (baudRate) {
    case 50:
      return B50;
    case 75:
      return B75;
    case 110:
      return B110;
    case 134:
      return B134;
    case 150:
      return B150;
    case 200:
      return B200;
    case 300:
      return B300;
    case 600:
      return B600;
    case 1200:
      return B1200;
    case 1800:
      return B1800;
    case 2400:
      return B2400;
    case 4800:
      return B4800;
    case 9600:
      return B9600;
    case 19200:
      return B19200;
    case 38400:
      return B38400;
    case 57600:
      return B57600;
    case 115200:
      return B115200;
    case 230400:
      return B230400;
  }
  return B0;
}

static int databits_to_constant(int dataBits) {
  switch (dataBits) {
    case 8:
      return CS8;
    case 7:
      return CS7;
    case 6:
      return CS6;
    case 5:
      return CS5;
  }
  return -1;
}

static void uart_read_cb(uv_poll_t* req, int status, int events) {
    _uart_dev_t* uart = (_uart_dev_t*)req->data;
    char buf[DEVICE_IO_WRITE_BUFFER_SIZE];
    int i = 0;
    i = read(uart->fd, buf, DEVICE_IO_WRITE_BUFFER_SIZE - 1);
    if (i > 0) {
        buf[i] = '\0';
        evm_t *e = uart->e;
        evm_val_t this = evm_val_duplicate(e, uart->this);
        evm_val_t emitCallBack = evm_prop_get(e, this, "emit");
        if (evm_is_callable(e, emitCallBack)){
            evm_val_t buffer =  evm_buffer_create(e, (uint8_t*)buf, (int)i);
            evm_val_t args[3];
            args[0] = evm_mk_string(e, "data");
            args[1] = buffer;
            args[2] = evm_mk_number(e, i);
            evm_call_free(e, emitCallBack, this, 3, args);
            evm_val_free(e, args[0]);
            evm_val_free(e, args[1]);
            evm_val_free(e, args[2]);
        }
        evm_val_free(e, emitCallBack);
        evm_val_free(e, this);
    }
}

static void uart_register_read_cb(_uart_dev_t* uart) {
    uv_poll_start(&uart->uart_poll_handle, UV_READABLE, uart_read_cb);
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
    sprintf(dev->dev, "%s", evm_2_string(e, val));
    int fd = open(dev->dev, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        evm_free(dev);
        evm_throw(e, evm_mk_string(e, "Failed to open uart"));
    }

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

    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag = CLOCAL | CREAD;
    options.c_cflag |= (tcflag_t)baud_to_constant(dev->baudrate);
    options.c_cflag |= (tcflag_t)databits_to_constant(dev->databits);
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
    dev->fd = fd;
    dev->uart_poll_handle.data = dev;
    uart_register_read_cb(dev);
    return dev;
}

int evm_uart_write(evm_t *e, void *dev, void *buffer, int size){
    _uart_dev_t *uart = dev;
    int bytesWritten = 0;
    int offset = 0;
    int fd = uart->fd;
    do {
        errno = 0;
        bytesWritten = write(fd, buffer, size);
        tcdrain(fd);
        if (bytesWritten != -1) {
            offset += (unsigned)bytesWritten;
            continue;
        }
        if (errno == EINTR) {
            continue;
        }
        return 0;
    } while (size > offset);

    return 1;
}

int evm_uart_read(evm_t *e, void *dev, void *buf, int size){
    _uart_dev_t *uart = dev;
    return read(uart->fd, buf, size);
}

void evm_uart_close(evm_t *e, void *dev){
    _uart_dev_t *uart = dev;
    close(uart->fd);
}

void evm_uart_destroy(evm_t *e, void *dev){
    evm_free(dev);
}

#endif
