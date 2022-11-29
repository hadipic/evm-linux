#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_FS
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//stats.isDirectory()
static evm_val_t evm_module_fs_stats_isDirectory(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    struct stat *st = (struct stat *)evm_object_get_user_data(e, p);
    if( !st )
        return EVM_UNDEFINED;

    if( S_ISDIR(st->st_mode) )
        return evm_mk_boolean(e, 1);
    return evm_mk_boolean(e, 0);
}

//stats.isFile()
static evm_val_t evm_module_fs_stats_isFile(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    struct stat *st = (struct stat *)evm_object_get_user_data(e, p);
    if( !st )
        return EVM_UNDEFINED;

    if( S_ISREG(st->st_mode) )
        return evm_mk_boolean(e, 1);
    return evm_mk_boolean(e, 0);
}

//fs.close(fd)
static evm_val_t evm_module_fs_close(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 )
        return EVM_UNDEFINED;

    if( !evm_is_integer(e, v[0]) || evm_2_integer(e, v[0]) == -1 )
        return EVM_UNDEFINED;
    close(evm_2_integer(e, v[0]));
    return EVM_UNDEFINED;
}

//fs.closeSync(fd)
static evm_val_t evm_module_fs_closeSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 )
        return EVM_UNDEFINED;

    if( !evm_is_integer(e, v[0]) || evm_2_integer(e, v[0]) == -1 )
        return EVM_UNDEFINED;
    close(evm_2_integer(e, v[0]));

    return EVM_UNDEFINED;
}

//fs.createReadStream
static evm_val_t evm_module_fs_createReadStream(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return EVM_UNDEFINED;
}

//fs.createWriteStream
static evm_val_t evm_module_fs_createWriteStream(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return EVM_UNDEFINED;
}

//fs.existsSync
static evm_val_t evm_module_fs_existsSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_string(e, v[0]) )
        return evm_mk_boolean(e, 0);
    if( access(evm_2_string(e, v[0]), F_OK) == 0 ) {
        return evm_mk_boolean(e, 1);
    }
    return evm_mk_boolean(e, 0);
}

//fs.exists
static evm_val_t evm_module_fs_exists(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t exists = evm_module_fs_existsSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &exists);
    }
    return EVM_UNDEFINED;
}

//fs.fstatSync(fd)
static evm_val_t evm_module_fs_fstatSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_integer(e, v[0]) )
        return EVM_UNDEFINED;
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    fstat(evm_2_integer(e, v[0]), st);
    evm_val_t obj = evm_object_create_user_data(e, st);
    evm_prop_set(e, obj, "isDirectory", evm_mk_native(e, evm_module_fs_stats_isDirectory, "isDirectory", 0));
    evm_prop_set(e, obj, "isFile", evm_mk_native(e, evm_module_fs_stats_isFile, "isFile", 0));
    return obj;
}

//fs.fstat(fd, callback)
static evm_val_t evm_module_fs_fstat(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t obj = evm_module_fs_fstatSync(e, p, argc, v);
    if( evm_is_undefined(e, obj) )
        return EVM_UNDEFINED;
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_null(e);
        args[1] = obj;
        evm_call_free(e, v[0], EVM_UNDEFINED, 2, args);
    }
    return EVM_UNDEFINED;
}

//fs.mkdir(path[, mode], callback)
static evm_val_t evm_module_fs_mkdirSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_string(e, v[0]) )
        return EVM_UNDEFINED;
#if defined (__linux)
    __mode_t mode = 777;
    if( argc > 1 && evm_is_integer(e, v[1]) )
        mode = (__mode_t)evm_2_integer(e, v[1]);
    mkdir(evm_2_string(e, v[0]), mode);
#elif defined (WIN32) || defined (WIN64)
    mkdir(evm_2_string(e, v[0]));
#endif
    return EVM_UNDEFINED;
}

//fs.mkdir
static evm_val_t evm_module_fs_mkdir(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_module_fs_mkdirSync(e, p, argc, v);
    evm_val_t args = evm_mk_number(e, errno);
    if( argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_call_free(e, v[2], EVM_UNDEFINED, 1, &args);
    } else if( argc > 1 && evm_is_callable(e, v[1]) ){
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
    }
    return EVM_UNDEFINED;
}

