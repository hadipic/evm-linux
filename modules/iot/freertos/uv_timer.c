/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

static void timer_callback(TimerHandle_t xTimer) {
    uv_handle_t *timer = (uv_handle_t*) pvTimerGetTimerID(xTimer);
    uv_queue_put(timer, 0);
}

int uv_timer_init(uv_loop_t* loop, uv_timer_t* handle) {
    handle->type = UV_TIMER;
}

int uv_timer_start(uv_timer_t* handle,
                   uv_timer_cb cb,
                   uint64_t timeout,
                   uint64_t repeat) {
    TimerHandle_t os_timer;
    handle->timeout = timeout;
    handle->repeat = repeat;
    os_timer = xTimerCreate("timer", timeout / portTICK_RATE_MS, repeat, handle, timer_callback);
    if (!os_timer) {
        return -1;
    }
    int re = xTimerStart(os_timer, 0);
    handle->cb = cb;
    handle->timer_data = os_timer;
    return re == pdPASS ? 0 : -1;
}

int uv_timer_stop(uv_timer_t* handle) {
    xTimerDelete(handle->timer_data, 0);
    return 0;
}

