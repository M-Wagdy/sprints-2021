/*
 * SPI_Config.c
 *
 * Created: 8/2/2021 6:18:42 PM
 *  Author: Mohamed Wagdy
 */  
/*- INCLUDES
----------------------------------------------*/
#include "SPI_Config.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* SPI_CH_0 */
const uint8_t SPI_CH_0_CONTROL_MASK = (SPI_EN | MSB_SEND_FIRST | CLK2_FREQ_DIVIDE_32);
const uint8_t SPI_CH_0_DOUBLE_SPEED = SPI_DOUBLE_SPEED_ON;
const uint8_t SPI_CH_0_MOSI_PORT = PORTB;
const uint8_t SPI_CH_0_MOSI_PIN = PIN_5;
const uint8_t SPI_CH_0_MISO_PORT = PORTB;
const uint8_t SPI_CH_0_MISO_PIN = PIN_6;
const uint8_t SPI_CH_0_SCK_PORT = PORTB;
const uint8_t SPI_CH_0_SCK_PIN = PIN_7;

const uint8_t SPI_CH_0_SS_CH_0_PORT = PORTB;
const uint8_t SPI_CH_0_SS_CH_0_PIN = PIN_4;