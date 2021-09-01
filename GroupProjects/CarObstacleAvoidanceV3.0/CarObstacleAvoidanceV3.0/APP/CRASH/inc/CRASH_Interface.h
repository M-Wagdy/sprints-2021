/*
 * CRASH_Interface.h
 *
 * Created: 8/19/2021 11:18:58 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __CRASH_INTERFACE_H__
#define __CRASH_INTERFACE_H__

/*INCLUDES-------------------------------*/
#include "STD_TYPES.h"

/*- MACROS -------------------------------------------------*/
/*DIRECTIONS*/
#define  STEERING_FORWARD           (uint8_t)( 0 )
#define  STEERING_BACKWARD          (uint8_t)( 1 )
#define  STEERING_RIGHT             (uint8_t)( 2 )
#define  STEERING_LEFT              (uint8_t)( 3 )
#define  INVALID_STEERING           (uint8_t)( 4 )
/*SPEEDS*/
#define  STEERING_MAX_SPEED         (uint16_t)(100)
#define  STEERING_MIN_SPEED         (uint16_t)(0)

/*APIs DECLARATIONS------------------------*/
/*Set the direction and speed*/
extern ERROR_STATE_t  CRASH_SetSpeed(uint16_t Speed );
extern ERROR_STATE_t  CRASH_SetDirection(uint8_t  Dir);

/*Get the direction and speed*/
extern ERROR_STATE_t  CRASH_GetSpeed(ptr_uint16_t Speed );
extern ERROR_STATE_t  CRASH_GetDirection(ptr_uint8_t  Dir);

#endif /* __CRASH_INTERFACE_H__ */