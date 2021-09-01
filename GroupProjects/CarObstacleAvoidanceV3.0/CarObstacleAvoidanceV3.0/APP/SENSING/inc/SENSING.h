/*
 * File Name: SENSING.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: Header File for Sensing Module....
 */ 

#ifndef __SENSING__
#define __SENSING__

//FILES INCLUDING
#include "STD_TYPES.h"
#include "USONIC.h"
#include "SENSING_Interface.h"

//FUNCTIONS PROTOTYPES
void SENSING_MainFunction(void);

extern ERROR_STATE_t SENSING_Init(void);
#endif
