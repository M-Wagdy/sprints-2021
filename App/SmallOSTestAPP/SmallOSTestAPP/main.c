/*
 * SmallOSTestAPP.c
 *
 * Created: 8/28/2021 3:18:37 PM
 * Author : Mohamed Wagdy
 */ 

#include "SOS.h"
#include "LED.h"

STR_TaskHandler_t LED_1_Handler;

void LED_1_Toggle(void);
void LED_2_Toggle(void);
void LED_3_Toggle(void);

void LED_1_Toggle(void)
{
   LED_Toggle(LED_CH_1);
   for(volatile uint8_t x = 0; x<255;x++)
   {
      for(volatile uint8_t y =0; y<10;y++);
   }
   while(1)
   {
      
   }
}

void LED_2_Toggle(void)
{
   LED_Toggle(LED_CH_2);
   SOS_SuspendTask(&LED_1_Handler);
}

void LED_3_Toggle(void)
{
   LED_Toggle(LED_CH_3);
   SOS_UnsuspendTask(&LED_1_Handler);
}

int main(void)
{
   LED_Init();
   
   SOS_Init();
   
   SOS_CreateTask(LED_1_Toggle, 0, 1, &LED_1_Handler);
   SOS_CreateTask(LED_2_Toggle, 1, 5, NULL_PTR);
   SOS_CreateTask(LED_3_Toggle, 1, 8, NULL_PTR);
   
   SOS_Run();
   
   while(1)
   {
      /* If stuck in it then the scheduler returned unsuspectingly. */
   }
}

