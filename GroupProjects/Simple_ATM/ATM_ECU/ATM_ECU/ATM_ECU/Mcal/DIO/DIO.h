/*
 * File Name: DIO.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for DIO peripheral....
 */ 

#ifndef __DIO__
#define __DIO__

//FILES INCLUDING
#include "../../Infrastructure/STD_types.h"
#include "../../Infrastructure/BIT_MATH.h"
#include "../MC_REGISTERS.h"
#include "DIO_Config.h"
#include "DIO_RetVal.h"


//FUNCTIONS PROTOTYPES
uint8_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection);
uint8_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue);
uint8_t DIO_TogglePin(uint8_t PortName,uint8_t PinNo);
uint8_t DIO_ReadPin(uint8_t PortName,uint8_t PinNo,uint8_t * PinData);
uint8_t DIO_EnablePinPullup(uint8_t PortName,uint8_t PinNo);

#endif