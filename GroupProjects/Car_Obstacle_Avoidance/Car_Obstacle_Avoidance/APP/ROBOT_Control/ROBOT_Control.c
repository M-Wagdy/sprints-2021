/*
 * ROBOT_Control.c
 *
 * Created: 8/12/2021 4:25:04 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "ROBOT_Control.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MOTOR_START_STATE           (uint8_t)(2)
#define MOTOR_FORWARD_STATE         (uint8_t)(3)
#define MOTOR_BACKWARD_STATE        (uint8_t)(4)
#define MOTOR_ROTATE_STATE          (uint8_t)(5)
#define MOTOR_DELAY_STATE           (uint8_t)(6)

#define LCD_REFRESH_DELAY           (uint8_t)(30)

#define DISTANCE_RANGE_UPPER_VALUE  (uint8_t)(52)
#define DISTANCE_RANGE_LOWER_VALUE  (uint8_t)(48)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static int8_t * gau8_DistanceMessage = (int8_t *)"Distance: ";
static int8_t * gau8_CarNameMessage = (int8_t *)"   Magnum Car";
static int8_t * gau8_FreeSpaces = (int8_t *)"    ";

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initializes the Robot Car.
*
* @return function error state.
*/
ERROR_STATE_t RC_Init(void)
{
   ERROR_STATE_t LCD_Init_RetVal = OperationStarted;
   
   USONIC_Init();
   STEERING_Init();
   while(LCD_Init_RetVal != OperationSuccess)
   {
      LCD_Init_RetVal = LCD_Init();
   }
   
   while(LCD_SendCommand(LCD_CURS_Position0) != OperationSuccess);
   while(LCD_SendCommand(LCD_CLR) != OperationSuccess);
   LCD_SendString(gau8_DistanceMessage);
   while(LCD_SendCommand(LCD_CURS_LINE2) != OperationSuccess);
   LCD_SendString(gau8_CarNameMessage);
   return ERROR_OK;
}

/**
* @brief: This function Updates the Robot Car State.
*
* @return function error state.
*/
ERROR_STATE_t RC_Update(void)
{
   static uint8_t State = OperationStarted;
   static uint8_t u8_Counter = 0;
   static double64_t d64_distance = 0;
   ERROR_STATE_t USonic_State = OperationStarted;
   
   switch(State)
   {
      case OperationStarted:
         USonic_State = USONIC_GetDistance(&d64_distance);
         if(USonic_State == ERROR_OK)
         {
            u8_Counter++;
            if(LCD_REFRESH_DELAY <= u8_Counter)
            {
               u8_Counter = 0;
               while(LCD_SendCommand(LCD_CURS_Position10) != OperationSuccess);
               LCD_SendString(gau8_FreeSpaces);
               while(LCD_SendCommand(LCD_CURS_Position10) != OperationSuccess);
               LCD_SendNumber((uint32_t)(d64_distance));
               while(TIM_DelayUs(TIMER_2, 500) != ERROR_OK);
            }
            State = MOTOR_START_STATE;
         }
         break;
      case MOTOR_START_STATE:
         if(d64_distance > DISTANCE_RANGE_UPPER_VALUE)
         {
            State = MOTOR_FORWARD_STATE;
         }
         else if (d64_distance < DISTANCE_RANGE_LOWER_VALUE)
         {
            State = MOTOR_BACKWARD_STATE;
         }
         else
         {
            State = MOTOR_ROTATE_STATE;
         }
         break;
      case MOTOR_FORWARD_STATE:
         STEERING_Move(STEERING_FORWARD);
         State = OperationStarted;
         break;
      case MOTOR_BACKWARD_STATE:
         STEERING_Move(STEERING_BACKWARD);
         State = OperationStarted;
         break;
      case MOTOR_ROTATE_STATE:
         STEERING_Move(STEERING_RIGHT);
         TIM_DelayMs(TIMER_2, 500);
         State = MOTOR_DELAY_STATE;
         break;
      case MOTOR_DELAY_STATE:
         if(ERROR_OK == TIM_DelayMs(TIMER_2, 500))
         {
            State = OperationStarted;
         }
      default:
         break;
   }
   
   return ERROR_OK;         
}