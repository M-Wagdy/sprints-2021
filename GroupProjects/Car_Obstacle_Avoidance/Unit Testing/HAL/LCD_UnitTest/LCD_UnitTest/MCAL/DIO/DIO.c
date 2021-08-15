/*
 * File Name: DIO.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for DIO peripheral....
 */ 

#include "../../LIB/MC_REGISTERS.h"
#include "DIO.h"

ERROR_STATE_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection)
{
	switch(PortName)
	{
		case PORT_A:
			BIT_WRITE(DDRA,PinNo,PinDirection);
			break;
		case PORT_B:
			BIT_WRITE(DDRB,PinNo,PinDirection);
			break;
		case PORT_C:
			BIT_WRITE(DDRC,PinNo,PinDirection);
			break;
		case PORT_D:
			BIT_WRITE(DDRD,PinNo,PinDirection);
			break;
		default:
			break;
	}
	return ERROR_OK;
}

ERROR_STATE_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue)
{
	switch(PortName)
	{
		case PORT_A:
			BIT_WRITE(PORTA,PinNo,PinValue);
			break;
		case PORT_B:
			BIT_WRITE(PORTB,PinNo,PinValue);
			break;
		case PORT_C:
			BIT_WRITE(PORTC,PinNo,PinValue);
			break;
		case PORT_D:
			BIT_WRITE(PORTD,PinNo,PinValue);
			break;
		default:
			break;
	}	
	return ERROR_OK;
}
ERROR_STATE_t DIO_TogglePin(uint8_t PortName,uint8_t PinNo)
{
	switch(PortName)
	{
		case PORT_A:
			BIT_TOGGLE(PORTA,PinNo);
			break;
		case PORT_B:
			BIT_TOGGLE(PORTB,PinNo);
			break;
		case PORT_C:
			BIT_TOGGLE(PORTC,PinNo);
			break;
		case PORT_D:
			BIT_TOGGLE(PORTD,PinNo);
			break;
		default:
			break;	
	}	
	return ERROR_OK;
}
ERROR_STATE_t DIO_ReadPin(uint8_t PortName,uint8_t PinNo,ptr_uint8_t PinData)
{
	switch(PortName)
	{
		case PORT_A:
			* PinData=BIT_GET(PINA,PinNo);
			break;
		case PORT_B:
			* PinData=BIT_GET(PINB,PinNo);
			break;
		case PORT_C:
			* PinData=BIT_GET(PINC,PinNo);
			break;
		case PORT_D:
			* PinData=BIT_GET(PIND,PinNo);
			break;
		default:
			break;
	}
	return ERROR_OK;
}


ERROR_STATE_t DIO_EnablePinPullup(uint8_t PortName,uint8_t PinNo)
{
	switch(PortName)
	{
		case PORT_A:
			BIT_WRITE(PORTA,PinNo,PIN_HIGH);
			break;
		case PORT_B:
			BIT_WRITE(PORTB,PinNo,PIN_HIGH);
			break;                            
		case PORT_C:                          
			BIT_WRITE(PORTC,PinNo,PIN_HIGH);
			break;                            
		case PORT_D:                          
			BIT_WRITE(PORTD,PinNo,PIN_HIGH);
			break;
		default:
			break;
	}	
	return ERROR_OK;
}