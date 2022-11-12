#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>
#include <FreeRTOS.h>
#include <task.h>

static int fd_console;

void evm_repl_init(evm_t *e) {
    fd_console = aos_open("/dev/ttyS0", 0);
}

char evm_repl_tty_read(evm_t *e)
{
    EVM_UNUSED(e);
    char buffer[16];
    if( aos_read(fd_console, buffer, 1) ) 
        return buffer[0];
    else {
        vTaskDelay(10);
        return 0;
    }
}

void evm_repl_tty_write(int n, char *s)
{
    aos_write(fd_console, s, n);
}


#endif


