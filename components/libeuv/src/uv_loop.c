/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

static uv_loop_t* default_loop_ptr;
static uv_loop_t default_loop_struct;

int uv_loop_init(uv_loop_t* loop) {
    loop->is_running = false;
    QUEUE_INIT(&loop->timer_queue);
    QUEUE_INIT(&loop->async_queue);
    loop->done_asyncs = NULL;
    QUEUE_INIT(&loop->tick_queue);
    QUEUE_INIT(&loop->work_queue);
    QUEUE_INIT(&loop->poll_queue);
    QUEUE_INIT(&loop->tcp_queue);
    pthread_mutex_init(&loop->worker_lock, NULL);
    pthread_cond_init(&loop->worker_cond, NULL);
    loop->worker_count = 0;
    loop->watcher_count = 0;
    loop->poll_count = 0;
    pthread_mutex_init(&loop->async_lock, NULL);
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    #if !(defined(__APPLE__) && defined(__MACH__))
    pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);
    #endif
    pthread_cond_init(&loop->async_cond, &cond_attr);
    #ifndef __ESP_IDF__
    pthread_condattr_destroy(&cond_attr);
    #endif
    loop->closing_handles = NULL;
    loop->pending_handles = NULL;
    loop->is_running = true;
    uv_threadpool_init(loop);
    uv_update_time(loop);
    return 0;
}

uv_loop_t* uv_default_loop(void) {
    if (default_loop_ptr != NULL)
        return default_loop_ptr;

    if (uv_loop_init(&default_loop_struct))
        return NULL;

    default_loop_ptr = &default_loop_struct;
    return default_loop_ptr;
}
