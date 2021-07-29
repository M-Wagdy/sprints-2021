/*
 * File Name: Keypad_Config.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for Keyoad Configuration ...
 */ 
 
#include "Keypad.h"

Str_KeypadConfig_t gastr_KeypadConfig[KEYPAD_TOTAL_PINS_NUMBER] = {
																		{PORT_B,PIN0,PIN_INPUT},
																		{PORT_B,PIN1,PIN_INPUT},
																		{PORT_B,PIN2,PIN_INPUT},
																		{PORT_B,PIN3,PIN_INPUT},
																		{PORT_B,PIN4,PIN_OUTPUT},
																		{PORT_B,PIN5,PIN_OUTPUT},
																		{PORT_B,PIN6,PIN_OUTPUT}
																  };
																  
																  
																  
uint8_t gau8_Keypad[ROWS_NUMBER][COLUMNS_NUMBER]={
													{'1','2','3'},
													{'4','5','6'},
													{'7','8','9'},
													{'*','0','#'}
												 };																  