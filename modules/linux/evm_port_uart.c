#include "evm_port_uart.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <pthread.h>

typedef struct _uart_user_t {
    pthread_t pid;
    int fd;
} _uart_user_t;

int evm_port_uart_exist(int uartid) {
    return uartid >= 0;
}

static int _uart_handler(evm_t *e, void* ptr) {
    evm_port_uart_t* info = (evm_port_uart_t*)ptr;
    _uart_user_t *user = info->user;
    if (!evm_port_uart_exist(user->fd)) {
        return 0;
    }
    if( !evm_is_callable(e, info->callback) )
        return 0;
    evm_val_t cb_func = info->callback;
    evm_val_t args[2];
    if( info->rx_size ) {
        args[0] = evm_buffer_create(e, info->rx_buf, info->rx_size);
        args[1] = evm_mk_number(e, info->rx_size);
        evm_call_free(e, cb_func, EVM_UNDEFINED, args, 2);
        evm_val_free(e, args[0]);
    }
    return 1;
}

static void* uart_task(void *arg)
{
    int length = 0, fd;
    evm_port_uart_t *uart = (evm_port_uart_t*)arg;
    _uart_user_t *user = uart->user;
    fd = user->fd;
    while (1) {
        length = read(fd, uart->rx_buf, UART_RX_BUF_SIZE);
        if( length > 0 ) {
            rtos_msg_t msg;
            msg.handler = _uart_handler;
            msg.ptr = uart;
            uart->rx_size = length;
            evm_port_msgbus_put(&msg, 1);
        }
        usleep(10 * 1000);
    }
}

void evm_port_uart_setup(evm_port_uart_t *info, const char *port)
{
    _uart_user_t *user = NULL;
    if( !info->user ) {
        user = evm_malloc(sizeof (_uart_user_t));
        user->fd = open(port , O_RDWR|O_NOCTTY|O_NDELAY, 0);
        if( user->fd < 0 )
            return;
        user->pid = -1;
    }

    struct termios new_cfg;
    tcgetattr(user->fd, &new_cfg);
    new_cfg.c_cflag |= (CLOCAL | CREAD);

    switch (info->baudrate) {
    case 2400: cfsetispeed(&new_cfg, B2400);break;
    case 4800: cfsetispeed(&new_cfg, B4800);break;
    case 9600: cfsetispeed(&new_cfg, B9600);break;
    case 19200: cfsetispeed(&new_cfg, B19200);break;
    case 38400: cfsetispeed(&new_cfg, B38400);break;
    case 57600: cfsetispeed(&new_cfg, B57600);break;
    case 115200: cfsetispeed(&new_cfg, B115200);break;
    default:
        cfsetispeed(&new_cfg, B115200);break;
    }

    switch (info->databits) {
    case 8: new_cfg.c_cflag |= CS8;break;
    case 7: new_cfg.c_cflag |= CS7;break;
    case 6: new_cfg.c_cflag |= CS6;break;
    case 5: new_cfg.c_cflag |= CS5;break;
    }

    switch (info->parity) {
    case EVM_PORT_UART_NO_PARITY: new_cfg.c_iflag |= IGNPAR;break;
    case EVM_PORT_UART_EVEN_PARITY: new_cfg.c_iflag |= PARENB;break;
    case EVM_PORT_UART_ODD_PARITY: new_cfg.c_iflag |= PARODD;break;
    }

    info->callback = EVM_UNDEFINED;
    tcflush(user->fd,TCIFLUSH);
    tcsetattr(user->fd, TCSANOW, &new_cfg);
    if( user->pid != -1)
        pthread_create(&user->pid, NULL, uart_task, info);
}

int evm_port_uart_write(evm_port_uart_t* info, void* data, size_t length)
{
    _uart_user_t *user = info->user;
    return write(user->fd, data, length);
}

int evm_port_uart_read(evm_port_uart_t* info, void* buffer, size_t length)
{
    _uart_user_t *user = info->user;
    return read(user->fd, buffer, length);
}

int evm_port_uart_close(evm_port_uart_t* info)
{
    _uart_user_t *user = info->user;
    return close(user->fd);
}


