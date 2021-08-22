/*
 * File Name: DIO.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for DIO peripheral....
 */

#ifndef __DIO__
#define __DIO__

//FILES INCLUDING
#include "../../LIB/STD_TYPES.h"
#include "DIO_Cfg.h"


//FUNCTIONS PROTOTYPES
ERROR_STATE_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection);
ERROR_STATE_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue);
ERROR_STATE_t DIO_TogglePin(uint8_t PortName,uint8_t PinNo);
ERROR_STATE_t DIO_ReadPin(uint8_t PortName,uint8_t PinNo,uint8_t * PinData);
ERROR_STATE_t DIO_EnablePinPullup(uint8_t PortName,uint8_t PinNo);

#endif
