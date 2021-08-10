#ifndef MOTOR_H_
#define MOTOR_H_
/*INCLUDES-------------------------------*/
#include "Infrastructure/STD_TYPES.h"
#include "Infrastructure/BIT_MATH.h"
#include "Infrastructure/MC_REGISTERS.h"
#include "Mcal/DIO/DIO.h"
#include "MotorRetVal.h"
#include "MotorConfig.h"

/*- LOCAL MACROS------------------------------------------*/
/****MOTORS NUMBERS****/
#define MOTOR1    (uint8_t)0
#define MOTOR2    (uint8_t)1
/****MOTOR DIRECTIONS****/
#define MOTOR_FORWARD  (uint8_t)1
#define MOTOR_BACKWARD (uint8_t)0
/*APIs DECLARATIONS------------------------*/
MOTOR_ERROR_state_t MOTOR_init(void);
MOTOR_ERROR_state_t MOTOR_stop(uint8_t motor_no);
MOTOR_ERROR_state_t MOTOR_start(uint8_t motor_no,uint8_t dir);
MOTOR_ERROR_state_t MOTOR_Update_dir(uint8_t motor_no,uint8_t dir);
#endif
