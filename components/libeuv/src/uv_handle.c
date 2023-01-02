#include "uv.h"

static void uv_remove_handle_from_link(uv_handle_t *handle,
                                           uv_handle_t **head) {
  while (*head) {
    if (*head == handle) {
      *head = NULL;
      break;
    }
    if ((*head)->next == handle) {
      (*head)->next = handle->next;
      break;
    }
    head = &(*head)->next;
  }
  handle->next = NULL;
}

int uv_handle_init(uv_loop_t *loop, uv_handle_t *handle,
                       uv_handle_type type, uv_close_cb close_cb) {
  if (handle->state == UV_STATE_CLOSING) {
    uv_remove_handle_from_link(handle, &handle->loop->closing_handles);
  }
  handle->loop= loop;
  handle->state = UV_STATE_PENDING;
  handle->close_cb = close_cb;
  QUEUE_INIT(&handle->node);
  handle->type = type;
  handle->next = NULL;
  return 0;
}

void uv_close_handles(uv_loop_t *loop) {
  uv_handle_t *handle;
  while (loop->closing_handles) {
    handle = loop->closing_handles;
    loop->closing_handles = handle->next;
    handle->next = NULL;
    EVM_ASSERT(handle->state == UV_STATE_CLOSING);
    QUEUE_REMOVE(&handle->node);
    QUEUE_INIT(&handle->node);
    handle->state = UV_STATE_CLOSED;
    EVM_ASSERT(loop->watcher_count > 0);
    --loop->watcher_count;
    if (handle->close_cb) {
      handle->close_cb(handle);
    }
  }
}

int uv_handle_pending(uv_handle_t *handle) {
    EVM_ASSERT(handle->loop);
    EVM_ASSERT(handle->state == UV_STATE_PENDING);
    EVM_ASSERT(!handle->next);
    uv_handle_t **pending_handle = &handle->loop->pending_handles;
    while (*pending_handle) {
        EVM_ASSERT(*pending_handle != handle);
        pending_handle = &(*pending_handle)->next;
    }
    *pending_handle = handle;
    ++handle->loop->watcher_count;
    return 0;
}

void uv_add_pending_handles(uv_loop_t *loop) {
  uv_handle_t *watcher;
  while (loop->pending_handles) {
    watcher = loop->pending_handles;
    loop->pending_handles = watcher->next;
    watcher->next = NULL;
    EVM_ASSERT(watcher->state = UV_STATE_PENDING);
    watcher->state = UV_STATE_RUNNING;
    if (watcher->type == UV_TIMER) {
      QUEUE *q;
      uv_timer_t *pt = (uv_timer_t *) watcher;
      uv_timer_t *t;
      if (QUEUE_EMPTY(&loop->timer_queue)) {
        QUEUE_INSERT_HEAD(&loop->timer_queue, &watcher->node);
      } else {
        QUEUE_FOREACH(q, &loop->timer_queue) {
          t = QUEUE_DATA(q, uv_timer_t, node);
          if (t->timeout > pt->timeout) {
            QUEUE_INSERT_HEAD(&t->node, &watcher->node);
            break;
          }
        }
      }
    } else if (watcher->type == UV_ASYNC) {
      QUEUE_INSERT_TAIL(&loop->async_queue, &watcher->node);
    } else if (watcher->type == UV_WORK) {
      pthread_mutex_lock(&loop->worker_lock);
      ++loop->worker_count;
      QUEUE_INIT(&watcher->node);
      QUEUE_INSERT_TAIL(&loop->work_queue, &watcher->node);
      pthread_cond_signal(&loop->worker_cond);
      pthread_mutex_unlock(&loop->worker_lock);
    } else {
      EVM_ASSERT(0);
    }
  }
}

void uv_handle_close(uv_handle_t *handle) {
    if (handle->state == UV_STATE_PENDING) {
        uv_remove_handle_from_link(handle, &handle->loop->pending_handles);
    } else if (handle->state != UV_STATE_RUNNING) {
        EVM_ASSERT(0);
    }
    EVM_ASSERT(!handle->next);
    handle->state = UV_STATE_CLOSING;
    uv_handle_t **last_watcher = &handle->loop->closing_handles;
    while (*last_watcher) {
        EVM_ASSERT(*last_watcher != handle);
        last_watcher = &(*last_watcher)->next;
    }
    *last_watcher = handle;
}
