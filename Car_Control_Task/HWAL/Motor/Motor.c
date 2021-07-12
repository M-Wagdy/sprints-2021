#include"Motor.h"

void MOTOR_init(void) {
	PwmInit();
	/*SETTING MOTOR1 DIR PINS TO OUTPUT*/
	GpioSetPinDirection(PORT_D, PIN4, PIN_OUTPUT);
	GpioSetPinDirection(PORT_D, PIN2, PIN_OUTPUT);
	GpioSetPinDirection(PORT_D, PIN3, PIN_OUTPUT);
	/*SETTING MOTOR2 DIR PINS TO OUTPUT*/
	GpioSetPinDirection(PORT_D, PIN5, PIN_OUTPUT);
	GpioSetPinDirection(PORT_D, PIN6, PIN_OUTPUT);
	GpioSetPinDirection(PORT_D, PIN7, PIN_OUTPUT);
	/*START THE PWM WAVE*/
	PwmStart(PWM_CHANNEL_OC1A);
	/*STOP MOTOER EN PINS AT THE START*/

}
void MOTOR_start(uint8_t motor_no, uint8_t speed, uint8_t dir) {
	switch (motor_no) {
	case MOTER1 :
		PwmSetDuty(PWM_CHANNEL_OC1A, speed);
		PwmConnect(PWM_CHANNEL_OC1A);
		switch (dir) {
		case MOTOR1_FORWARD :
			GpioWritePin(PORT_D, PIN2,PIN_HIGH);
			GpioWritePin(PORT_D, PIN3,PIN_LOW);
			break;
		case MOTOR1_BACKWARD :
			GpioWritePin(PORT_D, PIN2,PIN_LOW);
			GpioWritePin(PORT_D, PIN3,PIN_HIGH);
			break;
		default:
			break;
		}
		break;
	case MOTER2 :
		PwmSetDuty(PWM_CHANNEL_OC1B, speed);
		PwmConnect(PWM_CHANNEL_OC1B);
		switch (dir) {
		case MOTOR2_FORWARD :
			GpioWritePin(PORT_D, PIN6,PIN_HIGH);
			GpioWritePin(PORT_D, PIN7,PIN_LOW);
			break;
		case MOTOR2_BACKWARD :
			GpioWritePin(PORT_D, PIN6,PIN_LOW);
			GpioWritePin(PORT_D, PIN7,PIN_HIGH);
			break;
		default:
			break;

		}
		break;
	default:
		break;
	}

}
void MOTOR_stop(uint8_t motor_no) {
	switch (motor_no){
	case MOTER1:
		PwmDisconnect(PWM_CHANNEL_OC1A);
		GpioWritePin(PORT_D, PIN4,PIN_LOW);//TO ENSURE PIN IS LOW LEVEL
		break;
	case MOTER2:
		PwmDisconnect(PWM_CHANNEL_OC1B);
		GpioWritePin(PORT_D, PIN5,PIN_LOW);//TO ENSURE PIN IS LOW LEVEL
		break;
	default:
		break;
	}
}
void MOTOR_speed(uint8_t motor_no, uint8_t speed) {
	switch (motor_no){
	case MOTER1:
		PwmSetDuty(PWM_CHANNEL_OC1A, speed);
		break;
	case MOTER2:
		PwmSetDuty(PWM_CHANNEL_OC1B, speed);
		break;
	default:
		break;
	}
}
void MOTOR_dir(uint8_t motor_no, uint8_t dir) {
	switch (motor_no) {
		case MOTER1 :
			switch (dir) {
			case MOTOR1_FORWARD :
				GpioWritePin(PORT_D, PIN2,PIN_HIGH);
				GpioWritePin(PORT_D, PIN3,PIN_LOW);
				break;
			case MOTOR1_BACKWARD :
				GpioWritePin(PORT_D, PIN2,PIN_LOW);
				GpioWritePin(PORT_D, PIN3,PIN_HIGH);
				break;
			default:
				break;
			}
			break;
		case MOTER2 :
			switch (dir) {
			case MOTOR2_FORWARD :
				GpioWritePin(PORT_D, PIN6,PIN_HIGH);
				GpioWritePin(PORT_D, PIN7,PIN_LOW);
				break;
			case MOTOR2_BACKWARD :
				GpioWritePin(PORT_D, PIN6,PIN_LOW);
				GpioWritePin(PORT_D, PIN7,PIN_HIGH);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
}
