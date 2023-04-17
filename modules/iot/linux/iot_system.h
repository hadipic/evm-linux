/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef IOT_SYSTEM_H
#define IOT_SYSTEM_H

#include "evm_module.h"
#include "uv.h"
#include <unistd.h>
#include <stdbool.h>

#define DEVICE_IO_NAME_LEN 64
#define DEVICE_IO_PATH_BUFFER_SIZE 64
#define DEVICE_IO_PIN_BUFFER_SIZE 10
#define DEVICE_IO_WRITE_BUFFER_SIZE 512

int system_check_path(const char* path);
int system_open_write_close(const char* path, const char* value);
int system_open_read_close(const char* path, char* buffer, unsigned buffer_len);
int system_device_open(const char* export_path, uint32_t value,
                         const char* exported_path,
                         const char** created_files,
                         int created_files_length);
int system_device_close(const char* export_path, uint32_t value);
void system_set_uv_loop(uv_loop_t *loop);
uv_loop_t *system_get_uv_loop();
void system_loop();
char system_getchar(void);
#endif

