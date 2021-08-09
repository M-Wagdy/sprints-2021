/*
 * USonic_Car.c
 *
 * Created: 8/9/2021 11:56:36 AM
 * Author : Mohamed Wagdy
 */ 

#include "Mcal/Timer/Timer.h"

#define PORTA_DATA      (*((volatile uint8_t *) (0x3B)))
#define PORTA_DIR       (*((volatile uint8_t *) (0x3A)))

int main(void)
{
   PORTA_DIR |= 0x01;
   TIM_Init(TIMER_0);
   
   /* Replace with your application code */
   while (1) 
   {
      while(TIM_DelayMs(TIMER_0, 1000) == TIMER_E_PENDING);
      PORTA_DATA ^= 0x01;
   }
}

