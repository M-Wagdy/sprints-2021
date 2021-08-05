/*
 * File Name: LCD.h
 * Creation Date: 07/23/2020
 * Author: Rehab
 * Description: Header File for LCD...
 */ 

#ifndef __LCD__
#define __LCD__

//FILES INCLUDING
#include "../../Infrastructure/STD_types.h"
#include "../../Infrastructure/BIT_MATH.h"
#include "../../Mcal/DIO/DIO.h"
#include "LCD_Config.h"
#include "LCD_RetVal.h"

//RW PIN
#define WRITE 	PIN_LOW
#define READ 	PIN_HIGH

//RS PIN
#define IR 		PIN_LOW
#define DR 		PIN_HIGH


//FUNCTIONS PROTOTYPES
uint8_t LCD_Init(void);
uint8_t LCD_SendCommand(uint8_t Cmd);
uint8_t LCD_SendData(uint8_t Data);
uint8_t LCD_SendString(ptr_int8_t String);
uint8_t LCD_SendNumber(uint32_t Number);
#endif