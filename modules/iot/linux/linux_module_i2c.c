#ifdef CONFIG_EVM_MODULE_I2C

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include "evm_module_i2c.h"


#define I2C_SLAVE_FORCE 0x0706

struct iot_i2c_platform_data_s {
  char *device;
  int device_fd;
  uint8_t addr;
};

void iot_i2c_create_platform_data(iot_i2c_t* i2c) {
  i2c->platform_data = evm_malloc(sizeof (iot_i2c_platform_data_t));
  i2c->platform_data->device_fd = -1;
}

void iot_i2c_destroy_platform_data(iot_i2c_platform_data_t* pdata) {
  evm_free(pdata->device);
  evm_free(pdata);
}

evm_val_t iot_i2c_set_platform_config(evm_t *e, iot_i2c_t* i2c, const evm_val_t jconfig) {
  iot_i2c_platform_data_t* platform_data = i2c->platform_data;
  evm_val_t str = evm_prop_get(e, jconfig, IOT_MAGIC_STRING_DEVICE);
  int len = evm_string_len(e, str);
  platform_data->device = evm_malloc(len + 1);
  memcpy(platform_data->device, evm_2_string(e, str), len);
  return EVM_UNDEFINED;
}


#define I2C_METHOD_HEADER(arg)                                   \
  iot_i2c_platform_data_t* platform_data = arg->platform_data; \
  EVM_ASSERT(platform_data);                                   \
  if (platform_data->device_fd < 0) {                            \
    DLOG("%s: I2C is not opened", __func__);                     \
    return false;                                                \
  }

bool iot_i2c_open(iot_i2c_t* i2c) {
  iot_i2c_platform_data_t* platform_data = i2c->platform_data;

  platform_data->device_fd = open(platform_data->device, O_RDWR);

  if (platform_data->device_fd == -1) {
    DLOG("%s : cannot open", __func__);
    return false;
  }

  if (ioctl(platform_data->device_fd, I2C_SLAVE_FORCE, i2c->address) < 0) {
    DLOG("%s : cannot set address", __func__);
    return false;
  }

  return true;
}

bool iot_i2c_close(iot_i2c_t* i2c) {
  I2C_METHOD_HEADER(i2c);

  if (close(platform_data->device_fd) < 0) {
    DLOG("%s : cannot close", __func__);
    return false;
  }

  platform_data->device_fd = -1;

  return true;
}

bool iot_i2c_write(iot_i2c_t* i2c) {
  I2C_METHOD_HEADER(i2c);

  uint8_t len = i2c->buf_len;
  char* data = i2c->buf_data;

  int ret = write(platform_data->device_fd, data, len);

  evm_free(i2c->buf_data);

  return ret == len;
}

bool iot_i2c_read(iot_i2c_t* i2c) {
  I2C_METHOD_HEADER(i2c);

  uint8_t len = i2c->buf_len;
  i2c->buf_data = evm_malloc(len);

  return read(platform_data->device_fd, i2c->buf_data, len) == len;
}

#endif
