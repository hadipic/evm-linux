/****************************************************************************
**
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  Email	: scriptiot@aliyun.com
**  Website	: https://gitee.com/scriptiot
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

#define CHECK_QUEUE(name) \
  EVM_ASSERT(QUEUE_EMPTY(&loop->name))

#define CHECK_LINK(name) \
  EVM_ASSERT(!loop->name)

typedef struct {
  uv_malloc_func local_malloc;
  uv_realloc_func local_realloc;
  uv_calloc_func local_calloc;
  uv_free_func local_free;
} uv__allocator_t;

static uv__allocator_t uv__allocator = {
  malloc,
  realloc,
  calloc,
  free,
};

void* uv__malloc(size_t size) {
  return uv__allocator.local_malloc(size);
}

void uv__free(void* ptr) {
  int saved_errno;

  /* Libuv expects that free() does not clobber errno.  The system allocator
   * honors that assumption but custom allocators may not be so careful.
   */
  saved_errno = errno;
  uv__allocator.local_free(ptr);
  errno = saved_errno;
}

void* uv__calloc(size_t count, size_t size) {
  return uv__allocator.local_calloc(count, size);
}

void* uv__realloc(void* ptr, size_t size) {
  return uv__allocator.local_realloc(ptr, size);
}

uv_buf_t uv_buf_init(char* base, unsigned int len) {
  uv_buf_t buf;
  buf.base = base;
  buf.len = len;
  return buf;
}

static void set_next_timeout(uv_loop_t *ctx, struct timespec *spec) {
  spec->tv_sec = 0;
  spec->tv_nsec = 0;
#if !(defined(__APPLE__) && defined(__MACH__))
  clock_gettime(CLOCK_MONOTONIC, spec);
#endif
  QUEUE *q;
  uv_timer_t *timer = NULL;
  QUEUE_FOREACH(q, &ctx->timer_queue) {
    uv_timer_t *t = QUEUE_DATA(q, uv_timer_t, node);
    if (t->state == UV_STATE_RUNNING) {
      EVM_ASSERT(t->timeout >= ctx->time);
      timer = t;
      break;
    }
  }
  uint64_t next_timeout;
  if (timer) {
    next_timeout = timer->timeout - ctx->time;
  } else if (!QUEUE_EMPTY(&ctx->tick_queue)) {
    next_timeout = 0;
  } else {
    next_timeout = UINT32_MAX;
  }
  spec->tv_sec += next_timeout / 1000;
  spec->tv_nsec += (long) (next_timeout % 1000) * 1000000;
}

static void goto_sleep(uv_loop_t *loop) {
  if (loop->closing_handles || loop->pending_handles) {
    return;
  }
  pthread_mutex_t *lock = &loop->async_lock;
  pthread_cond_t *cond = &loop->async_cond;
  pthread_mutex_lock(lock);
  if (!loop->done_asyncs) {
    struct timespec next_time;
    set_next_timeout(loop, &next_time);
#if defined(__APPLE__) && defined(__MACH__)
    pthread_cond_timedwait_relative_np(cond, lock, &next_time);
#else
    pthread_cond_timedwait(cond, lock, &next_time);
#endif
  }
  pthread_mutex_unlock(&loop->async_lock);
}

static void check_watchers(uv_loop_t *loop) {
  CHECK_QUEUE(timer_queue);
  CHECK_QUEUE(async_queue);
  CHECK_QUEUE(poll_queue);
  CHECK_QUEUE(tick_queue);
  CHECK_QUEUE(work_queue);
  CHECK_LINK(done_asyncs);
  CHECK_LINK(pending_handles);
  CHECK_LINK(closing_handles);
  CHECK_LINK(pending_requests);
}

int uv_run(uv_loop_t* loop, uv_run_mode mode) {
    int r;
    r = uv_loop_alive(loop);
    if (!r)
        uv_update_time(loop);

    while(r != 0 && loop->is_running) {
        uv_update_time(loop);
        while (loop->watcher_count > 0) {
            uv_add_pending_handles(loop);
            uv_run_timers(loop);
            uv_run_done_async(loop);
            uv_close_handles(loop);
        }

        while (loop->reqeust_count > 0) {
            uv_run_request(loop);
        }

        uv_run_poll(loop);
        r = uv_loop_alive(loop);
        if (mode == UV_RUN_ONCE || mode == UV_RUN_NOWAIT)
          break;
    }
    return r;
}

int uv_loop_alive(const uv_loop_t* loop) {
    if (loop->closing_handles || loop->pending_handles || loop->pending_requests || loop->worker_count || loop->poll_count) {
      return 1;
    }
    return 0;
}

int uv_is_closing(const uv_handle_t* handle) {
    return (handle->state == UV_STATE_CLOSING) || (handle->state == UV_STATE_CLOSED);
}

void uv_close(uv_handle_t* handle, uv_close_cb close_cb) {
    switch (handle->type) {
    case UV_TIMER:
        uv_timer_stop((uv_timer_t *) handle);
        return;
    case UV_ASYNC:
        uv_async_close((uv_async_t *) handle);
        return;
    case UV_WORK:
        uv_work_close((uv_work_t *) handle);
        return;
    case UV_TCP:
        uv_tcp_close((uv_tcp_t*) handle);
        return;
    default:
        EVM_ASSERT(0);
    }
}

#define UV_ERR_NAME_GEN(name, _) case UV_ ## name: return #name;
const char* uv_err_name(int err) {
  switch (err) {
    UV_ERRNO_MAP(UV_ERR_NAME_GEN)
    default:
      /* TUV_CHANGES@20170517: To figure out what error name is missing */
      return "uv_err_name: Unknown error";
  }
}
#undef UV_ERR_NAME_GEN

#define UV_STRERROR_GEN(name, msg) case UV_ ## name: return msg;
const char* uv_strerror(int err) {
  switch (err) {
    UV_ERRNO_MAP(UV_STRERROR_GEN)
    default:
        return "Unknown error";
    }
}
#undef UV_STRERROR_GEN

int uv_fs_scandir_next(uv_fs_t* req, uv_dirent_t* ent) {
  return 0;
}

size_t uv__count_bufs(const uv_buf_t bufs[], unsigned int nbufs) {
  unsigned int i;
  size_t bytes;

  bytes = 0;
  for (i = 0; i < nbufs; i++)
    bytes += (size_t) bufs[i].len;

  return bytes;
}


