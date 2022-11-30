#ifndef LINUX_SYSTEMIO_H
#define LINUX_SYSTEMIO_H

#include "evm.h"
#include "uv.h"
#include <unistd.h>

#define DEVICE_IO_NAME_LEN 64
#define DEVICE_IO_PATH_BUFFER_SIZE 64
#define DEVICE_IO_PIN_BUFFER_SIZE 10
#define DEVICE_IO_WRITE_BUFFER_SIZE 512

int systemio_check_path(const char* path);
int systemio_open_write_close(const char* path, const char* value);
int systemio_open_read_close(const char* path, char* buffer, unsigned buffer_len);
int systemio_device_open(const char* export_path, uint32_t value,
                         const char* exported_path,
                         const char** created_files,
                         int created_files_length);
int systemio_device_close(const char* export_path, uint32_t value);
void systemio_set_uv_loop(uv_loop_t *loop); 

#endif