//fs.openSync(path, flags[, mode])
static evm_val_t evm_module_fs_openSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 2 || !evm_is_string(e, v[0]) || !evm_is_string(e, v[1]) )
        return EVM_UNDEFINED;
    const char *flag = evm_2_string(e, v[1]);
    int mode = O_RDONLY;
    if (strstr(flag, "+") != NULL){
        mode = mode | O_CREAT;
    }

    if (strstr(flag, "r") != NULL){
        mode = mode | O_RDONLY;
    }

    if (strstr(flag, "w") != NULL){
        mode = mode | O_WRONLY;
    }

    if (strstr(flag, "a") != NULL){
        mode = mode | O_APPEND;
    }

#if defined (WIN32) || defined (WIN64)
    if (strstr(flag, "b") != NULL){
        mode = mode | O_BINARY;
    }
#endif
    return evm_mk_number(e, open(evm_2_string(e, v[0]), mode));
}

//fs.open(path, flags[, mode], callback)
static evm_val_t evm_module_fs_open(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t ret = evm_module_fs_openSync(e, p, argc, v);
    if(argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        evm_call_free(e, v[2], EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[0]);
        evm_val_free(e, args[1]);
    }
    return EVM_UNDEFINED;
}

//fs.readSync(fd, buffer, offset, length, position)
static evm_val_t evm_module_fs_readSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    int fd;
    void *buffer;
    size_t offset;
    size_t length;
    size_t position;

    if( argc < 5 )
        return EVM_UNDEFINED;

    if( !evm_is_integer(e, v[0]) || !evm_is_buffer(e, v[1]) || !evm_is_integer(e, v[2]) || !evm_is_integer(e, v[3]) || !evm_is_integer(e, v[4]) )
        return EVM_UNDEFINED;

    fd = evm_2_integer(e, v[0]);
    if( fd == -1 )
        return evm_mk_number(e, 0);

    buffer = evm_buffer_addr(e, v[1]);
    offset = (size_t)evm_2_integer(e, v[2]);
    length = (size_t)evm_2_integer(e, v[3]);
    position = (size_t)evm_2_integer(e, v[4]);

    return evm_mk_number(e, read(fd, buffer + offset, length) );
}

//fs.read(fd, buffer, offset, length, position, callback)
static evm_val_t evm_module_fs_read(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t ret = evm_module_fs_readSync(e, p, argc, v);
    if(argc > 4 && evm_is_callable(e, v[4]) ) {
        evm_val_t args[3];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        args[2] = v[1];
        evm_call_free(e, v[2], EVM_UNDEFINED, 3, args);
        evm_val_free(e, args[0]);
        evm_val_free(e, args[1]);
    }
    return EVM_UNDEFINED;
}

//fs.readdir
static evm_val_t evm_module_fs_readdir(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return EVM_UNDEFINED;
}

//fs.readdirSync
static evm_val_t evm_module_fs_readdirSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return EVM_UNDEFINED;
}

//fs.readFileSync(path)
static evm_val_t evm_module_fs_readFileSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_string(e, v[0]) )
        return EVM_UNDEFINED;

    const char * fpath = evm_2_string(e, v[0]);

    struct stat st;
    if(stat(fpath, &st) < 0){
       return EVM_UNDEFINED;
    }

#if defined (WIN32) || defined (WIN64)
    int fd = open(fpath, O_RDONLY | O_BINARY);
#else
    int fd = open(fpath, O_RDONLY);
#endif
    if( fd == -1 )
        return EVM_UNDEFINED;
    uint8_t *buf = malloc(st.st_size);
    EVM_ASSERT(buf);
    read(fd, buf, st.st_size);
    close(fd);
    evm_val_t buf_obj = evm_buffer_create(e, buf, st.st_size);
    free(buf);
    return buf_obj;
}

//fs.readFile(path, callback)
static evm_val_t evm_module_fs_readFile(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t ret = evm_module_fs_readFileSync(e, p, argc, v);
    if( evm_is_undefined(e, ret) )
        return ret;
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        evm_call_free(e, v[1], EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[0]);
    }
    return EVM_UNDEFINED;
}

//fs.renameSync(oldPath, newPath)
static evm_val_t evm_module_fs_renameSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 2 || !evm_is_string(e, v[0]) || !evm_is_string(e, v[1]) )
        return EVM_UNDEFINED;
    rename(evm_2_string(e, v[0]), evm_2_string(e, v[1]));
    return EVM_UNDEFINED;
}

