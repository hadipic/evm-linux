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
#include "iot_system.h"

static uv_loop_t *uv_loop = NULL;

void system_set_uv_loop(uv_loop_t *loop) {
    uv_loop = loop;
}

int system_check_path(const char* path) {
    uv_fs_t fs_req;
    int err = uv_fs_stat(uv_loop, &fs_req, path, NULL);
    uv_fs_req_cleanup(&fs_req);

    if (err || fs_req.result) {
        return 0;
    }
    return 1;
}

int system_open_write_close(const char* path, const char* value) {
    uv_fs_t fs_req;
    int fd = uv_fs_open(uv_loop, &fs_req, path, O_WRONLY, 0666, NULL);
    uv_fs_req_cleanup(&fs_req);
    if (fd < 0) {
        return 0;
    }

    uv_buf_t uvbuf = uv_buf_init((char*)value, strlen(value));
    int write_err = uv_fs_write(uv_loop, &fs_req, fd, &uvbuf, 1, 0, NULL);
    uv_fs_req_cleanup(&fs_req);

    int close_err = uv_fs_close(uv_loop, &fs_req, fd, NULL);
    uv_fs_req_cleanup(&fs_req);
    if (write_err < 0) {
        return 0;
    }
    if (close_err < 0) {
        return 0;
    }
    return 1;
}

int system_open_read_close(const char* path, char* buffer, unsigned buffer_len) {
    uv_fs_t fs_open_req;
    int fd = uv_fs_open(uv_loop, &fs_open_req, path, O_RDONLY, 0666, NULL);
    uv_fs_req_cleanup(&fs_open_req);
    if (fd < 0) {
        return 0;
    }

    uv_fs_t fs_write_req;
    uv_buf_t uvbuf = uv_buf_init(buffer, buffer_len);
    int err = uv_fs_read(uv_loop, &fs_write_req, fd, &uvbuf, 1, 0, NULL);
    uv_fs_req_cleanup(&fs_write_req);
    if (err < 0) {
        return 0;
    }

    uv_fs_t fs_close_req;
    err = uv_fs_close(uv_loop, &fs_close_req, fd, NULL);
    uv_fs_req_cleanup(&fs_close_req);
    if (err < 0) {
        return 0;
    }

    return 1;
}

int system_device_open(const char* export_path, uint32_t value,
                         const char* exported_path,
                         const char** created_files,
                         int created_files_length) {
    if (system_check_path(exported_path)) {
        return 1;
    }

    char buff[DEVICE_IO_PIN_BUFFER_SIZE] = { 0 };
    snprintf(buff, DEVICE_IO_PIN_BUFFER_SIZE - 1, "%d", value);
    if (!system_open_write_close(export_path, buff)) {
        return 0;
    }

    int count = 0;
    int count_limit = created_files_length * 10;
    char buffer[DEVICE_IO_PIN_BUFFER_SIZE];
    char path[DEVICE_IO_PATH_BUFFER_SIZE] = { 0 };

    while (!system_check_path(exported_path) && count < count_limit) {
        usleep(100 * 1000);
        count++;
    }

    for (int i = 0; i < created_files_length; i++) {
        snprintf(path, DEVICE_IO_PATH_BUFFER_SIZE - 1, "%s%s", exported_path,
                    created_files[i]);

        while (!system_open_read_close(path, buffer,
                                                DEVICE_IO_PIN_BUFFER_SIZE) &&
                count < count_limit) {
            usleep(100 * 1000); 
            count++;
        }
    }
    usleep(1000 * 100);
    return count < count_limit;
}

int system_device_close(const char* export_path, uint32_t value) {
    char buff[DEVICE_IO_PIN_BUFFER_SIZE];
    snprintf(buff, DEVICE_IO_PIN_BUFFER_SIZE - 1, "%d", value);
    if (!system_open_write_close(export_path, buff)) {
        return 0;
    }
    return 1;
}

uv_loop_t *system_get_uv_loop()
{
    return uv_loop;
}

void system_loop()
{
    uv_loop = uv_default_loop();
    int  more;
    more = uv_run(uv_loop, UV_RUN_NOWAIT);
    if (more == 0) {
        more = uv_loop_alive(uv_loop);
    }
}
