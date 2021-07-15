/*
 * LED_retval.h
 *
 * Created: 7/13/2021 7:48:20 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __LED_RETVAL_H__
#define __LED_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t LED_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_LED_SUCCESS           (LED_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function
* got an invalid channel number.
*/
#define           E_LED_INVALID_CH_NO     (LED_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function
* from DIO driver returned an error.
*/
#define           E_LED_DIO_ERROR         (LED_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that the init function
* was called before.
*/
#define           E_LED_INIT_BEFORE       (LED_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a function
* was called before initialization.
*/
#define           E_LED_NOT_INIT          (LED_ERROR_state_t)( 4 )

#endif /* __LED_RETVAL_H__ */