//fs.rename
static evm_val_t evm_module_fs_rename(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_module_fs_renameSync(e, p, argc, v);
    if( argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[2], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    return EVM_UNDEFINED;
}

//fs.rmdirSync(path)
static evm_val_t evm_module_fs_rmdirSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_string(e, v[0]) )
        return EVM_UNDEFINED;
    rmdir(evm_2_string(e, v[0]));
    return EVM_UNDEFINED;
}

//fs.rmdir(path, callback)
static evm_val_t evm_module_fs_rmdir(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_module_fs_rmdirSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    return EVM_UNDEFINED;
}

//fs.statSync(path)
static evm_val_t evm_module_fs_statSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_string(e, v[0]) ) {
        return EVM_UNDEFINED;
    }
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    if( !st )
        return EVM_UNDEFINED;
    stat(evm_2_string(e, v[0]), st);
    evm_val_t obj = evm_object_create_user_data(e, st);
    evm_prop_set(e, obj, "isDirectory", evm_mk_native(e, evm_module_fs_stats_isDirectory, "isDirectory", 0));
    evm_prop_set(e, obj, "isFile", evm_mk_native(e, evm_module_fs_stats_isFile, "isFile", 0));
    return obj;
}

//fs.stat(path, callback)
static evm_val_t evm_module_fs_stat(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t obj = evm_module_fs_statSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_null(e);
        args[1] = obj;
        evm_call_free(e, v[1], EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[0]);
        evm_val_free(e, args[1]);
    }
    return EVM_UNDEFINED;
}

//fs.unlinkSync(path)
static evm_val_t evm_module_fs_unlinkSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc == 0 || !evm_is_string(e, v[0]) ) {
        return EVM_UNDEFINED;
    }
    unlink(evm_2_string(e, v[0]));
    return EVM_UNDEFINED;
}

//fs.unlink(path, callback)
static evm_val_t evm_module_fs_unlink(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_module_fs_unlinkSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    return EVM_UNDEFINED;
}

//fs.writeSync(fd, buffer, offset, length[, position])
static evm_val_t evm_module_fs_writeSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    int fd;
    void *buffer;
    size_t offset;
    size_t length;

    if( argc < 5 )
        return EVM_UNDEFINED;

    if( !evm_is_integer(e, v[0]) || !evm_is_buffer(e, v[1]) || !evm_is_integer(e, v[2]) || !evm_is_integer(e, v[3]) || !evm_is_integer(e, v[4]) )
        return EVM_UNDEFINED;

    fd = evm_2_integer(e, v[0]);
    if( fd == -1 )
        return evm_mk_number(e, 0);

    buffer = evm_buffer_addr(e, v[1]);
    offset = (size_t)evm_2_integer(e, v[2]);
    length = (size_t)evm_2_integer(e, v[3]);

    return evm_mk_number(e, write(fd, buffer + offset, length) );
}

//fs.write(fd, buffer, offset, length[, position], callback)
static evm_val_t evm_module_fs_write(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_val_t ret = evm_module_fs_writeSync(e, p, argc, v);
    if(argc > 4 && evm_is_callable(e, v[4]) ) {
        evm_val_t args[3];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        args[2] = v[1];
        evm_call_free(e, v[2], EVM_UNDEFINED, 3, args);
    }
    return EVM_UNDEFINED;
}

//fs.writeFileSync(path, data)
static evm_val_t evm_module_fs_writeFileSync(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if( argc < 2 || !evm_is_string(e, v[0]) || !(evm_is_buffer(e, v[1]) || evm_is_string(e, v[1]) ) )
        return EVM_UNDEFINED;
#if defined (WIN32) || defined (WIN64)
    int fd = open(evm_2_string(e, v[0]), O_CREAT |O_RDWR | O_BINARY);
#else
    int fd = open(evm_2_string(e, v[0]), O_CREAT |O_RDWR);
#endif
    if( fd == -1 )
        return EVM_UNDEFINED;
    if( evm_is_buffer(e, v[1]) ){
        size_t len = (size_t)evm_buffer_len(e, v[1]);
        uint8_t *addr = evm_buffer_addr(e, v[2]);
        write(fd, addr, len);
    }else {
        write(fd, evm_2_string(e, v[1]), (size_t)evm_string_len(e, v[1]));
    }
    close(fd);
    return EVM_UNDEFINED;
}

