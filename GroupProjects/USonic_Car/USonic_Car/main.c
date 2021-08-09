/*
 * USonic_Car.c
 *
 * Created: 8/9/2021 11:56:36 AM
 * Author : Mohamed Wagdy
 */ 

#include "Mcal/Timer/Timer.h"

#define PORTB_DATA      (*((volatile uint8_t *) (0x38)))
#define PORTB_DIR       (*((volatile uint8_t *) (0x37)))

int main(void)
{
   TIMER_ERROR_state_t state;
   TIMER_ERROR_state_t state2;
   PORTB_DIR |= 0xF0;
   PORTB_DATA |= 0xF0;
   state = TIM_Init(TIMER_2);
   if(state == TIMER_E_SUCCESS)
   {
      PORTB_DATA = 0x00;
   }
   state2 = TIM_Init(TIMER_0);
   if(state2 == TIMER_E_SUCCESS)
   {
      PORTB_DATA = 0xF0;
   }
   /* Replace with your application code */
   while (1) 
   {
      
      state = TIM_DelayMs(TIMER_2, 5000);
      if(state == TIMER_E_SUCCESS)
      {
         PORTB_DATA ^= 0x80;
      }
      state2 = TIM_DelayUs(TIMER_0, 1000000);
      if(state2 == TIMER_E_SUCCESS)
      {
         PORTB_DATA ^= 0x40;
      }
   }
}

