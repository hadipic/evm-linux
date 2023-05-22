#ifndef __EVM_PORT_FS_H__
#define __EVM_PORT_FS_H__

#include "evm_module.h"

int evm_port_fs_open(char *path, int mode);
int evm_port_fs_read(int fd, void *buf, size_t size);
int evm_port_fs_write(int fd, void *buf, size_t size);
int evm_port_fs_lseek(int fd, int off, int whence);
void evm_port_fs_close(int fd);

#endif
