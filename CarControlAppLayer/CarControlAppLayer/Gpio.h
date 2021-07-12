/*
 * File Name: Gpio.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for GPIO peripheral....
 */ 

#ifndef __GPIO__
#define __GPIO__

//FILES INCLUDING
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MC_REGISTERS.h"
#include "Gpio_Config.h"
#include "Gpio_RetVal.h"


//FUNCTIONS PROTOTYPES
uint8_t GpioSetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection);
uint8_t GpioWritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue);
uint8_t GpioTogglePin(uint8_t PortName,uint8_t PinNo);
uint8_t GpioReadPin(uint8_t PortName,uint8_t PinNo,ptr_uint8_t PinData);
uint8_t GpioEnablePinPullup(uint8_t PortName,uint8_t PinNo);

#endif