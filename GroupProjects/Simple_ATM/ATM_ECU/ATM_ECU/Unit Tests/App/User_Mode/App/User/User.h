

#ifndef __USER_H__
#define __USER_H__

/*includes*/
#include "../../Infrastructure/utils.h"
#include "../../Infrastructure/BIT_MATH.h"
#include "../../Mcal/STUB_DIO/STUB_DIO.h"
#include "../../Mcal/STUB_SPI/STUB_SPI.h"
#include "../../Mcal/STUB_UART/STUB_UART.h"
#include "../../Firmware/STUB_EEPROM/STUB_EEPROM.h"
#include "../../Firmware/STUB_Motor/STUB_motor.h"
#include "../../Firmware/STUB_Button/STUB_PushButton.h"//ADEL AND REHAB PLEASE CHECK THIS AND CHANGE IT IF YOU WANT
#include "../../Firmware/STUB_Keypad/STUB_Keypad.h"//ADEL AND REHAB PLEASE CHECK THIS AND CHANGE IT IF YOU WANT
#include "../../Firmware/STUB_LCD/STUB_LCD.h"//ADEL AND REHAB PLEASE CHECK THIS AND CHANGE IT IF YOU WANT
#include "../../Firmware/STUB_Temp/STUB_temp.h"



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
uint8_t USER_Interface();//ADEL
uint8_t USER_PrintTemp(uint8_t Temp_Ch);//ESSAM (NO TEST FOR THIS API)
uint8_t USER_GetCardData(void);//ESSAM
EN_inServer_t USER_GetServerData(void);//ESSAM
uint8_t User_Authenticate(ptr_uint8_t PINState);//REHAB
uint8_t User_CheckAmount(ptr_uint8_t AmountState);//REHAB
uint8_t User_UpdateBalance(void);//REHAB

#endif /* __USER_H__ */
