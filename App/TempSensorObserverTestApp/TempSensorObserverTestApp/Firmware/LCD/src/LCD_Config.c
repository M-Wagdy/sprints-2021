/*
 * LCD_Config.c
 *
 * Created: 8/3/2021 12:29:54 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "LCD_Config.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
const uint8_t LCD_CH_0_RS_PORT = PORTC;
const uint8_t LCD_CH_0_RS_PIN = PIN_5;
const uint8_t LCD_CH_0_RW_PORT = PORTC;
const uint8_t LCD_CH_0_RW_PIN = PIN_6;
const uint8_t LCD_CH_0_E_PORT = PORTC;
const uint8_t LCD_CH_0_E_PIN = PIN_7;
const uint8_t LCD_CH_0_DATA_PORT = PORTD;
const uint8_t LCD_CH_0_DATA_START_PIN = PIN_4;