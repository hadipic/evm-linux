#ifndef _LINUX_UV_H
#define _LINUX_UV_H

#include "uv.h"
#include "linux_system.h"

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
} evm_uv_handle_data;

#define EVM_UV_REQUEST_CALLBACK(UV_REQ) ((evm_val_t*)(UV_REQ->data))

#define EVM_UV_HANDLE_DATA(UV_HANDLE) \
  ((evm_uv_handle_data*)((UV_HANDLE)->data))

uv_req_t* evm_uv_request_create(size_t request_size, evm_val_t jcallback, size_t extra_data_size);
void evm_uv_request_destroy(uv_req_t* request);
uv_handle_t* evm_uv_handle_create(size_t handle_size, evm_val_t jobject, size_t extra_data_size);
void evm_uv_handle_close(uv_handle_t* handle, OnCloseHandler close_handler);

#endif

