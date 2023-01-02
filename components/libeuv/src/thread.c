#include "uv.h"


void uv_queue_init() {

}

static void uv__cancelled(struct uv__work* w) {
  abort();
}

int uv_mutex_init(uv_mutex_t* mutex) {

}

void uv_mutex_lock(uv_mutex_t* mutex) {

}

void uv_mutex_unlock(uv_mutex_t* mutex) {

}

int uv_thread_create(uv_thread_t *tid, void (*entry)(void *arg), void *arg) {

}

void uv__work_submit(uv_loop_t* loop,
                     struct uv__work* w,
                     void (*work)(struct uv__work* w),
                     void (*done)(struct uv__work* w, int status)) {

}

#define NEW_TASK                                      \
  work = NULL;                                      \
  if (!QUEUE_EMPTY(&loop->work_queue)) {             \
    QUEUE *head = QUEUE_HEAD(&loop->work_queue);     \
    QUEUE_REMOVE(head);                               \
    QUEUE_INIT(head);                                 \
    work = QUEUE_DATA(head, uv_work_t, node);     \
  }

static void* worker(void *data) {
  uv_loop_t *loop = (uv_loop_t *) data;
  uv_work_t *work;
  pthread_mutex_lock(&loop->worker_lock);
  while (true) {
    NEW_TASK
    if (work == NULL) {
      pthread_cond_wait(&loop->worker_cond, &loop->worker_lock);
      if (loop->is_running == false) {
        pthread_cond_signal(&loop->worker_cond);
        pthread_mutex_unlock(&loop->worker_lock);
        break;
      }
      NEW_TASK
    }
    pthread_mutex_unlock(&loop->worker_lock);
    if (work == NULL) {
      continue;
    }
    work->cb(work);
    uv_async_send(work->async);
    pthread_mutex_lock(&loop->worker_lock);
    EVM_ASSERT(loop->worker_count > 0);
    --loop->worker_count;
  }
  return NULL;
}

void uv_threadpool_init(uv_loop_t *loop) {
  for (int i = 0; i < MAX_THREADPOOL_SIZE; ++i) {
    pthread_t worker_thread;
    pthread_create(&worker_thread, NULL, worker, loop);
    pthread_detach(worker_thread);
  }
}

static void work_close(uv_handle_t *watcher) {
  uv_work_t *worker = (uv_work_t *) watcher;
  uv_async_close(worker->async);
  if (worker->user_close_cb) {
    worker->user_close_cb(watcher);
  }
}

static void work_async_on_done(uv_async_t *async) {
  uv_work_t *worker = (uv_work_t *) async->data;
  worker->done_cb(worker);
}

static void work_async_on_close(uv_handle_t *handle) {
  uv__free(handle);
}

int uv_queue_work(uv_loop_t* loop,
                  uv_work_t* req,
                  uv_work_cb work_cb,
                  uv_after_work_cb after_work_cb) {
    uv_handle_t *w = (uv_handle_t *) req;
    int r = uv_handle_init(loop, w, UV_WORK, work_close);
    if (r != 0) {
    return r;
    }
    req->user_close_cb = NULL;
    req->cb = work_cb;
    req->done_cb = after_work_cb;
    req->async = (uv_async_t *) uv__malloc(sizeof(uv_async_t));
    req->async->data = req;
    uv_async_start(loop, req->async, work_async_on_done,
    work_async_on_close);
    return uv_handle_pending(w);
}

void uv_threadpool_stop(uv_loop_t *ctx) {
  EVM_ASSERT(!ctx->is_running);
  pthread_mutex_lock(&ctx->worker_lock);
  pthread_cond_signal(&ctx->worker_cond);
  pthread_mutex_unlock(&ctx->worker_lock);
}

void uv_work_close(uv_work_t *worker) {
    uv_handle_close((uv_handle_t *) worker);
}
