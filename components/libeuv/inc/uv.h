#ifndef UV_H
#define UV_H

#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "queue.h"
#include "evm.h"

typedef pthread_t uv_thread_t;
typedef pthread_mutex_t uv_mutex_t;

#define MAX_THREADPOOL_SIZE     1

typedef struct uv_loop_s uv_loop_t;
typedef struct uv_handle_s uv_handle_t;
typedef struct uv_stream_s uv_stream_t;
typedef struct uv_tcp_s uv_tcp_t;
typedef struct uv_poll_s uv_poll_t;
typedef struct uv_timer_s uv_timer_t;
typedef struct uv_async_s uv_async_t;

typedef struct uv_req_s uv_req_t;
typedef struct uv_fs_s uv_fs_t;
typedef struct uv_work_s uv_work_t;

# define UV_REQ_FIELDS                                                        \
  /* public */                                                                \
  void* data;                                                                 \
  uv_req_type type;                                                           \
  /* private */                                                               \
  void* active_queue[2];                                                      \

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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

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
    uv_async_t *done_asyncs;
    QUEUE tick_queue;
    QUEUE work_queue;
    int worker_count;
    pthread_mutex_t worker_lock;
    pthread_cond_t worker_cond;
    uv_handle_t *closing_handles;
    uv_handle_t *pending_handles;
    int watcher_count;
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

struct uv_fs_s {
    UV_REQ_FIELDS
    uv_fs_type fs_type;
    uv_loop_t* loop;
    uv_fs_cb cb;
    int result;
    const char* path;
    const char *new_path;
    uv_file file;
    int flags;
    int mode;
    unsigned int nbufs;                                                         \
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

#define UV_STREAM_FIELDS                                                      \
  /* number of bytes queued for writing */                                    \
  size_t write_queue_size;                                                    \
  uv_alloc_cb alloc_cb;                                                       \
  uv_read_cb read_cb;                                                         \

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
int uv_queue_work(uv_loop_t* loop,
                  uv_work_t* req,
                  uv_work_cb work_cb,
                  uv_after_work_cb after_work_cb);
int uv_run(uv_loop_t* loop, uv_run_mode mode);
uv_loop_t* uv_default_loop(void);
int uv_loop_alive(const uv_loop_t* loop);

int uv_poll_init(uv_loop_t* loop, uv_poll_t* handle, int fd);

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
#endif
