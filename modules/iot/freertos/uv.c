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

#define QUEUE_SIZE 128

static QueueHandle_t xQueue = {0};

static uv_loop_t uv_loop = {0};

uv_loop_t *uv_default_loop(void) {
    return &uv_loop;
}

static void uv_queue_init(void) {
    if (!xQueue) {
        xQueue = xQueueCreate(QUEUE_SIZE, sizeof(intptr_t));
        uv_loop.queue = xQueue;
    }
    uv_loop.work_queue = xQueueCreate(QUEUE_SIZE, sizeof(intptr_t));
    uv_loop.done_queue = xQueueCreate(QUEUE_SIZE, sizeof(intptr_t));
}

static int uv_queue_put(void *queue, uv_handle_t *msg, size_t timeout) {
    return xQueueSendFromISR(queue, &msg, NULL) == pdTRUE ? 1 : 0;
}

static int uv_queue_get(void *queue, uv_handle_t **msg, size_t timeout) {
    int re = xQueueReceive(queue, msg, timeout) == pdTRUE ? 1 : 0;
    return re;
}

void uv_init(void) {
    uv_queue_init();
}

void uv_run(void) {
    uv_handle_t *handle;
    int re = uv_queue_get(uv_loop.queue, &handle, 1);
    if( re ){
        switch (handle->type) {
        case UV_TIMER:{
            uv_timer_t *h = (uv_timer_t*)handle;
            h->cb(h);
            break;
        }

        }
    }

    re = uv_queue_get(uv_loop.done_queue, &handle, 1);
    if( re ){
        switch (handle->type) {
            case UV_WORK:{
                uv_work_t *h = (uv_work_t*)handle;
                h->done_cb(h, 0);
                break;
            }
        }
    }
}

int uv_async_send(uv_handle_t *msg) {
    return xQueueSendFromISR(uv_loop.queue, &msg, NULL) == pdTRUE ? 1 : 0;
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

static void* worker(void *data) {
    uv_work_t *work;
    while (true) {
        BaseType_t re = xQueueReceive(uv_loop.work_queue, work, -1);
        if(re == pdTRUE) {
            work->cb(work);
            uv_queue_put(uv_loop.done_queue, &work, 1);
        }
    }
    return NULL;
}

int uv_queue_work(uv_loop_t* loop,
                  uv_work_t* req,
                  uv_work_cb work_cb,
                  uv_after_work_cb after_work_cb) {
    req->user_close_cb = NULL;
    req->cb = work_cb;
    req->done_cb = after_work_cb;
}



