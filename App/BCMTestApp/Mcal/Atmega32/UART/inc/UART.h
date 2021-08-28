/*
 * UART.h
 *
 * Created: 7/13/2021 2:54:45 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __UART_H__
#define __UART_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "UART_Registers.h"
#include "UART_Config.h"
#include "UART_retval.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize UART. */
UART_ERROR_state_t UART_Init(uint8_t UartNumber);

/* Function that writes character to transmit buffer. */
UART_ERROR_state_t UART_TransmitChar(uint8_t UartNumber, uint8_t TxChar);

/* Function that reads character from receive buffer. */
UART_ERROR_state_t UART_ReceiveChar(uint8_t UartNumber, uint8_t * RxChar);

/* Function that writes characters in transmit buffer in order. */
UART_ERROR_state_t UART_TransmitString(uint8_t UartNumber, uint8_t * TxString);

/* Function that receives characters from receive buffer in order. */
UART_ERROR_state_t UART_ReceiveString(uint8_t UartNumber, uint8_t * RxString);

/* Function that enables UART interrupt */
UART_ERROR_state_t UART_EnableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType);

/* Function that disables UART interrupt */
UART_ERROR_state_t UART_DisableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType);

/* Function that sets interrupt callback function */
UART_ERROR_state_t UART_SetCallback(uint8_t UartNumber, uint8_t UartInterruptType, Ptr_VoidFuncVoid_t Callback);

/* Function that Flushes the receive buffer */
UART_ERROR_state_t UART_FlushReceiveBuffer(uint8_t UartNumber);

/* Function that set data in the UART data register */
UART_ERROR_state_t UART_SetData(uint8_t UartNumber,uint8_t TxChar);

/* Function that get data from the UART data register */
UART_ERROR_state_t UART_GetData(uint8_t UartNumber,uint8_t * RxChar);

#endif /* __UART_H__ */