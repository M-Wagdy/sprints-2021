/*
* STUB_DIO.h
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/


#ifndef __STUB_DIO_H__
#define __STUB_DIO_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_types.h"
#include "Mcal/Atmega32/DIO/DIO_retval.h"
#include "Mcal/Atmega32/DIO/DIO_Config.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

DIO_ERROR_state_t DIO_SetPinDirection(uint8_t port, uint8_t pin, uint8_t direction);
DIO_ERROR_state_t DIO_WritePin(uint8_t port, uint8_t pin, uint8_t data);
DIO_ERROR_state_t DIO_ReadPin(uint8_t port, uint8_t pin, uint8_t* data);
DIO_ERROR_state_t DIO_TogglePin(uint8_t port, uint8_t pin);

#endif /* __STUB_DIO_H__ */