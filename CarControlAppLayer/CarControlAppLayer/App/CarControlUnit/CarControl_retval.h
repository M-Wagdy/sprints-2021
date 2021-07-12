/*
 * CarControl_retval.h
 *
 * Created: 7/12/2021 7:04:38 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __CARCONTROL_RETVAL_H__
#define __CARCONTROL_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../STD_TYPES.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t CAR_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_CAR_SUCCESS                 (CAR_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a car control init function
* had an error in it.
*/
#define           E_CAR_INIT_ERROR              (CAR_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a car control update function
* had an invalid state.
*/
#define           E_CAR_INVALID_ERROR           (CAR_ERROR_state_t)( 2 )

#endif /* __CARCONTROL_RETVAL_H__ */