/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#ifndef UV_H
#define UV_H

#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <unistd.h>
#include "uv_errno.h"
#include "queue.h"
#include "evm.h"

#if defined (__linux__)

#define uv_posix_open       open
#define uv_posix_write      write
#define uv_posix_read       read
#define uv_posix_close      close

#endif

#define uv__stream_fd(handle) ((handle)->fd)

typedef pthread_t uv_thread_t;
typedef pthread_mutex_t uv_mutex_t;
typedef struct dirent uv__dirent_t;

#define MAX_THREADPOOL_SIZE     1

typedef struct uv_loop_s uv_loop_t;
typedef struct uv_handle_s uv_handle_t;
typedef struct uv_stream_s uv_stream_t;
typedef struct uv_tcp_s uv_tcp_t;
typedef struct uv_poll_s uv_poll_t;
typedef struct uv_timer_s uv_timer_t;
typedef struct uv_async_s uv_async_t;
typedef struct uv_dirent_s uv_dirent_t;
typedef struct uv_connect_s uv_connect_t;
typedef struct uv_shutdown_s uv_shutdown_t;
typedef struct uv_write_s uv_write_t;

typedef struct uv_req_s uv_req_t;
typedef struct uv_fs_s uv_fs_t;
typedef struct uv_work_s uv_work_t;

# define UV_REQ_FIELDS                                                        \
  /* public */                                                                \
  void* data;                                                                 \
  uv_req_type type;                                                           \
  QUEUE node;                                                                 \
  uv_req_t *next;                                                             \
  uv_req_cb cb;                                                               \
  int status;                                                                 \

# define UV_HANDLE_FIELDS                                                     \
  /* public */                                                                \
  void* data;                                                                 \
  /* read-only */                                                             \
  uv_loop_t* loop;                                                            \
  uv_handle_type type;                                                        \
  /* private */                                                               \
  uv_handle_state_t state;                                                    \
  QUEUE node;                                                                 \
  uv_close_cb close_cb;                                                       \
  uv_handle_t *next;                                                          \
  int flags;                                                                  \

typedef enum {
  UV_RUN_DEFAULT = 0,
  UV_RUN_ONCE,
  UV_RUN_NOWAIT
} uv_run_mode;

enum uv_poll_event {
  UV_READABLE = 1,
  UV_WRITABLE = 2,
  UV_DISCONNECT = 4
};

typedef enum {
  UV_STATE_PENDING = 1,
  UV_STATE_RUNNING,
  UV_STATE_CLOSING,
  UV_STATE_CLOSED,
} uv_handle_state_t;

typedef enum {
  UV_FS_UNKNOWN = -1,
  UV_FS_CUSTOM,
  UV_FS_OPEN,
  UV_FS_CLOSE,
  UV_FS_READ,
  UV_FS_WRITE,
  UV_FS_SENDFILE,
  UV_FS_STAT,
  UV_FS_LSTAT,
  UV_FS_FSTAT,
  UV_FS_FTRUNCATE,
  UV_FS_UTIME,
  UV_FS_FUTIME,
  UV_FS_ACCESS,
  UV_FS_CHMOD,
  UV_FS_FCHMOD,
  UV_FS_FSYNC,
  UV_FS_FDATASYNC,
  UV_FS_UNLINK,
  UV_FS_RMDIR,
  UV_FS_MKDIR,
  UV_FS_MKDTEMP,
  UV_FS_RENAME,
  UV_FS_SCANDIR,
  UV_FS_LINK,
  UV_FS_SYMLINK,
  UV_FS_READLINK,
  UV_FS_CHOWN,
  UV_FS_FCHOWN,
  UV_FS_REALPATH
} uv_fs_type;

