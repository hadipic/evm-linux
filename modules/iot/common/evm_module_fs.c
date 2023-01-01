#include "evm_module.h"
#ifdef CONFIG_EVM_MODULE_FS
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//stats.isDirectory()
EVM_FUNCTION(evm_module_fs_stats_isDirectory)
{
    EVM_EPCV;
    struct stat *st = (struct stat *)evm_object_get_user_data(e, p);
    if( !st )
        EVM_RETURN(EVM_UNDEFINED);

    if( S_ISDIR(st->st_mode) )
        EVM_RETURN(evm_mk_boolean(e, 1));
    EVM_RETURN(evm_mk_boolean(e, 0));
}

//stats.isFile()
EVM_FUNCTION(evm_module_fs_stats_isFile)
{
    EVM_EPCV;
    struct stat *st = (struct stat *)evm_object_get_user_data(e, p);
    if( !st )
        EVM_RETURN(EVM_UNDEFINED);

    if( S_ISREG(st->st_mode) )
        EVM_RETURN(evm_mk_boolean(e, 1));
    EVM_RETURN(evm_mk_boolean(e, 0));
}

//fs.close(fd)
EVM_FUNCTION(evm_module_fs_close)
{
    EVM_EPCV;
    if( argc == 0 )
        EVM_RETURN(EVM_UNDEFINED);

    if( !evm_is_integer(e, v[0]) || evm_2_integer(e, v[0]) == -1 )
        EVM_RETURN(EVM_UNDEFINED);
    close(evm_2_integer(e, v[0]));
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.closeSync(fd)
EVM_FUNCTION(evm_module_fs_closeSync)
{
    EVM_EPCV;
    if( argc == 0 )
        EVM_RETURN(EVM_UNDEFINED);

    if( !evm_is_integer(e, v[0]) || evm_2_integer(e, v[0]) == -1 )
        EVM_RETURN(EVM_UNDEFINED);
    close(evm_2_integer(e, v[0]));

    EVM_RETURN(EVM_UNDEFINED);
}

//fs.createReadStream
EVM_FUNCTION(evm_module_fs_createReadStream)
{
    EVM_EPCV;
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.createWriteStream
EVM_FUNCTION(evm_module_fs_createWriteStream)
{
    EVM_EPCV;
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.existsSync
EVM_FUNCTION(evm_module_fs_existsSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_string(e, v[0]) )
        EVM_RETURN(evm_mk_boolean(e, 0));
    if( access(evm_2_string(e, v[0]), F_OK) == 0 ) {
        EVM_RETURN(evm_mk_boolean(e, 1));;
    }
    EVM_RETURN(evm_mk_boolean(e, 0));
}

//fs.exists
EVM_FUNCTION(evm_module_fs_exists)
{
    EVM_EPCV;
    evm_val_t exists = evm_module_fs_existsSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &exists);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.fstatSync(fd)
EVM_FUNCTION(evm_module_fs_fstatSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_integer(e, v[0]) )
        EVM_RETURN(EVM_UNDEFINED);
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    fstat(evm_2_integer(e, v[0]), st);
    evm_val_t obj = evm_object_create_user_data(e, st);
    evm_prop_set(e, obj, "isDirectory", evm_mk_native(e, evm_module_fs_stats_isDirectory, "isDirectory", 0));
    evm_prop_set(e, obj, "isFile", evm_mk_native(e, evm_module_fs_stats_isFile, "isFile", 0));
    EVM_RETURN(obj);
}

//fs.fstat(fd, callback)
EVM_FUNCTION(evm_module_fs_fstat)
{
    EVM_EPCV;
    evm_val_t obj = evm_module_fs_fstatSync(e, p, argc, v);
    if( evm_is_undefined(e, obj) )
        EVM_RETURN(EVM_UNDEFINED);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_null(e);
        args[1] = obj;
        evm_call_free(e, v[0], EVM_UNDEFINED, 2, args);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.mkdir(path[, mode], callback)
EVM_FUNCTION(evm_module_fs_mkdirSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_string(e, v[0]) )
        EVM_RETURN(EVM_UNDEFINED);
#if defined (__linux)
    __mode_t mode = 777;
    if( argc > 1 && evm_is_integer(e, v[1]) )
        mode = (__mode_t)evm_2_integer(e, v[1]);
    mkdir(evm_2_string(e, v[0]), mode);
#elif defined (WIN32) || defined (WIN64)
    mkdir(evm_2_string(e, v[0]));
#endif
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.mkdir
EVM_FUNCTION(evm_module_fs_mkdir)
{
    EVM_EPCV;
    evm_module_fs_mkdirSync(e, p, argc, v);
    evm_val_t args = evm_mk_number(e, errno);
    if( argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_call_free(e, v[2], EVM_UNDEFINED, 1, &args);
    } else if( argc > 1 && evm_is_callable(e, v[1]) ){
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.openSync(path, flags[, mode])
EVM_FUNCTION(evm_module_fs_openSync)
{
    EVM_EPCV;
    if( argc < 2 || !evm_is_string(e, v[0]) || !evm_is_string(e, v[1]) )
        EVM_RETURN(EVM_UNDEFINED);
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
EVM_FUNCTION(evm_module_fs_open)
{
    EVM_EPCV;
    evm_val_t ret = evm_module_fs_openSync(e, p, argc, v);
    if(argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        evm_call_free(e, v[2], EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[0]);
        evm_val_free(e, args[1]);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.readSync(fd, buffer, offset, length, position)
EVM_FUNCTION(evm_module_fs_readSync)
{
    EVM_EPCV;
    int fd;
    void *buffer;
    size_t offset;
    size_t length;
    size_t position;

    if( argc < 5 )
        EVM_RETURN(EVM_UNDEFINED);

    if( !evm_is_integer(e, v[0]) || !evm_is_buffer(e, v[1]) || !evm_is_integer(e, v[2]) || !evm_is_integer(e, v[3]) || !evm_is_integer(e, v[4]) )
        EVM_RETURN(EVM_UNDEFINED);

    fd = evm_2_integer(e, v[0]);
    if( fd == -1 )
        EVM_RETURN(evm_mk_number(e, 0));

    buffer = evm_buffer_addr(e, v[1]);
    offset = (size_t)evm_2_integer(e, v[2]);
    length = (size_t)evm_2_integer(e, v[3]);
    position = (size_t)evm_2_integer(e, v[4]);

    EVM_RETURN(evm_mk_number(e, read(fd, buffer + offset, length) ));
}

//fs.read(fd, buffer, offset, length, position, callback)
EVM_FUNCTION(evm_module_fs_read)
{
    EVM_EPCV;
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
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.readdir
EVM_FUNCTION(evm_module_fs_readdir)
{
    EVM_EPCV;
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.readdirSync
EVM_FUNCTION(evm_module_fs_readdirSync)
{
    EVM_EPCV;
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.readFileSync(path)
EVM_FUNCTION(evm_module_fs_readFileSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_string(e, v[0]) )
        EVM_RETURN(EVM_UNDEFINED);

    const char * fpath = evm_2_string(e, v[0]);

    struct stat st;
    if(stat(fpath, &st) < 0){
       EVM_RETURN(EVM_UNDEFINED);
    }

#if defined (WIN32) || defined (WIN64)
    int fd = open(fpath, O_RDONLY | O_BINARY);
#else
    int fd = open(fpath, O_RDONLY);
#endif
    if( fd == -1 )
        EVM_RETURN(EVM_UNDEFINED);
    uint8_t *buf = malloc(st.st_size);
    EVM_ASSERT(buf);
    read(fd, buf, st.st_size);
    close(fd);
    evm_val_t buf_obj = evm_buffer_create(e, buf, st.st_size);
    free(buf);
    EVM_RETURN(buf_obj);
}

//fs.readFile(path, callback)
EVM_FUNCTION(evm_module_fs_readFile)
{
    EVM_EPCV;
    evm_val_t ret = evm_module_fs_readFileSync(e, p, argc, v);
    if( evm_is_undefined(e, ret) )
        EVM_RETURN(ret);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        evm_call_free(e, v[1], EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[0]);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.renameSync(oldPath, newPath)
EVM_FUNCTION(evm_module_fs_renameSync)
{
    EVM_EPCV;
    if( argc < 2 || !evm_is_string(e, v[0]) || !evm_is_string(e, v[1]) )
        EVM_RETURN(EVM_UNDEFINED);
    rename(evm_2_string(e, v[0]), evm_2_string(e, v[1]));
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.rename
EVM_FUNCTION(evm_module_fs_rename)
{
    EVM_EPCV;
    evm_module_fs_renameSync(e, p, argc, v);
    if( argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[2], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.rmdirSync(path)
EVM_FUNCTION(evm_module_fs_rmdirSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_string(e, v[0]) )
        EVM_RETURN(EVM_UNDEFINED);
    rmdir(evm_2_string(e, v[0]));
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.rmdir(path, callback)
EVM_FUNCTION(evm_module_fs_rmdir)
{
    EVM_EPCV;
    evm_module_fs_rmdirSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.statSync(path)
EVM_FUNCTION(evm_module_fs_statSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_string(e, v[0]) ) {
        EVM_RETURN(EVM_UNDEFINED);
    }
    struct stat *st = (struct stat *)malloc(sizeof(struct stat));
    if( !st )
        EVM_RETURN(EVM_UNDEFINED);
    stat(evm_2_string(e, v[0]), st);
    evm_val_t obj = evm_object_create_user_data(e, st);
    evm_prop_set(e, obj, "isDirectory", evm_mk_native(e, evm_module_fs_stats_isDirectory, "isDirectory", 0));
    evm_prop_set(e, obj, "isFile", evm_mk_native(e, evm_module_fs_stats_isFile, "isFile", 0));
    EVM_RETURN(obj);
}

//fs.stat(path, callback)
EVM_FUNCTION(evm_module_fs_stat)
{
    EVM_EPCV;
    evm_val_t obj = evm_module_fs_statSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args[2];
        args[0] = evm_mk_null(e);
        args[1] = obj;
        evm_call_free(e, v[1], EVM_UNDEFINED, 2, args);
        evm_val_free(e, args[0]);
        evm_val_free(e, args[1]);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.unlinkSync(path)
EVM_FUNCTION(evm_module_fs_unlinkSync)
{
    EVM_EPCV;
    if( argc == 0 || !evm_is_string(e, v[0]) ) {
        EVM_RETURN(EVM_UNDEFINED);
    }
    unlink(evm_2_string(e, v[0]));
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.unlink(path, callback)
EVM_FUNCTION(evm_module_fs_unlink)
{
    EVM_EPCV;
    evm_module_fs_unlinkSync(e, p, argc, v);
    if( argc > 1 && evm_is_callable(e, v[1]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.writeSync(fd, buffer, offset, length[, position])
EVM_FUNCTION(evm_module_fs_writeSync)
{
    EVM_EPCV;
    int fd;
    void *buffer;
    size_t offset;
    size_t length;

    if( argc < 5 )
        EVM_RETURN(EVM_UNDEFINED);

    if( !evm_is_integer(e, v[0]) || !evm_is_buffer(e, v[1]) || !evm_is_integer(e, v[2]) || !evm_is_integer(e, v[3]) || !evm_is_integer(e, v[4]) )
        EVM_RETURN(EVM_UNDEFINED);

    fd = evm_2_integer(e, v[0]);
    if( fd == -1 )
        EVM_RETURN(evm_mk_number(e, 0));

    buffer = evm_buffer_addr(e, v[1]);
    offset = (size_t)evm_2_integer(e, v[2]);
    length = (size_t)evm_2_integer(e, v[3]);

    EVM_RETURN(evm_mk_number(e, write(fd, buffer + offset, length) ));
}

//fs.write(fd, buffer, offset, length[, position], callback)
EVM_FUNCTION(evm_module_fs_write)
{
    EVM_EPCV
    evm_val_t ret = evm_module_fs_writeSync(e, p, argc, v);
    if(argc > 4 && evm_is_callable(e, v[4]) ) {
        evm_val_t args[3];
        args[0] = evm_mk_number(e, errno);
        args[1] = ret;
        args[2] = v[1];
        evm_call_free(e, v[2], EVM_UNDEFINED, 3, args);
    }
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.writeFileSync(path, data)
EVM_FUNCTION(evm_module_fs_writeFileSync)
{
    EVM_EPCV
    if( argc < 2 || !evm_is_string(e, v[0]) || !(evm_is_buffer(e, v[1]) || evm_is_string(e, v[1]) ) )
        EVM_RETURN(EVM_UNDEFINED);
#if defined (WIN32) || defined (WIN64)
    int fd = open(evm_2_string(e, v[0]), O_CREAT |O_RDWR | O_BINARY);
#else
    int fd = open(evm_2_string(e, v[0]), O_CREAT |O_RDWR);
#endif
    if( fd == -1 )
        EVM_RETURN(EVM_UNDEFINED);
    if( evm_is_buffer(e, v[1]) ){
        size_t len = (size_t)evm_buffer_len(e, v[1]);
        uint8_t *addr = evm_buffer_addr(e, v[2]);
        write(fd, addr, len);
    }else {
        write(fd, evm_2_string(e, v[1]), (size_t)evm_string_len(e, v[1]));
    }
    close(fd);
    EVM_RETURN(EVM_UNDEFINED);
}

//fs.writeFile(path, data, callback)
EVM_FUNCTION(evm_module_fs_writeFile)
{
    EVM_EPCV
    evm_module_fs_writeFileSync(e, p, argc, v);
    if( argc > 2 && evm_is_callable(e, v[2]) ) {
        evm_val_t args;
        args = evm_mk_number(e, errno);
        evm_call_free(e, v[1], EVM_UNDEFINED, 1, &args);
        evm_val_free(e, args);
    }
    EVM_RETURN(EVM_UNDEFINED);
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
