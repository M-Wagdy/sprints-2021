/*
 * Timer.c
 *
 * Created: 7/8/2021 1:55:33 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Timer.h"

/*- LOCAL MACROS
------------------------------------------*/
#define LOW                (uint8_t)( 0 )
#define HIGH               (uint8_t)( 1 )
#define NOT_INIT           (uint8_t)( 0 )
#define INIT               (uint8_t)( 1 )
#define CLK_BITS           (uint8_t)( 0x07 )
#define CLK_MODE_BITS      (uint8_t)( 0x48 )
#define INTERRUPT_BITS     (uint8_t)( 0x03 )
#define TIMER_0_INT_BITS   (uint8_t)( 0 )
#define TIMER_2_INT_BITS   (uint8_t)( 6 )

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_IsTimerInit = NOT_INIT;

void static (*gaptr_callback[TIMERS_NUMBER]) (void);

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function configures all Timers.
*
* @param [in]  configurations -  array containing the configurations for all timers.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_init(const STR_TIMER_config_t * configurations)
{
   /* pointer to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerControl = NULL_PTR;
   /* variable to carry the required timer interrupt shift bits value. */
   uint8_t u8_IntShiftBits;
   
   /* check if timers are initialized before. */
   if(INIT == gu8_IsTimerInit)
   {
      return E_TIMER_INIT_BEFORE;
   }
   /* check if configurations is a null pointer. */
   else if(NULL_PTR == configurations)
   {
      return E_TIMER_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* loops through the configuration array to initialize all timers. */
   for(uint8_t i = 0; i<TIMERS_NUMBER; i++)
   {
      /* sets the registers pointers according to the required timer. */
      switch(configurations[i].timer_no)
      {
         case TIMER_0:
            ptr_TimerControl = &TIMER_0_CONTROL;
            u8_IntShiftBits = TIMER_0_INT_BITS;
            break;
         case TIMER_2:
            ptr_TimerControl = &TIMER_2_CONTROL;
            u8_IntShiftBits = TIMER_2_INT_BITS;
            break;
         default:
            return E_INVALID_TIMER_NUMBER;
      }
      
      /* clear the previous clock */
      *ptr_TimerControl &= ~(CLK_BITS);
      
      /* clear mode bits */
      *ptr_TimerControl &= ~(CLK_MODE_BITS);
      /* sets the desired mode */
      *ptr_TimerControl |= configurations[i].mode;
      
      /* clears interrupt status */
      TIMER_INT_MASK &= ~(INTERRUPT_BITS);
      /* enable timer interrupt */
      TIMER_INT_MASK |= (configurations[i].interrupt_mode << u8_IntShiftBits);
   }
   
   /* set global variable to INIT. */
   gu8_IsTimerInit = INIT;
   /* return success message. */
   return E_TIMER_SUCCESS;
}

/**
* @brief: This function starts a given timer with the given ticks to count.
*
* @param [in]  timer_no -  timer number to start.
* @param [in]  ticks    -  number of ticks that the timer counts.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_start(uint8_t timer_no, uint64_t ticks)
{
   /* pointers to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerControl = NULL_PTR;
   volatile uint8_t * ptr_TimerData = NULL_PTR;
   
   /* check if timers are not initialized before. */
   if(NOT_INIT == gu8_IsTimerInit)
   {
      return E_TIMER_NOT_INIT;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(timer_no)
   {
      case TIMER_0:
         ptr_TimerControl = &TIMER_0_CONTROL;
         ptr_TimerData = &TIMER_0_DATA;
         break;
      case TIMER_2:
         ptr_TimerControl = &TIMER_2_CONTROL;
         ptr_TimerData = &TIMER_2_DATA;
         break;
      default:
         return E_INVALID_TIMER_NUMBER;
   }
   /* set timer ticks */
   *ptr_TimerData = (uint8_t)ticks;
   
   /* starts clock at 1 MHZ */
   *ptr_TimerControl |= CLK_1_KHZ;
   
   /* return success message. */
   return E_TIMER_SUCCESS;
}

/**
* @brief: This function returns value of the timer counter.
*
* @param [in]  timer_no -  timer number to read.
* @param [out] value    -  pointer to the variable to save the timer counter value in it.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_read(uint8_t timer_no, void * value)
{
   /* pointers to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerData = NULL_PTR;
   
   /* check if timers are not initialized before. */
   if(NOT_INIT == gu8_IsTimerInit)
   {
      return E_TIMER_NOT_INIT;
   }
   else if(NULL_PTR == value)
   {
      return E_TIMER_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(timer_no)
   {
      case TIMER_0:
         ptr_TimerData = &TIMER_0_DATA;
         break;
      case TIMER_2:
         ptr_TimerData = &TIMER_2_DATA;
         break;
      default:
         return E_INVALID_TIMER_NUMBER;
   }
   *(uint8_t * )value = *ptr_TimerData;
   
   /* return success message. */
   return E_TIMER_SUCCESS;
}

/**
* @brief: This function sets the timer ticks.
*
* @param [in]  timer_no -  timer number to set.
* @param [in]  value    -  number of ticks that the timer counts.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_set(uint8_t timer_no, uint64_t value)
{
   /* pointers to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerData = NULL_PTR;
   
   /* check if timers are not initialized before. */
   if(NOT_INIT == gu8_IsTimerInit)
   {
      return E_TIMER_NOT_INIT;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(timer_no)
   {
      case TIMER_0:
         ptr_TimerData = &TIMER_0_DATA;
         break;
      case TIMER_2:
         ptr_TimerData = &TIMER_2_DATA;
         break;
      default:
         return E_INVALID_TIMER_NUMBER;
   }
   
   *ptr_TimerData = value;
   
   /* return success message. */
   return E_TIMER_SUCCESS;
}

/**
* @brief: This function checks if a flag was raised for a given timer.
*
* @param [in]  timer_no -  timer number to check.
* @param [out] status   -  pointer to the variable to save the timer status in it.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_checkStatus(uint8_t timer_no, uint8_t * status)
{
   /* variable to carry the required timer interrupt shift bits value. */
   uint8_t u8_IntShiftBits;
   
   /* check if timers are not initialized before. */
   if(NOT_INIT == gu8_IsTimerInit)
   {
      return E_TIMER_NOT_INIT;
   }
   else if(NULL_PTR == status)
   {
      return E_TIMER_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(timer_no)
   {
      case TIMER_0:
         u8_IntShiftBits = TIMER_0_INT_BITS;
         break;
      case TIMER_2:
         u8_IntShiftBits = TIMER_2_INT_BITS;
         break;
      default:
         return E_INVALID_TIMER_NUMBER;
   }
   
   if( TIMER_INT_FLAG & (TIMER_OVERFLOW_FLAG << u8_IntShiftBits) )
   {
      *status = TIMER_OVERFLOW_FLAG;
      TIMER_INT_FLAG |= (TIMER_OVERFLOW_FLAG << u8_IntShiftBits);
   }
   else if(TIMER_INT_FLAG & (TIMER_COMPARE_FLAG << u8_IntShiftBits))
   {
      *status = TIMER_COMPARE_FLAG;
      TIMER_INT_FLAG |= (TIMER_COMPARE_FLAG << u8_IntShiftBits);
   }
   else
   {
      *status = TIMER_NOT_FINISHED;
   }
   
   /* return success message. */
   return E_TIMER_SUCCESS;
}

/**
* @brief: This function stops a timer.
*
* @param [in]  timer_no -  timer number to stop.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_stop(uint8_t timer_no)
{
   /* pointers to carry the required timer registers address. */
   volatile uint8_t * ptr_TimerControl = NULL_PTR;
   
   /* check if timers are not initialized before. */
   if(NOT_INIT == gu8_IsTimerInit)
   {
      return E_TIMER_NOT_INIT;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(timer_no)
   {
      case TIMER_0:
         ptr_TimerControl = &TIMER_0_CONTROL;
         break;
      case TIMER_2:
         ptr_TimerControl = &TIMER_2_CONTROL;
         break;
      default:
         return E_INVALID_TIMER_NUMBER;
   }
   
   /* clear the timer clock */
   *ptr_TimerControl &= ~(CLK_BITS);
   
   /* return success message. */
   return E_TIMER_SUCCESS;
}

/**
* @brief: This function sets callback function.
*
* @param [in]  timer_no -  timer number.
* @param [in]  ptr      -  pointer to the callback function.
*
* @return function error state.
*/
TIMER_ERROR_state_t TIMER_callback(uint8_t timer_no, void (*ptr) (void))
{
   /* check if timers are not initialized before. */
   if(NULL_PTR == ptr)
   {
      return E_TIMER_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the registers pointers according to the required timer. */
   switch(timer_no)
   {
      case TIMER_0:
         break;
      case TIMER_2:
         break;
      default:
         return E_INVALID_TIMER_NUMBER;
   }
   
   gaptr_callback[timer_no] = ptr;
   
   /* return success message. */
   return E_TIMER_SUCCESS;
}
