/*
 * File Name: DIO.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for DIO peripheral....
 */ 

#include "MC_REGISTERS.h"
#include "DIO.h"

ERROR_STATE_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection)
{
	uint8_t u8_ErrorState=ERROR_OK;
	if((PIN_INPUT!=PinDirection)&&(PIN_OUTPUT!=PinDirection))
	{
		u8_ErrorState=ERROR_NOK;
	}
	else if(PinNo>PIN7)
	{
		u8_ErrorState=ERROR_NOK;
	}
	else
	{
		switch(PortName)
		{
			case PORT_A:
				
				u8_ErrorState=ERROR_OK;
				break;
			case PORT_B:
				
				u8_ErrorState=ERROR_OK;
				break;
			case PORT_C:
				
				u8_ErrorState=ERROR_OK;
				break;
			case PORT_D:
				
				u8_ErrorState=ERROR_OK;
				break;
			default:
				
				break;
		}		
	}
	return u8_ErrorState;
}
