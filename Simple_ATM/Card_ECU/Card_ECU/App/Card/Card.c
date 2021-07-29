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
#define CARD_HOLDER_NAME_STRING_SIZE         (uint8_t)(9)
#define PAN_STRING_SIZE                      (uint8_t)(9)
#define PIN_STRING_SIZE                      (uint8_t)(4)
#define TRUE                                 (uint8_t)(1)
#define FALSE                                (uint8_t)(0)

#define GLOBAL_BUFFER_SIZE                   (uint8_t)(255)

#define STRING_COUNTER_START                 (uint8_t)(0)
#define STRING_NEXT_CHAR                     (uint8_t)(1)
#define STRING_PREV_CHAR                     (uint8_t)(1)
#define STRING_RETURN_TO_PREV_CHAR           (uint8_t)(2)

#define EEPROM_EMPTY_CELL                    (uint8_t)(0xFF)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_RxBuffer[GLOBAL_BUFFER_SIZE];
static uint8_t gu8_Counter = STRING_COUNTER_START;

static uint8_t * gu8_AdminCommand = (uint8_t *)"ADMIN";
static uint8_t * gu8_CardHolderNameMessage = (uint8_t *)"Enter The Card Holder Name:";
static uint8_t * gu8_PANMessage = (uint8_t *)"Enter The PAN:";
static uint8_t * gu8_PINMessage = (uint8_t *)"Enter The PIN:";
static uint8_t * gu8_InvalidCardHolderNameMessage = (uint8_t *)"Please enter a Card Holder Name between 1 and 9 characters long.";
static uint8_t * gu8_InvalidPANMessage = (uint8_t *)"Please enter a PAN of 9 characters long.";
static uint8_t * gu8_InvalidPINMessage = (uint8_t *)"Please enter a PIN of 4 characters long.";
static uint8_t * gu8_CardDataUpdatedMessage = (uint8_t *)"Data Updated! \rReturning to User Mode.";

static uint8_t gu8_TerminalData[10];
static STR_cardData_t gSTR_CardData;

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initializes Card Drivers.
*/
void CARD_Init()
{
   /* Initialize EEPROM driver */
   EEPROM_Init(EEPROM_CH_0);
   
   /* Initialize UART driver */
   UART_Init(UART_1);
   UART_EnableInterrupt(UART_1, RECIVE_INT);
   UART_SetCallback(UART_1, RECIVE_INT, CARD_Receive);
   
   /* Initialize SPI driver */
   SPI_Init(SPIChannel_1);
   SPI_Set_TX_CompleteCallback(SPIChannel_1, CARD_Send);
   SPI_EnableInterrupt(SPIChannel_1);
   
   /* Enable Global Interrupts */
   GLOBALINTTERUPTS_Enable();
   
   /* Get Card Data From EEPROM */
   CARD_GetData();
   
   /* Check If Pin is not Set */
   if(gSTR_CardData.au8_PIN[0] == EEPROM_EMPTY_CELL)
   {
      CARD_SetData();
   }
}

/**
* @brief: This function gets card data from EEPROM.
*/
void CARD_GetData(void)
{
   /* Read Card Holder Name From EEPROM */
   EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_1, CARD_HOLDER_NAME_START_ADDRESS, gSTR_CardData.au8_CardHolderName, CARD_HOLDER_NAME_STRING_SIZE);
   /* Read PAN From EEPROM */
   EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_1, PAN_START_ADDRESS, gSTR_CardData.au8_PAN, PAN_STRING_SIZE);
   /* Read PIN From EEPROM */
   EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_1, PIN_START_ADDRESS, gSTR_CardData.au8_PIN, PIN_STRING_SIZE);
}

