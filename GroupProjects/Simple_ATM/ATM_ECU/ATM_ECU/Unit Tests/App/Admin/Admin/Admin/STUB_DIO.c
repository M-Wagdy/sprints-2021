/*
* STUB_DIO.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/
/*- INCLUDES -----------------------------------------------*/
#include "STUB_DIO.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

uint8_t DIO_ReadPin(uint8_t PortName, uint8_t PinNo, uint8_t* PinData)
{
   *PinData = PIN_LOW;

   return ERROR_OK;
}