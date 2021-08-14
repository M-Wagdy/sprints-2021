/*
 * ADC_retval.h
 *
 * Created: 7/21/2021 6:22:55 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __ADC_RETVAL_H__
#define __ADC_RETVAL_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_types.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t ADC_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_ADC_SUCCESS                    (ADC_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that a function got a null pointer.
*/
#define           E_ADC_NULL_PTR                   (ADC_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that a function got an invalid ADC channel.
*/
#define           E_ADC_INVALID_CH                 (ADC_ERROR_state_t)( 2 )

/**
* @brief: This return value indicate that the initialization function
* already ran before.
*/
#define           E_ADC_INIT_BEFORE                (ADC_ERROR_state_t)( 3 )

/**
* @brief: This return value indicate that a function
* was called before the init function.
*/
#define           E_ADC_NOT_INIT                   (ADC_ERROR_state_t)( 4 )

#endif /* __ADC_RETVAL_H__ */