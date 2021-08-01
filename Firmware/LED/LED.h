/*
 * LED.h
 *
 * Created: 7/7/2021 1:50:00 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __LED_H__
#define __LED_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Mcal/Atmega32/DIO/DIO.h"
#include "LED_retval.h"
#include "LED_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Function that initialize all LEDS */
LED_ERROR_state_t LED_Init(void);

/* Function that turns off a LED */
LED_ERROR_state_t LED_Off(uint8_t LED_ch);

/* Function that turns on a LED */
LED_ERROR_state_t LED_On(uint8_t LED_ch);

/* Function that toggles a LED */
LED_ERROR_state_t LED_toggle(uint8_t LED_ch);

/* Function that returns a LED state */
LED_ERROR_state_t LED_Status(uint8_t LED_ch, uint8_t * state);

#endif /* __LED_H__ */