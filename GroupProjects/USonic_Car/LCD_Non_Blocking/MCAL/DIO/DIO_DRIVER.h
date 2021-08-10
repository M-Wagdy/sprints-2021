#ifndef __DIO_DRIVER_H__
	#define __DIO_DRIVER_H__
#include "DIO_DRIVER_TypeDef.h"
	#define PIN0 0
	#define PIN1 1
	#define PIN2 2
	#define PIN3 3
	#define PIN4 4
	#define PIN5 5
	#define PIN6 6
	#define PIN7 7
	
	#define PORTA 1
	#define PORTB 2
	#define PORTC 3
	#define PORTD 4
	
	#define PIN_INPUT  0
	#define PIN_OUTPUT 1
	
	#define PIN_LOW  0 
	#define PIN_HIGH 1
	
	#define PORT_INPUT  0x00
	#define PORT_OUTPUT 0xFF
	
	#define PORT_LOW  0x00
	#define PORT_HIGH 0xFF
	
	#define EXIT_SUCCESFUL 0
	#define EXIT_FAILURE   1
		
	
	DIO_ERROR_RETVAL_t DIO_PortInit (DIO_PORT_ID_t port, DIO_DIRECTION_t direction);
	DIO_ERROR_RETVAL_t DIO_SetPortVal (DIO_PORT_ID_t port, uint8_t value);
	DIO_ERROR_RETVAL_t DIO_ClrPortVal(DIO_PORT_ID_t DIO_port, uint8_t value);
	uint8_t DIO_GetPortVal (DIO_PORT_ID_t port);
	DIO_ERROR_RETVAL_t DIO_TogPortVal (DIO_PORT_ID_t DIO_port , uint8_t value);
	
	uint8_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection);

	uint8_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue);

	uint8_t DIO_TogglePin(uint8_t PortName,uint8_t PinNo);

	uint8_t DIO_ReadPin(uint8_t PortName,uint8_t PinNo,ptr_uint8_t PinData);

	uint8_t DIO_EnablePinPullup(uint8_t PortName,uint8_t PinNo);

#endif
