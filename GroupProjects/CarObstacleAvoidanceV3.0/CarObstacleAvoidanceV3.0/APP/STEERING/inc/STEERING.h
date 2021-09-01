/*
 * STEERING.h
 *
 * Created: 8/16/2021 4:46:42 PM
 *  Author: Ahmed Essam
 */ 


#ifndef __STEERING_H__
#define __STEERING_H__

/*INCLUDES-------------------------------*/
#include "STD_TYPES.h"
#include "MOTOR.h"
#include "CRASH.h"
#include "STEERING_Interface.h"

/*APIs DECLARATIONS------------------------*/


/* Main Function. */
extern void STEERING_MainFunction(void);

extern ERROR_STATE_t STEERING_Init(void);

#endif /* __STEERING_H__ */