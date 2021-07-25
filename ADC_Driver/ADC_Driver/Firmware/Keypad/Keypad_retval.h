/*
 * Keypad_retval.h
 *
 * Created: 7/25/2021 4:46:56 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __KEYPAD_RETVAL_H__
#define __KEYPAD_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t KEYPAD_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_KEYPAD_SUCCESS                    (KEYPAD_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function got an 
* uninitialized pointer.
*/
#define           E_KEYPAD_NULL_PTR                   (KEYPAD_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function got an 
* invalid channel.
*/
#define           E_KEYPAD_INVALID_CH                 (KEYPAD_ERROR_state_t)( 2 )

#endif /* __KEYPAD_RETVAL_H__ */