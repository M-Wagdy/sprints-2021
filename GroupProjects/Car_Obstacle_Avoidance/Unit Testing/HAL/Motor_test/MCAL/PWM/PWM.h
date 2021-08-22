/*
 * File Name: PWM.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for PWM peripheral....
 */

#ifndef __PWM__
#define __PWM__

//FILES INCLUDING
#include "../../LIB/STD_TYPES.h"
#include "PWM_Cfg.h"

//FUNCTIONS PROTOTYPES
ERROR_STATE_t PwmInit(void);
ERROR_STATE_t PwmStart(uint8_t PwmChannelNumber);
ERROR_STATE_t PwmStop(uint8_t PwmChannelNumber);
ERROR_STATE_t PwmConnect(uint8_t PwmChannelNumber);
ERROR_STATE_t PwmDisconnect(uint8_t PwmChannelNumber);
ERROR_STATE_t PwmSetDuty(uint8_t PwmChannelNumber,uint8_t PwmDuty);

#endif
