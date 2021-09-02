/*
 * UART_retval.h
 *
 * Created: 7/13/2021 2:53:17 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __UART_RETVAL_H__
#define __UART_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t UART_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_UART_SUCCESS             (UART_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that the receive function
* got a frame error.
*/
#define           E_UART_FRAME_ERROR         (UART_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that the receive function
* got a parity error.
*/
#define           E_UART_PARITY_ERROR        (UART_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that the receive function
* got an over run error.
*/
#define           E_OVER_RUN_ERROR           (UART_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a function
* got an uninitialized pointer.
*/
#define           E_UART_NULL_PTR            (UART_ERROR_state_t)( 4 )

/**
* @brief: This return value indicate that the init function
* got invalid baud rate value.
*/
#define           E_UART_INVALID_BAUD_RATE   (UART_ERROR_state_t)( 5 )

/**
* @brief: This return value indicate that a function
* got invalid channel number.
*/
#define           E_UART_INVALID_CH          (UART_ERROR_state_t)( 6 )

/**
* @brief: This return value indicate that a function
* got invalid interrupt type.
*/
#define           E_UART_INVALID_INT_TYPE    (UART_ERROR_state_t)( 7 )

#endif /* __UART_RETVAL_H__ */