/*
 * TIMER.c
 *
 * Created: 8/9/2021 12:04:01 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "TIMER.h"

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
#define  FULL_8_BITS                (uint8_t)( 255 )

#define  SECOND_TO_MICROSECOND      (uint8_t)( 1000000 )
#define  MILLISECOND_TO_MICROSECOND (uint8_t)( 1000 )

#define  TIMER_OVERFLOW_FACTOR      (uint8_t)( 256 )

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static ERROR_STATE_t GetFreqPrescaleRatio(TIM_CH_t TIM_channel, float32_t * Ratio); 

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_TIMER_config_t gastr_Timer_Config[TIMERS_NUMBER];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function configures all Timers.
*
* @param [in]  TIM_channel -  Timer channel number.
* @param [in]  Ratio       -  Ratio between CPU clock frequency and Prescalar values.
*
* @return function error state.
*/
static ERROR_STATE_t GetFreqPrescaleRatio(TIM_CH_t TIM_channel, float32_t * Ratio)
{
   /* For Timer 0 and 1 */
   if(TIMER_0 == TIM_channel || TIMER_1 == TIM_channel)
   {
      switch(gastr_Timer_Config[TIM_channel].u8_prescale)
      {
         case CLK_NO_PRESCALE:
            *Ratio = 1.0 * SECOND_TO_MICROSECOND / F_CPU;
            break;
         case CLK_8_PRESCALE:
            *Ratio = 8.0 * SECOND_TO_MICROSECOND / F_CPU;
            break;
         case CLK_64_PRESCALE:
            *Ratio = 64.0 * SECOND_TO_MICROSECOND / F_CPU;
            break;
         case CLK_256_PRESCALE:
            *Ratio = 256.0 * SECOND_TO_MICROSECOND / F_CPU;
            break;
         case CLK_1024_PRESCALE:
            *Ratio = 1024.0 * SECOND_TO_MICROSECOND / F_CPU;
            break;
         default:
         return TIMER_E_UNSUPPORTED_PRESCALE;
      }
   }
   /* For Timer 2 */
   else if(TIMER_2 == TIM_channel)
   {
      switch(gastr_Timer_Config[TIM_channel].u8_prescale)
      {
         case T2_CLK_NO_PRESCALE:
         *Ratio = 1.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         case T2_CLK_8_PRESCALE:
         *Ratio = 8.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         case T2_CLK_32_PRESCALE:
         *Ratio = 32.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         case T2_CLK_64_PRESCALE:
         *Ratio = 64.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         case T2_CLK_128_PRESCALE:
         *Ratio = 128.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         case T2_CLK_256_PRESCALE:
         *Ratio = 256.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         case T2_CLK_1024_PRESCALE:
         *Ratio = 1024.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
         default:
         return TIMER_E_UNSUPPORTED_PRESCALE;
      }
   }
   
   return ERROR_OK;
}

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function configures all Timers.
*
* @param [in]  TIM_channel -  Timer channel number.
*
* @return function error state.
*/
ERROR_STATE_t TIM_Init(TIM_CH_t TIM_channel)
{
   switch(TIM_channel)
   {
      case TIMER_0:
         /* Initialize Mode */
         TCCR0 = gastr_Timer_Config[TIM_channel].u8_mode;
         /* Initialize Interrupt Mode */
         TIMSK &= ~(INTERRUPT_BITS << TIMER_0_INT_BITS);
         TIMSK |= (gastr_Timer_Config[TIM_channel].u8_interrupt_mode << TIMER_0_INT_BITS);
         break;
      case TIMER_1:
         /* Initialize Mode */
         TCCR1B = gastr_Timer_Config[TIM_channel].u8_mode;
         /* Initialize Interrupt Mode */
         TIMSK &= ~(INTERRUPT_BITS << TIMER_1_INT_BITS);
         TIMSK |= (gastr_Timer_Config[TIM_channel].u8_interrupt_mode << TIMER_1_INT_BITS);
         break;
      case TIMER_2:
         /* Initialize Mode */
         TCCR2 = gastr_Timer_Config[TIM_channel].u8_mode;
         /* Initialize Interrupt Mode */
         TIMSK &= ~(INTERRUPT_BITS << TIMER_2_INT_BITS);
         TIMSK |= (gastr_Timer_Config[TIM_channel].u8_interrupt_mode << TIMER_2_INT_BITS);
         break;
      default:
         return TIMER_E_INVALID_CH_NUM;
   }
   
   /* return success message. */
   return ERROR_OK;
}

