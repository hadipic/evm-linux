#include "evm_port_fs.h"
#include <unistd.h>
#include <sys/fcntl.h>

int evm_port_fs_open(char *path, int mode) {
    return open(path, mode);
}

int evm_port_fs_read(int fd, void *buf, size_t size) {
    return read(fd, buf, size);
}

int evm_port_fs_write(int fd, void *buf, size_t size) {
    return write(fd, buf, size);
}

int evm_port_fs_lseek(int fd, int off, int whence) {
    return lseek(fd, off, whence);
}

void evm_port_fs_close(int fd) {
    close(fd);
}
