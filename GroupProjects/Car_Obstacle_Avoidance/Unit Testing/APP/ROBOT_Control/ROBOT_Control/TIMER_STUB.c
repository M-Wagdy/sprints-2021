/*
 * TIMER.c
 *
 * Created: 8/9/2021 12:04:01 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "TIMER_STUB.h"

/*- LOCAL MACROS
------------------------------------------*/
#define  LOW                        (uint8_t)( 0 )
#define  HIGH                       (uint8_t)( 1 )
#define  CLK_BITS                   (uint8_t)( 0x07 )
#define  CLK_MODE_BITS              (uint8_t)( 0x48 )
#define  INTERRUPT_BITS             (uint8_t)( 0x03 )
#define  TIMER_0_INT_BITS           (uint8_t)( 0 )
#define  TIMER_1_INT_BITS           (uint8_t)( 3 )
#define  TIMER_2_INT_BITS           (uint8_t)( 6 )

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function delays a given microseconds.
*
* @param [in]  TIM_channel -  timer channel number to check.
* @param [out] TIM_Delay   -  Time to delay in microseconds.
*
* @return function error state.
*/
ERROR_STATE_t TIM_DelayUs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay)
{
   return ERROR_OK;            
}

/**
* @brief: This function delays a given milliseconds.
*
* @param [in]  TIM_channel -  timer channel number to check.
* @param [out] TIM_Delay   -  Time to delay in milliseconds.
*
* @return function error state.
*/
ERROR_STATE_t TIM_DelayMs(TIM_CH_t TIM_channel, TIM_Delay_t TIM_Delay)
{
   return ERROR_OK;
}