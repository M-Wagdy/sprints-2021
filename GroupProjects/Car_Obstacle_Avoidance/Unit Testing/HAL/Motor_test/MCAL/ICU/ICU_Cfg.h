/*
 * File Name: ICU_Config.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for ICU Configuration ...
 */ 
 
#ifndef __ICU_CONFIG__
#define __ICU_CONFIG__

#define ICU_NUMBERS 1

#define ICU1 1
#if ICU1
	#define ICU1_PORT			PORT_D
	#define ICU1_PIN			PIN6
	#define ICU1_MODE			ICU1_NORMAL_MODE
	#define ICU1_MAX_COUNT 		((uint16_t)65535)
	#define ICU1_CLK_SOURCE 	ICU1_CLK_1024
	#define ICU1_PRESCALER		ICU1_PRESC_1024
#endif

enum Enu_ICUNumber
{
	ICU_1 = 0,
};

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

enum Enu_ICU1EdgeDetector
{
	ICU1_FALLING_EDGE = 0,
	ICU1_RISING_EDGE = 1
};

#endif