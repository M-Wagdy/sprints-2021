/*
 * USonic_Car.c
 *
 * Created: 8/9/2021 11:56:36 AM
 * Author : Mohamed Wagdy
 */ 

#include "Firmware/USONIC/usonic.h"
#include "Firmware/LCD/LCD.h"
#include "Firmware/Motor/Motor.h"

#define MOTOR_Start             2
#define MOTOR_Forward           3
#define MOTOR_Backward          4
#define MOTOR_Rotate            5

#define MOTOR_DUTY              (50)

int main(void)
{
   static uint8_t State = OperationStarted;
   static uint8_t u8_Counter = 0;
   
   uint8_t LCD_Init_RetVal = OperationStarted;
   USONIC_ERROR_state_t USonic_State = OperationStarted;
   double64_t distance = 0;
   
   /* App Init */
   USONIC_Init();
   MOTOR_init();
   while(LCD_Init_RetVal != OperationSuccess)
   {
      LCD_Init_RetVal = LCD_Init();
   }
   /* So don't keep changing PWM */
   MOTOR_start(MOTOR1, MOTOR_DUTY, MOTOR_FORWARD);
   MOTOR_start(MOTOR2, MOTOR_DUTY, MOTOR_FORWARD);
   
   while(1)
   {
      #if 0
      static uint8_t x = 0;
      if (1!=x)
      {
         LCD_Init_RetVal = LCD_Init();
         if (LCD_Init_RetVal == OperationSuccess)
         {
            x=1;
         }
      }
      #endif
      /* App Update */
      switch(State)
      {
         case OperationStarted:
            USonic_State = USONIC_GetDistance(&distance);
            if(USonic_State == OK)
            {
               u8_Counter++;
               if(15 <= u8_Counter)
               {
                  u8_Counter = 0;
                  while(LCD_SendCommand(LCD_CLR) != OperationSuccess);
                  LCD_SendNumber((uint32_t)(distance));
                  while(TIM_DelayUs(TIMER_2, 500) != TIMER_E_SUCCESS);
               }
               State = MOTOR_Start;
            }
            break;
         case MOTOR_Start:
            if(distance>52)
            {
               State = MOTOR_Forward;
            }
            else if (distance<48)
            {
               State = MOTOR_Backward;
            }
            else
            {
               State = MOTOR_Rotate;
            }
            break;
         case MOTOR_Forward:
            MOTOR_Update_dir(MOTOR1, MOTOR_FORWARD);
            MOTOR_Update_dir(MOTOR2, MOTOR_FORWARD);
            State = OperationStarted;
            break;
         case MOTOR_Backward:
            MOTOR_Update_dir(MOTOR1, MOTOR_BACKWARD);
            MOTOR_Update_dir(MOTOR2, MOTOR_BACKWARD);
            State = OperationStarted;
            break;
         case MOTOR_Rotate:
            MOTOR_Update_dir(MOTOR1, MOTOR_FORWARD);
            MOTOR_Update_dir(MOTOR2, MOTOR_BACKWARD);
            State = OperationStarted;
            break;
         default:
            break;
      }
   }
   
   /*USONIC_Init();
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
         MOTOR_start(MOTOR1, 55, MOTOR_FORWARD);
         MOTOR_start(MOTOR2, 55, MOTOR_BACKWARD);
         while(TIM_DelayUs(TIMER_2, 2000000) != TIMER_E_SUCCESS);
         MOTOR_stop(MOTOR1);
         MOTOR_stop(MOTOR2);
         while(TIM_DelayUs(TIMER_2, 2000000) != TIMER_E_SUCCESS);
         / *LCD_SendCommand(LCD_CLEAR_DISPALY);
         while(TIM_DelayUs(TIMER_2, 100) != TIMER_E_SUCCESS);
         LCD_SendNumber((uint32_t)(distance));* /
      }
       / *  if(distance>=48 &&distance<=70)
         {
           * /      //   LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0));
                   // LCD_SendData('R'); 
                   // MOTOR_start(MOTOR1,MOTOR_FORWARD);
                    //MOTOR_start(MOTOR2,MOTOR_BACKWARD);
                    
        // }
      //   else{
           // MOTOR_stop(MOTOR1);
         //   MOTOR_stop(MOTOR2);
       //  }
      
   }*/
}

