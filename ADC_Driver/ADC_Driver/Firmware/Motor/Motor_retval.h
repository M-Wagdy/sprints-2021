/*
 * Motor_retval.h
 *
 * Created: 7/25/2021 4:21:14 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __MOTOR_RETVAL_H__
#define __MOTOR_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t MOTOR_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_MOTOR_SUCCESS                     (MOTOR_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function got an invalid channel.
*/
#define           E_MOTOR_INVALID_CH                  (MOTOR_ERROR_state_t)( 1 )

#endif /* __MOTOR_RETVAL_H__ */