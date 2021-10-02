/*
 * STUB_BUTTON.c
 *
 * Created: 9/2/2021 1:50:41 PM
 *  Author: Mohamed Wagdy
 */

 /*- INCLUDES
 ----------------------------------------------*/
#include "STUB_BUTTON.h"

uint8_t ButtonState = 0;

/*- APIs IMPLEMENTATION
-----------------------------------*/
ERROR_STATE_t BUTTON_getState(uint8_t BUTTON_CH, uint8_t* State)
{
	*State = ButtonState;
	return ERROR_OK;
}