/*
 * Timer_retval.h
 *
 * Created: 7/8/2021 1:54:24 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TIMER_RETVAL_H__
#define __TIMER_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../../Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t TIMER_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_TIMER_SUCCESS               (TIMER_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that the Timer initialization function
* already ran before.
*/
#define           E_TIMER_INIT_BEFORE           (TIMER_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a Timer function
* was called before the init function.
*/
#define           E_TIMER_NOT_INIT              (TIMER_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that a Timer function
* got an uninitialized pointer.
*/
#define           E_TIMER_NULL_PTR              (TIMER_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a Timer function
* got an invalid timer number.
*/
#define           E_INVALID_TIMER_NUMBER        (TIMER_ERROR_state_t)( 4 )

#endif /* __TIMER_RETVAL_H__ */