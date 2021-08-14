/*
 * PushButton.h
 *
 *  Created on: Jul 11, 2021
 *      Author: zoldeyck
 */

#ifndef HAL_PUSHBUTTON_PUSHBUTTON_H_
	#define HAL_PUSHBUTTON_PUSHBUTTON_H_
   
   #include "Gpio.h"
   #include "PushButton_TypeDef.h"
   
	PSHBTTN_ERROR_RETVAL_t PSHBTTN_Init (DIO_PORT_ID_t port, DIO_PIN_ID_t pin, PSHBTTN_PULLUP_Status_t status);
	PSHBTTN_ERROR_RETVAL_t PSHBTTN_EnablePullUp (DIO_PORT_ID_t port, DIO_PIN_ID_t pin);
	uint8_t PSHBTTN_Status (DIO_PORT_ID_t port, DIO_PIN_ID_t pin);

#define PULLED_UP 0
#define PULLED_DWN 1

#define EXIT_SUCCESFUL 0
#define EXIT_FAILURE -1

#endif /* HAL_PUSHBUTTON_PUSHBUTTON_H_ */
