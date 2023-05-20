#include "evm_port_timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#define FREERTOS_TIMER_COUNT 32
static evm_port_timer_t* timers[FREERTOS_TIMER_COUNT] = {0};

static int nextTimerSlot() {
    for (int i = 0; i < FREERTOS_TIMER_COUNT; i++)
    {
        if (timers[i] == NULL) {
            return i;
        }
    }
    return -1;
}

static void _timer_callback(TimerHandle_t xTimer) {
    rtos_msg_t msg;
    evm_port_timer_t *timer = (evm_port_timer_t*) pvTimerGetTimerID(xTimer);
    msg.handler = timer->func;
    msg.ptr = timer;
    msg.arg1 = 0;
    msg.arg2 = 0;
    int re = evm_port_msgbus_put(&msg, 0);
}

static int timer_handler(evm_t *e, void* ptr) {
    evm_port_timer_t *timer = (evm_port_timer_t *)ptr;
    if (timer->repeat == 0) {
        evm_port_timer_stop(timer);
        evm_free(timer);
    }
    else if (timer->repeat > 0) {
        timer->repeat --;
    }
    evm_call_free(e, timer->callback, EVM_UNDEFINED, 0, NULL);
    return 3;
}

int evm_port_timer_start(evm_port_timer_t *timer) {
    TimerHandle_t os_timer;
    int timerIndex;
    timerIndex = nextTimerSlot();
    if (timerIndex < 0) {
        return 1;
    }
    timer->func = &timer_handler;
    os_timer = xTimerCreate("luat_timer", timer->timeout / portTICK_RATE_MS, timer->repeat, timer, _timer_callback);
    if (!os_timer) {
        return -1;
    }
    timers[timerIndex] = timer;

    timer->os_timer = os_timer;
    int re = xTimerStart(os_timer, 0);
    if (re != pdPASS) {
        xTimerDelete(os_timer, 0);
        timers[timerIndex] = 0;
    }
    return re == pdPASS ? 0 : -1;

}

int evm_port_timer_stop(evm_port_timer_t *timer) {
    if (!timer)
        return 1;
    for (size_t i = 0; i < FREERTOS_TIMER_COUNT; i++)
    {
        if (timers[i] == timer) {
            timers[i] = NULL;
            break;
        }
    }
    xTimerStop((TimerHandle_t)timer->os_timer, 10);
    xTimerDelete((TimerHandle_t)timer->os_timer, 10);
    return 0;
}
