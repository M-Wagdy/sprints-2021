/*
 * icu.h
 *
 *  Created on: Aug 10, 2021
 *      Author: Ahmed
 */

#ifndef MCAL_ICU_ICU_H_
#define MCAL_ICU_ICU_H_
#include"../../Infrastructure/infrastructure.h"

#define START_STATE					0
#define WAITING_RISING_EDGE_STATE 	1
#define WAITING_FALLING_EDGE_STATE 	2
#define END_STATE					3

enum Enu_ICUNumber
{
	ICU_1 = 1,
};

uint8_t ICU_Init(uint8_t ICUNumber);
uint8_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t OnTime);
#endif /* MCAL_ICU_ICU_H_ */
