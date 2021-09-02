/*
 * CRASH_Interface.c
 *
 * Created: 8/19/2021 11:19:23 AM
 *  Author: Mohamed Wagdy
 */ 

/*INCLUDES-------------------------------*/
#include "CRASH_Interface.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint16_t gu16_Speed = STEERING_MIN_SPEED;
static uint8_t gu8_Dir = STEERING_FORWARD;

/*APIs IMPLEMENTATION------------------------*/
/**
* @brief: This function sets the Speed of the car.
*
* @param [in]  Speed -  Speed of Car to move.
*
* @return function error state.
*/
extern ERROR_STATE_t  CRASH_SetSpeed(uint16_t Speed){
	ERROR_STATE_t CRASH_ErrorState = ERROR_OK;
	/*CHECK IF INVLAID SPEED*/
	if(Speed>STEERING_MAX_SPEED){
		CRASH_ErrorState = ERROR_NOK;
	}
	else{
		/*SET THE SPEED*/
		gu16_Speed = Speed;
		CRASH_ErrorState = ERROR_OK;
	}
	return CRASH_ErrorState;
}

/**
* @brief: This function sets the Direction of the car.
*
* @param [in]  Dir -  Direction of Car to move.
*	
* @return function error state.
*/
extern ERROR_STATE_t  CRASH_SetDirection(uint8_t  Dir){
	ERROR_STATE_t CRASH_ErrorState = ERROR_OK;
	/*CHECK IF INVALID DIRECTION*/
	if(Dir>=INVALID_STEERING){
		CRASH_ErrorState = ERROR_NOK;
	}
	else{
		/*SET THE DIRECTION*/
		gu8_Dir = Dir;
		CRASH_ErrorState = ERROR_OK;
	}
	return CRASH_ErrorState;
}

/**
* @brief: This function gets the speed of the car.
*
* @param [out]  Speed - Speed of Car.
*
* @return function error state.
*/
extern ERROR_STATE_t  CRASH_GetSpeed(ptr_uint16_t Speed){
	ERROR_STATE_t CRASH_ErrorState = ERROR_OK;
	/*CHECK IF NULL_PTR*/
	if(NULL_PTR == Speed)
	{
		CRASH_ErrorState=ERROR_NOK;
	}
	else
	{
		/*GET THE SPEED*/
		*Speed = gu16_Speed;
		CRASH_ErrorState = ERROR_OK;
	}
	return CRASH_ErrorState;
}

/**
* @brief: This function gets the direction of the car.
*
* @param [out]  Dir - Direction of Car.
*
* @return function error state.
*/
extern ERROR_STATE_t  CRASH_GetDirection(ptr_uint8_t  Dir){
	ERROR_STATE_t CRASH_ErrorState = ERROR_OK;
	/*CHECK IF NULL_PTR*/
	if(NULL_PTR == Dir)
	{
		CRASH_ErrorState=ERROR_NOK;
	}
	else
	{
		/*GET THE DIRECTION*/
		*Dir = gu8_Dir;
		CRASH_ErrorState = ERROR_OK;
	}
	return CRASH_ErrorState;
}