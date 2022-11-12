#ifdef CONFIG_EVM_MODULE_EVENT
#include "evm_module.h"

#include "FreeRTOS.h"
#include "queue.h"

#define QUEUE_LENGTH 0xFF
#define ITEM_SIZE sizeof(evm_eventbus_t)

static StaticQueue_t xStaticQueue = {0};
static QueueHandle_t xQueue = {0};
static uint8_t ucQueueStorageArea[ QUEUE_LENGTH * ITEM_SIZE ];

void evm_eventbus_init(void) {
    if (!xQueue) {
        xQueue = xQueueCreateStatic( QUEUE_LENGTH,
                                 ITEM_SIZE,
                                 ucQueueStorageArea,
                                 &xStaticQueue );
    }
}
int evm_eventbus_set(evm_eventbus_t* event) {
    if (xQueue == NULL)
        return 1;
    return xQueueSendFromISR(xQueue, event, NULL) == pdTRUE ? 0 : 1;
}

int evm_eventbus_get(evm_eventbus_t* event) {
    if (xQueue == NULL)
        return 1;
    return xQueueReceive(xQueue, event, 10) == pdTRUE ? 0 : 1;
}

#endif
