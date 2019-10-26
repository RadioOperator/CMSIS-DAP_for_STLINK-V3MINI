/**
  ******************************************************************************
  * @file    STLINK-V3MINI_BSP.h
  * @author  RadioOperator
  * @brief   STLINK-V3MINI Board Support Package
  *          LED GPIO initialize
  *          DAP GPIO initialize
  * @version V1.0
  * @date    2019-10-10
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STLINK_V3MINI_BSP_H
#define STLINK_V3MINI_BSP_H

 /* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"


// Debug Port I/O Pins for STM32F723, matched with STLINK-V3MINI board

//SWCLK/TCK input pin           PB2 input
#define PIN_SWCLK_TCK_I_PORT    GPIOB
#define PIN_SWCLK_TCK_I_BIT     GPIO_PIN_2

// SWCLK/TCK Pin                PH6 output
#define PIN_SWCLK_TCK_O_PORT    GPIOH
#define PIN_SWCLK_TCK_O_BIT     GPIO_PIN_6

// SWDIO/TMS Pin input          PH7 input
#define PIN_SWDIO_TMS_I_PORT    GPIOH
#define PIN_SWDIO_TMS_I_BIT     GPIO_PIN_7

// SWDIO Output Enable Pin      PF9 output
#define PIN_SWDIO_TMS_O_PORT    GPIOF
#define PIN_SWDIO_TMS_O_BIT     GPIO_PIN_9

// TDI Pin                      PA1 input
#define PIN_TDI_I_PORT          GPIOA
#define PIN_TDI_I_BIT           GPIO_PIN_1

// TDI Pin                      PF8 output
#define PIN_TDI_O_PORT          GPIOF
#define PIN_TDI_O_BIT           GPIO_PIN_8

// TDO Pin                      PD2, input, UART5_RX
#define PIN_TDO_PORT            GPIOD
#define PIN_TDO_BIT             GPIO_PIN_2

// nTRST Pin                    Not available
#define PIN_nTRST_PORT
#define PIN_nTRST_BIT

// nRESET Pin                   PA6 output
#define PIN_nRESET_PORT         GPIOA
#define PIN_nRESET_BIT          GPIO_PIN_6

// nRESET Output Enable Pin     Not available
#define PIN_nRESET_OE_PORT      
#define PIN_nRESET_OE_BIT       


// Debug Unit LEDs

// Connected LED                PA10 - High, RED
#define LED_CONNECTED_PORT      GPIOA
#define LED_CONNECTED_BIT       GPIO_PIN_10

// Target Running LED           PA10 - Low,  GREEN
#define LED_RUNNING_PORT        GPIOA
#define LED_RUNNING_BIT         GPIO_PIN_10


void BSP_GPIO_Init(void);

typedef enum
{
  LED_STANDBY,     //GRN:RED = 15:1, Standby mode, 1=125ms
  LED_DEBUG_PAUSE, //GRN:RED = RED, Target board Pause mode, RED only.
  LED_DEBUG_RUN,   //GRN:RED = 4:4, Target board running mode, slow blink.
  LED_VCP_RUN,     //GRN:RED = 1:1, VCP data transfering, fast blink, active at Standby mode only.
  
} LED_Mode_t;

extern LED_Mode_t LED_Mode;

int Init_LED_Timer (void);

void vResetTarget(uint32_t bit);

void vDelayMS(uint32_t ms);

#endif //#ifndef STLINK_V3MINI_BSP_H
