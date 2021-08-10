/*
 * USonic_Car.c
 *
 * Created: 8/9/2021 11:56:36 AM
 * Author : Mohamed Wagdy
 */ 

#include "Firmware/USONIC/usonic.h"
#include "Firmware/LCD_adel/LCD.h"
#include "Firmware/Motor/Motor.h"

#define PORTB_DATA      (*((volatile uint8_t *) (0x38)))
#define PORTB_DIR       (*((volatile uint8_t *) (0x37)))

int main(void)
{
   USONIC_Init();
   while(LCD_Init()!= OperationSuccess);
   //LCD_Init();
   MOTOR_init();
   double64_t distance;
   USONIC_ERROR_state_t USonic_State;
   while(1)
   {
      USonic_State = USONIC_GetDistance(&distance);
      if(OK==USonic_State)
      {
         while(LCD_SendCommand(LCD_CLR) != OperationSuccess);
         LCD_SendNumber((uint32_t)(distance));
         MOTOR_start(MOTOR1,MOTOR_FORWARD);
         MOTOR_start(MOTOR2,MOTOR_BACKWARD);
         while(TIM_DelayUs(TIMER_2, 500000) != TIMER_E_SUCCESS);
         MOTOR_stop(MOTOR1);
         MOTOR_stop(MOTOR2);
         while(TIM_DelayUs(TIMER_2, 500000) != TIMER_E_SUCCESS);
         /*LCD_SendCommand(LCD_CLEAR_DISPALY);
         while(TIM_DelayUs(TIMER_2, 100) != TIMER_E_SUCCESS);
         LCD_SendNumber((uint32_t)(distance));*/
      }
       /*  if(distance>=48 &&distance<=70)
         {
           */      //   LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0));
                   // LCD_SendData('R'); 
                   // MOTOR_start(MOTOR1,MOTOR_FORWARD);
                    //MOTOR_start(MOTOR2,MOTOR_BACKWARD);
                    
        // }
      //   else{
           // MOTOR_stop(MOTOR1);
         //   MOTOR_stop(MOTOR2);
       //  }
      
   }
}

