#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" \
                            issue*/
#include <SDL2/SDL.h>
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/mousewheel.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/lvgl.h"
#include "evm_module.h"
#include "FreeRTOS.h"
#include "task.h"

static void hal_init(void);
static int tick_thread(void* data);

char __platfrom_getChar(void){
    return (char)getchar();
}

char* getdir(const char* filepath) {
    int len = strlen(filepath);

    int i = len - 1;
    while(i >= 0) {
        char c = filepath[i];
        if (c == '/' || c == '\\') {
            break;
        }
        i--;
    }

    if (i == -1 || (i == 1 && filepath[0] == '.')) {
        char* filepath = malloc(256);
        if(getcwd(filepath, 256) == NULL) {
            return NULL;
        }
        return filepath;
    }

    char* dirname = malloc(i + 1);
    memcpy(dirname, filepath, i);
    dirname[i] = '\0';

    return dirname;
}

char* getfilename(const char* filepath) {
    int len = strlen(filepath);

    int i = len - 1;
    while(i >= 0) {
        char c = filepath[i];
        if (c == '/' || c == '\\') {
            break;
        }
        i--;
    }


    char* filename = NULL;
    if (i == -1) {
        filename = malloc(len + 1);
        memcpy(filename, filepath, len);
        filename[len] = '\0';
    } else {
        int flen = len - i;
        filename = (char *)malloc(flen + 1);
        memcpy(filename, filepath + i + 1, flen);
        filename[flen] = '\0';
    }

    return filename;
}

static char *filename;

static void _evm_main(void *args) {
    evm_main(filename);
    while (1) {
        lv_timer_handler();
        lv_task_handler();
        usleep(5 * 1000);
        evm_loop();
    }
}

int main(int argc, char** argv) {
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    if( argc < 2) {
        return 0;
    }

    char *dirname = getdir(argv[1]);
    if (dirname == NULL) {
        return 0;
    }

    filename = getfilename(argv[1]);
    if (filename == NULL) {
        return 0;
    }

    chdir(dirname);

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();

    xTaskCreate( _evm_main, "evm", 1024*16, NULL, 21, NULL );
    vTaskStartScheduler();

    return 0;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static void hal_init(void) {
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate
     * a display*/
    monitor_init();
    /* Tick init.
     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL
     * about how much time were elapsed Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);

    /*Create a display buffer*/
    static lv_disp_draw_buf_t disp_buf1;
    static lv_color_t buf1_1[SDL_HOR_RES * SDL_VER_RES];
    static lv_color_t buf1_2[SDL_HOR_RES * SDL_VER_RES];
    lv_disp_draw_buf_init(&disp_buf1, buf1_1, buf1_2, SDL_HOR_RES * SDL_VER_RES);

    /*Create a display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    disp_drv.antialiasing = 1;

    lv_disp_t* disp = lv_disp_drv_register(&disp_drv);

    lv_group_t* g = lv_group_create();
    lv_group_set_default(g);

    /* Add the mouse as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the
     * mouse position and state*/
    indev_drv_1.read_cb = mouse_read;
    lv_indev_t* mouse_indev = lv_indev_drv_register(&indev_drv_1);

    keyboard_init();
    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_2.read_cb = keyboard_read;
    lv_indev_t* kb_indev = lv_indev_drv_register(&indev_drv_2);
    lv_indev_set_group(kb_indev, g);
    mousewheel_init();
    static lv_indev_drv_t indev_drv_3;
    lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
    indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_3.read_cb = mousewheel_read;

    lv_indev_t* enc_indev = lv_indev_drv_register(&indev_drv_3);
    lv_indev_set_group(enc_indev, g);
}

/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void* data) {
    (void)data;

    while (1) {
        SDL_Delay(5);
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

//--------------------------------------------------------------------------------
// for freertos

/* When configSUPPORT_STATIC_ALLOCATION is set to 1 the application writer can
use a callback function to optionally provide the memory required by the idle
and timer tasks.  This is the stack that will be used by the timer task.  It is
declared here, as a global, so it can be checked by a test that is implemented
in a different file. */
StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

/* Notes if the trace is running or not. */
static BaseType_t xTraceRunning = pdTRUE;

void vApplicationIdleHook( void )
{
#ifdef LUA_USE_WINDOWS
    Sleep(1);
#else
    usleep(1000);
#endif
}

void vAssertCalled( unsigned long ulLine, const char * const pcFileName ) {
  printf( "ASSERT! Line %d, file %s\r\n", ulLine, pcFileName );
  exit(255);
}

void vApplicationDaemonTaskStartupHook( void )
{
    /* This function will be called once only, when the daemon task starts to
    execute	(sometimes called the timer task).  This is useful if the
    application includes initialisation code that would benefit from executing
    after the scheduler has been started. */
}
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  This function is
    provided as an example only as stack overflow checking does not function
    when running the FreeRTOS Windows port. */
    vAssertCalled( __LINE__, __FILE__ );
}

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}


/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
    size of the	heap available to pvPortMalloc() is defined by
    configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
    API function can be used to query the size of free heap space that remains
    (although it does not provide information on how the remaining heap might be
    fragmented).  See http://www.freertos.org/a00111.html for more
    information. */
    vAssertCalled( __LINE__, __FILE__ );
}

void vConfigureTimerForRunTimeStats(){}
/*-----------------------------------------------------------*/
