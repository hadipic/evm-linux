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

void *evm_realloc(void * p, size_t size)
{
    return pvPortMalloc(size);
}

evm_val_t native_print(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    for( int i = 0; i < argc; i++)
        printf("%s ", evm_2_string(e, v[i]));
    printf("\r\n");
    return EVM_UNDEFINED;
}

void evm_main (void) {
    evm_t *env = evm_init();
    
    evm_global_set(env, "print", evm_mk_native(env, native_print, "print", 0));
    evm_module_init(env);
#ifdef CONFIG_EVM_MODULE_REPL
    evm_run_repl(env);
    printf("quit repl mode\r\n");
#else
    evm_run_file(env, "main.js");
#endif
    
    while(1){
    #ifdef CONFIG_EVM_MODULE_PROCESS
        evm_module_process_poll(env);
    #endif
    }
}
