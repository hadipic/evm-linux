/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
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

#endif
