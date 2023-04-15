/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"
#include "FreeRTOS.h"
#include "task.h"

int uv_poll_init(uv_loop_t* loop, uv_poll_t* handle, int fd) {
    handle->type = UV_POLL;
    return 0;
}

int uv_poll_start(uv_poll_t* handle, int pevents, uv_poll_cb poll_cb) {
    handle->poll_cb = poll_cb;
    handle->state = UV_STATE_RUNNING;
    return 0;
}

int uv_poll_stop(uv_poll_t* handle) {
    return 0;
}

