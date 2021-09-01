/*
 * CRASH.h
 *
 * Created: 8/16/2021 1:31:13 PM
 *  Author: Mohamed Wagdy 
 */ 


#ifndef __CRASH_H__
#define __CRASH_H__

/*INCLUDES-------------------------------*/
#include "STD_TYPES.h"
#include "SENSING_Interface.h"
#include "STEERING_Interface.h"
#include "CRASH_Interface.h"

/*APIs DECLARATIONS------------------------*/

/* Main Function. */
extern void CRASH_MainFunction(void);

extern ERROR_STATE_t CRASH_Logic(double64_t gd64_distance, uint8_t * CarDirection, uint16_t * CarSpeed);
#endif /* __CRASH_H__ */