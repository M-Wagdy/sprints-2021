

#ifndef __USER_H__
#define __USER_H__

/*includes*/
#include "../../Infrastructure/utils.h"
#include "../../Infrastructure/BIT_MATH.h"
#include "../../Mcal/DIO/DIO.h"
#include "../../Mcal/SPI/SPI.h"
#include "../../Mcal/UART/UART.h"
#include "../../Mcal/Timer/TIMER_DRIVER.h"
#include "../../Mcal/ADC/adc.h"
#include "../../Firmware/EEPROM/EEPROM.h"
#include "../../Firmware/Motor/motor.h"
#include "../../Firmware/Button/PushButton.h"
#include "../../Firmware/Keypad/Keypad.h"
#include "../../Firmware/LCD/LCD.h"
#include "../../Firmware/Temp/temp.h"

#define PIN_LENGTH 5
#define AMOUNT_LENGTH 8

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
#define OperationFailed 1
#define OperationSuccess 0

/*typedefs*/
typedef enum EN_inServer_t
{
   NOTEXIST,
   EXIST
}EN_inServer_t;

typedef struct ST_cardData
{
   f32_t balance;
   uint8_t primaryAccountNumber[10];
   uint8_t pin[5];
   uint8_t index;
}ST_cardData_t;

/*APIs prototypes*/
void USER_Mode();
uint8_t USER_Interface();
uint8_t USER_PrintTemp(uint8_t Temp_Ch);
uint8_t USER_GetCardData(void);
EN_inServer_t USER_GetServerData(void);
uint8_t User_Authenticate(ptr_uint8_t PINState);
uint8_t User_CheckAmount(ptr_uint8_t AmountState);
uint8_t User_UpdateBalance(void);

#endif /* __USER_H__ */