/**
* @brief: This function starts a given timer with the given ticks to count.
*
* @param [in]  TIM_channel -  timer channel number to start.
* @param [in]  PreloadVal  -  number of ticks that the timer counts.
*
* @return function error state.
*/
ERROR_STATE_t TIM_Start(TIM_CH_t TIM_channel, TIM_Preload_t PreloadVal)
{
   /* pointers to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerControl = NULL_PTR;
   volatile uint8_t * ptr_TimerData = NULL_PTR;
   
   /* sets the registers pointers according to the required timer. */
   switch(TIM_channel)
   {
      case TIMER_0:
         ptr_TimerControl = &TCCR0;
         ptr_TimerData = &TCNT0;
         break;
      case TIMER_1:
         ptr_TimerControl = &TCCR1B;
         ptr_TimerData = &TCNT1;
         break;
      case TIMER_2:
         ptr_TimerControl = &TCCR2;
         ptr_TimerData = &TCNT2;
         break;
      default:
         return TIMER_E_INVALID_CH_NUM;
   }
   /* set timer ticks */
   *ptr_TimerData = PreloadVal;
   
   /* starts clock */
   *ptr_TimerControl |= gastr_Timer_Config[TIM_channel].u8_prescale;
   
   /* return success message. */
   return ERROR_OK;
}

/**
* @brief: This function stops a timer.
*
* @param [in]  TIM_channel -  timer channel number to stop.
*
* @return function error state.
*/
ERROR_STATE_t TIM_Stop(TIM_CH_t TIM_channel)
{
   /* pointers to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerControl = NULL_PTR;
   
   /* sets the registers pointers according to the required timer. */
   switch(TIM_channel)
   {
      case TIMER_0:
         ptr_TimerControl = &TCCR0;
         break;
      case TIMER_1:
         ptr_TimerControl = &TCCR1B;
         break;
      case TIMER_2:
         ptr_TimerControl = &TCCR2;
         break;
      default:
         return TIMER_E_INVALID_CH_NUM;
   }
   
   /* clear the timer clock */
   *ptr_TimerControl &= ~(CLK_BITS);
   
   /* return success message. */
   return ERROR_OK;
}

