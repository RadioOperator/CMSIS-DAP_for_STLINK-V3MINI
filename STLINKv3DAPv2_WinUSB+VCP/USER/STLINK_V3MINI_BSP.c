/**
  ******************************************************************************
  * @file    STLINK-V3MINI_BSP.c
  * @author  RadioOperator
  * @brief   STLINK-V3MINI Board Support Package
  *          LED GPIO initialize
  *          DAP GPIO initialize
  * @version V1.0
  * @date    2019-09-21
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "stm32f7xx_hal.h"

#include "DAP_Config.h"
#include "DAP.h"

#include "STLINK_V3MINI_BSP.h"

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void BSP_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  
  /*Configure GPIOA pins : PA15 PA12 PA11
                           PA9 PA8 PA0 
                           PA4 PA2 PA5 
                           PA3 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_11
                          |GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_0 
                          |GPIO_PIN_4|GPIO_PIN_2|GPIO_PIN_5 
                          |GPIO_PIN_3|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIOB pins : PB8 PB5 PB4 PB3 
                           PB9 PB12 PB13 
                           PB1 PB0 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3 
                          |GPIO_PIN_9|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_10|GPIO_PIN_11;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  /*Configure GPIOC pins : PC11 PC10 PC13 PC14 
                           PC15 PC9 PC8 PC7 
                           PC6 PC0 PC1 PC2 
                           PC3 PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_7 
                          |GPIO_PIN_6|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2 
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  /*Configure GPIOD pins : PD7 PD0 PD1 PD4 
                           PD3 PD15 PD14 PD13 
                           PD12 PD11 PD10 PD9 
                           PD8 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4 
                          |GPIO_PIN_3|GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13 
                          |GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9 
                          |GPIO_PIN_8;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  /*Configure GPIOE pins : PE3 PE2 PE1 PE0 
                           PE4 PE5 PE6 PE13 
                           PE8 PE9 PE11 PE14 
                           PE7 PE10 PE12 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_13 
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_14 
                          |GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_15;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIOF pins : PF0 PF2 PF1 PF3 
                           PF4 PF7 PF6 PF5 
                           PF10 PF13 
                           PF12 PF15 PF11 PF14 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5 
                          |GPIO_PIN_10|GPIO_PIN_13 
                          |GPIO_PIN_12|GPIO_PIN_15|GPIO_PIN_11|GPIO_PIN_14;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  
  /*Configure GPIOG pins : PG13 PG15 PG12 PG11 
                           PG10 PG8 PG4 PG5
                           PG3 PG2 PG1 PG0 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15|GPIO_PIN_12|GPIO_PIN_11 
                          |GPIO_PIN_10|GPIO_PIN_8|GPIO_PIN_4 |GPIO_PIN_5
                          |GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIOH pins : PH15 PH13 PH14 PH2 
                           PH3 PH4 PH5 PH12 
                           PH11 PH10 PH8 PH9 */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_2 
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_12 
                          |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_8|GPIO_PIN_9;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
  
  /*Configure GPIO pins : PI7 PI6 PI5 PI3 
                           PI2 PI8 PI9 PI4 
                           PI1 PI10 PI11 PI0 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_3 
                          |GPIO_PIN_2|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_4 
                          |GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_0;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);


//OUTPUT pins

//PA10=Low,  Green LED on
//PA10=High, Red   LED on
  GPIO_InitStruct.Pin   = LED_CONNECTED_BIT;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LED_CONNECTED_PORT, &GPIO_InitStruct);
  
// nRESET Pin                   PA6 output
  GPIO_InitStruct.Pin   = PIN_nRESET_BIT;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_nRESET_PORT, &GPIO_InitStruct);

// SWDIO Output Enable Pin      PF9 output
  GPIO_InitStruct.Pin   = PIN_SWDIO_TMS_O_BIT;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_SWDIO_TMS_O_PORT, &GPIO_InitStruct);

// TDI Pin                      PF8 output
  GPIO_InitStruct.Pin   = PIN_TDI_O_BIT;
//  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull  = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_TDI_O_PORT, &GPIO_InitStruct);

// SWCLK/TCK Pin                PH6 output
  GPIO_InitStruct.Pin   = PIN_SWCLK_TCK_O_BIT;
//  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull  = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_SWCLK_TCK_O_PORT, &GPIO_InitStruct);


//INPUT pins

// SWCLK/TCK Pin                      PB2, input
  GPIO_InitStruct.Pin = PIN_SWCLK_TCK_I_BIT;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_SWCLK_TCK_I_PORT, &GPIO_InitStruct);
  
// TDO Pin                      PD2, UART5_RX for SWO input
  GPIO_InitStruct.Pin = PIN_TDO_BIT;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_TDO_PORT, &GPIO_InitStruct);
    
// SWDIO/TMS Pin input          PH7 input
  GPIO_InitStruct.Pin = PIN_SWDIO_TMS_I_BIT;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_SWDIO_TMS_I_PORT, &GPIO_InitStruct);
  
// TDI Pin                      PA1 input
  GPIO_InitStruct.Pin   = PIN_TDI_I_BIT;
//  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull  = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(PIN_TDI_I_PORT, &GPIO_InitStruct);
}


//=============LED Control=====================================================

#define LED_TIMER_TICK_TIME   125     //125ms

LED_Mode_t LED_Mode = LED_STANDBY;    //LED mode

static uint8_t u8counter1 = 0;        //0~0x0F counter
static uint8_t u8counter2 = 0;        //special counter for VCP

void LED_Timer_Callback (void const *arg)
{
  u8counter1++;
  u8counter1 &= 0x0F;
  
  switch (LED_Mode)
  {
    case LED_DEBUG_PAUSE:
      LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT; //RED
    break;
    
    case LED_DEBUG_RUN:
      if (u8counter1 & 0x02 ) LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT << 16;
      else                    LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT;
    break;
    
    case LED_VCP_RUN:
      if (u8counter1 & 0x01 ) LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT << 16;
      else                    LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT;
      
      if (++u8counter2 >= 3)
      {
        u8counter2 = 0;
        LED_Mode = LED_STANDBY;
      }
    break;
      
    default:  //LED_STANDBY mode
      if (u8counter1 >= 1 ) LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT << 16;
      else                  LED_CONNECTED_PORT->BSRR = LED_CONNECTED_BIT;
      LED_Mode = LED_STANDBY;
    break;
  }
}

/*----- Periodic Timer  -----*/

