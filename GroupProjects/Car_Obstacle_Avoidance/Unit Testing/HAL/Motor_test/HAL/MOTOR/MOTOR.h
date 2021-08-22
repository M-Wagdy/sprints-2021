#ifndef MOTOR_H_
#define MOTOR_H_
/*INCLUDES-------------------------------*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/PWM/PWM.h"
#include "MOTOR_Lcfg.h"

/*- LOCAL MACROS------------------------------------------*/
/****MOTORS NUMBERS****/
#define MOTOR1    (uint8_t)0
#define MOTOR2    (uint8_t)1
/****MOTOR DIRECTIONS****/
#define MOTOR_FORWARD  (uint8_t)1
#define MOTOR_BACKWARD (uint8_t)0
/***ERROR DEFINATIONS***/
/*
		This Error happens if USONIC is already initialized before
*/
#define           MOTOR_SEC_INIT             (ERROR_STATE_t)( -1 )
/*
 *     This Error happens if USONIC is not  initialized before
 */
#define           MOTOR_NOT_INIT             (ERROR_STATE_t)(- 2 )
/*
 *     This Error happens if USONIC is not  initialized before
 */
#define           MOTOR_INVALID_DIR             (ERROR_STATE_t)(- 3 )
/*
 *     This Error happens if USONIC is not  initialized before
 */
#define           MOTOR_INVALID_CH             (ERROR_STATE_t)(- 4 )

/*APIs DECLARATIONS------------------------*/
ERROR_STATE_t MOTOR_init(void);
ERROR_STATE_t MOTOR_stop(uint8_t motor_no);
ERROR_STATE_t MOTOR_start(uint8_t motor_no, uint8_t speed,uint8_t dir);
ERROR_STATE_t MOTOR_Update_dir(uint8_t motor_no,uint8_t dir);
#endif
