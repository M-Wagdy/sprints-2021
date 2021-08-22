/*
 * File Name: ICU.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for ICU peripheral....
 */ 

#ifndef __ICU__
#define __ICU__

//FILES INCLUDING
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "ICU_Cfg.h"
#include "ICU_Lcfg.h"

//ICU_UpdateTimeOn() States
#define START_STATE					0
#define WAITING_RISING_EDGE_STATE 	1
#define WAITING_FALLING_EDGE_STATE 	2
#define END_STATE					3


enum Enu_ICUNumber
{
	ICU_1 = 0,
};


//FUNCTIONS PROTOTYPES
ERROR_STATE_t ICU_Init(uint8_t ICUNumber);
ERROR_STATE_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t TimeOnValue);

#endif