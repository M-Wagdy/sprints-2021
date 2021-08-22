/*
 * File Name: ICU_Lcfg.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for ICU Linker Configuration ...
 */ 
 
#ifndef __ICU_LCFG__
#define __ICU_LCFG__

#include "../../LIB/STD_TYPES.h"

#define ICU_CHANNEL_NUMBERS (1)

enum Enu_ICU1Mode
{
	ICU1_NORMAL_MODE = 0,
};

enum Enu_ICU1ClkSource
{
	ICU1_NO_CLK 	= 0,
	ICU1_CLK_1 		= 1,
	ICU1_CLK_8 		= 2,
	ICU1_CLK_64 	= 3,
	ICU1_CLK_256 	= 4,
	ICU1_CLK_1024 	= 5
};	

enum Enu_ICU1Prescaler
{
	ICU1_PRESC_1 		= 1,
	ICU1_PRESC_8 		= 8,
	ICU1_PRESC_64 		= 64,
	ICU1_PRESC_256 		= 256,
	ICU1_PRESC_1024 	= 1024
};

typedef struct Str_ICUConfig
{
	uint8_t ICUMode;
	uint8_t ICUClkSource;
	uint16_t ICUPrescaler;
}Str_ICUConfig_t ;

#endif