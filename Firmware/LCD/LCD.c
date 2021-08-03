/*
 * LCD.c
 *
 * Created: 7/25/2021 5:29:47 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "LCD.h"

/*- LOCAL MACROS
------------------------------------------*/
#define HIGH                  (uint8_t)(1)
#define LOW                   (uint8_t)(0)
#define DATA_PINS_NUM         (uint8_t)(4)

#ifdef LCD_CH_0
extern const uint8_t LCD_CH_0_RS_PORT;
extern const uint8_t LCD_CH_0_RS_PIN;
extern const uint8_t LCD_CH_0_RW_PORT;
extern const uint8_t LCD_CH_0_RW_PIN;
extern const uint8_t LCD_CH_0_E_PORT;
extern const uint8_t LCD_CH_0_E_PIN;
extern const uint8_t LCD_CH_0_DATA_PORT;
extern const uint8_t LCD_CH_0_DATA_START_PIN;
#endif

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initializes a LCD channel.
*
* @param [in]  LCD_CH   -  LCD channel number.
*
* @return function error state.
*/
LCD_ERROR_state_t LCD_Init(uint8_t LCD_CH)
{
   uint8_t u8_LCDRSPort;
   uint8_t u8_LCDRSPin;
   uint8_t u8_LCDRWPort;
   uint8_t u8_LCDRWPin;
   uint8_t u8_LCDEPort;
   uint8_t u8_LCDEPin;
   uint8_t u8_LCDDataPort;
   uint8_t u8_LCDDataPin;
   
   switch(LCD_CH)
   {
      #ifdef LCD_CH_0
      case LCD_CH_0:
         u8_LCDRSPort = LCD_CH_0_RS_PORT;
         u8_LCDRSPin = LCD_CH_0_RS_PIN;
         u8_LCDRWPort = LCD_CH_0_RW_PORT;
         u8_LCDRWPin = LCD_CH_0_RW_PIN;
         u8_LCDEPort = LCD_CH_0_E_PORT;
         u8_LCDEPin = LCD_CH_0_E_PIN;
         u8_LCDDataPort = LCD_CH_0_DATA_PORT;
         u8_LCDDataPin = LCD_CH_0_DATA_START_PIN;
         break;
      #endif
      default:
         return E_LCD_INVALID_CH;
   }
   
   /* Set control pins to output */
   DIO_SetPinDirection(u8_LCDRSPort, u8_LCDRSPin, OUTPUT);
   DIO_SetPinDirection(u8_LCDRWPort, u8_LCDRWPin, OUTPUT);
   DIO_SetPinDirection(u8_LCDEPort, u8_LCDEPin, OUTPUT);
   
   /* Set data pins to output */
   for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
   {
      DIO_SetPinDirection(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , OUTPUT);
   }
   
   /* Initialize LCD Commands */
   LCD_SendCommand(LCD_CH_0, LCD_4_BIT_MODE);
   LCD_SendCommand(LCD_CH_0, LCD_ENABLE_2_ROWS);
   LCD_SendCommand(LCD_CH_0, LCD_CURSOR_OFF);
   LCD_SendCommand(LCD_CH_0, LCD_CLEAR);
   
   /* return success status */
   return E_LCD_SUCCESS;
}

