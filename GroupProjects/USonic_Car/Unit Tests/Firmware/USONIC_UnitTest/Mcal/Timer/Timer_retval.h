/*
 * Timer_retval.h
 *
 * Created: 8/9/2021 12:05:17 PM
 *  Author: Mohamed Wagdy
 */


#ifndef __TIMER_RETVAL_H__
#define __TIMER_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_TYPES.h"
/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           TIMER_E_SUCCESS               (TIMER_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a Timer function
* got an uninitialized pointer.
*/
#define           TIMER_E_NULL_PTR              (TIMER_ERROR_state_t)( -1 )

/**
* @brief: This return value indicate that a Timer function
* got an invalid timer number.
*/
#define           TIMER_E_INVALID_CH_NUM        (TIMER_ERROR_state_t)( -2 )

/**
* @brief: This return value indicate that a Timer function
* didn't finish it's functionality yet.
*/
#define           TIMER_E_PENDING               (TIMER_ERROR_state_t)( -3 )

/**
* @brief: This return value indicate that a Timer Delay function
* got unsupported prescaler value
*/
#define           TIMER_E_UNSUPPORTED_PRESCALE  (TIMER_ERROR_state_t)( -4 )

#endif /* __TIMER_RETVAL_H__ */
