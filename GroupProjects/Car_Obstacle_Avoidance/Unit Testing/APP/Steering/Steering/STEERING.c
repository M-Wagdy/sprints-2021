/*
 * STEERING.c
 *
 * Created: 8/12/2021 1:03:41 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "STEERING.h"

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initializes Motors of the car.
*
* @return function error state.
*/
ERROR_STATE_t STEERING_Init(void)
{
   ERROR_STATE_t MOTOR_ErrorState = ERROR_NOK;
   
   MOTOR_ErrorState = MOTOR_init();
   
   if( MOTOR_ErrorState != ERROR_OK )
   {
      return ERROR_NOK;
   }
   
   return ERROR_OK;
}

/**
* @brief: This function Moves the robot to a given direction.
*
* @param [in]  Direction -  Direction of Car to move.
*
* @return function error state.
*/
ERROR_STATE_t STEERING_Move(uint8_t Direction)
{
   if(Direction >= INVALID_STEERING)
   {
      return ERROR_NOK;
   }
   
   ERROR_STATE_t MOTOR_ErrorState = ERROR_NOK;
   
   switch(Direction)
   {
      case STEERING_FORWARD:
         MOTOR_ErrorState = MOTOR_start(MOTOR1, MOTOR_SPEED_20, MOTOR_FORWARD);
         MOTOR_ErrorState |= MOTOR_start(MOTOR2, MOTOR_SPEED_20, MOTOR_FORWARD);
         break;
      case STEERING_BACKWARD:
         MOTOR_ErrorState = MOTOR_start(MOTOR1, MOTOR_SPEED_20, MOTOR_BACKWARD);
         MOTOR_ErrorState |= MOTOR_start(MOTOR2, MOTOR_SPEED_20, MOTOR_BACKWARD);
         break;
      case STEERING_RIGHT:
         MOTOR_ErrorState = MOTOR_start(MOTOR1, MOTOR_SPEED_35, MOTOR_BACKWARD);
         MOTOR_ErrorState |= MOTOR_start(MOTOR2, MOTOR_SPEED_35, MOTOR_FORWARD);
         break;
      case STEERING_LEFT:
         MOTOR_ErrorState = MOTOR_start(MOTOR1, MOTOR_SPEED_35, MOTOR_FORWARD);
         MOTOR_ErrorState |= MOTOR_start(MOTOR2, MOTOR_SPEED_35, MOTOR_BACKWARD);
         break;
   }
   
   if( MOTOR_ErrorState != ERROR_OK )
   {
      return ERROR_NOK;
   }
   
   return ERROR_OK;
}