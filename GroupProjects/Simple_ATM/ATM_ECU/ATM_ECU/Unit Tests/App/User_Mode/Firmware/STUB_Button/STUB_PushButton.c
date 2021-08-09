/*
 * PushButton.c
 *
 *  Created on: Jul 11, 2021
 *      Author: zoldeyck
 */

#include "STUB_PushButton.h"
uint8_t Push_Button_Status=0;
PSHBTTN_ERROR_RETVAL_t PSHBTTN_Init(uint8_t port, uint8_t pin,
		PSHBTTN_PULLUP_Status_t status){

	return 1;
}
PSHBTTN_ERROR_RETVAL_t PSHBTTN_EnablePullUp(uint8_t port,
		uint8_t pin){

	return 1;
}
uint8_t PSHBTTN_Status (uint8_t port, uint8_t pin){

	return Push_Button_Status;//Return 1 or 0 denpend on what you need (ADEL/REHAB)
}
