/*
 * File Name: ICU.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for ICU peripheral....
 */ 

#ifndef __ICU__
#define __ICU__

//FILES INCLUDING
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO.h"
#include "ICU_Cfg.h"
#include "ICU_Lcfg.h"


#define START_STATE					0
#define WAITING_RISING_EDGE_STATE 	1
#define WAITING_FALLING_EDGE_STATE 	2
#define END_STATE					3

#define ICU1_MAX_COUNT 		((uint16_t)65535)

#define ICU1_OVERFLOW_INT		0
#define ICU1_INPUTCAPTURE_INT	1

enum Enu_ICU1EdgeDetector
{
   ICU1_FALLING_EDGE = 0,
   ICU1_RISING_EDGE = 1
};

enum Enu_ICUNumber
{
	ICU_1 = 0,
};

extern Str_ICUConfig_t gastr_ICUConfig[ICU_CHANNEL_NUMBERS];

//FUNCTIONS PROTOTYPES
ERROR_STATE_t ICU_Init(uint8_t ICUNumber);
ERROR_STATE_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t TimeOnValue);
ERROR_STATE_t ICU_Reset(uint8_t ICUNumber,uint8_t ICUEdgeDetector);

ERROR_STATE_t ICU_GetICR1Registert(uint8_t ICUNumber,ptr_uint16_t Register);
ERROR_STATE_t ICU_GetTIFRRegistert(uint8_t ICUNumber,ptr_uint8_t Register);
ERROR_STATE_t ICU_SetTCNT1Registert(uint8_t ICUNumber,uint16_t RegisterValue);

ERROR_STATE_t ICU_EnableInterrupt(uint8_t ICUNumber,uint8_t ICUInterruptType);
ERROR_STATE_t ICU_DisableInterrupt(uint8_t ICUNumber,uint8_t ICUInterruptType);

ERROR_STATE_t ICU_SetCallback(uint8_t ICUNumber,uint8_t ICUInterruptType,Ptr_VoidFuncVoid_t Callback);
#endif