/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "iot_uv.h"

#define IOT_ALIGNUP(value, alignment) \
  (((value) + ((alignment)-1)) & ~((alignment)-1))

uv_req_t* iot_uv_request_create(size_t request_size, evm_val_t jcallback, size_t extra_data_size) {
    EVM_ASSERT(evm_is_callable(evm_runtime(), jcallback));
    /* Make sure that the jerry_value_t is aligned */
    size_t aligned_request_size = IOT_ALIGNUP(request_size, 8u);
    char* request_memory = evm_malloc(
      aligned_request_size + sizeof(evm_val_t) + extra_data_size);
    uv_req_t* uv_request = (uv_req_t*)request_memory;
    uv_request->data = request_memory + aligned_request_size;
    *IOT_UV_REQUEST_CALLBACK(uv_request) = jcallback;
    return uv_request;
}

void iot_uv_request_destroy(uv_req_t* request) {
    evm_val_free(evm_runtime(), *IOT_UV_REQUEST_CALLBACK(request));
    evm_free(request);
}

uv_handle_t* iot_uv_handle_create(size_t handle_size, evm_val_t jobject, size_t extra_data_size) {
  EVM_ASSERT(evm_is_object(evm_runtime(), jobject));

  /* Make sure that the jerry_value_t is aligned */
  size_t aligned_request_size = IOT_ALIGNUP(handle_size, 8u);

  char* request_memory = evm_malloc(
      aligned_request_size + sizeof(iot_uv_handle_data) + extra_data_size);
  uv_handle_t* uv_handle = (uv_handle_t*)request_memory;
  uv_handle->data = request_memory + aligned_request_size;

  IOT_UV_HANDLE_DATA(uv_handle)->jobject = jobject;
  IOT_UV_HANDLE_DATA(uv_handle)->on_close_cb = NULL;

  evm_object_set_user_data(evm_runtime(), jobject, uv_handle);
  return uv_handle;
}

static void uv_handle_close_processor(uv_handle_t* handle) {
  iot_uv_handle_data* handle_data = IOT_UV_HANDLE_DATA(handle);

  if (handle_data->on_close_cb != NULL) {
    handle_data->on_close_cb(handle);
  }

  evm_val_free(evm_runtime(), handle_data->jobject);
  evm_free(handle);
}

void iot_uv_handle_close(uv_handle_t* handle, OnCloseHandler close_handler) {
  if (handle == NULL || uv_is_closing(handle)) {
    printf("Attempt to close uninitialized or already closed handle\r\n");
    return;
  }

  iot_uv_handle_data* handle_data = IOT_UV_HANDLE_DATA(handle);
  handle_data->on_close_cb = close_handler;
  uv_close(handle, uv_handle_close_processor);
}
