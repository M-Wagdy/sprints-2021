/*
 * motorRetval.h
 *
 * Created: 7/13/2021 9:18:07 PM
 *  Author: Marco
 */ 


#ifndef MOTORRETVAL_H_
#define MOTORRETVAL_H_

/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include "../../Infrastructure/STD_types.h"

/******************************************************************************
*                              PRIMITIVE TYPES											*
*******************************************************************************/
#define MOTOR_STATUS_t uint8_t


/**
* @brief: This return value indicate that the function could
* run successfully and it returns no errors.
*/
#define MOTOR_SUCCESS (MOTOR_STATUS_t) 0
/**
* @brief: This return value indicate that the function tries
* to use an uninitialized module.
*/
#define MOTOR_INVALID_PORT (MOTOR_STATUS_t) 1
/**
* @brief: This return value indicate that the function tries
* to use an uninitialized module.
*/
#define MOTOR_INVALID_PIN (MOTOR_STATUS_t) 2
/**
* @brief: This return value indicate that the function tries
* to use an uninitialized module.
*/
#define MOTOR_INVALID_DIRECTION (MOTOR_STATUS_t) 3

#endif /* MOTORRETVAL_H_ */