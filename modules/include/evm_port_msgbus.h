
#ifndef EVM_PORT_MSGBUS
#define EVM_PORT_MSGBUS

#include "evm_module.h"

#define MSG_TIMER 1
#define MSG_GPIO 2
#define MSG_UART_RX 3
#define MSG_UART_TXDONE 4

typedef int (*evm_msg_handler) (evm_t *e, int type, void* ptr);

typedef struct rtos_msg {
    evm_msg_handler handler;
    void* ptr;
    int type;
} rtos_msg_t;

// 定义接口方法
void evm_port_msgbus_init(void);
uint32_t evm_port_msgbus_put(rtos_msg_t* msg, size_t timeout);
uint32_t evm_port_msgbus_get(rtos_msg_t* msg, size_t timeout);
uint32_t evm_port_msgbus_freesize(void);

#endif
