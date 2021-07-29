

#ifndef __USER_H__
#define __USER_H__

/*includes*/
#include "../../Infrastructure/utils.h"
#include "../../Mcal/DIO/DIO.h"
#include "../../Mcal/SPI/SPI.h"
#include "../../Mcal/UART/UART.h"
#include "../../Mcal/Timer/TIMER_DRIVER.h"
#include "../../Firmware/EEPROM/EEPROM.h"
#include "../../Firmware/Motor/motor.h"
#include "../../Firmware/Button/PushButton.h"
#include "../../Firmware/Keypad/Keypad.h"
#include "../../Firmware/LCD/LCD.h"

/*USER_Authenticate outputs*/
#define WRONG_PIN 0
#define CORRECT_PIN 1

/*USER_CheckAmount outputs*/
#define ERROR_FORMAT 0
#define EXCEED_MAX_AMOUNT 1
#define INSUFFICIENT_FUND 2
#define APPROVED 3

/*Error codes*/
#define OperationStarted 255
#define OperationFail 1
#define OperationSuccess 0

/*typedefs*/
typedef enum EN_inServer_t
{
   NOTEXIST,
   EXIST
}EN_inServer_t;

/*APIs prototypes*/
void USER_Mode();
uint8_t USER_Interface();


#endif /* __USER_H__ */