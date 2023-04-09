/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef EVM_MODULE_UART_H
#define EVM_MODULE_UART_H

#include "evm_module_periph_common.h"


void iot_uart_register_read_cb(uv_poll_t* uart_poll_handle);
void iot_uart_handle_close_cb(uv_handle_t* handle);

void iot_uart_create_platform_data(iot_uart_t* uart);
void iot_uart_destroy_platform_data(iot_uart_platform_data_t* platform_data);

evm_val_t iot_uart_set_platform_config(evm_t *e, iot_uart_t* uart,
                                             const evm_val_t jconfig);

bool iot_uart_open(uv_handle_t* uart_poll_handle);
bool iot_uart_write(uv_handle_t* uart_poll_handle);
void iot_uart_read_cb(uv_poll_t* req, int status, int events);

#endif
