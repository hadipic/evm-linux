/**
  ******************************************************************************
  * @file    DSI/DSI_CmdMode_SingleBuffer/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to configure and use LCD DSI to display
  *          an RGB image (390x390) using the STM32L4xx HAL API and BSP.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>
#include "stm32l4r9i_discovery.h"
#include "stm32l4r9i_discovery_psram.h"
#include "stm32l4r9i_discovery_ts.h"
#include "evm.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_port_fs.h"


/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static uint8_t isInitialized = 0;
UART_HandleTypeDef usart1;

int fputc(int ch, FILE *f)
{
	uint8_t c = ch;
    HAL_UART_Transmit(&usart1, &c, 1, 2);
    return ch;
}

char __platform_getchar(void){
    uint8_t ch;
	HAL_UART_Receive(&usart1, &ch, 1, 0xffff);
    return ch;
}

static void SD_Initialize(void)
{
  if (isInitialized == 0)
  {
    if (BSP_SD_Init() == MSD_OK)
    {
      isInitialized = 1;
    }

    BSP_SD_ITConfig();
  }
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Error Handler.
  * @retval None
  */
static void Error_Handler(void)
{
  BSP_LED_On(LED1);
  while(1) { ; } /* Blocking on error */
}

void SysTick_Handler(void)
{
  HAL_IncTick();
  lv_tick_inc(1);
}
FATFS fs;
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	
	
	HAL_Init();

	/* Configure the System clock to have a frequency of 120 MHz */
	SystemClock_Config();
	
	usart1.Init.BaudRate = 115200;
	usart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	usart1.Init.Mode = UART_MODE_TX_RX;
	usart1.Init.Parity = UART_PARITY_NONE;
	usart1.Init.StopBits = UART_STOPBITS_1;
	usart1.Init.WordLength = UART_WORDLENGTH_8B;
	

	/* Initialize used Leds */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_COM_Init(COM1, &usart1);
	  
	lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_port_fs_init();
	
	evm_t *e = evm_init();
    evm_run_shell(e);
	/* Infinite loop */
	while(1)
	{
	  HAL_Delay(1);
	  lv_task_handler();
	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 120000000
  *            HCLK(Hz)                       = 120000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 60
  *            PLL_Q                          = 2
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable voltage range 1 boost mode for frequency above 80 Mhz */
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  __HAL_RCC_PWR_CLK_DISABLE();

  /* Enable MSI Oscillator and activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* To avoid undershoot due to maximum frequency, select PLL as system clock source */
  /* with AHB prescaler divider 2 as first step */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* AHB prescaler divider at 1 as second step */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
