/*
 * File Name: Pwm.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for PWM peripheral....
 */ 

#ifndef __PWM__
#define __PWM__

//FILES INCLUDING
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MC_REGISTERS.h"
#include "Pwm_Config.h"
#include "Pwm_RetVal.h"


//FUNCTIONS PROTOTYPES
uint8_t PwmInit(void);
uint8_t PwmStart(uint8_t PwmChannelNumber);
uint8_t PwmStop(uint8_t PwmChannelNumber);
uint8_t PwmConnect(uint8_t PwmChannelNumber,uint8_t ConnectedPin);
uint8_t PwmDisconnect(uint8_t PwmChannelNumber,uint8_t ConnectedPin);
uint8_t PwmSetDuty(uint8_t PwmChannelNumber,uint8_t PwmDuty);

#endif
