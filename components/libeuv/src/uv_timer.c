/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

int uv_timer_init(uv_loop_t* loop, uv_timer_t* handle) {
    uv_handle_t *w = (uv_handle_t *) handle;
    int r = uv_handle_init(loop, w, UV_TIMER, NULL);
    if (r != 0) {
        return r;
    }
    return 0;
}

int uv_timer_start(uv_timer_t* handle,
                   uv_timer_cb cb,
                   uint64_t timeout,
                   uint64_t repeat) {
    uv_loop_t *loop = uv_default_loop();
    uv_handle_t *w = (uv_handle_t *) handle;
    handle->timeout = loop->time + timeout;
    handle->repeat = repeat;
    handle->cb = cb;
    return uv_handle_pending(w);
}

int uv_timer_stop(uv_timer_t* handle) {
    uv_handle_close((uv_handle_t *) handle);
    return 0;
}


void uv_update_time(uv_loop_t *ctx) {
  struct timespec spec;
  clock_gettime(CLOCK_MONOTONIC, &spec);
  ctx->time = spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
}

void uv_run_timers(uv_loop_t *loop) {
  QUEUE *q;
  uv_timer_t *t;
  QUEUE_FOREACH(q, &loop->timer_queue) {
    t = QUEUE_DATA(q, uv_timer_t, node);
    if (t->state != UV_STATE_RUNNING) {
      continue;
    }
    if (t->timeout > loop->time) {
      break;
    }
    if (t->repeat > 0) {
      t->timeout = loop->time + t->repeat;
    } else {
      uv_timer_stop(t);
    }
    t->cb(t);
  }
}