enum {
  UV_CLOSING              = 0x01,   /* uv_close() called but not finished. */
  UV_CLOSED               = 0x02,   /* close(2) finished. */
  UV_STREAM_READING       = 0x04,   /* uv_read_start() called. */
  UV_STREAM_SHUTTING      = 0x08,   /* uv_shutdown() called but not complete. */
  UV_STREAM_SHUT          = 0x10,   /* Write side closed. */
  UV_STREAM_READABLE      = 0x20,   /* The stream is readable */
  UV_STREAM_WRITABLE      = 0x40,   /* The stream is writable */
  UV_STREAM_BLOCKING      = 0x80,   /* Synchronous writes. */
  UV_STREAM_READ_PARTIAL  = 0x100,  /* read(2) read less than requested. */
  UV_STREAM_READ_EOF      = 0x200,  /* read(2) read EOF. */
  UV_TCP_NODELAY          = 0x400,  /* Disable Nagle. */
  UV_TCP_KEEPALIVE        = 0x800,  /* Turn on keep-alive. */
  UV_TCP_SINGLE_ACCEPT    = 0x1000, /* Only accept() when idle. */
  UV_HANDLE_IPV6          = 0x10000, /* Handle is bound to a IPv6 socket. */
  UV_UDP_PROCESSING       = 0x20000, /* Handle is running the send callback queue. */
  UV_HANDLE_BOUND         = 0x40000  /* Handle is bound to an address and port */
};

