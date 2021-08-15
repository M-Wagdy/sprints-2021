/*
 * TIMER.h
 *
 * Created: 8/9/2021 12:04:11 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TIMER_H__
#define __TIMER_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_TYPES.h"

/*- MACROS -------------------------------------------------*/
#define  TIMER_OVERFLOW_FLAG        (uint8_t)( 0 )
#define  TIMER_COMPARE_FLAG         (uint8_t)( 1 )

/* Timer Channels */
#define  TIMER_0                    (uint8_t)( 0 )
#define  TIMER_1                    (uint8_t)( 1 )
#define  TIMER_2                    (uint8_t)( 2 )
#define  INVALID_TIMER_CH           (uint8_t)( 3 )

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that a Timer function
* got an uninitialized pointer.
*/
#define           TIMER_E_NULL_PTR              (ERROR_STATE_t)( -1 )

/**
* @brief: This return value indicate that a Timer function
* got an invalid timer number.
*/
#define           TIMER_E_INVALID_CH_NUM        (ERROR_STATE_t)( -2 )

/**
* @brief: This return value indicate that a Timer function
* didn't finish it's functionality yet.
*/
#define           TIMER_E_PENDING               (ERROR_STATE_t)( -3 )

/**
* @brief: This return value indicate that a Timer Delay function
* got unsupported prescaler value
*/
#define           TIMER_E_UNSUPPORTED_PRESCALE  (ERROR_STATE_t)( -4 )

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t TIM_CH_t;
typedef uint32_t TIM_Delay_t;
typedef uint16_t TIM_Preload_t;

/*- ENUMS --------------------------------------------------*/
typedef enum 
{
   Ready = 0,
   Pending = 1,
} Enu_DelayStateMachine; 

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that uses a timer to delay useconds. */
ERROR_STATE_t TIM_DelayUs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay);

/* Function that uses a timer to delay mseconds. */
ERROR_STATE_t TIM_DelayMs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay);

#endif /* __TIMER_H__ */
