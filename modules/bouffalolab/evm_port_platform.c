#include "evm_module.h"
#include <FreeRTOS.h>
#include "task.h"
#include "bflb_uart.h"

static struct bflb_device_s *uartx;

char platform_getchar(void)
{
    int ch = bflb_uart_getchar(uartx);
    while (ch == -1) {
        ch = bflb_uart_getchar(uartx);
        vTaskDelay(1);
    }
    return ch;
}

void platform_init(void) {
    uartx = bflb_device_get_by_name("uart0");

    struct bflb_uart_config_s cfg;

    cfg.baudrate = 115200;
    cfg.data_bits = UART_DATA_BITS_8;
    cfg.stop_bits = UART_STOP_BITS_1;
    cfg.parity = UART_PARITY_NONE;
    cfg.flow_ctrl = 0;
    cfg.tx_fifo_threshold = 7;
    cfg.rx_fifo_threshold = 7;
    bflb_uart_init(uartx, &cfg);
}
