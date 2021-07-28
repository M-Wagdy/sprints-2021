/*
 * SPI.h
 *
 *  Created on: Jul 17, 2021
 *      Author: zoldeyck
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "SPI_CONFIG.h"
#include "SPI_PRIV.h"
uint8_t SPI_Init(uint8_t SpiNumber);

uint8_t SPI_TransmitChar(uint8_t SpiNumber,uint8_t TxChar,uint8_t slave_CH);
uint8_t SPI_ReceiveChar(uint8_t SpiNumber,ptr_uint8_t RxData,uint8_t slave_CH);
uint8_t SPI_DataExchange (uint8_t SpiNumber, uint8_t TxChar, ptr_uint8_t RxData, uint8_t slave_CH);
uint8_t SPI_TransmitString(uint8_t SpiNumber,ptr_uint8_t TxString,uint8_t slave_CH);
uint8_t SPI_ReceiveString(uint8_t SpiNumber,ptr_uint8_t RxString,uint8_t slave_CH);

uint8_t SPI_EnableInterrupt(uint8_t SpiNumber);
uint8_t SPI_DisableInterrupt(uint8_t SpiNumber);
uint8_t SPI_Set_TX_CompleteCallback(uint8_t SpiNumber,void(*callBack)(void));

#endif /* MCAL_SPI_SPI_H_ */
