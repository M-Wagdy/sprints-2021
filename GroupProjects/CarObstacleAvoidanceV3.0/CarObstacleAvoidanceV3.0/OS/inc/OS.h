/*
 * File Name: OS.h
 * Creation Date: 08/09/2021
 * Author: Ahmed&Rehab
 * Description: Header File for OS Module....
 */ 

#ifndef __OS__
#define __OS__

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "OS_Interface.h"


extern ERROR_STATE_t OS_Init(void);
extern void OS_Run(void);

#endif
