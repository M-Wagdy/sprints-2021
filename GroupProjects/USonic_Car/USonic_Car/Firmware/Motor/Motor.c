/*INCLUDES-------------------------------*/
#include"Motor.h"
/*----GLOBAL STATIC VARIABLES----*/
static uint8_t gu8_ERROR_STAT = MOTOR_SUCCESS;
static uint8_t gu8_InitFlag = NOT_INIT;
/*APIs IMPLEMENTATION------------------------*/
uint8_t MOTOR_init(void) {
		/*CHECK IF MOTORS HAS BEEN INITIALIZED*/
	if (INIT == gu8_InitFlag) {//IF MOTORS IS INITIALIZED
		gu8_ERROR_STAT = MOTOR_SEC_INIT;//STORE SEC INIT IN ERRROR STAT
	} else if (NOT_INIT == gu8_InitFlag) {//IF MOTORS IS NOT INITIALIZED
	PwmInit();
   /*SETTING MOTOR1 DIR PINS TO OUTPUT*/
	DIO_SetPinDirection(PORT_B, PIN3, PIN_OUTPUT);
	DIO_SetPinDirection(MOTOR1_PORT, MOTOR1_PIN1, PIN_OUTPUT);
	DIO_SetPinDirection(MOTOR1_PORT, MOTOR1_PIN2, PIN_OUTPUT);
	/*SETTING MOTOR2 DIR PINS TO OUTPUT*/
	DIO_SetPinDirection(MOTOR2_PORT, MOTOR2_PIN1, PIN_OUTPUT);
	DIO_SetPinDirection(MOTOR2_PORT, MOTOR2_PIN2, PIN_OUTPUT);
   /*START THE PWM WAVE*/
   PwmStart(PWM_CHANNEL_OC0);
	gu8_InitFlag = INIT;//SET INIT FLAG
	gu8_ERROR_STAT = MOTOR_SUCCESS;//STORE MOTOR_SUCCESS IN ERRROR STAT
	}
	/*STOP MOTOER EN PINS AT THE START*/
	return gu8_ERROR_STAT ;//RETURN FROM THE API
}
MOTOR_ERROR_state_t MOTOR_start(uint8_t motor_no, uint8_t speed,  uint8_t dir) {
	if (NOT_INIT == gu8_InitFlag) { //IF MOTOR IS NOT INITIALIZED
		gu8_ERROR_STAT = MOTOR_NOT_INIT; //STORE NOT INIT IN ERRROR STAT
	} else if (INIT == gu8_InitFlag) { //IF MOTOR IS INITIALIZED
      PwmSetDuty(PWM_CHANNEL_OC0, speed);
      PwmConnect(PWM_CHANNEL_OC0);
	switch (motor_no) {
	case MOTOR1 :
		switch (dir) {
		case MOTOR_FORWARD :
			DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1,PIN_HIGH);
			DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2,PIN_LOW);
			break;
		case MOTOR_BACKWARD :
			DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1,PIN_LOW);
			DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2,PIN_HIGH);
			break;
		default:
		gu8_ERROR_STAT=MOTOR_INVALID_DIR;
		//RETURN MOTOR_INVALID_DIR
			break;
		}
		break;
	case MOTOR2 :
		switch (dir) {
		case MOTOR_FORWARD :
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1,PIN_HIGH);
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2,PIN_LOW);
			break;
		case MOTOR_BACKWARD :
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1,PIN_LOW);
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2,PIN_HIGH);
			break;
		default:
		gu8_ERROR_STAT=MOTOR_INVALID_DIR;
			break;
		}
		break;
	default:
	gu8_ERROR_STAT=MOTOR_INVALID_CH;
		break;
	}
	}
	return gu8_ERROR_STAT ;
}
MOTOR_ERROR_state_t MOTOR_stop(uint8_t motor_no) {
	
   switch (motor_no){
	case MOTOR1:
      DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1,PIN_HIGH);
      DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2,PIN_HIGH);
		break;
	case MOTOR2:
		DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1,PIN_HIGH);
		DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2,PIN_HIGH);
		break;
	default:
	gu8_ERROR_STAT=MOTOR_INVALID_CH;
		break;
	}
	return gu8_ERROR_STAT ;
}
MOTOR_ERROR_state_t MOTOR_Update_dir(uint8_t motor_no, uint8_t dir) {
	switch (motor_no) {
		case MOTOR1 :
			switch (dir) {
			case MOTOR_FORWARD :
				DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1,PIN_HIGH);
				DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2,PIN_LOW);
				break;
			case MOTOR_BACKWARD :
				DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN1,PIN_LOW);
				DIO_WritePin(MOTOR1_PORT, MOTOR1_PIN2,PIN_HIGH);
				break;
			default:
			gu8_ERROR_STAT=MOTOR_INVALID_DIR;
				break;
			}
			break;
		case MOTOR2 :
			switch (dir) {
			case MOTOR_FORWARD :
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1,PIN_HIGH);
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2,PIN_LOW);
				break;
			case MOTOR_BACKWARD :
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN1,PIN_LOW);
			DIO_WritePin(MOTOR2_PORT, MOTOR2_PIN2,PIN_HIGH);
				break;
			default:
			gu8_ERROR_STAT=MOTOR_INVALID_DIR;
				break;
			}
			break;
		default:
		gu8_ERROR_STAT=MOTOR_INVALID_CH;
			break;
		}
		return gu8_ERROR_STAT ;
}