/**
* @brief: This function checks if a flag was raised for a given timer.
*
* @param [in]  TIM_channel -  timer channel number to check.
* @param [out] FlagStatus  -  pointer to the variable to save the timer status in it.
*
* @return function error state.
*/
ERROR_STATE_t TIM_GetStatus(TIM_CH_t TIM_channel, uint8_t* FlagStatus)
{
   if(NULL_PTR == FlagStatus)
   {
      return TIMER_E_NULL_PTR;
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(TIM_channel)
   {
      case TIMER_0:
         if(gastr_Timer_Config[TIM_channel].u8_mode == NORMAL_MODE)
         {
            if( TIFR & TIMER_0_OVERFLOW_FLAG )
            {
               *FlagStatus = TIMER_OVERFLOW_FLAG;
               TIFR |= TIMER_0_OVERFLOW_FLAG;
            }
            else
            {
               return TIMER_E_PENDING;
            }
         }
         else if(gastr_Timer_Config[TIM_channel].u8_mode == COMPARE_MATCH_MODE)
         {
            if(TIFR & TIMER_0_COMPARE_FLAG)
            {
               *FlagStatus = TIMER_COMPARE_FLAG;
               TIFR |= TIMER_0_COMPARE_FLAG;
            }
            else
            {
               return TIMER_E_PENDING;
            }
         }
         break;
      case TIMER_1:
         if(gastr_Timer_Config[TIM_channel].u8_mode == NORMAL_MODE)
         {
            if( TIFR & TIMER_1_OVERFLOW_FLAG )
            {
               *FlagStatus = TIMER_OVERFLOW_FLAG;
               TIFR |= TIMER_1_OVERFLOW_FLAG;
            }
            else
            {
               return TIMER_E_PENDING;
            }
         }
         else if(gastr_Timer_Config[TIM_channel].u8_mode == COMPARE_MATCH_MODE)
         {
            if(TIFR & TIMER_1A_COMPARE_FLAG)
            {
               *FlagStatus = TIMER_COMPARE_FLAG;
               TIFR |= TIMER_1A_COMPARE_FLAG;
            }
            else if(TIFR & TIMER_1B_COMPARE_FLAG)
            {
               *FlagStatus = TIMER_COMPARE_FLAG;
               TIFR |= TIMER_1B_COMPARE_FLAG;
            }
            else
            {
               return TIMER_E_PENDING;
            }
         }
         break;
      case TIMER_2:
         if(gastr_Timer_Config[TIM_channel].u8_mode == NORMAL_MODE)
         {
            if( TIFR & TIMER_2_OVERFLOW_FLAG )
            {
               *FlagStatus = TIMER_OVERFLOW_FLAG;
               TIFR |= TIMER_2_OVERFLOW_FLAG;
            }
            else
            {
               return TIMER_E_PENDING;
            }
         }
         else if(gastr_Timer_Config[TIM_channel].u8_mode == COMPARE_MATCH_MODE)
         {
            if(TIFR & TIMER_2_COMPARE_FLAG)
            {
               *FlagStatus = TIMER_COMPARE_FLAG;
               TIFR |= TIMER_2_COMPARE_FLAG;
            }
            else
            {
               return TIMER_E_PENDING;
            }
         }
         
         break;
      default:
         return TIMER_E_INVALID_CH_NUM;
   }
   
   /* return success message. */
   return ERROR_OK;
}

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
   /* Make sure not invalid timer channel */
   if(TIM_channel >= INVALID_TIMER_CH)
   {
      return TIMER_E_INVALID_CH_NUM;
   }
   
   /* Static variables used */
   static uint32_t u32_Overflows = 0;
   static uint8_t u8_OverflowsComplete = LOW;
   static uint8_t u8_Remindar = 0;
   static Enu_DelayStateMachine Enu_State = Ready;
   ERROR_STATE_t Timer_state;
   
   /* Ready state */
   if(Ready == Enu_State)
   {
      /* Calculate needed frequency Ratio */
      float32_t f32_FreqRatio;
      Timer_state = GetFreqPrescaleRatio(TIM_channel, &f32_FreqRatio);
      if(TIMER_E_UNSUPPORTED_PRESCALE == Timer_state)
      {
         return TIMER_E_UNSUPPORTED_PRESCALE;
      }
      
      if(f32_FreqRatio != 0)
      {
         TIM_Delay /= f32_FreqRatio;
      }
      
      /* Calculate how many overflows needed */
      u32_Overflows = TIM_Delay / TIMER_OVERFLOW_FACTOR;
      u8_Remindar = TIM_Delay % TIMER_OVERFLOW_FACTOR;
      
      if(u32_Overflows == 0)
      {
         u8_OverflowsComplete = HIGH;
         TIM_Start(TIM_channel, u8_Remindar);
      }
      else
      {
         /* Start timer with full register */
         TIM_Start(TIM_channel, FULL_8_BITS);
      }     
      /* Change to timer pending state */ 
      Enu_State = Pending;
      return TIMER_E_PENDING;
   }
   /* Pending state */
   else if(Pending == Enu_State)
   {
      uint8_t u8_FlagState;
      /* Check timer state */
      Timer_state = TIM_GetStatus(TIM_channel, &u8_FlagState);
      if(Timer_state == TIMER_OVERFLOW_FLAG)
      {
         /* If all overflows are finished and reminder. */
         if(u8_OverflowsComplete == HIGH)
         {
            /* Return to ready state */
            Enu_State = Ready;
            u8_OverflowsComplete = LOW;
            /* return success message. */
            return ERROR_OK;
         }
         
         /* Decrement overflows number */
         u32_Overflows--;
         /* If all overflows finished raise a flag so the next overflow will be the remainder's overflow */
         if(u32_Overflows == 0)
         {
            u8_OverflowsComplete = HIGH;
            TIM_Start(TIM_channel, u8_Remindar);
         }
         else
         {
            /* Start timer with full register */
            TIM_Start(TIM_channel, FULL_8_BITS);
         }
         
         return TIMER_E_PENDING;
      }         
   }
   
   return ERROR_NOK;            
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
   /* Make sure not invalid timer channel */
   if(TIM_channel >= INVALID_TIMER_CH)
   {
      return TIMER_E_INVALID_CH_NUM;
   }
   
   /* Static variables used */
   static uint32_t u32_Overflows = 0;
   static uint8_t u8_OverflowsComplete = LOW;
   static uint8_t u8_Remindar = 0;
   static Enu_DelayStateMachine Enu_State = Ready;
   ERROR_STATE_t Timer_state;
   
   /* Ready state */
   if(Ready == Enu_State)
   {
      /* Calculate needer frequency Ratio */
      float32_t f32_FreqRatio;
      Timer_state = GetFreqPrescaleRatio(TIM_channel, &f32_FreqRatio);
      if(TIMER_E_UNSUPPORTED_PRESCALE == Timer_state)
      {
         return TIMER_E_UNSUPPORTED_PRESCALE;
      }
      
      if(f32_FreqRatio != 0)
      {
         TIM_Delay /= f32_FreqRatio;
      }
      
      /* Calculate how many overflows needed */
      u32_Overflows = TIM_Delay*MILLISECOND_TO_MICROSECOND / TIMER_OVERFLOW_FACTOR;
      u8_Remindar = TIM_Delay*MILLISECOND_TO_MICROSECOND % TIMER_OVERFLOW_FACTOR;
      
      if(u32_Overflows == 0)
      {
         u8_OverflowsComplete = HIGH;
         TIM_Start(TIM_channel, u8_Remindar);
      }
      else
      {
         /* Start timer with full register */
         TIM_Start(TIM_channel, FULL_8_BITS);
      }
      /* Change to timer pending state */
      Enu_State= Pending;
      return TIMER_E_PENDING;
   }
   /* Pending state */
   else if(Pending == Enu_State)
   {
      uint8_t u8_FlagState;
      /* Check timer state */
      Timer_state= TIM_GetStatus(TIM_channel, &u8_FlagState);
      if(Timer_state == TIMER_OVERFLOW_FLAG)
      {
         /* If all overflows are finished and reminder. */
         if(u8_OverflowsComplete == HIGH)
         {
            /* Return to ready state */
            Enu_State = Ready;
            u8_OverflowsComplete = LOW;
            /* return success message. */
            return ERROR_OK;
         }
         
         /* Decrement overflows number */
         u32_Overflows--;
         /* If all overflows finished raise a flag so the next overflow will be the remainder's overflow */
         if(u32_Overflows == 0)
         {
            u8_OverflowsComplete = HIGH;
            TIM_Start(TIM_channel, u8_Remindar);
         }
         else
         {
            /* Start timer with full register */
            TIM_Start(TIM_channel, FULL_8_BITS);
         }
         
         return TIMER_E_PENDING;
      }
   }
   
   return ERROR_NOK;
}