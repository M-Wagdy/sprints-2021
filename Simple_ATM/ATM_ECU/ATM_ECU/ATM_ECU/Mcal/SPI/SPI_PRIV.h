/*
 * SPI_PRIV.h
 *
 *  Created on: Jul 17, 2021
 *      Author: zoldeyck
 */

#ifndef MCAL_SPI_SPI_PRIV_H_
#define MCAL_SPI_SPI_PRIV_H_

#define SPI_ControlReg	*((volatile uint8_t*)0x2D)
#define SPI_StatusReg	*((volatile uint8_t*)0x2E)
#define SPI_DataReg 	*((volatile uint8_t*)0x2F)

#define STATUS_REG		*((volatile uint8_t*)0x5F)//SREG
#endif /* MCAL_SPI_SPI_PRIV_H_ */
