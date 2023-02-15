/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

static void uv__to_stat(struct stat* src, uv_stat_t* dst) {
#if !defined(__NUTTX__) && !defined(__TIZENRT__)
  dst->st_dev = src->st_dev;
#endif
  dst->st_mode = src->st_mode;
#if !defined(__NUTTX__) && !defined(__TIZENRT__)
  dst->st_nlink = src->st_nlink;
  dst->st_uid = src->st_uid;
  dst->st_gid = src->st_gid;
  dst->st_rdev = src->st_rdev;
  dst->st_ino = src->st_ino;
#endif
  dst->st_size = src->st_size;
  dst->st_blksize = src->st_blksize;
  dst->st_blocks = src->st_blocks;

#if defined(__APPLE__)
  dst->st_atim.tv_sec = src->st_atimespec.tv_sec;
  dst->st_atim.tv_nsec = src->st_atimespec.tv_nsec;
  dst->st_mtim.tv_sec = src->st_mtimespec.tv_sec;
  dst->st_mtim.tv_nsec = src->st_mtimespec.tv_nsec;
  dst->st_ctim.tv_sec = src->st_ctimespec.tv_sec;
  dst->st_ctim.tv_nsec = src->st_ctimespec.tv_nsec;
  dst->st_birthtim.tv_sec = src->st_birthtimespec.tv_sec;
  dst->st_birthtim.tv_nsec = src->st_birthtimespec.tv_nsec;
  dst->st_flags = src->st_flags;
  dst->st_gen = src->st_gen;
#elif defined(__ANDROID__)
  dst->st_atim.tv_sec = src->st_atime;
  dst->st_atim.tv_nsec = src->st_atimensec;
  dst->st_mtim.tv_sec = src->st_mtime;
  dst->st_mtim.tv_nsec = src->st_mtimensec;
  dst->st_ctim.tv_sec = src->st_ctime;
  dst->st_ctim.tv_nsec = src->st_ctimensec;
  dst->st_birthtim.tv_sec = src->st_ctime;
  dst->st_birthtim.tv_nsec = src->st_ctimensec;
  dst->st_flags = 0;
  dst->st_gen = 0;
#elif !defined(_AIX) && !defined(__NUTTX__) && \
    (defined(_GNU_SOURCE)    || \
    defined(_BSD_SOURCE)     || \
    defined(_SVID_SOURCE)    || \
    defined(_XOPEN_SOURCE)   || \
    defined(_DEFAULT_SOURCE))
  dst->st_atim.tv_sec = src->st_atim.tv_sec;
  dst->st_atim.tv_nsec = src->st_atim.tv_nsec;
  dst->st_mtim.tv_sec = src->st_mtim.tv_sec;
  dst->st_mtim.tv_nsec = src->st_mtim.tv_nsec;
  dst->st_ctim.tv_sec = src->st_ctim.tv_sec;
  dst->st_ctim.tv_nsec = src->st_ctim.tv_nsec;
# if defined(__DragonFly__)  || \
     defined(__FreeBSD__)    || \
     defined(__OpenBSD__)    || \
     defined(__NetBSD__)
  dst->st_birthtim.tv_sec = src->st_birthtim.tv_sec;
  dst->st_birthtim.tv_nsec = src->st_birthtim.tv_nsec;
  dst->st_flags = src->st_flags;
  dst->st_gen = src->st_gen;
# else
  dst->st_birthtim.tv_sec = src->st_ctim.tv_sec;
  dst->st_birthtim.tv_nsec = src->st_ctim.tv_nsec;
  dst->st_flags = 0;
  dst->st_gen = 0;
# endif
#else
  dst->st_atim.tv_sec = src->st_atime;
  dst->st_atim.tv_nsec = 0;
  dst->st_mtim.tv_sec = src->st_mtime;
  dst->st_mtim.tv_nsec = 0;
  dst->st_ctim.tv_sec = src->st_ctime;
  dst->st_ctim.tv_nsec = 0;
  dst->st_birthtim.tv_sec = src->st_ctime;
  dst->st_birthtim.tv_nsec = 0;
  dst->st_flags = 0;
  dst->st_gen = 0;
#endif
}


static int uv__fs_stat(const char *path, uv_stat_t *buf) {
  struct stat pbuf;
  int ret;

  ret = uv_posix_stat(path, &pbuf);
  if (ret == 0)
    uv__to_stat(&pbuf, buf);

  return ret;
}


static int uv__fs_fstat(int fd, uv_stat_t *buf) {
#if defined(__NUTTX__) || defined(__TIZENRT__)
  return -1;
#else
  struct stat pbuf;
  int ret;

  ret = uv_posix_fstat(fd, &pbuf);
  if (ret == 0)
    uv__to_stat(&pbuf, buf);

  return ret;
#endif
}

