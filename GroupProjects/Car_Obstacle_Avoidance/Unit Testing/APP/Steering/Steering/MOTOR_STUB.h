/*
 * MOTOR_STUB.h
 *
 * Created: 8/12/2021 1:03:41 PM
 *  Author: Mohamed Wagdy
 */

#ifndef __MOTOR_STUB_H__
#define __MOTOR_STUB_H__

/*INCLUDES-------------------------------*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*- LOCAL MACROS------------------------------------------*/
/*-----MOTORS NUMBERS-----*/
#define MOTOR1    (uint8_t)0
#define MOTOR2    (uint8_t)1
/*-----MOTOR DIRECTIONS-----*/
#define MOTOR_FORWARD  (uint8_t)1
#define MOTOR_BACKWARD (uint8_t)0
/*-----MOTOR SPEEDS-----*/
#define MOTOR_SPEED_5                            (uint8_t)(5)
#define MOTOR_SPEED_10                           (uint8_t)(10)
#define MOTOR_SPEED_15                           (uint8_t)(15)
#define MOTOR_SPEED_20                           (uint8_t)(20)
#define MOTOR_SPEED_25                           (uint8_t)(25)
#define MOTOR_SPEED_30                           (uint8_t)(30)
#define MOTOR_SPEED_35                           (uint8_t)(35)
#define MOTOR_SPEED_40                           (uint8_t)(40)
#define MOTOR_SPEED_45                           (uint8_t)(45)
#define MOTOR_SPEED_50                           (uint8_t)(50)
#define MOTOR_SPEED_55                           (uint8_t)(55)
#define MOTOR_SPEED_60                           (uint8_t)(60)
#define MOTOR_SPEED_65                           (uint8_t)(65)
#define MOTOR_SPEED_70                           (uint8_t)(70)
#define MOTOR_SPEED_75                           (uint8_t)(75)
#define MOTOR_SPEED_80                           (uint8_t)(80)
#define MOTOR_SPEED_85                           (uint8_t)(85)
#define MOTOR_SPEED_90                           (uint8_t)(90)
#define MOTOR_SPEED_95                           (uint8_t)(95)
#define MOTOR_SPEED_100                          (uint8_t)(100)


/*-----ERROR DEFINATIONS-----*/
/*
		This Error happens if MOTOR is already initialized before
*/
#define           MOTOR_SEC_INIT             (ERROR_STATE_t)( -1 )
/*
 *     This Error happens if MOTOR is not  initialized before
 */
#define           MOTOR_NOT_INIT             (ERROR_STATE_t)(- 2 )
 /*
  *     This Error happens if MOTOR is not  initialized before
  */
#define           MOTOR_INVALID_DIR             (ERROR_STATE_t)(- 3 )
  /*
	*     This Error happens if MOTOR is not  initialized before
	*/
#define           MOTOR_INVALID_CH             (ERROR_STATE_t)(- 4 )
	/*APIs DECLARATIONS------------------------*/
ERROR_STATE_t MOTOR_init(void);
ERROR_STATE_t MOTOR_start(uint8_t motor_no, uint8_t speed, uint8_t dir);

#endif /* __MOTOR_STUB_H__ */