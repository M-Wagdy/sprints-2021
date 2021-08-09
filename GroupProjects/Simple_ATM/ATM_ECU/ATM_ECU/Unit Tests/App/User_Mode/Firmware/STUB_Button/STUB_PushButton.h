/*
 * PushButton.h
 *
 *  Created on: Jul 11, 2021
 *      Author: zoldeyck
 */

#ifndef HAL_PUSHBUTTON_PUSHBUTTON_H_
#define HAL_PUSHBUTTON_PUSHBUTTON_H_


#include "../../INFRASTRUCTURE/STD_types.h"
#include "PushButton_TypeDef.h"
   PSHBTTN_ERROR_RETVAL_t PSHBTTN_Init (uint8_t port, uint8_t pin, PSHBTTN_PULLUP_Status_t status);
	PSHBTTN_ERROR_RETVAL_t PSHBTTN_EnablePullUp (uint8_t port, uint8_t pin);
	uint8_t PSHBTTN_Status (uint8_t port, uint8_t pin);

#define PULLED_UP 0
#define PULLED_DWN 1

#endif /* HAL_PUSHBUTTON_PUSHBUTTON_H_ */