osTimerId_t LED_Timer_ID;                            // timer id
static uint32_t exec2;                          // argument for the timer call back function
 
// Create and Start periodic timer
int Init_LED_Timer (void) {
  osStatus_t status;                            // function return status

  exec2 = 2U;
  LED_Timer_ID = osTimerNew((osTimerFunc_t)&LED_Timer_Callback, osTimerPeriodic, &exec2, NULL);
  if (LED_Timer_ID != NULL) {  // Periodic timer created
    // start timer with periodic with interval LED_TIMER_TICK_TIME
    status = osTimerStart(LED_Timer_ID, LED_TIMER_TICK_TIME);            
    if (status != osOK) {
      return -1;
    }
  }
  return NULL;
}


//==========Soft reset + Hard reset============================================

#define PIN_SWCLK_SET PIN_SWCLK_TCK_SET
#define PIN_SWCLK_CLR PIN_SWCLK_TCK_CLR

#define RST_CLOCK_CYCLE()                \
  PIN_SWCLK_CLR();                       \
  PIN_DELAY();                           \
  PIN_SWCLK_SET();                       \
  PIN_DELAY()

#define RST_WRITE_BIT(bit)               \
  PIN_SWDIO_OUT(bit);                    \
  PIN_SWCLK_CLR();                       \
  PIN_DELAY();                           \
  PIN_SWCLK_SET();                       \
  PIN_DELAY()

