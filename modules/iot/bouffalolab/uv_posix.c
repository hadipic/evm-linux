#include <stddef.h>

int uv_posix_open (const char *__file, int __oflag, ...){

}

int uv_posix_write (int __fd, const void *__buf, size_t __n){

}

int uv_posix_read (int __fd, void *__buf, size_t __nbytes){

}

int uv_posix_close (int __fd){

}

int uv_posix_fsync (int __fd){

}

int uv_posix_fdatasync (int __fildes){

}

int uv_posix_stat(const char *path, struct stat *buf){

}

int uv_posix_fstat (int __fd, struct stat *__buf){

}

int uv_posix_rename(char *oldname, char *newname){

}
