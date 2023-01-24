/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

static void uv__fs_work(struct uv__work* w) {

}

static void uv__fs_done(struct uv__work* w, int status) {

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
