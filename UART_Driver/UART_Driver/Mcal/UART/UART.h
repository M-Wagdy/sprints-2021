/*
 * UART.h
 *
 * Created: 7/13/2021 2:54:45 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __UART_H__
#define __UART_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"
#include "UART_Registers.h"
#include "UART_retval.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize UART. */
UART_ERROR_state_t UART_init(uint16_t baudRate);

/* Function that writes character to transmit buffer. */
UART_ERROR_state_t UART_sendChar(uint8_t character);

/* Function that reads character from receive buffer. */
UART_ERROR_state_t UART_readChar(uint8_t * character);

/* Function that writes characters in transmit buffer in order. */
UART_ERROR_state_t UART_sendString(uint8_t * string);

/* Function that receives characters from receive buffer in order. */
UART_ERROR_state_t UART_readString(uint8_t * string);

#endif /* __UART_H__ */