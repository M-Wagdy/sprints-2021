/*
 * ROBOT_Control.h
 *
 * Created: 8/12/2021 4:25:21 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __ROBOT_CONTROL_H__
#define __ROBOT_CONTROL_H__

/*INCLUDES-------------------------------*/
#include "TIMER_STUB.h"
#include "USONIC_STUB.h"
#include "LCD_STUB.h"
#include "STEERING_STUB.h"

/*APIs DECLARATIONS------------------------*/

/* Initialize all motors of the car. */
ERROR_STATE_t RC_Init(void);

/* Move Car to a given direction. */
ERROR_STATE_t RC_Update(void);

#endif /* __ROBOT_CONTROL_H__ */