#ifdef CONFIG_EVM_MODULE_REPL
#include "evm_module.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static int fd_console;

void evm_repl_init(evm_t *e) {
    fd_console = open("/dev/uart/0", O_RDWR);
}

char evm_repl_tty_read(evm_t *e)
{
    EVM_UNUSED(e);
    char buffer;
    if( read(fd_console, &buffer, 1) ) 
        return buffer;
    else {
        vTaskDelay(10);
        return 0;
    }
}

void evm_repl_tty_write(int n, char *s)
{
    write(fd_console, s, n);
}


#endif


