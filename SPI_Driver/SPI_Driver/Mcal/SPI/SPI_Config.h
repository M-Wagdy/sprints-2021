/*
 * SPI_Config.h
 *
 * Created: 7/14/2021 2:09:08 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __SPI_CONFIG_H__
#define __SPI_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "../../Infrastructure/STD_types.h"

/*- MACROS -------------------------------------------------*/
#define INTERRUPT_EN          (uint8_t)(0X80)
#define SPI_EN                (uint8_t)(0X40)

#define MSB_SEND_FIRST        (uint8_t)(0X00)
#define LSB_SEND_FIRST        (uint8_t)(0X20)

#define MASTER_SELECT         (uint8_t)(0X10)
#define SLAVE_SELECT          (uint8_t)(0X00)

#define CLK_FREQ_DIVIDE_4     (uint8_t)(0X00)
#define CLK_FREQ_DIVIDE_16    (uint8_t)(0X01)
#define CLK_FREQ_DIVIDE_64    (uint8_t)(0X02)
#define CLK_FREQ_DIVIDE_128   (uint8_t)(0X03)

#define SPI_CONTROL_MASK      (SPI_EN | MSB_SEND_FIRST | MASTER_SELECT | CLK_FREQ_DIVIDE_4)

#endif /* __SPI_CONFIG_H__ */