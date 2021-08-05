/*
 * motor.c
 *
 * Created: 7/28/2021 12:07:13 PM
 *  Author: Marco
 */ 
/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include "motor.h"

/******************************************************************************
*                         APIS IMPLEMENTATION											*
*******************************************************************************/
MOTOR_STATUS_t MOTOR_INIT(void)
{
	DIO_SetPinDirection(MOTOR_PORT, MOTOR_PIN, PIN_OUTPUT);
	return MOTOR_SUCCESS;
}
MOTOR_STATUS_t MOTOR_START(void)
{
	DIO_WritePin(MOTOR_PORT, MOTOR_PIN, PIN_HIGH);
	return MOTOR_SUCCESS;
}
MOTOR_STATUS_t MOTOR_STOP(void)
{
	DIO_WritePin(MOTOR_PORT, MOTOR_PIN, PIN_LOW);
	return MOTOR_SUCCESS;
}
MOTOR_STATUS_t MOTOR_STATUS(uint8_t * status)
{
	DIO_ReadPin(MOTOR_PORT, MOTOR_PIN, status);
	return MOTOR_SUCCESS;
}