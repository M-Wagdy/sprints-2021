/*
 * File Name: Keypad_Config.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for Keyoad Configuration ...
 */ 
 
#include "Keypad.h"

Str_KeypadConfig_t gastr_KeypadConfig[KEYPAD_TOTAL_PINS_NUMBER] = {
																		{PORT_A,PIN4,PIN_INPUT},
																		{PORT_A,PIN5,PIN_INPUT},
																		{PORT_A,PIN6,PIN_INPUT},
																		{PORT_A,PIN7,PIN_INPUT},
																		{PORT_A,PIN1,PIN_OUTPUT},
																		{PORT_A,PIN2,PIN_OUTPUT},
																		{PORT_A,PIN3,PIN_OUTPUT}
																  };
																  
																  
																  
uint8_t gau8_Keypad[ROWS_NUMBER][COLUMNS_NUMBER]={
													{'1','2','3'},
													{'4','5','6'},
													{'7','8','9'},
													{'*','0','#'}
												 };																  