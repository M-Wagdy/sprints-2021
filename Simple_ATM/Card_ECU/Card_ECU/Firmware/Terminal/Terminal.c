/*
 * Terminal.c
 *
 * Created: 7/24/2021 5:39:49 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Terminal.h"

/*- LOCAL MACROS
------------------------------------------*/
#define RECEIVE_FINISHED                  (uint8_t)(1)
#define RECEIVE_NOT_FINISHED              (uint8_t)(0)        
#define GLOBAL_BUFFER_SIZE                (uint8_t)(255)

#define STRING_COUNTER_START              (uint8_t)(0)
#define STRING_NEXT_CHAR                  (uint8_t)(1)
#define STRING_PREV_CHAR                  (uint8_t)(1)
#define STRING_RETURN_TO_PREV_CHAR        (uint8_t)(2)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_RxBuffer[GLOBAL_BUFFER_SIZE];
static uint8_t gu8_Counter = STRING_COUNTER_START;
static uint8_t gu8_IsFinished = RECEIVE_NOT_FINISHED;

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initializes an EEPROM channel.
*
* @param [in]  EEPROM_CH   -  EEPROM channel number.
*
* @return function error state.
*/
TERMINAL_ERROR_state_t TERMINAL_Init(uint8_t Terminal_CH)
{
   UART_ERROR_state_t e_state;
   
   uint8_t u8_UART_CH;
   
   switch(Terminal_CH)
   {
      #ifdef TERMINAL_CH_0
      case TERMINAL_CH_0:
         u8_UART_CH = TERMINAL_CH_0_UART_CH;
         break;
      #endif
      default:
         return E_TERMINAL_INVALID_CH_NO;
   }
   
   /* configure uart pins */
   e_state = UART_Init(u8_UART_CH);
   /* make sure pin configuration is successful */
   if(E_UART_SUCCESS != e_state)
   {
      return E_TERMINAL_UART_ERROR;
   }
   
   /* enable Rx interrupt */
   e_state = UART_EnableInterrupt(u8_UART_CH, RX_INT);
   /* make sure function call is successful */
   if(E_UART_SUCCESS != e_state)
   {
      return E_TERMINAL_UART_ERROR;
   }
   
   /* Set callback function */
   e_state = UART_SetCallback(u8_UART_CH, RX_INT, TERMINAL_ReadCallBack);
   /* make sure function call is successful */
   if(E_UART_SUCCESS != e_state)
   {
      return E_TERMINAL_UART_ERROR;
   }
   
   /* return success message */
   return E_TERMINAL_SUCCESS;
   
}

/**
* @brief: This function writes an EEPROM memory block.
*
* @param [in]  Terminal_CH -  Terminal channel number.
* @param [in]  data        -  Data to write.
*
* @return function error state.
*/
TERMINAL_ERROR_state_t Terminal_Read(uint8_t * Data)
{
   if(NULL_PTR == Data)
   {
      return E_TERMINAL_NULL_PTR;
   }
   else if(RECEIVE_NOT_FINISHED == gu8_IsFinished)
   {
      Data[STRING_COUNTER_START] = END_OF_STRING;
      return E_TERMINAL_SUCCESS;
   }
   
   uint8_t u8_counter = STRING_COUNTER_START;
   
   while(gu8_RxBuffer[u8_counter] != END_OF_STRING )
   {
      Data[u8_counter] = gu8_RxBuffer[u8_counter];
      u8_counter++;
   }
   
   gu8_Counter = STRING_COUNTER_START;
   gu8_IsFinished = RECEIVE_NOT_FINISHED;
   
   /* return success message */
   return E_TERMINAL_SUCCESS;
}

/**
* @brief: This function writes an EEPROM memory block.
*
* @param [in]  Terminal_CH -  Terminal channel number.
* @param [in]  data        -  Data to write.
*
* @return function error state.
*/
TERMINAL_ERROR_state_t Terminal_Write(uint8_t Terminal_CH, uint8_t * Data)
{
   if(NULL_PTR == Data)
   {
      return E_TERMINAL_NULL_PTR;
   }
   
   UART_ERROR_state_t e_state;
   
   uint8_t u8_UART_CH;
   
   switch(Terminal_CH)
   {
      #ifdef TERMINAL_CH_0
      case TERMINAL_CH_0:
         u8_UART_CH = TERMINAL_CH_0_UART_CH;
         break;
      #endif
      default:
         return E_TERMINAL_INVALID_CH_NO;
   }
   
   /* transmit string */
   e_state = UART_TransmitString(u8_UART_CH, Data);
   if(E_UART_SUCCESS != e_state)
   {
      return E_TERMINAL_UART_ERROR;
   }
   
   /* return success message */
   return E_TERMINAL_SUCCESS;
}

/**
* @brief: This function reads from UART and put it in the global buffer.
*/
void TERMINAL_ReadCallBack(void)
{
   gu8_RxBuffer[gu8_Counter] = UART_DATA_R;
      
   /* enters an end of string character and breaks from the loop on receiving
      a new line character */
   if(gu8_RxBuffer[gu8_Counter] == NEW_LINE)
   {
      gu8_RxBuffer[gu8_Counter + STRING_NEXT_CHAR] = END_OF_STRING;
      gu8_IsFinished = RECEIVE_FINISHED;
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
}