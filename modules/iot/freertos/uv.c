/****************************************************************************
**  Copyright (C) 2022
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

static QueueHandle_t xQueue = {0};

static uv_loop_t uv_loop = {0};

uv_loop_t *uv_default_loop(void) {
    return &uv_loop;
}


static void uv_queue_init(void) {
    if (!xQueue) {
        xQueue = xQueueCreate(256, sizeof(intptr_t));
        uv_loop.queue = xQueue;
    }
}


void uv_init(void) {
    uv_queue_init();
}

void uv_run(void) {
    uv_handle_t *handle;
    int re = uv_queue_get(&handle, 1);
    if( re ){

        switch (handle->type) {
        case UV_TIMER:{
            uv_timer_t *h = (uv_timer_t*)handle;
            h->cb(h);
            break;
        }

        }
    }
}

uint32_t uv_queue_put(uv_handle_t *msg, size_t timeout) {
    if (xQueue == NULL)
        return 0;
    return xQueueSendFromISR(xQueue, &msg, NULL) == pdTRUE ? 1 : 0;
}

uint32_t uv_queue_get(uv_handle_t **msg, size_t timeout) {
    if (xQueue == NULL)
        return 1;
    uint32_t re = xQueueReceive(xQueue, msg, timeout) == pdTRUE ? 1 : 0;
    return re;
}

int uv_is_closing(const uv_handle_t* handle) {
    return (handle->state == UV_STATE_CLOSING) || (handle->state == UV_STATE_CLOSED);
}

void uv_close(uv_handle_t* handle, uv_close_cb close_cb) {
    switch (handle->type) {
    case UV_TIMER:
        uv_timer_stop((uv_timer_t *) handle);
        return;
    default:
        EVM_ASSERT(0);
    }
}

int uv_queue_work(uv_loop_t* loop,
                  uv_work_t* req,
                  uv_work_cb work_cb,
                  uv_after_work_cb after_work_cb) {

}



