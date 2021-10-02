/*
 * STUB_TIMER.h
 *
 * Created: 9/2/2021 12:04:11 PM
 *  Author: Mohamed Wagdy
 */


#ifndef __STUB_TIMER_H__
#define __STUB_TIMER_H__

 /*- INCLUDES -----------------------------------------------*/
#include "STD_TYPES.h"

/*- MACROS -------------------------------------------------*/
/* Timer Channels */
#define  TIMER_0                    (uint8_t)( 0 )
#define  TIMER_1                    (uint8_t)( 1 )
#define  TIMER_2                    (uint8_t)( 2 )
#define  INVALID_TIMER_CH           (uint8_t)( 3 )

/*- ERRORS DEFINITIONS--------------------------------------*/
/**
* @brief: This return value indicate that a Timer Delay is Empty
*/
#define           TIMER_E_DELAY_EMPTY           (ERROR_STATE_t)( -5 )

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t TIM_CH_t;
typedef uint32_t TIM_Delay_t;
typedef uint16_t TIM_Preload_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that uses a timer to delay mseconds. */
ERROR_STATE_t TIM_DelayMs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay, Ptr_VoidFuncVoid_t DelayRequester);

/* Function that return delay status. */
ERROR_STATE_t TIM_DelayStatus(TIM_CH_t TIM_channel, Ptr_VoidFuncVoid_t DelayRequester);

#endif /* __STUB_TIMER_H__ */