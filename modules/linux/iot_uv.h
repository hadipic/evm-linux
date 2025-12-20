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
#ifndef IOT_UV_H
#define IOT_UV_H

#include "uv.h"
#include "iot_system.h"

#ifndef EVM_MAX_READ_BUFFER_SIZE
#if defined(__NUTTX__) || defined(__TIZENRT__)
#define EVM_MAX_READ_BUFFER_SIZE 1023
#define EVM_MAX_PATH_SIZE 120
#else /* !__NUTTX__ && !__TIZENRT__ */
#define EVM_MAX_READ_BUFFER_SIZE 65535
#define EVM_MAX_PATH_SIZE PATH_MAX
#endif /* __NUTTX__ || TIZENRT */
#endif /* IOTJS_MAX_READ_BUFFER_SIZE */

typedef void (*OnCloseHandler)(uv_handle_t*);

typedef struct {
  evm_val_t jobject;
  OnCloseHandler on_close_cb;
} iot_uv_handle_data;

#define IOT_UV_REQUEST_CALLBACK(UV_REQ) ((evm_val_t*)(UV_REQ->data))

#define IOT_UV_HANDLE_DATA(UV_HANDLE) \
  ((iot_uv_handle_data*)((UV_HANDLE)->data))

#define IOT_UV_REQUEST_EXTRA_DATA(UV_REQ) \
  ((char*)((char*)(UV_REQ->data) + sizeof(evm_val_t)))

#define IOT_UV_HANDLE_EXTRA_DATA(UV_HANDLE) \
  ((char*)((char*)((UV_HANDLE)->data) + sizeof(iot_uv_handle_data)))

uv_req_t* iot_uv_request_create(size_t request_size, evm_val_t jcallback, size_t extra_data_size);
void iot_uv_request_destroy(uv_req_t* request);
uv_handle_t* iot_uv_handle_create(size_t handle_size, evm_val_t jobject, size_t extra_data_size);
void iot_uv_handle_close(uv_handle_t* handle, OnCloseHandler close_handler);

#endif

