/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "evm_module.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bflb_uart.h"
#include "bflb_romfs.h"

static struct bflb_device_s *uartx;

char iot_platform_getchar(void)
{
    int ch = bflb_uart_getchar(uartx);
    while (ch == -1) {
        ch = bflb_uart_getchar(uartx);
        vTaskDelay(1);
    }
    return ch;
}

void *evm_malloc(size_t size)
{
    void * m = malloc(size);
    if( m )
        memset(m, 0 ,size);
    return m;
}

void evm_free(void * p)
{
    if(p)
        free(p);
}

void *evm_realloc(void * p, size_t size)
{
    return realloc(p, size);
}

uint8_t *evm_load_file(const char *filename, size_t *size) {
    FILE *f;
    uint8_t *buf;
    size_t buf_len;
    long lret;
    f = fopen(filename, "rb");
    if (!f)
        return NULL;
    if (fseek(f, 0, SEEK_END) < 0)
        goto fail;
    lret = ftell(f);
    if (lret < 0)
        goto fail;

    buf_len = lret;
    if (fseek(f, 0, SEEK_SET) < 0)
        goto fail;
    buf = evm_malloc(buf_len + 1);
    if (!buf)
        goto fail;
    if (fread(buf, 1, buf_len, f) != buf_len) {
        evm_free(buf);
    fail:
        fclose(f);
        return NULL;
    }
    buf[buf_len] = '\0';
    fclose(f);
    *size = buf_len;
    return buf;
}

void evm_main (char *filename) {
    // romfs_mount(0xA0000000 - 0x1000 + 0x378000);
    romfs_mount(0xA0347000);

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

    evm_t *e = evm_init();
    evm_module_init(e);

#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_shell(e);
#else
    evm_run_file(e, EVM_UNDEFINED, filename);
#endif
}

void evm_loop() {
    system_loop();
}