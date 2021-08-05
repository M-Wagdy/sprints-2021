/*
 * File Name: Keypad.c
 * Creation Date: 07/23/2020
 * Author: Rehab
 * Description: C File for Keypad...
 */ 

#include "Keypad.h"

extern Str_KeypadConfig_t gastr_KeypadConfig[];

extern uint8_t gau8_Keypad[ROWS_NUMBER][COLUMNS_NUMBER];

uint8_t KEYPAD_Init(void)
{
	for(uint8_t au8_IterationNo=0;au8_IterationNo<KEYPAD_TOTAL_PINS_NUMBER;au8_IterationNo++)
	{
		DIO_SetPinDirection(	gastr_KeypadConfig[au8_IterationNo].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo].KeypadPin,
								gastr_KeypadConfig[au8_IterationNo].KeypadDirection );
		
		#if KEYPAD_INPUT_PINS_CONNECTION_MODE==KEYPAD_PULLUP_SW
			if(au8_IterationNo<ROWS_NUMBER)
			{	
				DIO_EnablePinPullup(	gastr_KeypadConfig[au8_IterationNo].KeypadPort,
										gastr_KeypadConfig[au8_IterationNo].KeypadPin );
			}
		#endif	
		
		#if KEYPAD_INPUT_PINS_CONNECTION_MODE==KEYPAD_PULLDOWN
			if(au8_IterationNo>=ROWS_NUMBER)
			{	
				DIO_WritePin(	gastr_KeypadConfig[au8_IterationNo].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo].KeypadPin,
								PIN_LOW);
			}
		#else
			if(au8_IterationNo>=ROWS_NUMBER)
			{	
				DIO_WritePin(	gastr_KeypadConfig[au8_IterationNo].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo].KeypadPin,
								PIN_HIGH);
			}			
		#endif	
	}	
	return ERROR_OK;
}

uint8_t KEYPAD_ReadKey(ptr_uint8_t Key)
{
	uint8_t u8_RowsVal=0,u8_Col=0;
	#if KEYPAD_INPUT_PINS_CONNECTION_MODE==KEYPAD_PULLDOWN
		for(u8_Col=0;u8_Col<COLUMNS_NUMBER;u8_Col++)
		{
			for(uint8_t au8_IterationNo=0;au8_IterationNo<COLUMNS_NUMBER;au8_IterationNo++)
			{
				DIO_WritePin(	gastr_KeypadConfig[au8_IterationNo+KEYPAD_COLUMN0].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo+KEYPAD_COLUMN0].KeypadPin,
								PIN_LOW);				
			}
							
			DIO_WritePin(	gastr_KeypadConfig[KEYPAD_COLUMN0+u8_Col].KeypadPort,
							gastr_KeypadConfig[KEYPAD_COLUMN0+u8_Col].KeypadPin,
							PIN_HIGH);
							
			for(uint8_t au8_IterationNo=0;au8_IterationNo<ROWS_NUMBER;au8_IterationNo++)
			{
				uint8_t u8_Data;
				DIO_ReadPin(	gastr_KeypadConfig[au8_IterationNo+KEYPAD_ROW0].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo+KEYPAD_ROW0].KeypadPin,
								&u8_Data);
				u8_RowsVal|=u8_Data<<au8_IterationNo;
			}
			
			if(u8_RowsVal!=FOUR_BITS_LOW)
			{
				break;
			}
			u8_RowsVal=0;
		}
		
		if(u8_Col==COLUMNS_NUMBER)
		{
			*Key=0;
		}
		else
		{
			uint8_t u8_Row;
			KEYPAD_WhichRow(u8_RowsVal,&u8_Row);
			*Key=gau8_Keypad[u8_Row][u8_Col];
		}				
	#else
		for(u8_Col=0;u8_Col<COLUMNS_NUMBER;u8_Col++)
		{
			for(uint8_t au8_IterationNo=0;au8_IterationNo<COLUMNS_NUMBER;au8_IterationNo++)
			{
				DIO_WritePin(	gastr_KeypadConfig[au8_IterationNo+KEYPAD_COLUMN0].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo+KEYPAD_COLUMN0].KeypadPin,
								PIN_HIGH);				
			}
							
			DIO_WritePin(	gastr_KeypadConfig[KEYPAD_COLUMN0+u8_Col].KeypadPort,
							gastr_KeypadConfig[KEYPAD_COLUMN0+u8_Col].KeypadPin,
							PIN_LOW);
							
			for(uint8_t au8_IterationNo=0;au8_IterationNo<ROWS_NUMBER;au8_IterationNo++)
			{
				uint8_t u8_Data;
				DIO_ReadPin(	gastr_KeypadConfig[au8_IterationNo+KEYPAD_ROW0].KeypadPort,
								gastr_KeypadConfig[au8_IterationNo+KEYPAD_ROW0].KeypadPin,
								&u8_Data);
				u8_RowsVal|=u8_Data<<au8_IterationNo;
			}
			
			if(u8_RowsVal!=FOUR_BITS_HIGH)
			{
				break;
			}
			u8_RowsVal=0;
		}
		
		if(u8_Col==COLUMNS_NUMBER)
		{
			*Key=0;
		}
		else
		{
			uint8_t u8_Row;
			KEYPAD_WhichRow(u8_RowsVal,&u8_Row);
			*Key=gau8_Keypad[u8_Row][u8_Col];
		}										
	#endif	
	return ERROR_OK;
}

uint8_t KEYPAD_WhichRow(uint8_t RowsVal,ptr_uint8_t RowNumber)
{
	#if KEYPAD_INPUT_PINS_CONNECTION_MODE==KEYPAD_PULLDOWN
		switch(RowsVal)
		{
			case 0X01:
				*RowNumber=0;			
				break;
			case 0X02:
				*RowNumber=1;		
				break;
			case 0X04:
				*RowNumber=2;
				break;
			case 0X08:
				*RowNumber=3;		
				break;
			default:
				*RowNumber=4;
				break;
		}
	#else
		switch(RowsVal)
		{
			case 0X0E:
				*RowNumber=0;			
				break;
			case 0X0D:
				*RowNumber=1;		
				break;
			case 0X0B:
				*RowNumber=2;		
				break;
			case 0X07:
				*RowNumber=3;		
				break;
			default:
				*RowNumber=4;
				break;
		}
	#endif	
	return ERROR_OK;
}

uint8_t KEYPAD_MustPressed(ptr_uint8_t Key)
{
	do 
	{
		KEYPAD_ReadKey(Key); 	 
	}while (*Key==0);
	return ERROR_OK;
}