/*
 * SPI_Registers.h
 *
 * Created: 7/14/2021 2:08:31 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __SPI_REGISTERS_H__
#define __SPI_REGISTERS_H__

#define TEST 0

#if !TEST
/*- SPI REGISTERS-----------------------------------------*/
#define  SPI_DATA_R        (*((volatile uint8_t *) (0x2F)))
#define  SPI_STATUS_R      (*((volatile uint8_t *) (0x2E)))
#define  SPI_CONTROL_R     (*((volatile uint8_t *) (0x2D)))
#else
/*- SPI REGISTERS-----------------------------------------*/
extern volatile uint8_t  SPI_DATA_R;
extern volatile uint8_t  SPI_STATUS_R;
extern volatile uint8_t  SPI_CONTROL_R;
#endif

#endif /* __SPI_REGISTERS_H__ */