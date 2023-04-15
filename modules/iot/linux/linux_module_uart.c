/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "evm_module_uart.h"

struct iot_uart_platform_data_s {
  char *device_path;
};

static unsigned baud_to_constant(unsigned baudRate) {
  switch (baudRate) {
    case 50:
      return B50;
    case 75:
      return B75;
    case 110:
      return B110;
    case 134:
      return B134;
    case 150:
      return B150;
    case 200:
      return B200;
    case 300:
      return B300;
    case 600:
      return B600;
    case 1200:
      return B1200;
    case 1800:
      return B1800;
    case 2400:
      return B2400;
    case 4800:
      return B4800;
    case 9600:
      return B9600;
    case 19200:
      return B19200;
    case 38400:
      return B38400;
    case 57600:
      return B57600;
    case 115200:
      return B115200;
    case 230400:
      return B230400;
  }
  return B0;
}

static int databits_to_constant(int dataBits) {
  switch (dataBits) {
    case 8:
      return CS8;
    case 7:
      return CS7;
    case 6:
      return CS6;
    case 5:
      return CS5;
  }
  return -1;
}

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

bool iot_uart_read(uv_handle_t* handle) {
    iot_uart_t* uart = (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(handle);
    evm_t *e = evm_runtime();
    char buf[UART_WRITE_BUFFER_SIZE];
    int i = read(uart->device_fd, buf, UART_WRITE_BUFFER_SIZE - 1);
    if (i > 0) {
        buf[i] = '\0';
        DDDLOG("%s - read length: %d", __func__, i);
        evm_val_t juart = IOT_UV_HANDLE_DATA(handle)->jobject;
        evm_val_t jemit =
            evm_prop_get(e, juart, IOT_MAGIC_STRING_EMIT);
        EVM_ASSERT(evm_is_callable(e, jemit));

        evm_val_t str = evm_mk_string(e, IOT_MAGIC_STRING_DATA);

        evm_val_t jbuf = evm_buffer_create(e, buf, (size_t)i);
        evm_val_t jargs[] = { str, jbuf };
        evm_val_t jres = evm_call(e, jemit, IOT_UV_HANDLE_DATA(handle)->jobject, 2, jargs);

        evm_val_free(e, jres);
        evm_val_free(e, str);
        evm_val_free(e, jbuf);
        evm_val_free(e, jemit);
    }
    return true;
}

bool iot_uart_open(uv_handle_t* uart_poll_handle) {
    iot_uart_t* uart =
      (iot_uart_t*)IOT_UV_HANDLE_EXTRA_DATA(uart_poll_handle);
    int fd = open(uart->platform_data->device_path,
                O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
    return false;
    }

    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag = CLOCAL | CREAD;
    options.c_cflag |= (tcflag_t)baud_to_constant(uart->baud_rate);
    options.c_cflag |= (tcflag_t)databits_to_constant(uart->data_bits);
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    uart->device_fd = fd;
    iot_uart_register_read_cb((uv_poll_t*)uart_poll_handle);
    return true;
}

void iot_uart_read_cb(uv_poll_t* req, int status, int events) {
    evm_t *e = evm_runtime();
    iot_uart_t* uart = (iot_uart_t*)req->data;
    char buf[UART_WRITE_BUFFER_SIZE];
    int i = read(uart->device_fd, buf, UART_WRITE_BUFFER_SIZE - 1);
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
  int fd = uart->device_fd;
  const char* buf_data = uart->buf_data;

  DDDLOG("%s - data: %s", __func__, buf_data);

  do {
    errno = 0;
    bytesWritten = write(fd, buf_data + offset, uart->buf_len - offset);
    tcdrain(fd);

    DDDLOG("%s - size: %d", __func__, uart->buf_len - offset);

    if (bytesWritten != -1) {
      offset += (unsigned)bytesWritten;
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
