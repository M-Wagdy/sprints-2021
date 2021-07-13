/*
 * LED.h
 *
 * Created: 7/7/2021 1:50:00 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __LED_H__
#define __LED_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Mcal/DIO/DIO.h"
#include "LED_retval.h"
#include "LED_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/
LED_ERROR_state_t LED_Off(uint8_t LED_ch);
LED_ERROR_state_t LED_On(uint8_t LED_ch);
LED_ERROR_state_t LED_toggle(uint8_t LED_ch);

#endif /* __LED_H__ */