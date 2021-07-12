/*
 * PushButton.c
 *
 *  Created on: Jul 11, 2021
 *      Author: zoldeyck
 */

#include "PushButton.h"

PSHBTTN_ERROR_RETVAL_t PSHBTTN_Init(DIO_PORT_ID_t port, DIO_PIN_ID_t pin,
		PSHBTTN_PULLUP_Status_t status){
	PSHBTTN_ERROR_RETVAL_t retVal = EXIT_SUCCESFUL;
	GpioSetPinDirection(port, pin, PIN_INPUT);
	if (!status)
		GpioEnablePinPullup(port, pin);
	return retVal;
}
PSHBTTN_ERROR_RETVAL_t PSHBTTN_EnablePullUp(DIO_PORT_ID_t port,DIO_PIN_ID_t pin){
	PSHBTTN_ERROR_RETVAL_t retVal = EXIT_SUCCESFUL;
	retVal = GpioEnablePinPullup(port,pin);
	return retVal;
}
uint8_t PSHBTTN_Status (DIO_PORT_ID_t port, DIO_PIN_ID_t pin){
	uint8_t pushButton = 1;
	GpioReadPin(port, pin, &pushButton);
	if (pushButton == 0)
   {
   	for(volatile uint16_t i=0; i<1000; i++)
      {
         for(volatile uint8_t j=0; j<16; j++)
         {
            for(volatile uint8_t k=0; k<20; k++)
            {
               
            }
         }
      }//dummy delay for 20ms
   	GpioReadPin(port, pin, &pushButton);
	}
	return pushButton;
}
