/*
* STUB_I2C.h
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/

#ifndef __STUB_I2C_H__
#define __STUB_I2C_H__

/*- INCLUDES -----------------------------------------------*/
#include "Infrastructure/STD_types.h"
#include "Mcal/I2C/I2C_retval.h"
#include "Mcal/I2C/I2C_Config.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

I2C_ERROR_state_t I2C_Init(uint8_t I2C_CH);
I2C_ERROR_state_t I2C_Start(uint8_t I2C_CH);
I2C_ERROR_state_t I2C_RepeatedStart(uint8_t I2C_CH);
I2C_ERROR_state_t I2C_Write(uint8_t I2C_CH, uint8_t Data);
I2C_ERROR_state_t I2C_ReadNoAck(uint8_t I2C_CH, uint8_t* Data);
I2C_ERROR_state_t I2C_Stop(uint8_t I2C_CH);

#endif /* __STUB_I2C_H__ */
