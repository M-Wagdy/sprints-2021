/*
* STUB_UART.h
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/


#ifndef __STUB_UART_H__
#define __STUB_UART_H__

/*- INCLUDES -----------------------------------------------*/
#include "..\..\Infrastructure\STD_types.h"
#include "uartConfig.h"
/*UART CHANNELS*/
#define UART_1             (uint8_t)0
/*UART INTERRUPTS*/
#define RECIVE_INT         (uint8_t)0
#define TRANSMIT_INT       (uint8_t)1
#define EMPTY_BUFFERR_INT  (uint8_t)2

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

uint8_t UART_Init(uint8_t UartNumber);
uint8_t UART_EnableInterrupt(uint8_t UartNumber, uint8_t UartInterruptType);
uint8_t UART_SetCallback(uint8_t UartNumber, uint8_t UartInterruptType, Ptr_VoidFuncVoid_t Callback);
uint8_t UART_TransmitString(uint8_t UartNumber, ptr_uint8_t TxString);
uint8_t UART_ReceiveString(uint8_t UartNumber, ptr_uint8_t RxString);
uint8_t UART_GetData(uint8_t UartNumber, ptr_uint8_t RxChar);

#endif /* __STUB_UART_H__ */
