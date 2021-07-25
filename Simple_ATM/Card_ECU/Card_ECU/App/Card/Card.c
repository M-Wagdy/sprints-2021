/*
 * Card.c
 *
 * Created: 7/24/2021 8:36:35 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Card.h"

/*- LOCAL MACROS
------------------------------------------*/
#define CARD_HOLDER_NAME_START_ADDRESS       (uint8_t)(0X00)
#define PAN_START_ADDRESS                    (uint8_t)(0X0A)
#define PIN_START_ADDRESS                    (uint8_t)(0X14)
#define CARD_HOLDER_NAME_STRING_SIZE         (uint8_t)(10)
#define PAN_STRING_SIZE                      (uint8_t)(10)
#define PIN_STRING_SIZE                      (uint8_t)(5)

static uint8_t * gu8_CardHolderNameMessage = "Enter The Card Holder Name: \r";
static uint8_t * gu8_PANMessage = "Enter The PAN: \r";
static uint8_t * gu8_PINMessage = "Enter The PIN: \r";

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initializes an EEPROM channel.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
*
* @return function error state.
*/
void CARD_Init()
{
   EEPROM_Init(EEPROM_CH_0);
   TERMINAL_Init(TERMINAL_CH_0);
   GLOBALINTTERUPTS_Enable();
}

/**
* @brief: This function initializes an EEPROM channel.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
*
* @return function error state.
*/
void CARD_GetUserData(STR_cardData_t * CardData)
{
   for(uint8_t i = 0; i<CARD_HOLDER_NAME_STRING_SIZE; i++)
   {
      /* get data from the given address */
      EEPROM_Read(EEPROM_CH_0, (CARD_HOLDER_NAME_START_ADDRESS + i), &CardData->au8_CardHolderName[i]);
   }
   
   for(uint8_t i = 0; i<PAN_STRING_SIZE; i++)
   {
      /* get data from the given address */
      EEPROM_Read(EEPROM_CH_0, (PAN_START_ADDRESS + i), &CardData->au8_PAN[i]);
   }
   
   for(uint8_t i = 0; i<PIN_STRING_SIZE; i++)
   {
      /* get data from the given address */
      EEPROM_Read(EEPROM_CH_0, (PIN_START_ADDRESS + i), &CardData->au8_PIN[i]);
   }
}

/**
* @brief: This function initializes an EEPROM channel.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
*
* @return function error state.
*/
void CARD_SetUserData(void)
{
   DIO_SetPinDirection(PORTA, PIN_0, OUTPUT);
   uint8_t TerminalData[255];
   GLOBALINTTERUPTS_Disable();
   
   Terminal_Write(TERMINAL_CH_0_UART_CH, gu8_CardHolderNameMessage);
   
   Terminal_Read(TerminalData);
   while(TerminalData[0] == END_OF_STRING)
   {
      Terminal_Read(TerminalData);
   }
   DIO_WritePin(PORTA, PIN_0, 1);
   for(uint8_t i = 0; i<CARD_HOLDER_NAME_STRING_SIZE; i++)
   {
      /* store data to the given address */
      EEPROM_Write(EEPROM_CH_0, (CARD_HOLDER_NAME_START_ADDRESS + i), TerminalData[i]);
   }
   
   Terminal_Write(TERMINAL_CH_0_UART_CH, gu8_PANMessage);
   
   Terminal_Read(TerminalData);
   while(TerminalData[0] == '\0')
   {
      Terminal_Read(TerminalData);
   }
   
   for(uint8_t i = 0; i<PAN_STRING_SIZE; i++)
   {
      /* store data to the given address */
      EEPROM_Write(EEPROM_CH_0, (PAN_START_ADDRESS + i), TerminalData[i]);
   }
   
   Terminal_Write(TERMINAL_CH_0_UART_CH, gu8_PINMessage);
   
   Terminal_Read(TerminalData);
   while(TerminalData[0] == '\0')
   {
      Terminal_Read(TerminalData);
   }
   
   for(uint8_t i = 0; i<PIN_STRING_SIZE; i++)
   {
      /* store data to the given address */
      EEPROM_Write(EEPROM_CH_0, (PIN_START_ADDRESS + i), TerminalData[i]);
   }
   
   GLOBALINTTERUPTS_Enable();
}