/**
* @brief: This function sends a command to LCD.
*
* @param [in]  LCD_CH   -  LCD channel number.
* @param [in]  Command  -  Command to send to LCD.
*
* @return function error state.
*/
LCD_ERROR_state_t LCD_SendCommand(uint8_t LCD_CH, uint8_t Command)
{
   uint8_t u8_LCDRSPort;
   uint8_t u8_LCDRSPin;
   uint8_t u8_LCDRWPort;
   uint8_t u8_LCDRWPin;
   uint8_t u8_LCDEPort;
   uint8_t u8_LCDEPin;
   uint8_t u8_LCDDataPort;
   uint8_t u8_LCDDataPin;
   
   switch(LCD_CH)
   {
      #ifdef LCD_CH_0
      case LCD_CH_0:
         u8_LCDRSPort = LCD_CH_0_RS_PORT;
         u8_LCDRSPin = LCD_CH_0_RS_PIN;
         u8_LCDRWPort = LCD_CH_0_RW_PORT;
         u8_LCDRWPin = LCD_CH_0_RW_PIN;
         u8_LCDEPort = LCD_CH_0_E_PORT;
         u8_LCDEPin = LCD_CH_0_E_PIN;
         u8_LCDDataPort = LCD_CH_0_DATA_PORT;
         u8_LCDDataPin = LCD_CH_0_DATA_START_PIN;
         break;
      #endif
      default:
         return E_LCD_INVALID_CH;
   }
   
   /* select control register */
   DIO_WritePin(u8_LCDRSPort, u8_LCDRSPin, LOW);
   DIO_WritePin(u8_LCDRWPort, u8_LCDRWPin, LOW);
   
   /* Send HIGH bits of the Command */
   for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
   {
      DIO_WritePin(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , ((Command >> (4 + u8_DataCounter)) & HIGH) );
   }
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, HIGH);
   dummy_delay();
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, LOW);
   
   /* Send LOW bits of the Command  */
   for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
   {
      DIO_WritePin(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , ((Command >> (u8_DataCounter)) & HIGH) );
   }
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, HIGH);
   dummy_delay();
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, LOW);
   
   
   /* return success status */
   return E_LCD_SUCCESS;
}

/**
* @brief: This function Prints a character to LCD.
*
* @param [in]  LCD_CH   -  LCD channel number.
* @param [in]  Data     -  Character to send to LCD.
*
* @return function error state.
*/
LCD_ERROR_state_t LCD_SendCharacter(uint8_t LCD_CH, uint8_t Data)
{
   uint8_t u8_LCDRSPort;
   uint8_t u8_LCDRSPin;
   uint8_t u8_LCDRWPort;
   uint8_t u8_LCDRWPin;
   uint8_t u8_LCDEPort;
   uint8_t u8_LCDEPin;
   uint8_t u8_LCDDataPort;
   uint8_t u8_LCDDataPin;
   
   switch(LCD_CH)
   {
      #ifdef LCD_CH_0
      case LCD_CH_0:
         u8_LCDRSPort = LCD_CH_0_RS_PORT;
         u8_LCDRSPin = LCD_CH_0_RS_PIN;
         u8_LCDRWPort = LCD_CH_0_RW_PORT;
         u8_LCDRWPin = LCD_CH_0_RW_PIN;
         u8_LCDEPort = LCD_CH_0_E_PORT;
         u8_LCDEPin = LCD_CH_0_E_PIN;
         u8_LCDDataPort = LCD_CH_0_DATA_PORT;
         u8_LCDDataPin = LCD_CH_0_DATA_START_PIN;
         break;
      #endif
      default:
         return E_LCD_INVALID_CH;
   }
   
   /* select data register */
   DIO_WritePin(u8_LCDRSPort, u8_LCDRSPin, HIGH);
   DIO_WritePin(u8_LCDRWPort, u8_LCDRWPin, LOW);
   
   /* Send HIGH bits of the Data */
   for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
   {
      DIO_WritePin(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , ((Data >> (4 + u8_DataCounter)) & HIGH) );
   }
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, HIGH);
   dummy_delay();
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, LOW);
   
   /* Send LOW bits of the Data */
   for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
   {
      DIO_WritePin(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , ((Data >> (u8_DataCounter)) & HIGH) );
   }
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, HIGH);
   dummy_delay();
   DIO_WritePin(u8_LCDEPort, u8_LCDEPin, LOW);
   
   /* return success status */
   return E_LCD_SUCCESS;
}

