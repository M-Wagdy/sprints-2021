/*
 * motor.h
 *
 * Created: 7/28/2021 12:07:24 PM
 *  Author: Marco
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include "motorConfig.h"
#include "motorRetval.h"

/******************************************************************************
*                               FUNCTION DECLARATIONS                         *
*******************************************************************************/
MOTOR_STATUS_t MOTOR_INIT(void);
MOTOR_STATUS_t MOTOR_START(void);
MOTOR_STATUS_t MOTOR_STOP(void);
MOTOR_STATUS_t MOTOR_STATUS(uint8_t * status);

#endif /* MOTOR_H_ */