/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device:CDC
 * Copyright (c) 2004-2019 Arm Limited (or its affiliates). All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    USBD_User_CDC_ACM_UART_0.c
 * Purpose: USB Device Communication Device Class (CDC)
 *          Abstract Control Model (ACM) USB <-> UART Bridge User module
 * Rev.:    V1.0.7
 *----------------------------------------------------------------------------*/
/**
 * \addtogroup usbd_cdcFunctions
 *
 * USBD_User_CDC_ACM_UART_0.c implements the application specific
 * functionality of the CDC ACM class and is used to demonstrate a USB <-> UART
 * bridge. All data received on USB is transmitted on UART and all data
 * received on UART is transmitted on USB.
 *
 * Details of operation:
 *   UART -> USB:
 *     Initial reception on UART is started after the USB Host sets line coding
 *     with SetLineCoding command. Having received a full UART buffer, any
 *     new reception is restarted on the same buffer. Any data received on
 *     the UART is sent over USB using the CDC0_ACM_UART_to_USB_Thread thread.
 *   USB -> UART:
 *     While the UART transmit is not busy, data transmission on the UART is
 *     started in the USBD_CDC0_ACM_DataReceived callback as soon as data is
 *     received on the USB. Further data received on USB is transmitted on
 *     UART in the UART callback routine until there is no more data available.
 *     In this case, the next UART transmit is restarted from the
 *     USBD_CDC0_ACM_DataReceived callback as soon as new data is received
 *     on the USB.
 *
 * The following constants in this module affect the module functionality:
 *
 *  - UART_PORT:        specifies UART Port
 *      default value:  0 (=UART0)
 *  - UART_BUFFER_SIZE: specifies UART data Buffer Size
 *      default value:  512
 *
 * Notes:
 *   If the USB is slower than the UART, data can get lost. This may happen
 *   when USB is pausing during data reception because of the USB Host being
 *   too loaded with other tasks and not polling the Bulk IN Endpoint often
 *   enough (up to 2 seconds of gap in polling Bulk IN Endpoint may occur).
 *   This problem can be solved by using a large enough UART buffer to
 *   compensate up to a few seconds of received UART data or by using UART
 *   flow control.
 *   If the device that receives the UART data (usually a PC) is too loaded
 *   with other tasks it can also loose UART data. This problem can only be
 *   solved by using UART flow control.
 *
 *   This file has to be adapted in case of UART flow control usage.
 */
 
 
//! [code_USBD_User_CDC_ACM]
 
#include <stdio.h>
 
#include "rl_usb.h"
 
#if defined(RTE_CMSIS_RTOS2)
  #include "cmsis_os2.h"
#if defined(RTE_CMSIS_RTOS2_RTX5)
  #include "rtx_os.h"
#endif
#endif
#if defined(RTE_CMSIS_RTOS)
  #include "cmsis_os.h"
#endif

#include "Driver_USART.h"
 
// UART Configuration, radiooperator ------------------------------------------

#include "STLINK_V3MINI_BSP.h"
#define  UART_PORT              6         // UART Port number, 
#define  UART_BUFFER_SIZE      (2048)     // UART Buffer Size
 
//-----------------------------------------------------------------------------
 
#define _UART_Driver_(n)        Driver_USART##n
#define  UART_Driver_(n)       _UART_Driver_(n)
extern   ARM_DRIVER_USART       UART_Driver_(UART_PORT);
#define  ptrUART              (&UART_Driver_(UART_PORT))
 
// External functions
#ifdef   USB_CMSIS_RTOS
extern   void                   CDC0_ACM_UART_to_USB_Thread (void const *arg);
#endif
 
// Local Variables
static            uint8_t       uart_rx_buf[UART_BUFFER_SIZE];
static            uint8_t       uart_tx_buf[UART_BUFFER_SIZE];
 
static   volatile int32_t       uart_rx_cnt         =   0;
static   volatile int32_t       usb_tx_cnt          =   0;
 
static   void                  *cdc_acm_bridge_tid  =   0U;
static   CDC_LINE_CODING        cdc_acm_line_coding = { 0U, 0U, 0U, 0U };

