#include "uv.h"

int errno;

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
  CHECK_QUEUE(tick_queue);
  CHECK_QUEUE(work_queue);
  CHECK_LINK(done_asyncs);
  CHECK_LINK(pending_handles);
  CHECK_LINK(closing_handles);
}

int uv_run(uv_loop_t* loop, uv_run_mode mode) {
    EVM_ASSERT(!loop->is_running);
    loop->is_running = true;
    uv_threadpool_init(loop);

    while (loop->watcher_count > 0) {
        uv_add_pending_handles(loop);
        uv_run_timers(loop);
        goto_sleep(loop);
        uv_run_done_async(loop);
        uv_close_handles(loop);
    }

    check_watchers(loop);

    loop->is_running = false;
    uv_threadpool_stop(loop);
    return 0;
}

int uv_loop_alive(const uv_loop_t* loop) {

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
    default:
        EVM_ASSERT(0);
    }
}

int uv_poll_init(uv_loop_t* loop, uv_poll_t* handle, int fd) {

}

int uv_poll_start(uv_poll_t* handle, int pevents, uv_poll_cb poll_cb) {

}






