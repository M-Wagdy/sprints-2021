#ifndef MOTOR_H_
#define MOTOR_H_
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MC_REGISTERS.h"
#include "Pwm.h"
#include "Gpio.h"
/****MOTORS NUMBERS****/
#define MOTER1    (uint8_t)0
#define MOTER2    (uint8_t)1
/****MOTORS SPEED****/
#define MOTOR_SPEED1	(uint8_t)30
#define MOTOR_SPEED2	(uint8_t)60
#define MOTOR_SPEED3	(uint8_t)90
/****MOTOR DIRECTIONS****/
#define MOTOR1_FORWARD  (uint8_t)1
#define MOTOR1_BACKWARD (uint8_t)0
#define MOTOR2_FORWARD  (uint8_t)1
#define MOTOR2_BACKWARD (uint8_t)0
/****FUNCTIONS PROTOTYPES****/
void MOTOR_init(void);
void MOTOR_stop(uint8_t motor_no);
void MOTOR_start(uint8_t motor_no,uint8_t speed,uint8_t dir);
void MOTOR_speed(uint8_t motor_no,uint8_t speed);
void MOTOR_dir(uint8_t motor_no,uint8_t dir);
#endif
