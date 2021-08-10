/*
 * main.c
 *
 *  Created on: Aug 9, 2021
 *      Author: zoldeyck
 */
#include "Infrastructure/infrastructure.h"
#include "MCAL/DIO/DIO_DRIVER.h"
#include "MCAL/Timer/Timer.h"
#include "HAL/LCD/LCD.h"
int main()
{
	TIM_Init(TIMER_2);
	while(LCD_Init() != OperationSuccess);
//	while(LCD_SendString("AMR_TEAM") != OperationSuccess);
//	while(LCD_SendData('A') != OperationSuccess);
	LCD_SendString("AMR_TEAM");
	LCD_SendNumber(5792);
	while (1)
	{
//		LCD_SendData('A');
	}
	return 0;
}
