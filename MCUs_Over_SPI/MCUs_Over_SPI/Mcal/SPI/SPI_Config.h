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
#define SPI_INTERRUPT_EN            (uint8_t)(0X80)
#define SPI_EN                      (uint8_t)(0X40)

#define MSB_SEND_FIRST              (uint8_t)(0X00)
#define LSB_SEND_FIRST              (uint8_t)(0X20)

#define MASTER_SELECT               (uint8_t)(0X10)
#define SLAVE_SELECT                (uint8_t)(0X00)

#define CLK_FREQ_DIVIDE_4           (uint8_t)(0X00)
#define CLK_FREQ_DIVIDE_16          (uint8_t)(0X01)
#define CLK_FREQ_DIVIDE_64          (uint8_t)(0X02)
#define CLK_FREQ_DIVIDE_128         (uint8_t)(0X03)

#define SPI_NUMBERS                 (uint8_t)(1)

#define SPI_TRANSMIT_COMPLETE_BIT   (uint8_t)(0X80)
#define SPI_WRITE_COLLISION_BIT     (uint8_t)(0X40)

#define SPI_CH_0                    (uint8_t)(0)
#define SPI_CH_0_CONTROL_MASK       (SPI_EN | MSB_SEND_FIRST | MASTER_SELECT | CLK_FREQ_DIVIDE_4)
#define SPI_CH_0_MOSI_PORT          PORTB
#define SPI_CH_0_MOSI_PIN           PIN_5
#define SPI_CH_0_MISO_PORT          PORTB
#define SPI_CH_0_MISO_PIN           PIN_6
#define SPI_CH_0_SCK_PORT           PORTB
#define SPI_CH_0_SCK_PIN            PIN_7

#define SPI_CH_0_SS_CH_0            (uint8_t)(0)
#define SPI_CH_0_SS_CH_0_PORT       PORTB
#define SPI_CH_0_SS_CH_0_PIN        PIN_4
#define SLAVE_SS_CH                 (uint8_t)(255)

#endif /* __SPI_CONFIG_H__ */