static ssize_t uv__fs_open(uv_fs_t* req) {
  int r;
  r = uv_posix_open(req->path, req->flags, req->mode);
  return r;
}

static ssize_t readv(int fd, uv_buf_t* iiovec, int count) {
  ssize_t result = 0;
  ssize_t total = 0;
  int idx;

  for (idx = 0; idx < count; ++idx) {
    result = uv_posix_read(fd, iiovec[idx].base, iiovec[idx].len);
    if (result < 0) {
      return result;
    } else {
      total += result;
    }
  }
  return total;
}


static ssize_t writev(int fd, uv_buf_t* iiovec, int count) {
  ssize_t result = 0;
  ssize_t total = 0;
  int idx;

  for (idx = 0; idx < count; ++idx) {
    result = uv_posix_write(fd, iiovec[idx].base, iiovec[idx].len);
    if (result < 0) {
      return result;
    } else {
      total += result;
    }
  }
  return total;
}

static ssize_t uv__fs_read(uv_fs_t* req) {
  ssize_t result = 0;
  if (req->off < 0) {
    if (req->nbufs == 1)
      result = uv_posix_read(req->file, req->bufs[0].base, req->bufs[0].len);
    else
      result = readv(req->file, req->bufs, req->nbufs);
  } else {

  }
  return result;
}

static ssize_t uv__fs_write(uv_fs_t* req) {
  ssize_t r = 0;
  if (req->off < 0) {
    if (req->nbufs == 1)
      r = uv_posix_write(req->file, req->bufs[0].base, req->bufs[0].len);
    else
      r = writev(req->file, req->bufs, req->nbufs);
  } else {

  }
  return r;
}

static void uv__fs_work(uv_work_t* w) {
    uv_fs_t* req;
    ssize_t r;

    req = w->data;

    do {
    errno = 0;

    #define X(type, action)                                                       \
    case UV_FS_ ## type:                                                        \
    r = action;                                                               \
    break;

    switch (req->fs_type) {
    X(CLOSE, uv_posix_close(req->file));
    X(FDATASYNC, uv_posix_fdatasync(req->file));
    X(FSTAT, uv__fs_fstat(req->file, &req->statbuf));
    X(FSYNC, uv_posix_fsync(req->file));
    X(OPEN, uv__fs_open(req));
    X(READ, uv__fs_read(req));
    X(RENAME, uv_posix_rename(req->path, req->new_path));
    X(STAT, uv__fs_stat(req->path, &req->statbuf));
    X(UNLINK, unlink(req->path));
    X(WRITE, uv__fs_write(req));
    }
    #undef X
    } while (r == -1 && errno == EINTR);

    if (r == -1)
        req->result = -errno;
    else
        req->result = r;

    if (r == 0 && (req->fs_type == UV_FS_STAT ||
                 req->fs_type == UV_FS_FSTAT ||
                 req->fs_type == UV_FS_LSTAT)) {
        req->ptr = &req->statbuf;
    }
}

static void uv__fs_done(uv_work_t* w, int status) {
    if( w->done_cb )
        w->done_cb(w);
}

static void INIT(uv_loop_t* loop, uv_fs_t* req, int subtype, uv_fs_cb cb) {
    req->type = UV_FS;
    req->fs_type = subtype;
    req->result = 0;
    req->loop = loop;
    req->path = NULL;
    req->cb = cb;
    req->new_path = NULL;
}

static void PATH(uv_fs_t* req, const char* path, uv_fs_cb cb) {
    if (cb == NULL) {
      req->path = path;
    } else {
      req->path = strdup(path);
      EVM_ASSERT(req->path);
    }
}

static void PATH2(uv_fs_t* req, const char* path, const char* new_path, uv_fs_cb cb) {
    if (cb == NULL) {
      req->path = path;
      req->new_path = new_path;
    } else {
      size_t path_len;
      size_t new_path_len;
      path_len = strlen(path) + 1;
      new_path_len = strlen(new_path) + 1;
      req->path = uv__malloc(path_len + new_path_len);
      EVM_ASSERT(req->path);
      req->new_path = req->path + path_len;
      memcpy((void*) req->path, path, path_len);
      memcpy((void*) req->new_path, new_path, new_path_len);
    }
}

static int POST(uv_loop_t* loop, uv_fs_t* req, uv_fs_cb cb) {
    req->work_req.data = req;
    if (cb != NULL) {
      uv_queue_work(loop, &req->work_req, uv__fs_work, uv__fs_done);
      return 0;
    }
    else {
      uv__fs_work(&req->work_req);
      return req->result;
    }
}

