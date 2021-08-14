/*
 * File Name: Gpio_Config.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for GPIO Configuration ...
 */ 
 
#ifndef __GPIO_CONFIG__
#define __GPIO_CONFIG__

//PORTS NAME
enum Enu_GpioPortName
{
	PORT_A = 0,
	PORT_B = 1,
	PORT_C = 2,
	PORT_D = 3	
};

//PINS
enum Enu_GpioPinNumber
{
	PIN0 = 0,
	PIN1 = 1,
	PIN2 = 2,
	PIN3 = 3,
	PIN4 = 4,
	PIN5 = 5,
	PIN6 = 6,
	PIN7 = 7	
};

//PIN Directions
enum Enu_GpioPinDirection
{
	PIN_INPUT = 0,
	PIN_OUTPUT = 1
};

enum Enu_GpioPinValue
{
	PIN_LOW = 0,
	PIN_HIGH = 1
};

#endif