#define RST_READ_BIT(bit)                \
  PIN_SWCLK_CLR();                       \
  PIN_DELAY();                           \
  bit = PIN_SWDIO_IN();                  \
  PIN_SWCLK_SET();                       \
  PIN_DELAY()

#define PIN_DELAY() PIN_DELAY_SLOW(DAP_Data.clock_delay)

uint8_t RST_Transfer(uint32_t request, uint32_t data)
{
  uint32_t ack;                                                                 \
  uint32_t bit;                                                                 \
  uint32_t val;                                                                 \
  uint32_t parity;                                                              \
  uint32_t n;                                                                   \
  \
  /* Packet Request */                                                          \
  parity = 0U;                                                                  \
  RST_WRITE_BIT(1U);                     /* Start Bit */                        \
  bit = request >> 0;                                                           \
  RST_WRITE_BIT(bit);                    /* APnDP Bit */                        \
  parity += bit;                                                                \
  bit = request >> 1;                                                           \
  RST_WRITE_BIT(bit);                    /* RnW Bit */                          \
  parity += bit;                                                                \
  bit = request >> 2;                                                           \
  RST_WRITE_BIT(bit);                    /* A2 Bit */                           \
  parity += bit;                                                                \
  bit = request >> 3;                                                           \
  RST_WRITE_BIT(bit);                    /* A3 Bit */                           \
  parity += bit;                                                                \
  RST_WRITE_BIT(parity);                 /* Parity Bit */                       \
  RST_WRITE_BIT(0U);                     /* Stop Bit */                         \
  RST_WRITE_BIT(1U);                     /* Park Bit */                         \
  \
  /* Turnaround */                                                              \
  PIN_SWDIO_OUT_DISABLE();                                                      \
  for (n = DAP_Data.swd_conf.turnaround; n; n--) {                              \
    RST_CLOCK_CYCLE();                                                          \
  }                                                                             \
  \
  /* Acknowledge response */                                                    \
  RST_READ_BIT(bit);                                                            \
  ack  = bit << 0;                                                              \
  RST_READ_BIT(bit);                                                            \
  ack |= bit << 1;                                                              \
  RST_READ_BIT(bit);                                                            \
  ack |= bit << 2;                                                              \
  \
  /* Data transfer */                                                           \
  /* Turnaround */                                                              \
  for (n = DAP_Data.swd_conf.turnaround; n; n--) {                              \
    RST_CLOCK_CYCLE();                                                          \
  }                                                                             \
  PIN_SWDIO_OUT_ENABLE();                                                       \
  /* Write data */                                                              \
  val = data;                                                                   \
  parity = 0U;                                                                  \
  for (n = 32U; n; n--) {                                                       \
    RST_WRITE_BIT(val);              /* Write WDATA[0:31] */                    \
    parity += val;                                                              \
    val >>= 1;                                                                  \
  }                                                                             \
  RST_WRITE_BIT(parity);             /* Write Parity Bit */                     \
  PIN_SWDIO_OUT_ENABLE();                                                       \
  PIN_SWDIO_OUT(1U);                                                            \
  return ((uint8_t)ack);                                                        \
}

void vResetTarget(uint32_t bit)
{
  uint32_t i;
  //soft-reset for Cortex-M
  RST_Transfer(0x00000CC5, 0xE000ED0C); //set AIRCR address
  for (i=0; i<300; i++);
  RST_Transfer(0x00000CDD, 0x05FA0007); //set RESET data
  for (i=0; i<300; i++);
  RST_Transfer(0x00000CC5, 0xE000ED0C); //repeat
  for (i=0; i<300; i++);
  RST_Transfer(0x00000CDD, 0x05FA0007);
  
  if (bit & 1) PIN_nRESET_PORT->BSRR = PIN_nRESET_BIT;
  else PIN_nRESET_PORT->BSRR = (uint32_t)PIN_nRESET_BIT << 16;
}

//=============END=============================================================
