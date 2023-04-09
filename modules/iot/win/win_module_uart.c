/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <windows.h>

#include "evm_module_uart.h"

struct iot_uart_platform_data_s {
  char *device_path;
};

void iot_uart_create_platform_data(iot_uart_t* uart) {
  uart->platform_data = evm_malloc( sizeof (iot_uart_platform_data_t) );
}

void iot_uart_destroy_platform_data(iot_uart_platform_data_t* platform_data) {
  EVM_ASSERT(platform_data);
  evm_free(platform_data->device_path);
  evm_free(platform_data);
}

evm_val_t iot_uart_set_platform_config(evm_t *e, iot_uart_t* uart,
                                             const evm_val_t jconfig) {
  evm_val_t str = evm_prop_get(e, jconfig, IOT_MAGIC_STRING_DEVICE);
  int len = evm_string_len(e, str);
  uart->platform_data->device_path = evm_malloc(len + 1);
  char *device_s = evm_2_string(e, str);
  memcpy(uart->platform_data->device_path, device_s, len);
  evm_string_free(e, device_s);
  return EVM_UNDEFINED;
}

static unsigned baud_to_constant(unsigned baudRate) {
  switch (baudRate) {
  case 2400: return CBR_2400;
  case 4800: return CBR_4800;
  case 9600: return CBR_9600;
  case 19200:return CBR_19200;
  case 38400:return CBR_38400;
  case 56000:return CBR_56000;
  case 115200:return CBR_115200;
  default:
          return CBR_115200;
  }
  return CBR_115200;
}

static int databits_to_constant(int dataBits) {
  switch (dataBits) {
    case 8:
      return 8;
    case 7:
      return 7;
    case 6:
      return 6;
    case 5:
      return 5;
  }
  return -1;
}

static int serial_port_config(iot_uart_t* uart)
{
    DCB dcbSerialParams = {0};
    BOOL Status;
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    Status = GetCommState((HANDLE)uart->device_fd, &dcbSerialParams);
    if(Status == FALSE)
        return -1;
    dcbSerialParams.BaudRate = baud_to_constant(uart->baud_rate);
    dcbSerialParams.ByteSize = databits_to_constant(uart->data_bits);
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    Status = SetCommState((HANDLE)uart->device_fd, &dcbSerialParams);
    return Status;
}

bool iot_uart_open(uv_handle_t* uart_poll_handle) {
    iot_uart_t* uart =
      (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);

    HANDLE fd;
    TCHAR comname[100];
    wsprintf(comname,TEXT("%S"), uart->platform_data->device_path);
    fd = CreateFile(comname,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
    if(fd == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier= 10;
    if(SetCommTimeouts(fd, &timeouts) == FALSE){
        return false;
    }

    if(SetCommMask(fd, EV_RXCHAR) == FALSE){
        return false;
    }

    uart->device_fd = (intptr_t)fd;
    serial_port_config(uart);
    iot_uart_register_read_cb((uv_poll_t*)uart_poll_handle);
    return true;
}

void iot_uart_read_cb(uv_poll_t* req, int status, int events) {
    evm_t *e = evm_runtime();
    iot_uart_t* uart = (iot_uart_t*)req->data;
    char buf[UART_WRITE_BUFFER_SIZE];
    int i;
    BOOL Status = ReadFile(uart->device_fd, buf, UART_WRITE_BUFFER_SIZE - 1, (DWORD *)&i, NULL);
    if(Status == FALSE){
        return;
    }
    if (i > 0) {
        buf[i] = '\0';
        DDDLOG("%s - read length: %d", __func__, i);
        evm_val_t juart = IOT_UV_HANDLE_DATA(req)->jobject;
        evm_val_t jemit =
            evm_prop_get(e, juart, IOT_MAGIC_STRING_EMIT);
        EVM_ASSERT(evm_is_callable(e, jemit));

        evm_val_t str = evm_mk_string(e, IOT_MAGIC_STRING_DATA);

        evm_val_t jbuf = evm_buffer_create(e, buf, (size_t)i);
        evm_val_t jargs[] = { str, jbuf };
        evm_val_t jres = evm_call(e, jemit, IOT_UV_HANDLE_DATA(req)->jobject, 2, jargs);

        evm_val_free(e, jres);
        evm_val_free(e, str);
        evm_val_free(e, jbuf);
        evm_val_free(e, jemit);
    }
}

bool iot_uart_write(uv_handle_t* uart_poll_handle) {
  iot_uart_t* uart =
      (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);

  int bytesWritten = 0;
  unsigned offset = 0;
  HANDLE fd = (HANDLE)uart->device_fd;
  const char* buf_data = uart->buf_data;

  DDDLOG("%s - data: %s", __func__, buf_data);
  DWORD dNoOFBytesWriten;
  do {
      errno = 0;
      WriteFile(fd,
                               buf_data + offset,
                               uart->buf_len - offset,
                               &dNoOFBytesWriten,
                               NULL);


      if (bytesWritten != -1) {
          offset += (unsigned)dNoOFBytesWriten;
          continue;
      }

      if (errno == EINTR) {
          continue;
      }

      return false;

  } while (uart->buf_len > offset);
  return true;
}

void iot_uart_handle_close_cb(uv_handle_t* uart_poll_handle) {
  iot_uart_t* uart =
      (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);

  if (close(uart->device_fd) < 0) {
    DLOG(iot_periph_error_str(kUartOpClose));
    EVM_ASSERT(0);
  }
}