/**
* @brief: This function Prints a string on LCD.
*
* @param [in]  LCD_CH   -  LCD channel number.
* @param [in]  Data     -  String to send to LCD.
*
* @return function error state.
*/
LCD_ERROR_state_t LCD_SendString(uint8_t LCD_CH, uint8_t * Data)
{
   if(NULL_PTR == Data)
   {
      return E_LCD_NULL_PTR;
   }
   
   uint8_t u8_LCDRSPort;
   uint8_t u8_LCDRSPin;
   uint8_t u8_LCDRWPort;
   uint8_t u8_LCDRWPin;
   uint8_t u8_LCDEPort;
   uint8_t u8_LCDEPin;
   uint8_t u8_LCDDataPort;
   uint8_t u8_LCDDataPin;
   
   switch(LCD_CH)
   {
      #ifdef LCD_CH_0
      case LCD_CH_0:
         u8_LCDRSPort = LCD_CH_0_RS_PORT;
         u8_LCDRSPin = LCD_CH_0_RS_PIN;
         u8_LCDRWPort = LCD_CH_0_RW_PORT;
         u8_LCDRWPin = LCD_CH_0_RW_PIN;
         u8_LCDEPort = LCD_CH_0_E_PORT;
         u8_LCDEPin = LCD_CH_0_E_PIN;
         u8_LCDDataPort = LCD_CH_0_DATA_PORT;
         u8_LCDDataPin = LCD_CH_0_DATA_START_PIN;
         break;
      #endif
      default:
         return E_LCD_INVALID_CH;
   }
   
   /* select data register */
   DIO_WritePin(u8_LCDRSPort, u8_LCDRSPin, HIGH);
   DIO_WritePin(u8_LCDRWPort, u8_LCDRWPin, LOW);
   
   uint8_t u8_StringCounter = 0;
   
   while (Data[u8_StringCounter] != END_OF_STRING)
   {
      /* Send HIGH bits of the Data */
      for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
      {
         DIO_WritePin(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , ((Data[u8_StringCounter] >> (4 + u8_DataCounter)) & HIGH) );
      }
      DIO_WritePin(u8_LCDEPort, u8_LCDEPin, HIGH);
      dummy_delay();
      DIO_WritePin(u8_LCDEPort, u8_LCDEPin, LOW);
      
      /* Send LOW bits of the Data */
      for(uint8_t u8_DataCounter = 0; u8_DataCounter < DATA_PINS_NUM; u8_DataCounter++)
      {
         DIO_WritePin(u8_LCDDataPort, (u8_LCDDataPin + u8_DataCounter) , ((Data[u8_StringCounter] >> (u8_DataCounter)) & HIGH) );
      }
      DIO_WritePin(u8_LCDEPort, u8_LCDEPin, HIGH);
      dummy_delay();
      DIO_WritePin(u8_LCDEPort, u8_LCDEPin, LOW);
      
      u8_StringCounter++;
   }
   
   
   /* return success status */
   return E_LCD_SUCCESS;
}

/**
* @brief: This function Sets LCD cursor on a specific position.
*
* @param [in]  LCD_CH   -  LCD channel number.
* @param [in]  Row      -  Row position.
* @param [in]  Col      -  Column position.
*
* @return function error state.
*/
LCD_ERROR_state_t LCD_SetToRowCol(uint8_t LCD_CH, uint8_t Row, uint8_t Col)
{
   uint8_t u8_LCDChannel;
   
   switch(LCD_CH)
   {
      #ifdef LCD_CH_0
      case LCD_CH_0:
         u8_LCDChannel = LCD_CH_0;
         break;
      #endif
      default:
         return E_LCD_INVALID_CH;
   }
   
   uint8_t u8_Address;
   /* set required address */
   switch (Row)
   {
      case 0:
         u8_Address = Col;
         break;
      case 1:
         u8_Address = Col + 0x40;
         break;
   }
   
   /* Send command with the required address */
   LCD_SendCommand(u8_LCDChannel , u8_Address | LDC_SET_CURSOR_LOCATION);
   
   /* return success status */
   return E_LCD_SUCCESS;
}