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
    pthread_mutex_init(&loop->worker_lock, NULL);
    pthread_cond_init(&loop->worker_cond, NULL);
    loop->worker_count = 0;
    loop->watcher_count = 0;
    pthread_mutex_init(&loop->async_lock, NULL);
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    #if !(defined(__APPLE__) && defined(__MACH__))
    pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC);
    #endif
    pthread_cond_init(&loop->async_cond, &cond_attr);
    // FIXME: link error in esp-idf
    #ifndef __ESP_IDF__
    pthread_condattr_destroy(&cond_attr);
    #endif
    loop->closing_handles = NULL;
    loop->pending_handles = NULL;
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
