/*
 * SPI_Registers.h
 *
 * Created: 7/14/2021 2:08:31 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __SPI_REGISTERS_H__
#define __SPI_REGISTERS_H__

/*- SPI REGISTERS-----------------------------------------*/
#define  SPI_DATA_R        (*((volatile uint8_t *) (0x2F)))
#define  SPI_STATUS_R      (*((volatile uint8_t *) (0x2E)))
#define  SPI_CONTROL_R     (*((volatile uint8_t *) (0x2D)))

#endif /* __SPI_REGISTERS_H__ */