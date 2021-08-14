/*
 * Keypad.h
 *
 * Created: 7/25/2021 4:47:04 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __KEYPAD_H__
#define __KEYPAD_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_types.h"
#include "Mcal/Atmega32/DIO/DIO.h"
#include "Keypad_retval.h"
#include "Keypad_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize a keypad */
KEYPAD_ERROR_state_t KP_Init(uint8_t KP_CH);

/* get keypad pressed key */
KEYPAD_ERROR_state_t KP_GetPressedValue(uint8_t KP_CH, uint8_t * Data);

#endif /* __KEYPAD_H__ */