int uv_fs_open(uv_loop_t* loop,
               uv_fs_t* req,
               const char* path,
               int flags,
               int mode,
               uv_fs_cb cb) {
    INIT(loop, req, UV_FS_OPEN, cb);
    PATH(req, path, cb);
    req->flags = flags;
    req->mode = mode;
    return POST(loop, req, cb);
}

int uv_fs_read(uv_loop_t* loop, uv_fs_t* req,
               uv_file file,
               const uv_buf_t bufs[],
               unsigned int nbufs,
               int64_t off,
               uv_fs_cb cb) {
    INIT(loop, req, UV_FS_READ, cb);
    req->file = file;
    req->nbufs = nbufs;
    req->bufs = req->bufsml;

    if (nbufs > ARRAY_SIZE(req->bufsml))
        req->bufs = uv__malloc(nbufs * sizeof(*bufs));
    EVM_ASSERT(req->bufs);
    memcpy(req->bufs, bufs, nbufs * sizeof(*bufs));
    req->off = off;
    return POST(loop, req, cb);
}

int uv_fs_write(uv_loop_t* loop,
                uv_fs_t* req,
                uv_file file,
                const uv_buf_t bufs[],
                unsigned int nbufs,
                int64_t off,
                uv_fs_cb cb) {
    INIT(loop, req, UV_FS_WRITE, cb);
    req->file = file;

    req->nbufs = nbufs;
    req->bufs = req->bufsml;
    if (nbufs > ARRAY_SIZE(req->bufsml))
        req->bufs = uv__malloc(nbufs * sizeof(*bufs));
    EVM_ASSERT(req->bufs);
    memcpy(req->bufs, bufs, nbufs * sizeof(*bufs));

    req->off = off;
    return POST(loop, req, cb);
}

int uv_fs_utime(uv_loop_t* loop,
                uv_fs_t* req,
                const char* path,
                double atime,
                double mtime,
                uv_fs_cb cb) {

}

int uv_fs_close(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_CLOSE, cb);
    req->file = file;
    return POST(loop, req, cb);
}

int uv_fs_fdatasync(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_FDATASYNC, cb);
    req->file = file;
    return POST(loop, req, cb);
}

int uv_fs_fstat(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_FSTAT, cb);
    req->file = file;
    return POST(loop, req, cb);
}

int uv_fs_fsync(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_FSYNC, cb);
    req->file = file;
    return POST(loop, req, cb);
}

int uv_fs_ftruncate(uv_loop_t* loop,
                    uv_fs_t* req,
                    uv_file file,
                    int64_t off,
                    uv_fs_cb cb) {
    INIT(loop, req, UV_FS_FTRUNCATE, cb);
    req->file = file;
    req->off = off;
    return POST(loop, req, cb);
}

int uv_fs_futime(uv_loop_t* loop,
                 uv_fs_t* req,
                 uv_file file,
                 double atime,
                 double mtime,
                 uv_fs_cb cb) {

}

int uv_fs_mkdir(uv_loop_t* loop,
                uv_fs_t* req,
                const char* path,
                int mode,
                uv_fs_cb cb) {
    INIT(loop, req, UV_FS_MKDIR, cb);
    PATH(req, path, cb);
    req->mode = mode;
    return POST(loop, req, cb);
}

int uv_fs_scandir(uv_loop_t* loop,
                  uv_fs_t* req,
                  const char* path,
                  int flags,
                  uv_fs_cb cb) {
    INIT(loop, req, UV_FS_SCANDIR, cb);
    PATH(req, path, cb);
    req->flags = flags;
    return POST(loop, req, cb);
}

int uv_fs_rename(uv_loop_t* loop,
                 uv_fs_t* req,
                 const char* path,
                 const char* new_path,
                 uv_fs_cb cb) {
    INIT(loop, req, UV_FS_SCANDIR, cb);
    PATH2(req, path, new_path, cb);
    return POST(loop, req, cb);
}

int uv_fs_rmdir(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_RMDIR, cb);
    PATH(req, path, cb);
    return POST(loop, req, cb);
}

int uv_fs_stat(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_STAT, cb);
    PATH(req, path, cb);
    return POST(loop, req, cb);
}

int uv_fs_unlink(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_fs_cb cb) {
    INIT(loop, req, UV_FS_UNLINK, cb);
    PATH(req, path, cb);
    return POST(loop, req, cb);
}

void uv_fs_req_cleanup(uv_fs_t* req) {
    if (req->path != NULL && (req->cb != NULL || req->fs_type == UV_FS_MKDTEMP))
        uv__free((void*) req->path);

    req->path = NULL;
    req->new_path = NULL;
}
