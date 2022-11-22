/**
 * @file lv_port_indev_templ.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "lvgl.h"
#include "stm32l4r9i_discovery_ts.h"
#include "mfxstm32l152.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
static TS_StateTypeDef  TS_State;
/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;
lv_indev_t * indev_mouse;
lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
lv_indev_t * indev_button;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    touchpad_init();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/
__IO FlagStatus MfxItOccurred = RESET;
__IO uint32_t TouchEvent = 0;

/*Initialize your touchpad*/
static void touchpad_init(void)
{
    BSP_TS_Init(390, 390);
	BSP_TS_ITConfig();
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == MFX_INT_PIN)
  {

    MfxItOccurred = SET;
	  
  }
  /* Check if interrupt comes Joystick SEL */
  else if(GPIO_Pin == SEL_JOY_PIN)
  {

  }
  else
  {
    /* Unexpected case */
  }
}

void EXTI1_IRQHandler(void)
{

  HAL_GPIO_EXTI_IRQHandler(MFX_INT_PIN);
}

#define MFX_IRQ_PENDING_GPIO    0x01
#define MFX_IRQ_PENDING_IDD     0x02
#define MFX_IRQ_PENDING_ERROR   0x04
#define MFX_IRQ_PENDING_TS_DET  0x08
#define MFX_IRQ_PENDING_TS_NE   0x10
#define MFX_IRQ_PENDING_TS_TH   0x20
#define MFX_IRQ_PENDING_TS_FULL 0x40
#define MFX_IRQ_PENDING_TS_OVF  0x80

__IO uint32_t errorSrc = 0;
__IO uint32_t errorMsg = 0;
void Mfx_Event(void)
{
  uint32_t irqPending;

  /* Reset joystick state */

  irqPending = MFX_IO_Read(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_PENDING);

  /* GPIO IT from MFX */
  if(irqPending & MFX_IRQ_PENDING_GPIO)
  {
    uint32_t JoystickStatus;
    uint32_t statusGpio = BSP_IO_ITGetStatus(RIGHT_JOY_PIN | LEFT_JOY_PIN | UP_JOY_PIN | DOWN_JOY_PIN | TS_INT_PIN | SD_DETECT_PIN);

    TouchEvent =  statusGpio & TS_INT_PIN;

    JoystickStatus = statusGpio & (RIGHT_JOY_PIN | LEFT_JOY_PIN | UP_JOY_PIN | DOWN_JOY_PIN);

    /* Insert a little delay to avoid debounce */
    HAL_Delay(1);

    /* Clear IO Expander IT */
    BSP_IO_ITClear(statusGpio);
  }
  if(irqPending & MFX_IRQ_PENDING_ERROR)
  {
    errorSrc = MFX_IO_Read(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_ERROR_SRC);
    errorMsg = MFX_IO_Read(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_ERROR_MSG);
  }

  /* Ack all IRQ pending except GPIO if any */
  irqPending &= ~MFX_IRQ_PENDING_GPIO;
  if(irqPending)
  {
    MFX_IO_Write(IO_I2C_ADDRESS, MFXSTM32L152_REG_ADR_IRQ_ACK, irqPending);
  }

  MfxItOccurred = RESET;

  /* Re-enable MFX interrupt */
  HAL_NVIC_EnableIRQ(MFX_INT_EXTI_IRQn);
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    int16_t x, y;	
	if(MfxItOccurred == SET)
    {
        Mfx_Event();
		if(TouchEvent != 0){
			BSP_TS_GetState(&TS_State);
			if(TS_State.touchDetected){
				data->state = LV_INDEV_STATE_PR;
				x = TS_State.touchX[0];
				y = TS_State.touchY[0];	
			} else {
				x = -1;y = -1;
				data->state = LV_INDEV_STATE_REL;
			}
			TouchEvent = 0;
		}
	}
	 else {
		x = -1;y = -1;
		data->state = LV_INDEV_STATE_REL;
	}
    data->point.x = x;
    data->point.y = y;
    return;
}