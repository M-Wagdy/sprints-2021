/*
 * SPI.h
 *
 * Created: 7/14/2021 2:09:16 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __SPI_H__
#define __SPI_H__
/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "DIO.h"
#include "SPI_Registers.h"
#include "SPI_retval.h"
#include "SPI_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* initialize SPI */
SPI_ERROR_state_t SPI_Init(uint8_t SpiNumber);

/* put a character in the SPI driver */
SPI_ERROR_state_t SPI_TransmitChar(uint8_t SpiNumber,uint8_t TxChar,uint8_t slave_CH);

/* read a character from the SPI driver */
SPI_ERROR_state_t SPI_ReceiveChar(uint8_t SpiNumber,uint8_t * RxData,uint8_t slave_CH);

/* sends a stream of characters */
SPI_ERROR_state_t SPI_TransmitString(uint8_t SpiNumber,uint8_t * TxString,uint8_t slave_CH);

/* receives a stream of characters */
SPI_ERROR_state_t SPI_ReceiveString(uint8_t SpiNumber,uint8_t * RxString,uint8_t slave_CH);

/* enable SPI interrupts */
SPI_ERROR_state_t SPI_EnableInterrupt(uint8_t SpiNumber);

/* disable SPI interrupts */
SPI_ERROR_state_t SPI_DisableInterrupt(uint8_t SpiNumber);

/* set callback function */
SPI_ERROR_state_t SPI_SetCallback(uint8_t SpiNumber, Ptr_VoidFuncVoid_t Callback);

/* Function that set data in the SPI data register */
SPI_ERROR_state_t SPI_SetData(uint8_t SpiNumber, uint8_t TxChar);

/* Function that get data from the SPI data register */
SPI_ERROR_state_t SPI_GetData(uint8_t SpiNumber,uint8_t * RxData);

#endif /* __SPI_H__ */