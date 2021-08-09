/*
 * File Name: Keypad.c
 * Creation Date: 07/23/2020
 * Author: Rehab
 * Description: C File for Keypad...
 */

#include "STUB_Keypad.h"

uint8_t testing_key;

uint8_t Entered_PIN_Flag=0;
uint8_t Entered_Amount_Flag=0;

uint8_t au8_Entered_PIN_Test[5];
uint8_t u8_Entered_PIN_Index=0;

uint8_t au8_Entered_Amount_Test[8];
uint8_t u8_Entered_Amount_Index=0;

uint8_t KEYPAD_Init(void)
{
	//NO NEED TO DO ANYTHING
	return ERROR_OK;
}

uint8_t KEYPAD_ReadKey(ptr_uint8_t Key)
{
	//NEED TO DO SOMETHING DEPEND ON WHERE YOU NEED IT (REHAB,ADEL)
	return ERROR_OK;
}

uint8_t KEYPAD_WhichRow(uint8_t RowsVal,ptr_uint8_t RowNumber)
{
	//NO NEED TO DO ANYTHING
	return ERROR_OK;
}

uint8_t KEYPAD_MustPressed(ptr_uint8_t Key)
{
	//CHANGE IT DEPEND ON YOUR LOGIC(REHAB/ADEL)
	if(Entered_PIN_Flag==1)
	{
		*Key=au8_Entered_PIN_Test[u8_Entered_PIN_Index];
		u8_Entered_PIN_Index++;
	}

	if(Entered_Amount_Flag==1)
	{
		*Key=au8_Entered_Amount_Test[u8_Entered_Amount_Index];
		u8_Entered_Amount_Index++;
	}

	return ERROR_OK;
}
