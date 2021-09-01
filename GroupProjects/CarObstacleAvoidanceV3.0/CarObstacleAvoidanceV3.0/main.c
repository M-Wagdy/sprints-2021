/*
 * OS.c
 *
 * Created: 08/29/2021 7:56:24 PM
 * Author: REHAB
 */ 

#include "SENSING.h"
#include "CRASH.h"
#include "STEERING.h"
#include "OS.h"

static TaskHandler_t SensingHandler;
static TaskHandler_t CrashHandler;
static TaskHandler_t SteeringHandler;

void SensingTask(void);
void CrashTask(void);
void SteeringTask(void);

void SensingTask(void)
{
	SENSING_MainFunction();
   double64_t gd64_distance;
   SENSING_Get(&gd64_distance);
   if(gd64_distance < 30)
   {
      DIO_WritePin(PORT_B, PIN5, PIN_LOW);
      DIO_WritePin(PORT_B, PIN4, PIN_HIGH);
   }
   else
   {
      DIO_WritePin(PORT_B, PIN4, PIN_LOW);
      DIO_WritePin(PORT_B, PIN5, PIN_HIGH);
   }
}

void CrashTask(void)
{
	ERROR_STATE_t CRASH_MainErrorState;
	
   double64_t gd64_distance;
   uint16_t u16_CarSpeed;
   uint8_t u8_CarDirection;
   
	/* Call Distance Getter Function */
	SENSING_Get(&gd64_distance);
	
	/* Call Crash Logic API */
	CRASH_MainErrorState = CRASH_Logic(gd64_distance, &u8_CarDirection, &u16_CarSpeed);
	
	/* Set Car Direction and Speed */
	if(ERROR_OK == CRASH_MainErrorState)
	{
   	CRASH_SetSpeed(u16_CarSpeed);
   	CRASH_SetDirection(u8_CarDirection);
      OS_UnsuspandTask(SteeringHandler);
      OS_SuspandTask(CrashHandler);
   }
}

void SteeringTask(void)
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
      uint16_t u16_speed;
      uint8_t u8_dir;
      
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
      OS_SuspandTask(SteeringHandler);
	}
	else
	{
   	//DO Nothing
	}
}

int main(void)
{
   DIO_SetPinDirection(PORT_B, PIN5, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN4, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN6, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN7, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN0, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN1, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN2, PIN_OUTPUT);
   DIO_SetPinDirection(PORT_B, PIN3, PIN_OUTPUT);
   
   while(1)
   {
      SENSING_MainFunction();
      double64_t gd64_distance;
      SENSING_Get(&gd64_distance);
      if(gd64_distance < 30)
      {
         DIO_WritePin(PORT_B, PIN5, PIN_LOW);
         DIO_WritePin(PORT_B, PIN4, PIN_HIGH);
      }
      else
      {
         DIO_WritePin(PORT_B, PIN4, PIN_LOW);
         DIO_WritePin(PORT_B, PIN5, PIN_HIGH);
      }
   }        
	OS_Init();
	
   OS_CreateTask(1,0,1,SensingTask,&SensingHandler);
	/*OS_CreateTask(0,1,1,CrashTask,&CrashHandler);
	OS_CreateTask(0,1,1,SteeringTask,&SteeringHandler);
	
   OS_SuspandTask(CrashHandler);
   OS_SuspandTask(SteeringHandler);*/
   
	OS_Run();
   
   while(1)
   {
      //TODO:: Please write your application code
   }
}