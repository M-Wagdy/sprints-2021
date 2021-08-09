/*
 * File Name: LCD_Config.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for LCD Configuration ...
 */

#include "STUB_LCD.h"

Str_LCDConfig_t gastr_LCDConfig[LCD_PINS_NUMBER] = {
														{PORT_D,PIN2,PIN_OUTPUT},
														{PORT_D,PIN3,PIN_OUTPUT},
														{PORT_C,PIN2,PIN_OUTPUT},
														{PORT_B,PIN0,PIN_OUTPUT},
														{PORT_B,PIN1,PIN_OUTPUT},
														{PORT_B,PIN2,PIN_OUTPUT},
														{PORT_B,PIN3,PIN_OUTPUT}
													};
