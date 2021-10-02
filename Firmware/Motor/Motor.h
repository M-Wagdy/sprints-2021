/*
 * Motor.h
 *
 * Created: 7/25/2021 4:20:05 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __MOTOR_H__
#define __MOTOR_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "DIO.h"
#include "Motor_retval.h"
#include "Motor_Config.h"

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize motor */
MOTOR_ERROR_state_t MOTOR_Init(uint8_t MOTOR_CH);

/* starts a motor */
MOTOR_ERROR_state_t MOTOR_Start(uint8_t MOTOR_CH);

/* stops a motor */
MOTOR_ERROR_state_t MOTOR_Stop(uint8_t MOTOR_CH);

#endif /* __MOTOR_H__ */