/*
 * Motor.c
 *
 * Created: 7/25/2021 4:20:25 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Motor.h"

/*- LOCAL MACROS
------------------------------------------*/
#define HIGH         (uint8_t)(1)
#define LOW          (uint8_t)(0)

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef MOTOR_CH_0
extern const uint8_t MOTOR_CH_0_PORT;
extern const uint8_t MOTOR_CH_0_PIN;
#endif

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initializes a motor.
*
* @param [in]  MOTOR_CH   -  Motor channel number.
*
* @return function error state.
*/
MOTOR_ERROR_state_t MOTOR_Init(uint8_t MOTOR_CH)
{
   uint8_t u8_MotorPort;
   uint8_t u8_MotorPin;
   
   switch(MOTOR_CH)
   {
      #ifdef MOTOR_CH_0
      case MOTOR_CH_0:
         u8_MotorPort = MOTOR_CH_0_PORT;
         u8_MotorPin = MOTOR_CH_0_PIN;
         break;
      #endif
      default:
         return E_MOTOR_INVALID_CH;
   }   
   
   /* Initialize motor pin */
   DIO_SetPinDirection(u8_MotorPort, u8_MotorPin, OUTPUT);
   
   /* return success status */
   return E_MOTOR_SUCCESS;
}

/**
* @brief: This function Starts a motor.
*
* @param [in]  MOTOR_CH   -  Motor channel number.
*
* @return function error state.
*/
MOTOR_ERROR_state_t MOTOR_Start(uint8_t MOTOR_CH)
{
   uint8_t u8_MotorPort;
   uint8_t u8_MotorPin;
   
   switch(MOTOR_CH)
   {
      #ifdef MOTOR_CH_0
      case MOTOR_CH_0:
         u8_MotorPort = MOTOR_CH_0_PORT;
         u8_MotorPin = MOTOR_CH_0_PIN;
         break;
      #endif
      default:
         return E_MOTOR_INVALID_CH;
   }
   
   /* Start motor */
   DIO_WritePin(u8_MotorPort, u8_MotorPin, HIGH);
   
   /* return success status */
   return E_MOTOR_SUCCESS;
}

/**
* @brief: This function Stops a motor.
*
* @param [in]  MOTOR_CH   -  Motor channel number.
*
* @return function error state.
*/
MOTOR_ERROR_state_t MOTOR_Stop(uint8_t MOTOR_CH)
{
   uint8_t u8_MotorPort;
   uint8_t u8_MotorPin;
   
   switch(MOTOR_CH)
   {
      #ifdef MOTOR_CH_0
      case MOTOR_CH_0:
         u8_MotorPort = MOTOR_CH_0_PORT;
         u8_MotorPin = MOTOR_CH_0_PIN;
         break;
      #endif
      default:
         return E_MOTOR_INVALID_CH;
   }
   
   /* stop motor */
   DIO_WritePin(u8_MotorPort, u8_MotorPin, LOW);
   
   /* return success status */
   return E_MOTOR_SUCCESS;
}