enum uv_tcp_flags {
  /* Used with uv_tcp_bind, when an IPv6 address is used. */
  UV_TCP_IPV6ONLY = 1
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#define UV_ERRNO_MAP(XX)                                                      \
  XX(E2BIG, "argument list too long")                                         \
  XX(EACCES, "permission denied")                                             \
  XX(EADDRINUSE, "address already in use")                                    \
  XX(EADDRNOTAVAIL, "address not available")                                  \
  XX(EAFNOSUPPORT, "address family not supported")                            \
  XX(EAGAIN, "resource temporarily unavailable")                              \
  XX(EAI_ADDRFAMILY, "address family not supported")                          \
  XX(EAI_AGAIN, "temporary failure")                                          \
  XX(EAI_BADFLAGS, "bad ai_flags value")                                      \
  XX(EAI_BADHINTS, "invalid value for hints")                                 \
  XX(EAI_CANCELED, "request canceled")                                        \
  XX(EAI_FAIL, "permanent failure")                                           \
  XX(EAI_FAMILY, "ai_family not supported")                                   \
  XX(EAI_MEMORY, "out of memory")                                             \
  XX(EAI_NODATA, "no address")                                                \
  XX(EAI_NONAME, "unknown node or service")                                   \
  XX(EAI_OVERFLOW, "argument buffer overflow")                                \
  XX(EAI_PROTOCOL, "resolved protocol is unknown")                            \
  XX(EAI_SERVICE, "service not available for socket type")                    \
  XX(EAI_SOCKTYPE, "socket type not supported")                               \
  XX(EALREADY, "connection already in progress")                              \
  XX(EBADF, "bad file descriptor")                                            \
  XX(EBUSY, "resource busy or locked")                                        \
  XX(ECANCELED, "operation canceled")                                         \
  XX(ECHARSET, "invalid Unicode character")                                   \
  XX(ECONNABORTED, "software caused connection abort")                        \
  XX(ECONNREFUSED, "connection refused")                                      \
  XX(ECONNRESET, "connection reset by peer")                                  \
  XX(EEXIST, "file already exists")                                           \
  XX(EFAULT, "bad address in system call argument")                           \
  XX(EHOSTUNREACH, "host is unreachable")                                     \
  XX(EINVAL, "invalid argument")                                              \
  XX(EIO, "i/o error")                                                        \
  XX(EISCONN, "socket is already connected")                                  \
  XX(EISDIR, "illegal operation on a directory")                              \
  XX(ELOOP, "too many symbolic links encountered")                            \
  XX(EMFILE, "too many open files")                                           \
  XX(EMSGSIZE, "message too long")                                            \
  XX(ENAMETOOLONG, "name too long")                                           \
  XX(ENETUNREACH, "network is unreachable")                                   \
  XX(ENOBUFS, "no buffer space available")                                    \
  XX(ENOENT, "no such file or directory")                                     \
  XX(ENOMEM, "not enough memory")                                             \
  XX(ENOSPC, "no space left on device")                                       \
  XX(ENOSYS, "function not implemented")                                      \
  XX(ENOTCONN, "socket is not connected")                                     \
  XX(ENOTDIR, "not a directory")                                              \
  XX(ENOTEMPTY, "directory not empty")                                        \
  XX(ENOTSOCK, "socket operation on non-socket")                              \
  XX(ENOTSUP, "operation not supported on socket")                            \
  XX(EPERM, "operation not permitted")                                        \
  XX(EPIPE, "broken pipe")                                                    \
  XX(ESRCH, "no such process")                                                \
  XX(EPROTONOSUPPORT, "protocol not supported")                               \
  XX(EROFS, "read-only file system")                                          \
  XX(ETIMEDOUT, "connection timed out")                                       \
  XX(EXDEV, "cross-device link not permitted")                                \
  XX(EOF, "end of file")                                                      \
  XX(UNKNOWN, "unknown error")                                                \

#define UV_HANDLE_TYPE_MAP(XX)                                                \
  XX(ASYNC, async)                                                            \
  XX(CHECK, check)                                                            \
  XX(FS_EVENT, fs_event)                                                      \
  XX(FS_POLL, fs_poll)                                                        \
  XX(HANDLE, handle)                                                          \
  XX(IDLE, idle)                                                              \
  XX(NAMED_PIPE, pipe)                                                        \
  XX(POLL, poll)                                                              \
  XX(PREPARE, prepare)                                                        \
  XX(PROCESS, process)                                                        \
  XX(STREAM, stream)                                                          \
  XX(TCP, tcp)                                                                \
  XX(TIMER, timer)                                                            \
  XX(TTY, tty)                                                                \
  XX(UDP, udp)                                                                \
  XX(SIGNAL, signal)                                                          \

#define UV_REQ_TYPE_MAP(XX)                                                   \
  XX(REQ, req)                                                                \
  XX(CONNECT, connect)                                                        \
  XX(WRITE, write)                                                            \
  XX(SHUTDOWN, shutdown)                                                      \
  XX(UDP_SEND, udp_send)                                                      \
  XX(FS, fs)                                                                  \
  XX(WORK, work)                                                              \
  XX(GETADDRINFO, getaddrinfo)                                                \
  XX(GETNAMEINFO, getnameinfo)                                                \

typedef enum {
#define XX(code, _) UV_ ## code = UV__ ## code,
  UV_ERRNO_MAP(XX)
#undef XX
  UV_ERRNO_MAX = UV__EOF - 1
} uv_errno_t;


typedef enum {
  UV_UNKNOWN_HANDLE = 0,
#define XX(uc, lc) UV_##uc,
  UV_HANDLE_TYPE_MAP(XX)

#undef XX
  UV_FILE,
  UV_HANDLE_TYPE_MAX
} uv_handle_type;

typedef enum {
  UV_UNKNOWN_REQ = 0,
#define XX(uc, lc) UV_##uc,
  UV_REQ_TYPE_MAP(XX)
#undef XX
  UV_REQ_TYPE_MAX
} uv_req_type;

typedef int uv_file;

typedef void (*uv_work_cb)(uv_work_t* req);
typedef void (*uv_close_cb)(uv_handle_t* handle);
typedef void (*uv_poll_cb)(uv_poll_t* handle, int status, int events);
typedef void (*uv_fs_cb)(uv_fs_t* req);
typedef void (*uv_timer_cb)(uv_timer_t* handle);
typedef void (*uv_async_cb)(uv_async_t* handle);
typedef void (*uv_work_cb)(uv_work_t *worker);
typedef void (*uv_req_cb)(uv_req_t* req, int status);

typedef struct {
  long tv_sec;
  long tv_nsec;
} uv_timespec_t;


typedef struct {
  uint64_t st_dev;
  uint64_t st_mode;
  uint64_t st_nlink;
  uint64_t st_uid;
  uint64_t st_gid;
  uint64_t st_rdev;
  uint64_t st_ino;
  uint64_t st_size;
  uint64_t st_blksize;
  uint64_t st_blocks;
  uint64_t st_flags;
  uint64_t st_gen;
  uv_timespec_t st_atim;
  uv_timespec_t st_mtim;
  uv_timespec_t st_ctim;
  uv_timespec_t st_birthtim;
} uv_stat_t;

typedef enum {
  UV_DIRENT_UNKNOWN,
  UV_DIRENT_FILE,
  UV_DIRENT_DIR,
  UV_DIRENT_LINK,
  UV_DIRENT_FIFO,
  UV_DIRENT_SOCKET,
  UV_DIRENT_CHAR,
  UV_DIRENT_BLOCK
} uv_dirent_type_t;

struct uv_dirent_s {
  const char* name;
  uv_dirent_type_t type;
};

struct uv_work_s {
  UV_HANDLE_FIELDS
  uv_async_t *async;
  uv_work_cb cb;
  uv_work_cb done_cb;
  uv_close_cb user_close_cb;
};

typedef struct uv_buf_t {
  char* base;
  size_t len;
} uv_buf_t;

typedef struct uv_loop_s {
    bool is_running;
    QUEUE timer_queue;
    QUEUE async_queue;
    QUEUE poll_queue;
    QUEUE tick_queue;
    QUEUE tcp_queue;
    uv_async_t *done_asyncs;
    QUEUE work_queue;
    int worker_count;
    int poll_count;
    pthread_mutex_t worker_lock;
    pthread_cond_t worker_cond;
    uv_handle_t *closing_handles;
    uv_handle_t *pending_handles;
    uv_req_t *pending_requests;
    int watcher_count;
    int reqeust_count;
    uint64_t time;          // in ms
    pthread_mutex_t async_lock;
    pthread_cond_t async_cond;
} uv_loop_s;

struct uv_handle_s {
    UV_HANDLE_FIELDS
} ;

struct uv_req_s {
    UV_REQ_FIELDS
} ;

int uv_request_init(uv_loop_t *loop, uv_req_t *req, uv_req_type type, uv_req_cb cb);
void uv_run_request(uv_loop_t *loop);
int uv_request_pending(uv_req_t *req);

struct uv_fs_s {
    UV_REQ_FIELDS
    uv_fs_type fs_type;
    uv_loop_t* loop;
    int result;
    void* ptr;
    const char* path;
    uv_stat_t statbuf;
    const char *new_path;
    uv_file file;
    int flags;
    int mode;
    unsigned int nbufs;
    uv_buf_t* bufs;
    off_t off;
    uv_work_t work_req;
    uv_buf_t bufsml[4];
} ;

struct uv_async_s {
  UV_HANDLE_FIELDS
  uv_async_cb cb;
};

struct uv_poll_s {
  UV_HANDLE_FIELDS
  uv_poll_cb poll_cb;
  int events;
} ;

struct uv_timer_s {
  UV_HANDLE_FIELDS
  uint64_t timeout;
  uint64_t repeat;
  uv_timer_cb cb;
};

typedef void (*uv_alloc_cb)(uv_handle_t* handle,
                            size_t suggested_size,
                            uv_buf_t* buf);
typedef void (*uv_read_cb)(uv_stream_t* stream,
                           ssize_t nread,
                           const uv_buf_t* buf);
typedef void (*uv_after_work_cb)(uv_work_t* req, int status);
typedef void (*uv_write_cb)(uv_write_t* req, int status);
typedef void (*uv_connect_cb)(uv_connect_t* req, int status);
typedef void (*uv_shutdown_cb)(uv_shutdown_t* req, int status);
typedef void (*uv_connection_cb)(uv_stream_t* server, int status);
typedef void (*uv_stream_cb)(uv_loop_t* loop, uv_stream_t* stream, unsigned int events);

#define UV_STREAM_FIELDS                                                      \
  uv_work_t req;                                                              \
  uv_poll_t io_watcher;                                                       \
  /* number of bytes queued for writing */                                    \
  QUEUE write_queue;                                                          \
  size_t write_queue_size;                                                    \
  uv_alloc_cb alloc_cb;                                                       \
  uv_read_cb read_cb;                                                         \
  int fd;                                                                     \
  int accepted_fd;                                                            \
  uv_connect_t *connect_req;                                                  \
  uv_shutdown_t *shutdown_req;                                                \
  uv_connection_cb connection_cb;                                             \
  int delayed_error;                                                          \
  uv_stream_cb cb;                                                            \
  QUEUE write_completed_queue;                                                \

typedef struct uv_stream_s {
  UV_HANDLE_FIELDS
  UV_STREAM_FIELDS
} uv_stream_s;

typedef struct uv_tcp_s {
  UV_HANDLE_FIELDS
  UV_STREAM_FIELDS
} uv_tcp_s;

typedef void* (*uv_malloc_func)(size_t size);
typedef void* (*uv_realloc_func)(void* ptr, size_t size);
typedef void* (*uv_calloc_func)(size_t count, size_t size);
typedef void (*uv_free_func)(void* ptr);

void* uv__malloc(size_t size);
void uv__free(void* ptr);
void* uv__realloc(void* ptr, size_t size);

uv_buf_t uv_buf_init(char* base, unsigned int len);
size_t uv__count_bufs(const uv_buf_t bufs[], unsigned int nbufs);
int uv_queue_work(uv_loop_t* loop,
                  uv_work_t* req,
                  uv_work_cb work_cb,
                  uv_after_work_cb after_work_cb);
int uv_run(uv_loop_t* loop, uv_run_mode mode);
uv_loop_t* uv_default_loop(void);
int uv_loop_alive(const uv_loop_t* loop);

int uv_poll_init(uv_loop_t* loop, uv_poll_t* handle, int fd);
int uv_poll_start(uv_poll_t* handle, int pevents, uv_poll_cb poll_cb);
void uv_run_poll(uv_loop_t *loop);

void uv_threadpool_init(uv_loop_t *loop);
void uv_threadpool_stop(uv_loop_t *ctx);
int uv_thread_create(uv_thread_t *tid, void (*entry)(void *arg), void *arg);
int uv_mutex_init(uv_mutex_t* mutex);
void uv_mutex_lock(uv_mutex_t* mutex);
void uv_mutex_unlock(uv_mutex_t* mutex);

int uv_is_closing(const uv_handle_t* handle);
void uv_close(uv_handle_t* handle, uv_close_cb close_cb);

void uv_close_handles(uv_loop_t *loop);
int uv_handle_init(uv_loop_t *loop, uv_handle_t *handle,
                       uv_handle_type type, uv_close_cb close_cb);
int uv_handle_pending(uv_handle_t *handle);
void uv_add_pending_handles(uv_loop_t *loop);
void uv_update_time(uv_loop_t *ctx);
void uv_run_timers(uv_loop_t *loop);
void uv_run_done_async(uv_loop_t *loop);

int uv_timer_init(uv_loop_t* loop, uv_timer_t* handle);
int uv_timer_start(uv_timer_t* handle,
                   uv_timer_cb cb,
                   uint64_t timeout,
                   uint64_t repeat);


int uv_async_send(uv_async_t *async);
int uv_async_start(uv_loop_t *ctx, uv_async_t *async, uv_async_cb cb, uv_close_cb close_cb);

void uv_async_close(uv_async_t *async);
int uv_timer_stop(uv_timer_t* handle);
void uv_handle_close(uv_handle_t *handle);
void uv_work_close(uv_work_t *worker);

int uv_fs_open(uv_loop_t* loop,
               uv_fs_t* req,
               const char* path,
               int flags,
               int mode,
               uv_fs_cb cb);
int uv_fs_read(uv_loop_t* loop, uv_fs_t* req,
               uv_file file,
               const uv_buf_t bufs[],
               unsigned int nbufs,
               int64_t off,
               uv_fs_cb cb);
int uv_fs_write(uv_loop_t* loop,
                uv_fs_t* req,
                uv_file file,
                const uv_buf_t bufs[],
                unsigned int nbufs,
                int64_t off,
                uv_fs_cb cb);
int uv_fs_utime(uv_loop_t* loop,
                uv_fs_t* req,
                const char* path,
                double atime,
                double mtime,
                uv_fs_cb cb);
int uv_fs_close(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb);
int uv_fs_fdatasync(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb);
int uv_fs_fstat(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb);
int uv_fs_fsync(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb);
int uv_fs_ftruncate(uv_loop_t* loop,
                    uv_fs_t* req,
                    uv_file file,
                    int64_t off,
                    uv_fs_cb cb);
int uv_fs_futime(uv_loop_t* loop,
                 uv_fs_t* req,
                 uv_file file,
                 double atime,
                 double mtime,
                 uv_fs_cb cb);
int uv_fs_mkdir(uv_loop_t* loop,
                uv_fs_t* req,
                const char* path,
                int mode,
                uv_fs_cb cb);
int uv_fs_scandir(uv_loop_t* loop,
                  uv_fs_t* req,
                  const char* path,
                  int flags,
                  uv_fs_cb cb);
int uv_fs_rename(uv_loop_t* loop,
                 uv_fs_t* req,
                 const char* path,
                 const char* new_path,
                 uv_fs_cb cb);
int uv_fs_rmdir(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_fs_cb cb);
int uv_fs_stat(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_fs_cb cb);
int uv_fs_unlink(uv_loop_t* loop, uv_fs_t* req, const char* path, uv_fs_cb cb);
int uv_fs_scandir_next(uv_fs_t* req, uv_dirent_t* ent);
void uv_fs_req_cleanup(uv_fs_t* req);

const char* uv_strerror(int err);
const char* uv_err_name(int err);

#define uv_nonblock uv_nonblock_ioctl
#define uv__cloexec uv__cloexec_ioctl
int uv_nonblock_ioctl(int fd, int set);
int uv__cloexec_ioctl(int fd, int set);

struct uv_connect_s {
  UV_REQ_FIELDS
  uv_stream_t* handle;
};

struct uv_shutdown_s {
  UV_REQ_FIELDS
  uv_stream_t* handle;
};

struct uv_write_s {
    UV_REQ_FIELDS
    uv_stream_t* send_handle;
    uv_stream_t* handle;
    unsigned int write_index;
    uv_buf_t* bufs;
    unsigned int nbufs;
    int error;
    uv_buf_t bufsml[4];
    uv_async_t async;
};

int uv__close(int fd);
int uv_socket(int domain, int type, int protocol);
int uv_ip4_addr(const char* ip, int port, struct sockaddr_in* addr);
int uv_tcp_bind(uv_tcp_t* handle,
                const struct sockaddr* addr,
                unsigned int flags);
int uv_tcp_connect(uv_connect_t* req,
                   uv_tcp_t* handle,
                   const struct sockaddr* addr,
                   uv_connect_cb cb);
int uv_accept(uv_stream_t* server, uv_stream_t* client);
int uv_shutdown(uv_shutdown_t* req, uv_stream_t* handle, uv_shutdown_cb cb);
int uv_read_start(uv_stream_t* stream,
                  uv_alloc_cb alloc_cb,
                  uv_read_cb read_cb);
int uv_tcp_init(uv_loop_t* loop, uv_tcp_t* tcp);
int uv_tcp_keepalive(uv_tcp_t* handle, int on, unsigned int delay);
void uv_tcp_close(uv_tcp_t* handle);
int uv_inet_ntop(int af, const void* src, char* dst, size_t size);
int uv_tcp_getsockname(const uv_tcp_t* handle,
                       struct sockaddr* name,
                       int* namelen);
int uv_write(uv_write_t* req,
             uv_stream_t* handle,
             const uv_buf_t bufs[],
             unsigned int nbufs,
             uv_write_cb cb);

int uv__getiovmax(void);

#endif