// Called when UART has transmitted or received requested number of bytes.
// \param[in]   event         UART event
//               - ARM_USART_EVENT_SEND_COMPLETE:    all requested data was sent
//               - ARM_USART_EVENT_RECEIVE_COMPLETE: all requested data was received
static void UART_Callback (uint32_t event) {
  int32_t cnt;
 
  if (event & ARM_USART_EVENT_SEND_COMPLETE) {
    // USB -> UART
    cnt = USBD_CDC_ACM_ReadData(0U, uart_tx_buf, UART_BUFFER_SIZE);
    if (cnt > 0) {
      ptrUART->Send(uart_tx_buf, (uint32_t)(cnt));
    }
  }
 
  if (event & ARM_USART_EVENT_RECEIVE_COMPLETE) {
    // UART data received, restart new reception
    uart_rx_cnt += UART_BUFFER_SIZE;
    ptrUART->Receive(uart_rx_buf, UART_BUFFER_SIZE);
  }
  
  //LED handling, radiooperator
  if (LED_Mode == LED_STANDBY)
  {
    LED_Mode = LED_VCP_RUN;
  }
}
 
// Thread: Sends data received on UART to USB
// \param[in]     arg           not used.
#ifdef USB_CMSIS_RTOS2
__NO_RETURN static void CDC0_ACM_UART_to_USB_Thread (void *arg) {
#else
__NO_RETURN        void CDC0_ACM_UART_to_USB_Thread (void const *arg) {
#endif
  int32_t cnt, cnt_to_wrap;
 
  (void)(arg);
 
  while (1) {
    // UART - > USB
    if (ptrUART->GetStatus().rx_busy != 0U) {
      cnt  = uart_rx_cnt;
      cnt += ptrUART->GetRxCount();
      cnt -= usb_tx_cnt;
      if (cnt >= UART_BUFFER_SIZE) {
        // Dump data received on UART if USB is not consuming fast enough
        usb_tx_cnt += cnt;
        cnt = 0U;
      }
      if (cnt > 0) {
        cnt_to_wrap = (int32_t)(UART_BUFFER_SIZE - ((uint32_t)usb_tx_cnt & (UART_BUFFER_SIZE - 1)));
        if (cnt > cnt_to_wrap) {
          cnt = cnt_to_wrap;
        }
        cnt = USBD_CDC_ACM_WriteData(0U, (uart_rx_buf + ((uint32_t)usb_tx_cnt & (UART_BUFFER_SIZE - 1))), cnt);
        if (cnt > 0) {
          usb_tx_cnt += cnt;
        }
      }
    }
    osDelay(10U);
  }
}
#ifdef USB_CMSIS_RTOS2
#ifdef USB_CMSIS_RTOS2_RTX5
static osRtxThread_t        cdc0_acm_uart_to_usb_thread_cb_mem               __SECTION(.bss.os.thread.cb);
static uint64_t             cdc0_acm_uart_to_usb_thread_stack_mem[512U / 8U] __SECTION(.bss.os.thread.stack);
#endif
static const osThreadAttr_t cdc0_acm_uart_to_usb_thread_attr = {
  "CDC0_ACM_UART_to_USB_Thread",
  0U,
#ifdef USB_CMSIS_RTOS2_RTX5
 &cdc0_acm_uart_to_usb_thread_cb_mem,
  sizeof(osRtxThread_t),
 &cdc0_acm_uart_to_usb_thread_stack_mem[0],
#else
  NULL,
  0U,
  NULL,
#endif
  512U,
  osPriorityNormal,
  0U,
  0U
};
#else
extern const osThreadDef_t os_thread_def_CDC0_ACM_UART_to_USB_Thread;
osThreadDef (CDC0_ACM_UART_to_USB_Thread, osPriorityNormal, 1U, 0U);
#endif
 
 
// CDC ACM Callbacks -----------------------------------------------------------
 
// Called when new data was received from the USB Host.
// \param[in]   len           number of bytes available to read.
void USBD_CDC0_ACM_DataReceived (uint32_t len) {
  int32_t cnt;
 
  (void)(len);
 
  if (ptrUART->GetStatus().tx_busy == 0U) {
    // Start USB -> UART
    cnt = USBD_CDC_ACM_ReadData(0U, uart_tx_buf, UART_BUFFER_SIZE);
    if (cnt > 0) {
      ptrUART->Send(uart_tx_buf, (uint32_t)(cnt));
    }
  }
}
 
// Called during USBD_Initialize to initialize the USB CDC class instance (ACM).
void USBD_CDC0_ACM_Initialize (void) {
  ptrUART->Initialize   (UART_Callback);
  ptrUART->PowerControl (ARM_POWER_FULL);
 
#ifdef USB_CMSIS_RTOS2
  cdc_acm_bridge_tid = osThreadNew (CDC0_ACM_UART_to_USB_Thread, NULL, &cdc0_acm_uart_to_usb_thread_attr);
#else
  cdc_acm_bridge_tid = osThreadCreate (osThread (CDC0_ACM_UART_to_USB_Thread), NULL);
#endif
}
 
 
// Called during USBD_Uninitialize to de-initialize the USB CDC class instance (ACM).
void USBD_CDC0_ACM_Uninitialize (void) {
 
  if (osThreadTerminate (cdc_acm_bridge_tid) == osOK) {
    cdc_acm_bridge_tid = NULL;
  }
 
  ptrUART->Control      (ARM_USART_ABORT_RECEIVE, 0U);
  ptrUART->PowerControl (ARM_POWER_OFF);
  ptrUART->Uninitialize ();
}
 
 
// Called upon USB Bus Reset Event.
void USBD_CDC0_ACM_Reset (void) {
  ptrUART->Control      (ARM_USART_ABORT_SEND,    0U);
  ptrUART->Control      (ARM_USART_ABORT_RECEIVE, 0U);
}
 
 
// Called upon USB Host request to change communication settings.
// \param[in]   line_coding   pointer to CDC_LINE_CODING structure.
// \return      true          set line coding request processed.
// \return      false         set line coding request not supported or not processed.
bool USBD_CDC0_ACM_SetLineCoding (const CDC_LINE_CODING *line_coding) {
  uint32_t data_bits = 0U, parity = 0U, stop_bits = 0U;
  int32_t  status;
 
  ptrUART->Control (ARM_USART_ABORT_SEND,    0U);
  ptrUART->Control (ARM_USART_ABORT_RECEIVE, 0U);
  ptrUART->Control (ARM_USART_CONTROL_TX,    0U);
  ptrUART->Control (ARM_USART_CONTROL_RX,    0U);
 
  switch (line_coding->bCharFormat) {
    case 0:                             // 1 Stop bit
      stop_bits = ARM_USART_STOP_BITS_1;
      break;
    case 1:                             // 1.5 Stop bits
      stop_bits = ARM_USART_STOP_BITS_1_5;
      break;
    case 2:                             // 2 Stop bits
      stop_bits = ARM_USART_STOP_BITS_2;
  }
 
  switch (line_coding->bParityType) {
    case 0:                             // None
      parity = ARM_USART_PARITY_NONE;
      break;
    case 1:                             // Odd
      parity = ARM_USART_PARITY_ODD;
      break;
    case 2:                             // Even
      parity = ARM_USART_PARITY_EVEN;
      break;
    default:
      return false;
  }
 
  switch (line_coding->bDataBits) {
    case 5:
      data_bits = ARM_USART_DATA_BITS_5;
      break;
    case 6:
      data_bits = ARM_USART_DATA_BITS_6;
      break;
    case 7:
      data_bits = ARM_USART_DATA_BITS_7;
      break;
    case 8:
      data_bits = ARM_USART_DATA_BITS_8;
      break;
    default:
      return false;
  }
 
  status = ptrUART->Control(ARM_USART_MODE_ASYNCHRONOUS  |
                            data_bits                    |
                            parity                       |
                            stop_bits                    |
                            ARM_USART_FLOW_CONTROL_NONE  ,
                            line_coding->dwDTERate       );

  if (status != ARM_DRIVER_OK) {
    return false;
  }
 
  // Store requested settings to local variable
  cdc_acm_line_coding = *line_coding;
 
  uart_rx_cnt = 0;
  usb_tx_cnt  = 0;
 
  ptrUART->Control (ARM_USART_CONTROL_TX, 1U);
  ptrUART->Control (ARM_USART_CONTROL_RX, 1U);
 
  ptrUART->Receive (uart_rx_buf, UART_BUFFER_SIZE);
 
  return true;
}
 
 
// Called upon USB Host request to retrieve communication settings.
// \param[out]  line_coding   pointer to CDC_LINE_CODING structure.
// \return      true          get line coding request processed.
// \return      false         get line coding request not supported or not processed.
bool USBD_CDC0_ACM_GetLineCoding (CDC_LINE_CODING *line_coding) {
 
  // Load settings from ones stored on USBD_CDC0_ACM_SetLineCoding callback
  *line_coding = cdc_acm_line_coding;
 
  return true;
}
 
 
// Called upon USB Host request to set control line states.
// \param [in]  state         control line settings bitmap.
//                - bit 0: DTR state
//                - bit 1: RTS state
// \return      true          set control line state request processed.
// \return      false         set control line state request not supported or not processed.
bool USBD_CDC0_ACM_SetControlLineState (uint16_t state) {
  // Add code for set control line state
 
  (void)(state);
 
  return true;
}
 
//! [code_USBD_User_CDC_ACM]
