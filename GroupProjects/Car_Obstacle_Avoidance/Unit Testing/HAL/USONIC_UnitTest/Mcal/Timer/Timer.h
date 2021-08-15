/*
 * Timer.h
 *
 * Created: 8/9/2021 12:04:11 PM
 *  Author: Mohamed Wagdy
 */


#ifndef __TIMER_H__
#define __TIMER_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_TYPES.h"

#include "Timer_retval.h"


/*- MACROS -------------------------------------------------*/
#define  TIMER_OVERFLOW_FLAG     (uint8_t)( 0 )
#define  TIMER_COMPARE_FLAG      (uint8_t)( 1 )
#define  TIMER_0                 (uint8_t)( 0 )

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t TIMER_ERROR_state_t;

typedef uint8_t TIM_CH_t;
typedef uint32_t TIM_Delay_t;
typedef uint16_t TIM_Preload_t;


/*- FUNCTION DECLARATIONS ----------------------------------*/


/* Function that uses a timer to delay useconds. */
TIMER_ERROR_state_t TIM_DelayUs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay);



#endif /* __TIMER_H__ */
