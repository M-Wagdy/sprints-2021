/*
 * PushButton.c
 *
 *  Created on: Jul 11, 2021
 *      Author: zoldeyck
 */
#include "../../INFRASTRUCTURE/STD_types.h"
#include "../../INFRASTRUCTURE/Bit Operations.h"
#include "../../Mcal/DIO/DIO.h"
#include "../../Mcal/Timer/TIMER_DRIVER.h"
#include "PushButton.h"

PSHBTTN_ERROR_RETVAL_t PSHBTTN_Init(uint8_t port, uint8_t pin,
		PSHBTTN_PULLUP_Status_t status){
	PSHBTTN_ERROR_RETVAL_t retVal = EXIT_SUCCESFUL;
	DIO_SetPinDirection(port, pin, PIN_INPUT);
	if (!status)
		PSHBTTN_EnablePullUp(port, pin);
	return retVal;
}
PSHBTTN_ERROR_RETVAL_t PSHBTTN_EnablePullUp(uint8_t port,
		uint8_t pin){
	PSHBTTN_ERROR_RETVAL_t retVal = EXIT_SUCCESFUL;
	DIO_EnablePinPullup(port,pin);
	return retVal;
}
uint8_t PSHBTTN_Status (uint8_t port, uint8_t pin){
	uint8_t retVal = EXIT_FAILURE;
	DIO_ReadPin(port, pin, &retVal);
	if (retVal == 0){
			//TIM_Delay_MS(TIMER0,20);//dummy delay for 20ms
			DIO_ReadPin(port, pin, &retVal);
		}
	return retVal;
}
