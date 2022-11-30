#include "linux_systemio.h"

static uv_loop_t *uv_loop = NULL;

void systemio_set_uv_loop(uv_loop_t *loop) {
    uv_loop = loop;
}

int systemio_check_path(const char* path) {
    uv_fs_t fs_req;
    int err = uv_fs_stat(uv_loop, &fs_req, path, NULL);
    uv_fs_req_cleanup(&fs_req);

    if (err || fs_req.result) {
        return 0;
    }
    return 1;
}

int systemio_open_write_close(const char* path, const char* value) {
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

int systemio_open_read_close(const char* path, char* buffer, unsigned buffer_len) {
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

int systemio_device_open(const char* export_path, uint32_t value,
                         const char* exported_path,
                         const char** created_files,
                         int created_files_length) {
    if (systemio_check_path(exported_path)) {
        return 1;
    }

    char buff[DEVICE_IO_PIN_BUFFER_SIZE] = { 0 };
    snprintf(buff, DEVICE_IO_PIN_BUFFER_SIZE - 1, "%d", value);
    if (!systemio_open_write_close(export_path, buff)) {
        return 0;
    }

    int count = 0;
    int count_limit = created_files_length * 10;
    char buffer[DEVICE_IO_PIN_BUFFER_SIZE];
    char path[DEVICE_IO_PATH_BUFFER_SIZE] = { 0 };

    while (!systemio_check_path(exported_path) && count < count_limit) {
        usleep(100 * 1000);
        count++;
    }

    for (int i = 0; i < created_files_length; i++) {
        snprintf(path, DEVICE_IO_PATH_BUFFER_SIZE - 1, "%s%s", exported_path,
                    created_files[i]);

        while (!systemio_open_read_close(path, buffer,
                                                DEVICE_IO_PIN_BUFFER_SIZE) &&
                count < count_limit) {
            usleep(100 * 1000); 
            count++;
        }
    }
    usleep(1000 * 100);
    return count < count_limit;
}

int systemio_device_close(const char* export_path, uint32_t value) {
    char buff[DEVICE_IO_PIN_BUFFER_SIZE];
    snprintf(buff, DEVICE_IO_PIN_BUFFER_SIZE - 1, "%d", value);
    if (!systemio_open_write_close(export_path, buff)) {
        return 0;
    }
    return 1;
}
