/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

void uv_run_poll(uv_loop_t *loop) {
    QUEUE *q;
    uv_poll_t *t;
    QUEUE_FOREACH(q, &loop->poll_queue) {
        t = QUEUE_DATA(q, uv_poll_t, node);
        if (t->state != UV_STATE_RUNNING) {
            continue;
        }
        t->poll_cb(t, 0, t->events);
    }
}

int uv_poll_init(uv_loop_t* loop, uv_poll_t* handle, int fd) {
    int err = uv_nonblock(fd, 1);
    if (err)
        return err;
    uv_handle_init(loop, (uv_handle_t*)handle, UV_POLL, NULL);
    handle->poll_cb = NULL;
    return 0;
}

int uv_poll_start(uv_poll_t* handle, int pevents, uv_poll_cb poll_cb) {
    uv_loop_t *loop = uv_default_loop();
    handle->poll_cb = poll_cb;
    handle->events = pevents;
    loop->poll_count++;
    handle->state = UV_STATE_RUNNING;
    QUEUE_INSERT_TAIL(&loop->poll_queue, &handle->node);
    return 0;
}

int uv_poll_stop(uv_poll_t* handle) {
  uv_handle_close((uv_handle_t *) handle);
  return 0;
}