//fs.writeFile(path, data, callback)
static evm_val_t evm_module_fs_writeFile(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    evm_module_fs_writeFileSync(e, p, argc, v);
    if( argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    return EVM_UNDEFINED;
}

void evm_module_fs(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "close", evm_mk_native(e, evm_module_fs_close, "close", 1));
    evm_prop_set(e, obj, "closeSync", evm_mk_native(e, evm_module_fs_closeSync, "closeSync", 1));
    evm_prop_set(e, obj, "createReadStream", evm_mk_native(e, evm_module_fs_createReadStream, "createReadStream", 1));
    evm_prop_set(e, obj, "createWriteStream", evm_mk_native(e, evm_module_fs_createWriteStream, "createWriteStream", 1));
    evm_prop_set(e, obj, "exists", evm_mk_native(e, evm_module_fs_exists, "exists", 1));
    evm_prop_set(e, obj, "existsSync", evm_mk_native(e, evm_module_fs_existsSync, "existsSync", 1));
    evm_prop_set(e, obj, "fstat", evm_mk_native(e, evm_module_fs_fstat, "fstat", 1));
    evm_prop_set(e, obj, "fstatSync", evm_mk_native(e, evm_module_fs_fstatSync, "fstatSync", 1));
    evm_prop_set(e, obj, "mkdir", evm_mk_native(e, evm_module_fs_mkdir, "mkdir", 1));
    evm_prop_set(e, obj, "mkdirSync", evm_mk_native(e, evm_module_fs_mkdirSync, "mkdirSync", 1));
    evm_prop_set(e, obj, "open", evm_mk_native(e, evm_module_fs_open, "open", 1));
    evm_prop_set(e, obj, "openSync", evm_mk_native(e, evm_module_fs_openSync, "openSync", 1));
    evm_prop_set(e, obj, "read", evm_mk_native(e, evm_module_fs_read, "read", 1));
    evm_prop_set(e, obj, "readSync", evm_mk_native(e, evm_module_fs_readSync, "readSync", 1));
    evm_prop_set(e, obj, "readdir", evm_mk_native(e, evm_module_fs_readdir, "readdir", 1));
    evm_prop_set(e, obj, "readdirSync", evm_mk_native(e, evm_module_fs_readdirSync, "readdirSync", 1));
    evm_prop_set(e, obj, "readFile", evm_mk_native(e, evm_module_fs_readFile, "readFile", 1));
    evm_prop_set(e, obj, "readFileSync", evm_mk_native(e, evm_module_fs_readFileSync, "readFileSync", 1));
    evm_prop_set(e, obj, "rename", evm_mk_native(e, evm_module_fs_rename, "rename", 1));
    evm_prop_set(e, obj, "renameSync", evm_mk_native(e, evm_module_fs_renameSync, "renameSync", 1));
    evm_prop_set(e, obj, "rmdir", evm_mk_native(e, evm_module_fs_rmdir, "rmdir", 1));
    evm_prop_set(e, obj, "rmdirSync", evm_mk_native(e, evm_module_fs_rmdirSync, "rmdirSync", 1));
    evm_prop_set(e, obj, "stat", evm_mk_native(e, evm_module_fs_stat, "stat", 1));
    evm_prop_set(e, obj, "statSync", evm_mk_native(e, evm_module_fs_statSync, "statSync", 1));
    evm_prop_set(e, obj, "unlink", evm_mk_native(e, evm_module_fs_unlink, "unlink", 1));
    evm_prop_set(e, obj, "unlinkSync", evm_mk_native(e, evm_module_fs_unlinkSync, "unlinkSync", 1));
    evm_prop_set(e, obj, "write", evm_mk_native(e, evm_module_fs_write, "write", 1));
    evm_prop_set(e, obj, "writeSync", evm_mk_native(e, evm_module_fs_writeSync, "writeSync", 1));
    evm_prop_set(e, obj, "writeFile", evm_mk_native(e, evm_module_fs_writeFile, "writeFile", 1));
    evm_prop_set(e, obj, "writeFileSync", evm_mk_native(e, evm_module_fs_writeFileSync, "writeFileSync", 1));
}
#endif
