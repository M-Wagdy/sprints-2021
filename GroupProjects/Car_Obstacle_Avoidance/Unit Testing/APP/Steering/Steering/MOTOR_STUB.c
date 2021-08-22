/*
 * MOTOR_STUB.c
 *
 * Created: 8/12/2021 1:03:41 PM
 *  Author: Mohamed Wagdy
 */

 /*INCLUDES-------------------------------*/
#include "MOTOR_STUB.h"

/*----GLOBAL STATIC VARIABLES----*/
static ERROR_STATE_t gu8_ERROR_STAT = ERROR_OK;
static uint8_t gu8_InitFlag = NOT_INIT;

/*APIs IMPLEMENTATION------------------------*/
ERROR_STATE_t MOTOR_init(void) {
   /*CHECK IF MOTORS HAS BEEN INITIALIZED*/
   if (INIT == gu8_InitFlag) {//IF MOTORS IS INITIALIZED
      gu8_ERROR_STAT = MOTOR_SEC_INIT;//STORE SEC INIT IN ERRROR STAT
   }
   else if (NOT_INIT == gu8_InitFlag) {//IF MOTORS IS NOT INITIALIZED
      gu8_InitFlag = INIT;//SET INIT FLAG
      gu8_ERROR_STAT = ERROR_OK;//STORE ERROR_OK IN ERRROR STAT
   }
   /*STOP MOTOER EN PINS AT THE START*/
   return gu8_ERROR_STAT;//RETURN FROM THE API
}

ERROR_STATE_t MOTOR_start(uint8_t motor_no, uint8_t speed, uint8_t dir) {
   if (NOT_INIT == gu8_InitFlag) { //IF MOTOR IS NOT INITIALIZED
      gu8_ERROR_STAT = MOTOR_NOT_INIT; //STORE NOT INIT IN ERRROR STAT
   }
   else {
      gu8_ERROR_STAT = ERROR_OK;//STORE ERROR_OK IN ERRROR STAT
   }
   
   return gu8_ERROR_STAT;
}