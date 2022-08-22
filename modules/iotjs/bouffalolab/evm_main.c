#include "evm_module.h"

#include <FreeRTOS.h>
#include <vfs.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <event_device.h>
#include <cli.h>
#include <bl_uart.h>
#include <bl_chip.h>
#include <bl_sec.h>
#include <bl_irq.h>
#include <bl_dma.h>
#include <hal_uart.h>
#include <hal_sys.h>
#include <hal_boot2.h>
#include <hal_board.h>
#include <bl_sys_time.h>
#include <fdt.h>
#include <libfdt.h>
#include <blog.h>


void *evm_malloc(size_t size)
{
    void * m = pvPortMalloc(size);
    if( m ) 
        memset(m, 0 ,size);
    return m;
}

void evm_free(void * p)
{
    if(p) 
        vPortFree(p);
}

void evm_main (void) {
    evm_t *env = evm_init();
    evm_module_init(env);
    evm_val_t res = evm_run_file(env, "main.js");
    evm_val_free(env, res);
}
