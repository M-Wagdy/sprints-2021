/*
 * SPI.h
 *
 * Created: 7/14/2021 2:09:16 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __SPI_H__
#define __SPI_H__
/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"
#include "../DIO/DIO.h"
#include "SPI_Registers.h"
#include "SPI_retval.h"
#include "SPI_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/
SPI_ERROR_state_t SPI_Init(void);
SPI_ERROR_state_t SPI_SendChar(uint8_t character);
SPI_ERROR_state_t SPI_ReadChar(uint8_t * character);
SPI_ERROR_state_t SPI_Send(uint8_t * data);
SPI_ERROR_state_t SPI_Read(uint8_t * data);
SPI_ERROR_state_t SPI_SelectSlave(uint8_t slave_CH);
SPI_ERROR_state_t SPI_UnselectSlave(uint8_t slave_CH);

#endif /* __SPI_H__ */