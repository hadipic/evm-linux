/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

int uv_async_start(uv_loop_t *ctx, uv_async_t *async,
                     uv_async_cb cb, uv_close_cb close_cb) {
  uv_handle_t *w = (uv_handle_t *) async;
  int r = uv_handle_init(ctx, w, UV_ASYNC, close_cb);
  if (r != 0) {
    return r;
  }
  async->cb = cb;
  return uv_handle_pending(w);
}

void uv_run_done_async(uv_loop_t *loop) {
  uv_async_t *async;
  pthread_mutex_lock(&loop->async_lock);
  async = loop->done_asyncs;
  loop->done_asyncs = NULL;
  pthread_mutex_unlock(&loop->async_lock);

  uv_async_t *a;
  while (async != NULL) {
    if (async->state == UV_STATE_RUNNING) {
      async->cb(async);
    }
    a = (uv_async_t *) async->next;
    async->next = NULL;
    async = a;
  }
}

int uv_async_send(uv_async_t *async) {
  EVM_ASSERT(async->state == UV_STATE_RUNNING ||
              async->state == UV_STATE_PENDING);
  pthread_mutex_lock(&async->loop->async_lock);
  uv_handle_t **a = (uv_handle_t **) &async->loop->done_asyncs;
  while (*a) {
    if (*a == (uv_handle_t *) async) {
      break;
    }
    a = &(*a)->next;
  }
  if (!*a) {
    *a = (uv_handle_t *) async;
  }
  pthread_cond_signal(&async->loop->async_cond);
  pthread_mutex_unlock(&async->loop->async_lock);
  return 0;
}

void uv_async_close(uv_async_t *async) {
    uv_handle_close((uv_handle_t *) async);
}
