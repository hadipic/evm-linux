/****************************************************************************
**
** Copyright (C) 2022 @武汉市凡迈科技有限公司
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  Version	: 1.0
**  Email	: scriptiot@aliyun.com
**  Website	: https://gitee.com/scriptiot
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_H
#define EVM_MODULE_H

#include "evm.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EVM_GPIO_DIRECTION_IN   0
#define EVM_GPIO_DIRECTION_OUT  1
#define EVM_GPIO_MODE_NONE      0
#define EVM_GPIO_MODE_PULLUP    1
#define EVM_GPIO_MODE_PULLDOWN  2
#define EVM_GPIO_MODE_FLOAT     3
#define EVM_GPIO_MODE_PUSHPULL  4
#define EVM_GPIO_MODE_OPENDRAIN 5
#define EVM_GPIO_EDGE_NONE      0
#define EVM_GPIO_EDGE_RISING    1
#define EVM_GPIO_EDGE_FALLING   2
#define EVM_GPIO_EDGE_BOTH      3

#define EVM_TIMER_PERIOD        0
#define EVM_TIMER_ONE_SHOT      1

#ifdef __linux
#define EVM_HEAP_SIZE (500 * 1024)
#define EVM_STACK_SIZE (50 * 1024)
#else
#define EVM_HEAP_SIZE (50 * 1024)
#define EVM_STACK_SIZE (5 * 1024)
#endif
#define EVM_MODULE_REGISTRY_SIZE 20

#ifdef CONFIG_EVM_MODULE_ADC
extern void evm_module_adc(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_GPIO
extern void evm_module_gpio(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_TIMER
extern void evm_module_timers(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_I2C
extern void evm_module_i2c(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_UART
extern void evm_module_uart(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_FS
extern void evm_module_fs(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_UDP
extern evm_err_t evm_module_udp(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_NET
extern evm_err_t evm_module_net(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_PROCESS
extern evm_val_t evm_module_process_nextTick(evm_t *e, evm_val_t p, int argc, evm_val_t *v);
extern void evm_module_process_poll(evm_t *e);
extern evm_err_t evm_module_process(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_EVENT
typedef void (*event_handler) (evm_t *e, void* ptr);
typedef struct evm_eventbus_t{
    event_handler handler;
    void* ptr;
} evm_eventbus_t;
extern evm_err_t evm_module_events(evm_t *e);
extern void evm_eventbus_init(void);
extern int evm_eventbus_set(evm_eventbus_t *msg);
extern int evm_eventbus_get(evm_eventbus_t *msg);
#endif

#ifdef CONFIG_EVM_MODULE_DNS
extern evm_err_t evm_module_dns(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_BUFFER
extern evm_err_t evm_module_buffer(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_ASSERT
extern evm_err_t evm_module_assert(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_CFFI
typedef union  {
    void *p; 
    char *s; 
    double f64;
    float f32; 
    int32_t i32; 
    int64_t i64;
} evm_cffi_val_t;
extern void evm_cffi_exec_param(evm_t *e, evm_cffi_val_t *cffi_vals, const char *signature, int argc, evm_val_t *v);
extern evm_val_t evm_cffi_exec_ret(evm_t *e, evm_cffi_val_t cffi_val, const char *signature);
#endif

#ifdef CONFIG_EVM_MODULE_LIBC
void evm_module_libc(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_WLAN
void evm_module_wlan(evm_t *e);
#endif

#ifdef CONFIG_EVM_MODULE_REPL
void evm_run_repl(evm_t *e);
#endif

extern void evm_main(char *filename);
extern void evm_loop();

extern int evm_module_registry_add(evm_t *e, evm_val_t v);
extern evm_val_t evm_module_registry_get(evm_t *e, int id);
extern void evm_module_registry_remove(evm_t *e, int id);
extern void evm_module_next_tick(evm_t *e, int argc, evm_val_t *v);
extern evm_err_t evm_module_event_add_listener(evm_t *e, evm_val_t pthis, const char *type, evm_val_t listener);
extern void evm_module_event_remove_listener(evm_t *e, evm_val_t pthis, const char *type);
extern void evm_module_event_emit (evm_t *e, evm_val_t pthis, const char *type, int argc, evm_val_t *v);
void evm_module_init(evm_t *env);
extern evm_t *evm_runtime(void);

extern void *evm_adc_open(evm_t *e, evm_val_t obj);
extern int evm_adc_read(evm_t *e, void *dev);
extern void evm_adc_close(evm_t *e, void *dev);
extern void evm_adc_destroy(evm_t *e, void *dev);

extern void *evm_gpio_open(evm_t *e, evm_val_t obj);
extern void evm_gpio_set_direction(evm_t *e, void *dev, int value);
extern void evm_gpio_write(evm_t *e, void *dev, int value);
extern int evm_gpio_read(evm_t *e, void *dev);
extern void evm_gpio_close(evm_t *e, void *dev);
extern void evm_gpio_destroy(evm_t *e, void *dev);

extern void *evm_i2c_open(evm_t *e, evm_val_t obj);
extern void evm_i2c_read(evm_t *e, void *dev, void *buf, int size);
extern void evm_i2c_write(evm_t *e, void *dev, void *buf, int size);
extern void evm_i2c_close(evm_t *e, void *dev);
extern void evm_i2c_destroy(evm_t *e, void *dev);

extern void *evm_timer_open(evm_t *e, evm_val_t cb, int tick, int flag);
extern void evm_timer_destroy(evm_t *e, void *dev);

extern void *evm_uart_open(evm_t *e, evm_val_t obj);
extern int evm_uart_write(evm_t *e, void *dev, void *buffer, int size);
extern int evm_uart_read(evm_t *e, void *dev, void *buf, int size);
extern void evm_uart_close(evm_t *e, void *dev);
extern void evm_uart_destroy(evm_t *e, void *dev);

extern void evm_wlan_connect(evm_t *e, char *ssid, char *pwd);
extern void evm_wlan_disconnect(evm_t *e);
extern evm_val_t evm_wlan_scan(evm_t *e);
extern int evm_wlan_is_connectd(evm_t *e);
extern void evm_wlan_init(evm_t *e);

extern void evm_repl_init(evm_t *e);
extern void evm_repl_tty_write(int n, char *c);
extern char evm_repl_tty_read(evm_t *e);

#ifdef __cplusplus
}
#endif

#endif
