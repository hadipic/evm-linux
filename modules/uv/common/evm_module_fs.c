/****************************************************************************
**  Copyright (C) 2023
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifdef CONFIG_EVM_MODULE_FS
#include "iot_uv.h"

evm_val_t make_stat_object(uv_stat_t* statbuf);


static evm_val_t iot_create_uv_exception(int errorno,
                                               const char* syscall) {
  evm_t *e = evm_runtime();
  static char msg[256];
  snprintf(msg, sizeof(msg), "'%s' %s", syscall, uv_strerror(errorno));
  return evm_mk_string(e, msg);
}


static void fs_after_async(uv_fs_t* req) {
  evm_t *e = evm_runtime();
  const evm_val_t cb = *IOT_UV_REQUEST_CALLBACK(req);
  EVM_ASSERT(evm_is_callable(e, cb));

  evm_val_t jargs[2] = { EVM_UNDEFINED };
  int jargc = 0;
  if (req->result < 0) {
    evm_val_t jerror = iot_create_uv_exception(req->result, "open");
    jargs[jargc++] = jerror;
  } else {
    jargs[jargc++] = evm_mk_null(e);
    switch (req->fs_type) {
      case UV_FS_CLOSE: {
        break;
      }
      case UV_FS_OPEN:
      case UV_FS_READ:
      case UV_FS_WRITE: {
        jargs[jargc++] = evm_mk_number(e, (double)req->result);
        break;
      }
      case UV_FS_SCANDIR: {
        int r;
        uv_dirent_t ent;
        int idx = 0;
        jargs[jargc++] = evm_list_create(e);
        while ((r = uv_fs_scandir_next(req, &ent)) != UV_EOF) {
          evm_val_t name =
              evm_mk_string(e, (const char*)ent.name);
          evm_list_set(e, jargs[1], idx, name);
          evm_val_free(e, name);
          idx++;
        }
        break;
      }
      case UV_FS_FSTAT:
      case UV_FS_STAT: {
        uv_stat_t s = (req->statbuf);
        jargs[jargc++] = make_stat_object(&s);
        break;
      }
      default: { break; }
    }
  }

  evm_call_free(e, cb, EVM_UNDEFINED, jargc, jargs);

  evm_val_free(e, jargs[0]);
  evm_val_free(e, jargs[1]);
  uv_fs_req_cleanup(req);
  iot_uv_request_destroy((uv_req_t*)req);
}


static evm_val_t fs_after_sync(uv_fs_t* req, int err,
                                   const char* syscall_name) {
  evm_t *e = evm_runtime();
  if (err < 0) {
    evm_val_t jvalue = iot_create_uv_exception(err, syscall_name);
    return jvalue;
  }

  switch (req->fs_type) {
    case UV_FS_CLOSE:
      break;
    case UV_FS_OPEN:
    case UV_FS_READ:
    case UV_FS_WRITE:
      return evm_mk_number(e, err);
    case UV_FS_FSTAT:
    case UV_FS_STAT: {
      uv_stat_t* s = &(req->statbuf);
      return make_stat_object(s);
    }
    case UV_FS_MKDIR:
    case UV_FS_RMDIR:
    case UV_FS_UNLINK:
    case UV_FS_RENAME:
      return evm_mk_undefined(e);
    case UV_FS_SCANDIR: {
      int r;
      uv_dirent_t ent;
      int idx = 0;
      evm_val_t ret = evm_list_create(e);
      while ((r = uv_fs_scandir_next(req, &ent)) != UV_EOF) {
        evm_val_t name = evm_mk_string(e, (const char*)ent.name);
        evm_list_set(e, ret, idx, name);
        evm_val_free(e, name);
        idx++;
      }
      return ret;
    }
    default: {
      EVM_ASSERT(false);
      break;
    }
  }
  return evm_mk_undefined(e);
}


static inline bool is_within_bounds(size_t off, size_t len, size_t max) {
  if (off >= max || max - off < len)
    return false;

  return true;
}


#define FS_ASYNC(e, syscall, pcallback, ...)                                \
  uv_fs_t* fs_req =                                                           \
      (uv_fs_t*)iot_uv_request_create(sizeof(uv_fs_t), pcallback, 0);       \
  int err = uv_fs_##syscall(system_get_uv_loop(), fs_req, __VA_ARGS__, \
                            fs_after_async);                                  \
  if (err < 0) {                                                              \
    fs_req->result = err;                                                     \
    fs_after_async(fs_req);                                                   \
  }                                                                           \
  ret_value = evm_mk_null(e);


#define FS_SYNC(syscall, ...)                                             \
  uv_fs_t fs_req;                                                              \
  int err = uv_fs_##syscall(system_get_uv_loop(), &fs_req, __VA_ARGS__, \
                            NULL);                                             \
  ret_value = fs_after_sync(&fs_req, err, #syscall);                           \
  uv_fs_req_cleanup(&fs_req);


EVM_FUNCTION(fs_close) {
  EVM_EPCV;

  int fd = evm_2_double(e, v[0]);
  const evm_val_t jcallback = v[1];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, close, jcallback, fd);
  } else {
    FS_SYNC(close, fd);
  }
  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_open) {
  EVM_EPCV

  const char *path = evm_2_string(e, v[0]);
  int flags = evm_2_integer(e, v[1]);
  int mode = evm_2_integer(e, v[2]);
  const evm_val_t jcallback = v[3];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, open, jcallback, path, flags, mode);
  } else {
    FS_SYNC(open, path, flags, mode);
  }

  EVM_RETURN(ret_value);
}


typedef enum { IOT_FS_READ, IOT_FS_WRITE } iot_fs_op_t;

evm_val_t fs_do_read_or_write(const evm_val_t jthis,
                                  const evm_val_t v[],
                                  const int jargc,
                                  const iot_fs_op_t fs_op) {
  evm_t *e = evm_runtime();
  int fd = evm_2_integer(e, v[0]);
  const evm_val_t jbuffer = v[1];
  size_t offset = evm_2_integer(e, v[2]);
  size_t length = evm_2_integer(e, v[3]);
  int position = evm_2_integer(e, v[4]);
  const evm_val_t jcallback = v[5];

  char* data = (char*)evm_buffer_addr(e, jbuffer);
  size_t data_length = evm_buffer_len(e, jbuffer);

  if (!is_within_bounds(offset, length, data_length)) {
    evm_throw(e, evm_mk_string(e, "length out of bound"));
  }

  uv_buf_t uvbuf = uv_buf_init(data + offset, length);

  evm_val_t ret_value;
  if (fs_op == IOT_FS_READ) {
    if (!evm_is_null(e,jcallback)) {
      FS_ASYNC(e, read, jcallback, fd, &uvbuf, 1, position);
    } else {
      FS_SYNC(read, fd, &uvbuf, 1, position);
    }
  } else {
    if (!evm_is_null(e, jcallback)) {
      FS_ASYNC(e, write, jcallback, fd, &uvbuf, 1, position);
    } else {
      FS_SYNC(write, fd, &uvbuf, 1, position);
    }
  }
  EVM_RETURN_VAL(ret_value);
}


EVM_FUNCTION(fs_read) {
  EVM_EPCV
  EVM_RETURN(fs_do_read_or_write(p, v, argc, IOT_FS_READ));
}


EVM_FUNCTION(fs_write) {
  EVM_EPCV
  EVM_RETURN(fs_do_read_or_write(p, v, argc, IOT_FS_WRITE));
}


evm_val_t make_stat_object(uv_stat_t* statbuf) {
  evm_t *e = evm_runtime();
  const evm_val_t fs = evm_module_get(e, "fs");

  evm_val_t stat_prototype =
      evm_prop_get(e, fs, IOT_MAGIC_STRING_STATS);
  EVM_ASSERT(evm_is_object(e, stat_prototype));

  evm_val_t jstat = evm_object_create(e);
  evm_prop_set(e, jstat, "prototype", stat_prototype);

  evm_val_free(e, stat_prototype);


#define X(statobj, name) \
  evm_prop_set(e, statobj, #name, evm_mk_number(e, statbuf->st_##name));

  X(jstat, dev)
  X(jstat, mode)
  X(jstat, nlink)
  X(jstat, uid)
  X(jstat, gid)
  X(jstat, rdev)
  X(jstat, blksize)
  X(jstat, ino)
  X(jstat, size)
  X(jstat, blocks)

#undef X

  return jstat;
}


EVM_FUNCTION(fs_stat) {
  EVM_EPCV

  const char *path = evm_2_string(e, v[0]);
  const evm_val_t jcallback = v[1];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, stat, jcallback, path);
  } else {
    FS_SYNC(stat, path);
  }

  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_fstat) {
  EVM_EPCV

  int fd = evm_2_integer(e, v[0]);
  const evm_val_t jcallback = v[1];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, fstat, jcallback, fd);
  } else {
    FS_SYNC(fstat, fd);
  }
  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_mkdir) {
  EVM_EPCV

  const char *path = evm_2_string(e, v[0]);
  int mode = evm_2_integer(e, v[1]);
  const evm_val_t jcallback = v[2];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, mkdir, jcallback, path, mode);
  } else {
    FS_SYNC(mkdir, path, mode);
  }

  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_rmdir) {
  EVM_EPCV

  const char *path = evm_2_string(e, v[0]);
  const evm_val_t jcallback = v[1];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, rmdir, jcallback, path);
  } else {
    FS_SYNC(rmdir, path);
  }

  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_unlink) {
  EVM_EPCV

  const char *path = evm_2_string(e, v[0]);
  const evm_val_t jcallback = v[1];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, unlink, jcallback, path);
  } else {
    FS_SYNC(unlink, path);
  }

  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_rename) {
  EVM_EPCV

  const char *old_path = evm_2_string(e, v[0]);
  const char *new_path = evm_2_string(e, v[1]);
  const evm_val_t jcallback = v[2];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, rename, jcallback, old_path, new_path);
  } else {
    FS_SYNC(rename, old_path, new_path);
  }

  EVM_RETURN(ret_value);
}


EVM_FUNCTION(fs_read_dir) {
  EVM_EPCV
  const char *path = evm_2_string(e, v[0]);
  const evm_val_t jcallback = v[1];

  evm_val_t ret_value;
  if (!evm_is_null(e, jcallback)) {
    FS_ASYNC(e, scandir, jcallback, path, 0);
  } else {
    FS_SYNC(scandir, path, 0);
  }

  EVM_RETURN(ret_value);
}

static evm_val_t stats_is_typeof(evm_val_t stats, int type) {
  evm_t *e = evm_runtime();
  evm_val_t mode = evm_prop_get(e, stats, IOT_MAGIC_STRING_MODE);

  if (!evm_is_number(e, mode)) {
    evm_val_free(e, mode);
    evm_throw(e, evm_mk_string(e, "fstat: file mode should be a number"));
  }

  int mode_number = (int)evm_2_integer(e, mode);

  evm_val_free(e, mode);

  return evm_mk_boolean(e, (mode_number & S_IFMT) == type);
}

EVM_FUNCTION(fs_stats_is_directory) {
  EVM_EPCV
  evm_val_t stats = p;
  EVM_RETURN(stats_is_typeof(stats, S_IFDIR));
}

EVM_FUNCTION(fs_stats_is_file) {
  EVM_EPCV
  evm_val_t stats = p;
  EVM_RETURN(stats_is_typeof(stats, S_IFREG));
}

EVM_FUNCTION(fs_size) {
  EVM_EPCV
  int fd = open(evm_2_string(e, v[0]), O_RDONLY);
  if( fd < 0 ){
      EVM_RETURN(evm_mk_boolean(e, 0))
  }
  struct stat buf;
  fstat(fd, &buf);
  close(fd);
  EVM_RETURN(evm_mk_number(e, buf.st_size));
}

EVM_FUNCTION(fs_exists) {
  EVM_EPCV
  int fd = open(evm_2_string(e, v[0]), O_RDONLY);
  if( fd < 0 ){
      EVM_RETURN(evm_mk_boolean(e, 0))
  }
  close(fd);
  EVM_RETURN(evm_mk_boolean(e, 1))
}

EVM_FUNCTION(fs_readFile) {
  EVM_EPCV;
  const char *path = evm_2_string(e, v[0]);
  const char *mode = evm_2_string(e, v[1]);
  int fd = open(path, O_RDONLY);
  if( fd < 0 ){
      EVM_RETURN(EVM_UNDEFINED)
  }
  struct stat buf;
  fstat(fd, &buf);
  char *temp_buf = zmalloc(buf.st_size);
  EVM_ASSERT(temp_buf);
  evm_val_t ret = EVM_UNDEFINED;
  if( strstr(mode, "b") ){
    read(fd, temp_buf, buf.st_size);
    ret = evm_buffer_create(e, temp_buf, buf.st_size);
  } else {
    read(fd, temp_buf, buf.st_size);
    ret = evm_mk_lstring(e, temp_buf, buf.st_size);
  }
  zfree(temp_buf);
  close(fd);
  EVM_RETURN(ret)
}

EVM_FUNCTION(fs_writeFile) {
  EVM_EPCV;
  if( !evm_is_string(e, v[0]) || (!evm_is_buffer(e, v[1]) && !evm_is_string(e, v[1])))
    EVM_RETURN(EVM_UNDEFINED);
  const char *path = evm_2_string(e, v[0]);
  int fd = open(path, O_WRONLY);
  if( fd < 0 ){
      EVM_RETURN(EVM_UNDEFINED)
  }
  if( evm_is_string(e, v[1]) ){
      write(fd, evm_2_string(e, v[1]), evm_string_len(e, v[1]));
  } else if( evm_is_buffer(e, v[1]) ){
      write(fd, evm_buffer_addr(e, v[1]), evm_buffer_len(e, v[1]));
  }
  close(fd);
  EVM_RETURN(EVM_UNDEFINED);
}

void evm_module_fs(evm_t *e) {
  evm_val_t fs = evm_object_create(e);

  evm_prop_set(e, fs, IOT_MAGIC_STRING_CLOSE, evm_mk_native(e, fs_close, IOT_MAGIC_STRING_CLOSE, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_OPEN, evm_mk_native(e, fs_open, IOT_MAGIC_STRING_OPEN, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_READ, evm_mk_native(e, fs_read, IOT_MAGIC_STRING_READ, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_WRITE, evm_mk_native(e, fs_write, IOT_MAGIC_STRING_WRITE, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_STAT, evm_mk_native(e, fs_stat, IOT_MAGIC_STRING_STAT, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_FSTAT, evm_mk_native(e, fs_fstat, IOT_MAGIC_STRING_FSTAT, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_MKDIR, evm_mk_native(e, fs_mkdir, IOT_MAGIC_STRING_MKDIR, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_RMDIR, evm_mk_native(e, fs_rmdir, IOT_MAGIC_STRING_RMDIR, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_UNLINK, evm_mk_native(e, fs_unlink, IOT_MAGIC_STRING_UNLINK, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_RENAME, evm_mk_native(e, fs_rename, IOT_MAGIC_STRING_RENAME, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_READDIR, evm_mk_native(e, fs_read_dir, IOT_MAGIC_STRING_READDIR, EVM_VARARGS));
  evm_prop_set(e, fs, IOT_MAGIC_STRING_EXISTS, evm_mk_native(e, fs_exists, IOT_MAGIC_STRING_EXISTS, EVM_VARARGS));
  evm_prop_set(e, fs, "readFile", evm_mk_native(e, fs_readFile, "readFile", EVM_VARARGS));
  evm_prop_set(e, fs, "writeFile", evm_mk_native(e, fs_writeFile, "writeFile", EVM_VARARGS));
  evm_prop_set(e, fs, "size", evm_mk_native(e, fs_size, "size", EVM_VARARGS));

  evm_val_t stats_prototype = evm_object_create(e);

  evm_prop_set(e, stats_prototype, IOT_MAGIC_STRING_ISDIRECTORY,
                        evm_mk_native(e, fs_stats_is_directory, IOT_MAGIC_STRING_ISDIRECTORY, EVM_VARARGS));
  evm_prop_set(e, stats_prototype, IOT_MAGIC_STRING_ISFILE,
                        evm_mk_native(e, fs_stats_is_file, IOT_MAGIC_STRING_ISFILE, EVM_VARARGS));

  evm_prop_set(e, fs, IOT_MAGIC_STRING_STATS, stats_prototype);
  evm_module_add(e, "@system.fs", fs);
}
#endif
