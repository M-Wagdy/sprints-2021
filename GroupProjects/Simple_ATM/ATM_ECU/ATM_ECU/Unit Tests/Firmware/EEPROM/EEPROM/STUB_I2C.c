/*
* STUB_I2C.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/

/*- INCLUDES
----------------------------------------------*/
#include "STUB_I2C.h"

/*- APIs IMPLEMENTATION
-----------------------------------*/

I2C_ERROR_state_t I2C_Init(uint8_t I2C_CH)
{
   return E_I2C_SUCCESS;
}

I2C_ERROR_state_t I2C_Start(uint8_t I2C_CH)
{
   return E_I2C_SUCCESS;
}

I2C_ERROR_state_t I2C_RepeatedStart(uint8_t I2C_CH)
{
   return E_I2C_SUCCESS;
}

I2C_ERROR_state_t I2C_Write(uint8_t I2C_CH, uint8_t Data)
{
   return E_I2C_SUCCESS;
}

I2C_ERROR_state_t I2C_ReadNoAck(uint8_t I2C_CH, uint8_t* Data)
{
   /* Always returns 'A' in the Data */
   *Data = 'A';

   return E_I2C_SUCCESS;
}

I2C_ERROR_state_t I2C_Stop(uint8_t I2C_CH)
{
   return E_I2C_SUCCESS;
}