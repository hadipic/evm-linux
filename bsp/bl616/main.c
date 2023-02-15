#include <FreeRTOS.h>
#include "semphr.h"
#include "board.h"
#include "evm_module.h"

#define DBG_TAG "MAIN"
#include "log.h"

static TaskHandle_t evm_handle;

static void evm_task(void *pvParameters)
{
    evm_main("main.ts");

    while (1) {
        evm_loop();
        vTaskDelay(5);
    }

    vTaskDelete(NULL);
}

int main(void)
{
    board_init();

    configASSERT((configMAX_PRIORITIES > 4));

    LOG_I("[OS] Starting evm task...\r\n");
    xTaskCreate(evm_task, (char *)"evm_task", 512, NULL, configMAX_PRIORITIES - 2, &evm_handle);

    vTaskStartScheduler();

    while (1) {
    }
}
