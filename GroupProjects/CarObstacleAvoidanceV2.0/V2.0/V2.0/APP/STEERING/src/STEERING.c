/*
 * STEERING.c
 *
 * Created: 8/16/2021 04:46:48 PM
 *  Author: Ahmed Essam
 */ 
/*- INCLUDES----------------------------------------------*/
#include "STEERING.h"
/*- LOCAL FUNCTIONS PROTOTYPES----------------------------*/
static ERROR_STATE_t STEERING_Init(void);
/*- GLOBAL STATIC VARIABLES-------------------------------*/
static uint16_t u16_speed;
static uint8_t u8_dir;
/*- LOCAL FUNCTIONS IMPLEMENTATION------------------------*/
static ERROR_STATE_t STEERING_Init(void)
{
   ERROR_STATE_t MOTOR_ErrorState = ERROR_NOK;
   /*Initlaize the motors*/
   MOTOR_ErrorState = MOTOR_init();
      
   return MOTOR_ErrorState;
}
/*- APIs IMPLEMENTATION-----------------------------------*/
/**
* @brief: This function Moves the robot to a given direction.
*/
extern void STEERING_MainFunction(void)
{
	static ERROR_STATE_t u8_InitFlag=NOT_INIT;
	/*Check if the moduled has been init before*/
	if(NOT_INIT==u8_InitFlag)
	{
		/*Check if the init function returned OK*/
		if(ERROR_OK==STEERING_Init())
		{
			u8_InitFlag=INIT;
		}
		else{
			//DO Nothing
		}
	}
	else
	{
        //DO Nothing
	}
    if(INIT==u8_InitFlag)
	{
		/*Get speed and direction from crash module*/
		CRASH_GetSpeed(&u16_speed);
		CRASH_GetDirection(&u8_dir);
		/*Set speed and dirction in structure*/
		STEERING_Set(u8_dir,u16_speed);
		/*Check the direction*/
		switch(u8_dir)
		{
		  case STEERING_FORWARD:
             MOTOR_start(MOTOR1, u16_speed, MOTOR_FORWARD);
             MOTOR_start(MOTOR2, u16_speed, MOTOR_FORWARD);
			 break;
		  case STEERING_BACKWARD:
			 MOTOR_start(MOTOR1, u16_speed, MOTOR_BACKWARD);
             MOTOR_start(MOTOR2, u16_speed, MOTOR_BACKWARD);
			 break;
		  case STEERING_RIGHT:
			 MOTOR_start(MOTOR1, u16_speed, MOTOR_BACKWARD);
			 MOTOR_start(MOTOR2, u16_speed, MOTOR_FORWARD);
			 break;
		  case STEERING_LEFT:
			 MOTOR_start(MOTOR1, u16_speed, MOTOR_FORWARD);
			 MOTOR_start(MOTOR2, u16_speed, MOTOR_BACKWARD);
			 break;
			 default:
			 break;
		}
	}
	else
	{
        //DO Nothing
	}
}