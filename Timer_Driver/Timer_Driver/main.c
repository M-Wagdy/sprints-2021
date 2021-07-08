/*
 * Timer_Driver.c
 *
 * Created: 7/8/2021 1:55:18 PM
 * Author : Mohamed Wagdy
 */ 

#include <assert.h>
#include "Mcal/Timer/Timer.h"

/*- LOCAL MACROS
------------------------------------------*/
#define PORTA_DATA      (*((volatile uint8_t *) (0x3B)))
#define PORTA_DIR       (*((volatile uint8_t *) (0x3A)))
#define RED_LED_TIMER   TIMER_0
#define RED_LED_PIN     (uint8_t)(0x01)
#define RED_LED_TIME    (uint8_t)(100)
#define GREEN_LED_TIMER TIMER_2
#define GREEN_LED_PIN   (uint8_t)(0x02)
#define GREEN_LED_TIME  (uint8_t)(0)

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* variable containing all timers configurations */
extern const STR_TIMER_config_t gastr_TIMER_configurations;

int main(void)
{
   /* set green and red pins to output pins */
   PORTA_DIR |= (RED_LED_PIN|GREEN_LED_PIN);
   
   TIMER_ERROR_state_t Timer_error_state;
   /* initialize timers */
   Timer_error_state = TIMER_init(&gastr_TIMER_configurations);
   
   if(E_TIMER_SUCCESS != Timer_error_state)
   {
      /* super loop for debugging */
      while(1){}
   }
   
   /* start green led timer */
   Timer_error_state = TIMER_start(GREEN_LED_TIMER, GREEN_LED_TIME);
   /* start red led timer */
   Timer_error_state |= TIMER_start(RED_LED_TIMER, RED_LED_TIME);
   if(E_TIMER_SUCCESS != Timer_error_state)
   {
      /* super loop for debugging */
      while(1){}
   }
   
   while(1)
   {
      uint8_t timer_status;
      
      /* check timer status of the red led */
      TIMER_checkStatus(RED_LED_TIMER, &timer_status);
      /* toggles pin if timer overflowed */
      if(TIMER_OVERFLOW_FLAG == timer_status)
      {
         PORTA_DATA ^= RED_LED_PIN;
      }
      
      /* check timer status of the green led */
      TIMER_checkStatus(GREEN_LED_TIMER, &timer_status);
      /* toggles pin if timer overflowed */
      if(TIMER_OVERFLOW_FLAG == timer_status)
      {
         PORTA_DATA ^= GREEN_LED_PIN;
      }
   }
}

