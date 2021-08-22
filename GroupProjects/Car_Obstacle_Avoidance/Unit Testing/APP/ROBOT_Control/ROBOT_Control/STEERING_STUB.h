/*
 * STEERING.h
 *
 * Created: 8/12/2021 1:02:44 PM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __STEERING_H__
#define __STEERING_H__

/*INCLUDES-------------------------------*/
#include "STD_TYPES.h"

/*- MACROS -------------------------------------------------*/
#define  STEERING_FORWARD           (uint8_t)( 0 )
#define  STEERING_BACKWARD          (uint8_t)( 1 )
#define  STEERING_RIGHT             (uint8_t)( 2 )
#define  STEERING_LEFT              (uint8_t)( 3 )
#define  INVALID_STEERING           (uint8_t)( 4 )

/*APIs DECLARATIONS------------------------*/

/* Initialize all motors of the car. */
ERROR_STATE_t STEERING_Init(void);

/* Move Car to a given direction. */
ERROR_STATE_t STEERING_Move(uint8_t Direction);

#endif /* __STEERING_H__ */