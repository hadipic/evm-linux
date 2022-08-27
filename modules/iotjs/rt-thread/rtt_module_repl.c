
#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_REPL
#include <rtthread.h>

static rt_device_t fd_console;

void evm_repl_init(evm_t *e) {
    fd_console = rt_device_find(CONFIG_EVM_REPL_DEV_NAME);
    rt_device_open(fd_console, RT_DEVICE_FLAG_STREAM);
}

char evm_repl_tty_read(evm_t *e)
{
    EVM_UNUSED(e);
    char buffer;
    if( rt_device_read(fd_console, 0, &buffer, 1) == 1) 
        return buffer;
    else {
        rt_thread_mdelay(10);
        return 0;
    }
}

void evm_repl_tty_write(int n, char *s)
{
    rt_device_write(fd_console, 0, s, n);
}


#endif


