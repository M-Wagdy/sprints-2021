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
#define HIGH      (uint8_t)(1)
#define LOW       (uint8_t)(0)
#define NOT_INIT  (uint8_t)(0)
#define INIT      (uint8_t)(1)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_is_Timer_init = NOT_INIT;

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
   
}
