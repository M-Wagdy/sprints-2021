/*
 * Keypad.c
 *
 * Created: 7/25/2021 4:47:13 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Keypad.h"

/*- LOCAL MACROS
------------------------------------------*/
#define HIGH            (uint8_t)(1)
#define LOW             (uint8_t)(0)
#define PRESSED         (uint8_t)(0)
#define NOT_PRESSED     (uint8_t)(1)

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
#ifdef KP_CH_0
extern const uint8_t KP_CH_0_COL_PORT;
extern const uint8_t KP_CH_0_COL_START_PIN;
extern const uint8_t KP_CH_0_ROW_PORT;
extern const uint8_t KP_CH_0_ROW_START_PIN;
extern const uint8_t KP_CH_0_MAP[KP_CH_0_ROWS][KP_CH_0_COLS];
#endif

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initializes a Keypad channel.
*
* @param [in]  KP_CH   -  Keypad channel number.
*
* @return function error state.
*/
KEYPAD_ERROR_state_t KP_Init(uint8_t KP_CH)
{
   uint8_t u8_KPColPort;
   uint8_t u8_KPColPin;
   uint8_t u8_KPColsNum;
   uint8_t u8_KPRowPort;
   uint8_t u8_KPRowPin;
   uint8_t u8_KPRowsNum;
   
   switch(KP_CH)
   {
      #ifdef KP_CH_0
      case KP_CH_0:
         u8_KPColPort = KP_CH_0_COL_PORT;
         u8_KPColPin = KP_CH_0_COL_START_PIN;
         u8_KPColsNum = KP_CH_0_COLS;
         u8_KPRowPort = KP_CH_0_ROW_PORT;
         u8_KPRowPin = KP_CH_0_ROW_START_PIN;
         u8_KPRowsNum = KP_CH_0_ROWS;
         break;
      #endif
      default:
         return E_KEYPAD_INVALID_CH;
   }
   
   /* Set columns pins to output initially High */
   for(uint8_t u8_Counter = 0; u8_Counter < u8_KPColsNum; u8_Counter++)
   {
      DIO_SetPinDirection(u8_KPColPort, (u8_KPColPin + u8_Counter) , OUTPUT);
      DIO_WritePin(u8_KPColPort, (u8_KPColPin + u8_Counter) , HIGH);
   }
   
   /* Set rows pins to input and set pull up resistors */
   for(uint8_t u8_Counter = 0; u8_Counter < u8_KPRowsNum; u8_Counter++)
   {
      DIO_SetPinDirection(u8_KPRowPort, (u8_KPRowPin + u8_Counter) , INPUT);
      DIO_WritePin(u8_KPRowPort, (u8_KPRowPin + u8_Counter) , HIGH);
   }
   
   /* return success status */
   return E_KEYPAD_SUCCESS;
}

/**
* @brief: This function gets the pressed button value on the keypad.
*
* @param [in]  KP_CH    -  Keypad channel number.
* @param [out] Data     -  Pressed Key Value.
*
* @return function error state.
*/
KEYPAD_ERROR_state_t KP_GetPressedValue(uint8_t KP_CH, uint8_t * Data)
{
   /* Make sure the function didn't get an uninitialized pointer */
   if(NULL_PTR == Data)
   {
      return E_KEYPAD_NULL_PTR;
   }
   
   uint8_t u8_KPColPort;
   uint8_t u8_KPColPin;
   uint8_t u8_KPColsNum;
   uint8_t u8_KPRowPort;
   uint8_t u8_KPRowPin;
   uint8_t u8_KPRowsNum;
   
   switch(KP_CH)
   {
      #ifdef KP_CH_0
      case KP_CH_0:
         u8_KPColPort = KP_CH_0_COL_PORT;
         u8_KPColPin = KP_CH_0_COL_START_PIN;
         u8_KPColsNum = KP_CH_0_COLS;
         u8_KPRowPort = KP_CH_0_ROW_PORT;
         u8_KPRowPin = KP_CH_0_ROW_START_PIN;
         u8_KPRowsNum = KP_CH_0_ROWS;
         break;
      #endif
      default:
         return E_KEYPAD_INVALID_CH;
   }
   
   uint8_t u8_KeyState;
   uint8_t u8_Flag = NOT_PRESSED;
   
   /* loops on every column */
   for(uint8_t u8_ColCounter = 0; u8_ColCounter < u8_KPColsNum; u8_ColCounter++)
   {
      /* set column value to low */
      DIO_WritePin(u8_KPColPort, (u8_KPColPin + u8_ColCounter) , LOW);
      
      /* loops on every row */
      for(uint8_t u8_RowCounter = 0; u8_RowCounter < u8_KPRowsNum; u8_RowCounter++)
      {
         /* read row value */
         DIO_ReadPin(u8_KPRowPort, (u8_KPRowPin + u8_RowCounter), &u8_KeyState);
         /* check if row is pressed */
         if(u8_KeyState == PRESSED)
         {
            u8_Flag = PRESSED;
            *Data = KP_CH_0_MAP[u8_RowCounter][u8_ColCounter];
            while(u8_KeyState == PRESSED)
            {
               DIO_ReadPin(u8_KPRowPort, (u8_KPRowPin + u8_RowCounter), &u8_KeyState);
            }
            break;
         }
      }
      
      /* return column value to HIGH */
      DIO_WritePin(u8_KPColPort, (u8_KPColPin + u8_ColCounter) , HIGH);
      
      if(PRESSED == u8_Flag)
      {
         break;
      }
   }
   
   /* return value 0 if it didn't find any pressed button */
   if(NOT_PRESSED == u8_Flag)
   {
      *Data = 0;
   }
   
   /* return success status */
   return E_KEYPAD_SUCCESS;
}