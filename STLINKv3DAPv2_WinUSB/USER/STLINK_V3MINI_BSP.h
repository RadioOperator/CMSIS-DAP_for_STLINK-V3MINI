/**
  ******************************************************************************
  * @file    STLINK-V3MINI_BSP.h
  * @author  RadioOperator
  * @brief   STLINK-V3MINI Board Support Package
  *          LED GPIO initialize
  *          DAP GPIO initialize
  * @version V1.0
  * @date    2019-09-21
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STLINK_V3MINI_BSP_H
#define STLINK_V3MINI_BSP_H

 /* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

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

#endif //#ifndef STLINK_V3MINI_BSP_H
