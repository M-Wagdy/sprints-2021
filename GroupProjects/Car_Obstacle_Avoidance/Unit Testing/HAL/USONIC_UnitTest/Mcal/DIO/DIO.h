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


#include "DIO_Config.h"



//FUNCTIONS PROTOTYPES
uint8_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection);
uint8_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue);


#endif
