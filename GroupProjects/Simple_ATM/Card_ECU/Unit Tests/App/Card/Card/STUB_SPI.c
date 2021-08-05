/*
* STUB_SPI.c
*
* Created: 8/5/2021 10:49:17 AM
*  Author: Mohamed Wagdy
*/

/*- INCLUDES -----------------------------------------------*/
#include "STUB_SPI.h"

/*- STUB FUNCTION DECLARATIONS ----------------------------------*/

uint8_t SPI_Init(uint8_t SpiNumber)
{
   return 1;
}

uint8_t SPI_EnableInterrupt(uint8_t SpiNumber)
{
   return 1;
}

uint8_t SPI_Set_TX_CompleteCallback(uint8_t SpiNumber, void(*callBack)(void))
{
   return 1;
}

uint8_t SPI_TransmitString(uint8_t SpiNumber, ptr_uint8_t TxString, uint8_t slave_CH)
{
   return 1;
}