/**
* @brief: This function Sets Card Data in EEPROM.
*/
void CARD_SetData(void)
{
   /* Disable Interrupts for critical Section */
   GLOBALINTTERUPTS_Disable();
   
   /* Set Card Holder Name */
   /* Transmit Card holder name message */
   UART_TransmitString(UART_1, gu8_CardHolderNameMessage);
   
   /* Receive Card Holder Name from Terminal*/
   UART_ReceiveString(UART_1, gu8_TerminalData);
   /* Check For Valid Card Holder Name Length */
   while (StringLength(gu8_TerminalData) > CARD_HOLDER_NAME_STRING_SIZE || StringLength(gu8_TerminalData) == EMPTY_STRING)
   {
      UART_TransmitString(UART_1, gu8_InvalidCardHolderNameMessage);
      UART_ReceiveString(UART_1, gu8_TerminalData);
   }
   
   /* Save Card Holder Name in EEPROM */
   EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_1, CARD_HOLDER_NAME_START_ADDRESS, gu8_TerminalData, CARD_HOLDER_NAME_STRING_SIZE);
   
   /* Set PAN */
   /* Transmit PAN message */
   UART_TransmitString(UART_1, gu8_PANMessage);
   
   /* Receive PAN from Terminal */
   UART_ReceiveString(UART_1, gu8_TerminalData);
   /* Check For Valid PAN Length */
   while (StringLength(gu8_TerminalData) != PAN_STRING_SIZE )
   {
      UART_TransmitString(UART_1, gu8_InvalidPANMessage);
      UART_ReceiveString(UART_1, gu8_TerminalData);
   }
   
   /* Save PAN in EEPROM */
   EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_1, PAN_START_ADDRESS, gu8_TerminalData, PAN_STRING_SIZE);
   
   /* Set PIN */
   /* Transmit PIN message */
   UART_TransmitString(UART_1, gu8_PINMessage);
   
   /* Receive PIN from Terminal */
   UART_ReceiveString(UART_1, gu8_TerminalData);
   /* Check For Valid PIN Length */
   while (StringLength(gu8_TerminalData) != PIN_STRING_SIZE )
   {
      UART_TransmitString(UART_1, gu8_InvalidPINMessage);
      UART_ReceiveString(UART_1, gu8_TerminalData);
   }
   
   /* Save PIN in EEPROM */
   EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_1, PIN_START_ADDRESS, gu8_TerminalData, PIN_STRING_SIZE);
   
   UART_TransmitString(UART_1, gu8_CardDataUpdatedMessage);
   
   /* Update Card Data in the global variable */
   CARD_GetData();
   
   /* Enable Interrupts for exiting critical Section */
   GLOBALINTTERUPTS_Enable();
}

/**
* @brief: This function Sends Card Data to ATM through SPI.
*/
void CARD_Send(void)
{
   /* Read Slave Select Line if Selected. */
   uint8_t u8_SSState;
   DIO_ReadPin(SPI_PORT, SPI_SS_PIN, &u8_SSState);
   /* Make Sure ATM is Listening before Sending Card data. */
   if(u8_SSState == PIN_LOW)
   {
      /* Disable Interrupts for critical Section */
      GLOBALINTTERUPTS_Disable();
      /* Transmit PAN */
      SPI_TransmitString(SPIChannel_1, gSTR_CardData.au8_PAN, SlaveID_1);
      /* Transmit PIN */
      SPI_TransmitString(SPIChannel_1, gSTR_CardData.au8_PIN, SlaveID_1);
      /* Small delay to wait for transmission to complete before exiting critical section */
      dummy_delay();
      /* Enable Interrupts for exiting critical Section */
      GLOBALINTTERUPTS_Enable();
   }
}

/**
* @brief: This function Receives ADMIN from Terminal to enter Programming mode.
*/
void CARD_Receive(void)
{
   /* Get Character */
   UART_GetData(UART_1, &gu8_RxBuffer[gu8_Counter]);
      
   /* enters an end of string character and breaks from the loop on receiving
      a new line character */
   if(gu8_RxBuffer[gu8_Counter] == NEW_LINE)
   {
      gu8_RxBuffer[gu8_Counter + STRING_NEXT_CHAR] = END_OF_STRING;
      /* If Received String is "ADMIN" */
      if(StringCompare(gu8_RxBuffer, gu8_AdminCommand) == TRUE)
      {
         CARD_SetData();
      }
   }
   gu8_Counter++;
      
   /* return to the previous character to overwrite if the entered character 
      is backspace */
   if(gu8_RxBuffer[gu8_Counter - STRING_PREV_CHAR] == BACKSPACE)
   {
      if (gu8_Counter - STRING_PREV_CHAR != STRING_COUNTER_START)
      {
         gu8_Counter -= STRING_RETURN_TO_PREV_CHAR;
      }
      /* return to the string start if the counter is still at first character */
      else
      {
         gu8_Counter = STRING_COUNTER_START;
      }
   }
   
   /* Reset Receive Buffer on receiving a new line character. */
   if(gu8_RxBuffer[gu8_Counter - STRING_PREV_CHAR] == NEW_LINE)
   {
      gu8_Counter = STRING_COUNTER_START;
   }
}