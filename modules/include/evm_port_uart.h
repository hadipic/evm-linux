#ifndef __EVM_PORT_UART_H__
#define __EVM_PORT_UART_H__

#include "evm_module.h"
#include "evm_port_msgbus.h"

#define UART_RX_BUF_SIZE    512

typedef struct evm_port_uart_t {
    evm_val_t callback;
    int baudrate;
    int databits;
    int stopbits;
    int parity;
    uint8_t rx_buf[UART_RX_BUF_SIZE];
    uint32_t rx_size;
   void *user;
} evm_port_uart_t;

#define EVM_PORT_UART_NO_PARITY       0x00
#define EVM_PORT_UART_EVEN_PARITY     0x01
#define EVM_PORT_UART_ODD_PARITY      0x02

void evm_port_uart_setup(evm_port_uart_t *info, const char *port);
int evm_port_uart_write(evm_port_uart_t* info, void* data, size_t length);
int evm_port_uart_read(evm_port_uart_t* info, void* buffer, size_t length);
int evm_port_uart_close(evm_port_uart_t* info);

#endif
