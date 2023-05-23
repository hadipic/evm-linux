#include "evm_port_fs.h"
#include <sys/fcntl.h>

static int convert_fs_mode_to_oflag(const char *mode)
{
    if (strcmp(mode, "w") == 0) return (O_WRONLY | O_CREAT | O_TRUNC);
    if (strcmp(mode, "r") == 0) return (O_RDONLY);
    if (strcmp(mode, "w+") == 0) return (O_RDWR | O_CREAT | O_TRUNC);
    if (strcmp(mode, "r+") == 0) return (O_RDWR);
    if (strcmp(mode, "a") == 0) return (O_RDWR | O_CREAT | O_APPEND);
    if (strcmp(mode, "a+") == 0) return (O_RDWR | O_CREAT | O_APPEND);

    return (O_WRONLY | O_CREAT);
}
//sting = read(path, mode)
EVM_FUNCTION(fs_read) {
    EVM_EPCV;
    if( argc < 1 || evm_is_string(e, v[0]) )
        return EVM_UNDEFINED;
    evm_val_t res = EVM_UNDEFINED;
    char *path = evm_2_string(e, v[0]);
    char *mode = evm_2_string(e, v[1]);
    int fd = evm_port_fs_open(path, convert_fs_mode_to_oflag(mode));
    if( fd < 0 )
        return EVM_UNDEFINED;
    int size = evm_port_fs_lseek(fd, 0, SEEK_END);
    evm_port_fs_lseek(fd, 0, SEEK_SET);
    char *buf = evm_malloc(size + 1);
    int len = evm_port_fs_read(fd, buf, size);
    if( len > 0 ){
        buf[len] = 0;
        res = evm_string_create(e, buf);
    }
    evm_free(buf);
    evm_string_free(e, path);
    evm_string_free(e, mode);
    return res;
}

//write(path, buffer|string)
EVM_FUNCTION(fs_write)
{
    EVM_EPCV;
    int mode = O_WRONLY;
    if( argc < 2 )
        return EVM_UNDEFINED;

    if( argc > 2 && evm_is_string(e, v[2]) ) {
        char *mode_str = evm_2_string(e, v[2]);
        mode = convert_fs_mode_to_oflag(mode_str);
        evm_string_free(e, mode_str);
    }
    char *path = evm_2_string(e, v[0]);
    int fd = evm_port_fs_open(path, mode);
    if( fd < 0 )
        return EVM_UNDEFINED;
    evm_string_free(e, path);
    int ret = 0;
    if( evm_is_string(e, v[1]) ){
        char *buf = evm_2_string(e, v[1]);
        int size = evm_string_len(e, v[1]);
        ret = evm_port_fs_write(e, buf, size);
        evm_string_free(e, buf);
    } else if( evm_is_buffer(e, v[1]) ){
        uint8_t *buf = evm_buffer_addr(e, v[1]);
        int size = evm_buffer_len(e, v[1]);
        ret = evm_port_fs_write(e, buf, size);
    }
    evm_port_fs_close(fd);
    return evm_mk_number(e, ret);
}

EVM_FUNCTION(fs_delete) {

}

void evm_module_fs(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "read", evm_mk_native(e, fs_read, "read", EVM_VARARGS));
    evm_prop_set(e, obj, "write", evm_mk_native(e, fs_write, "write", EVM_VARARGS));
    evm_prop_set(e, obj, "delete", evm_mk_native(e, fs_delete, "delete", EVM_VARARGS));
    evm_module_add(e, "@native.fs", obj);
    evm_val_free(e, obj);
}
