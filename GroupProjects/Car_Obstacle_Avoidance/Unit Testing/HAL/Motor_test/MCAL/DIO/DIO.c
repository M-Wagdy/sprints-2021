/*
 * File Name: DIO.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for DIO peripheral....
 */

#include "DIO.h"

ERROR_STATE_t DIO_SetPinDirection(uint8_t PortName , uint8_t PinNo ,uint8_t PinDirection)
{

	return ERROR_OK;
}

ERROR_STATE_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue)
{

	return ERROR_OK;
}
ERROR_STATE_t DIO_TogglePin(uint8_t PortName,uint8_t PinNo)
{

	return ERROR_OK;
}
ERROR_STATE_t DIO_ReadPin(uint8_t PortName,uint8_t PinNo,ptr_uint8_t PinData)
{

	return ERROR_OK;
}


ERROR_STATE_t DIO_EnablePinPullup(uint8_t PortName,uint8_t PinNo)
{

	return ERROR_OK;
}
