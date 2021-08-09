/*
* STUB_SPI.h
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/


#ifndef __STUB_SPI_H__
#define __STUB_SPI_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../../../ATM_ECU/Infrastructure/STD_types.h"
#include "../../../../ATM_ECU/Mcal/SPI/SPI_CONFIG.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

uint8_t SPI_Init(uint8_t SpiNumber);
uint8_t SPI_EnableInterrupt(uint8_t SpiNumber);
uint8_t SPI_Set_TX_CompleteCallback(uint8_t SpiNumber, void(*callBack)(void));
uint8_t SPI_TransmitString(uint8_t SpiNumber, ptr_uint8_t TxString, uint8_t slave_CH);


#endif /* __STUB_SPI_H__ */