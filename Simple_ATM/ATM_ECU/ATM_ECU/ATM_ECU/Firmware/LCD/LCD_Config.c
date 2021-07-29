/*
 * File Name: LCD_Config.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for LCD Configuration ...
 */ 
 
#include "LCD.h"

Str_LCDConfig_t gastr_LCDConfig[LCD_PINS_NUMBER] = {
														{PORT_C,PIN5,PIN_OUTPUT},
														{PORT_C,PIN6,PIN_OUTPUT},
														{PORT_C,PIN7,PIN_OUTPUT},
														{PORT_D,PIN4,PIN_OUTPUT},
														{PORT_D,PIN5,PIN_OUTPUT},
														{PORT_D,PIN6,PIN_OUTPUT},
														{PORT_D,PIN7,PIN_OUTPUT}
													};