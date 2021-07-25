/*
 * Terminal_retval.h
 *
 * Created: 7/24/2021 5:40:09 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TERMINAL_RETVAL_H__
#define __TERMINAL_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t TERMINAL_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_TERMINAL_SUCCESS            (TERMINAL_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function
* got an invalid channel number.
*/
#define           E_TERMINAL_INVALID_CH_NO      (TERMINAL_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function
* from UART driver returned an error.
*/
#define           E_TERMINAL_UART_ERROR         (TERMINAL_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that a function
* got an uninitialized pointer.
*/
#define           E_TERMINAL_NULL_PTR           (TERMINAL_ERROR_state_t)( 3 )

#endif /* __TERMINAL_RETVAL_H__ */