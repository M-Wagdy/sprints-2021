/*
 * usonic.c
 *
 *  Created on: Aug 9, 2021
 *      Author: Ahmed
 */
/*INCLUDES-------------------------------*/
#include "usonic.h"

/*----GLOBAL STATIC VARIABLES----*/
static uint8_t gu8_ERROR_STAT = USONIC_SUCCESS;
static uint8_t gu8_InitFlag = NOT_INIT;
/*LOCAL MACROS--------------------------*/
#define TRIG_TIME   (uint8_t)10
#define SOUND_SPPED  34300
/*APIs IMPLEMENTATION------------------------*/
/*
 * THIS API INITIALIZE THE ULTRASONIC
 * */
USONIC_ERROR_state_t USONIC_Init(void) {
	/*CHECK IF ULTASONIC HAS BEEN INITIALIZED*/
	if (INIT == gu8_InitFlag) {//IF ULTRA SONIC IS INITIALIZED
		gu8_ERROR_STAT = USONIC_SEC_INIT;//STORE SEC INIT IN ERRROR STAT
	} else if (NOT_INIT == gu8_InitFlag) {//IF ULTRA SONIC IS NOT INITIALIZED
		DIO_SetPinDirection(USONIC_TRIG_PORT, USONIC_TRIG_PIN, PIN_OUTPUT); //SET THE TRIGGER PIN AS AN OUTPUT
		ICU_Init(ICU_1); //INIT THE ICU CH 1
		gu8_InitFlag = INIT;
		gu8_ERROR_STAT=USONIC_SUCCESS;
	} else {
		//DO NOTHING
	}
	return gu8_ERROR_STAT ;
}
/*
 * THIS API GET THE DISTANCE
 * */
USONIC_ERROR_state_t USONIC_GetDistance(ptr_double64_t distance) {
	static uint8_t ICU_STAT = START_STATE;
	double64_t au64_TIME = 0;
	/*CHECK IF ULTASONIC HAS BEEN INITIALIZED*/
	if (NOT_INIT == gu8_InitFlag) { //IF ULTRA SONIC IS NOT INITIALIZED
		gu8_ERROR_STAT = USONIC_NOT_INIT; //STORE NOT INIT IN ERRROR STAT
	} else if (INIT == gu8_InitFlag) { //IF ULTRA SONIC IS INITIALIZED
		/*CHECK IF ptr_float32_t distance EUALS NULL */
		if (NULL_PTR == distance) {
			gu8_ERROR_STAT = USONIC_NULL_POINTER; //STORE NOT INIT IN ERRROR STAT
		} else {
			/*CHECK IF THE ICU IS NOT STARTED YET*/
			if (START_STATE == ICU_STAT) {
            gu8_ERROR_STAT = NOT_OK;
				/*FIRE THE ULTASONIC TRIGGER*/
				DIO_WritePin(USONIC_TRIG_PORT, USONIC_TRIG_PIN, PIN_HIGH); //SET TRIGGER PIN
				do
					TIM_DelayUs(TIMER_2, TRIG_TIME); //WAIT 10 MICRO SEC
				while (OK != TIM_DelayUs(TIMER_2, TRIG_TIME));
				DIO_WritePin(USONIC_TRIG_PORT, USONIC_TRIG_PIN, PIN_LOW); //CLEAR TRIGER PIN
				ICU_UpdateTimeOn(ICU_1, &ICU_STAT, &au64_TIME); //START ICU
			} else  { //IF ICU IS NOT FINISHED
				ICU_UpdateTimeOn(ICU_1, &ICU_STAT, &au64_TIME); //CALL ICU UPDATE
				gu8_ERROR_STAT = USONIC_PENDING; //STORE PENDING
            if (END_STATE == ICU_STAT) { //IF ICU IS FINISHED
               *(distance) = (((SOUND_SPPED) * au64_TIME) / 2); //CALCULATE THE DISTANCE
               ICU_STAT = START_STATE; //RESET ICU STAT
               gu8_ERROR_STAT = OK; //RETURN OK(FINISHED)
            }
			}
		}
	} else {
		//DO NOTHING
	}
	return gu8_ERROR_STAT; //RETURN API STAT
}
