/*
 * File Name: LCD_Config.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for LCD Configuration ...
 */ 
 
#include "LCD.h"

Str_LCDConfig_t gastr_LCDConfig[LCD_PINS_NUMBER] = {
														{PORT_A,PIN1,PIN_OUTPUT},
														{PORT_A,PIN2,PIN_OUTPUT},
														{PORT_A,PIN3,PIN_OUTPUT},
														{PORT_A,PIN4,PIN_OUTPUT},
														{PORT_A,PIN5,PIN_OUTPUT},
														{PORT_A,PIN6,PIN_OUTPUT},
														{PORT_A,PIN7,PIN_OUTPUT}
													};