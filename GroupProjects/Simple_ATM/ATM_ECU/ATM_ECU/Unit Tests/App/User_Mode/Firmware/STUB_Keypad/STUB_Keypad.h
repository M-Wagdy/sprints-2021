/*
 * File Name: Keypad.h
 * Creation Date: 07/23/2020
 * Author: Rehab
 * Description: Header File for Keypad...
 */

#ifndef __KEYPAD__
#define __KEYPAD__

//FILES INCLUDING
#include "../../Infrastructure/STD_types.h"
#include "Keypad_RetVal.h"


//FUNCTIONS PROTOTYPES
uint8_t KEYPAD_Init(void);
uint8_t KEYPAD_ReadKey(ptr_uint8_t Key);
uint8_t KEYPAD_WhichRow(uint8_t RowsVal,ptr_uint8_t RowNumber);
uint8_t KEYPAD_MustPressed(ptr_uint8_t Key);
#endif
