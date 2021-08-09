/*
 * Timer.h
 *
 * Created: 8/9/2021 12:04:11 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __TIMER_H__
#define __TIMER_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_TYPES.h"
#include "Timer_Registers.h"
#include "Timer_retval.h"
#include "Timer_Cfg.h"

/*- MACROS -------------------------------------------------*/
#define  TIMER_OVERFLOW_FLAG     (uint8_t)( 0 )
#define  TIMER_COMPARE_FLAG      (uint8_t)( 1 )

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

/* Function that initializes a timer */
TIMER_ERROR_state_t TIM_Init(TIM_CH_t TIM_channel);

/* Function that starts a timer */
TIMER_ERROR_state_t TIM_Start(TIM_CH_t TIM_channel, TIM_Preload_t PreloadVal);

/* Function that stops a timer. */
TIMER_ERROR_state_t TIM_Stop(TIM_CH_t TIM_channel);

/* Function that check if a timer raised a flag */
TIMER_ERROR_state_t TIM_GetStatus(TIM_CH_t TIM_channel, uint8_t* FlagStatus);

/* Function that uses a timer to delay useconds. */
TIMER_ERROR_state_t TIM_DelayUs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay);

/* Function that uses a timer to delay mseconds. */
TIMER_ERROR_state_t TIM_DelayMs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay);

#endif /* __TIMER_H__ */