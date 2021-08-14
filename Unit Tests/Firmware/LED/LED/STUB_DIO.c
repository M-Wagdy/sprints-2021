/*
* STUB_DIO.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/

/*- INCLUDES
----------------------------------------------*/
#include "STUB_DIO.h"

/*- APIs IMPLEMENTATION
-----------------------------------*/

DIO_ERROR_state_t DIO_SetPinDirection(uint8_t port, uint8_t pin, uint8_t direction)
{
   return E_DIO_SUCCESS;
}

DIO_ERROR_state_t DIO_WritePin(uint8_t port, uint8_t pin, uint8_t data)
{
   return E_DIO_SUCCESS;
}

DIO_ERROR_state_t DIO_ReadPin(uint8_t port, uint8_t pin, uint8_t* data)
{
   /* Always returns 1 */
   *data = (uint8_t)(1);

   return E_DIO_SUCCESS;
}

DIO_ERROR_state_t DIO_TogglePin(uint8_t port, uint8_t pin)
{
   return E_DIO_SUCCESS;
}