/*
 * File Name: ICU.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for ICU peripheral....
 */ 

#ifndef __ICU__
#define __ICU__

//FILES INCLUDING
#include "../../Infrastructure/STD_TYPES.h"
#include "../../Infrastructure/BIT_MATH.h"
#include "../../Infrastructure/MC_REGISTERS.h"
#include "../DIO/DIO.h"
#include "ICU_Cfg.h"
#include "ICU_RetVal.h"

#define START_STATE					0
#define WAITING_RISING_EDGE_STATE 	1
#define WAITING_FALLING_EDGE_STATE 	2
#define END_STATE					3

//FUNCTIONS PROTOTYPES
uint8_t ICU_Init(uint8_t ICUNumber);
uint8_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t TimeOnValue);

#endif
