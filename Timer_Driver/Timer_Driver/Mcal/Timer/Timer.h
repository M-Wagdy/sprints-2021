/*
 * Timer.h
 *
 * Created: 7/8/2021 1:55:58 PM
 *  Author: Mohamed Wagdy
 */ 

#ifndef __TIMER_H__
#define __TIMER_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"
#include "Timer_Registers.h"
#include "Timer_retval.h"
#include "Timer_Pbcfg.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initializes the timers */
TIMER_ERROR_state_t TIMER_init(const STR_TIMER_config_t * configurations); 

/* Function that starts a timer */
TIMER_ERROR_state_t TIMER_start(uint8_t timer_no, uint64_t ticks); 

/* Function that read a timer value */
TIMER_ERROR_state_t TIMER_read(uint8_t timer_no, void * value); 

/* Function that sets a timer value */
TIMER_ERROR_state_t TIMER_set(uint8_t timer_no, uint64_t value); 

/* Function that check if a timer raised a flag */
TIMER_ERROR_state_t TIMER_checkStatus(uint8_t timer_no, uint8_t * status);

/* Function that stops a timer. */
TIMER_ERROR_state_t TIMER_stop(uint8_t timer_no);

/* Function that sets a callback function in a global variable */
TIMER_ERROR_state_t TIMER_callback(uint8_t timer_no, void (*ptr) (void));

#endif /* __TIMER_H__ */