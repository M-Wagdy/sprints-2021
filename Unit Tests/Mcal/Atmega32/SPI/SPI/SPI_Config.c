/*
 * SPI_Config.c
 *
 * Created: 8/2/2021 6:18:42 PM
 *  Author: Mohamed Wagdy
 */  
/*- INCLUDES
----------------------------------------------*/
#include "../../../../../Mcal/Atmega32/SPI/SPI_Config.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
const uint8_t SPI_CH_0_CONTROL_MASK = (SPI_EN | MSB_SEND_FIRST | MASTER_SELECT | CLK_FREQ_DIVIDE_4);
const uint8_t SPI_CH_0_MOSI_PORT = PORTB;
const uint8_t SPI_CH_0_MOSI_PIN = PIN_5;
const uint8_t SPI_CH_0_MISO_PORT = PORTB;
const uint8_t SPI_CH_0_MISO_PIN = PIN_6;
const uint8_t SPI_CH_0_SCK_PORT = PORTB;
const uint8_t SPI_CH_0_SCK_PIN = PIN_7;

const uint8_t SPI_CH_0_SS_CH_0_PORT = PORTB;
const uint8_t SPI_CH_0_SS_CH_0_PIN = PIN_4;
