/*
 * File Name: Keypad.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for Keypad Configuration ...
 */ 
 
#ifndef __KEYPAD_CONFIG__
#define __KEYPAD_CONFIG__

//AM USED ROWS AS INPUT AND COLUMNS AS OUTPUT
#define KEYPAD_TOTAL_PINS_NUMBER    7
#define KEYPAD_INPUT_PINS_NUMBER 	4
#define KEYPAD_OUTPUT_PINS_NUMBER 	3

#define ROWS_NUMBER					4 //Input
#define COLUMNS_NUMBER				3 //Output

//KEYPAD PINS ARRAY LOCATION 
#define KEYPAD_ROW0		0
#define KEYPAD_ROW1		1	
#define KEYPAD_ROW2		2
#define KEYPAD_ROW3		3

#define KEYPAD_COLUMN0	4
#define KEYPAD_COLUMN1	5
#define KEYPAD_COLUMN2	6


//KEYPAD INPUT PINS CONNECTION MODE
#define KEYPAD_INPUT_PINS_CONNECTION_MODE KEYPAD_PULLUP_SW

#define KEYPAD_PULLDOWN		0
#define KEYPAD_PULLUP_HW 	1
#define KEYPAD_PULLUP_SW 	2

typedef struct Str_KeypadConfig
{
	uint8_t KeypadPort;
	uint8_t KeypadPin;
	uint8_t KeypadDirection;
}Str_KeypadConfig_t ;

#endif