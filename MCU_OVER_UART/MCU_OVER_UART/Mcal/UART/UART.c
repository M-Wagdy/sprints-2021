/*
 * UART.c
 *
 * Created: 7/13/2021 2:55:15 PM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define NOT_INIT                          (uint8_t)(0)
#define INIT                              (uint8_t)(1)

#define ENABLE_RX                         (uint8_t)(0x10)
#define ENABLE_TX                         (uint8_t)(0x08)

#define SET_PARITY_STOP_AND_DATA_SIZE     (uint8_t)(0x80)

#define EVEN_PARITY                       (uint8_t)(0x20)
#define ODD_PARITY                        (uint8_t)(0x30)
#define NO_PARITY                         (uint8_t)(0x00)

#define STOP_1_BIT                        (uint8_t)(0x00)
#define STOP_2_BIT                        (uint8_t)(0x08)

#define DATA_5_BITS                       (uint8_t)(0x00)
#define DATA_6_BITS                       (uint8_t)(0x02)
#define DATA_7_BITS                       (uint8_t)(0x04)
#define DATA_8_BITS                       (uint8_t)(0x06)

#define MAX_BAUD_VALUE                    (uint8_t)(4095)   
#define BAUD_MAX_LOW_BITS                 (uint8_t)(255) 
#define BAUD_HIGH_BITS_SHIFT              (uint8_t)(8)   

#define EMPTY_BUFFER_BIT                  (uint8_t)(0x20)
#define RECEIVE_COMPLETE_BIT              (uint8_t)(0x80)

#define STRING_COUNTER_START              (uint8_t)(0)
#define STRING_NEXT_CHAR                  (uint8_t)(1)
#define STRING_PREV_CHAR                  (uint8_t)(1)
#define STRING_RETURN_TO_PREV_CHAR        (uint8_t)(2)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_is_UART_init = NOT_INIT;


/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initialize the UART pin.
*
* @param [in]  baudRate  -  baud rate of the UART.
*
* @return function error state.
*/
UART_ERROR_state_t UART_init(uint16_t baudRate)
{
   /* making sure the driver wasn't initialized before or invalid baud rate was given */
   if(INIT == gu8_is_UART_init)
   {
      return E_UART_INIT_BEFORE;
   }
   else if(MAX_BAUD_VALUE < baudRate)
   {
      return E_UART_INVALID_BAUD_RATE;
   }
   else
   {
      /* do nothing */
   }
   
   /* Enable Receiver and Transmitter */
   UART_CONTROL_R = (ENABLE_RX | ENABLE_TX);
   /* Set Odd parity, 2 stop bits and 8 bits data size */
   UART_CONTROL_2_R = (SET_PARITY_STOP_AND_DATA_SIZE | NO_PARITY | STOP_1_BIT | DATA_8_BITS);
       
   /* Set Baud Rate low bits */
   UART_BAUDRATE_LOW_R = (uint8_t)baudRate;
   /* Set Baud Rate high bits if needed */
   if(BAUD_MAX_LOW_BITS < baudRate)
   {
      UART_BAUDRATE_HIGH_R = (uint8_t)( baudRate >> BAUD_HIGH_BITS_SHIFT );
   }
   
   /* sets global variable to initialized */
   gu8_is_UART_init = INIT;
   
   /* return success status */
   return E_UART_SUCCESS;
}

UART_ERROR_state_t UART_sendChar(uint8_t character)
{
   /* making sure the driver was initialized before calling this function */
   if( NOT_INIT == gu8_is_UART_init)
   {
      return E_UART_NOT_INIT;
   }
   else
   {
      /* do nothing */
   }
   
   /* Wait for empty transmit buffer */
   while ( !( UART_STATUS_R & EMPTY_BUFFER_BIT) );
   
   /* Put data into buffer, sends the data */
   UART_DATA_R = character;
   
   /* return success status */
   return E_UART_SUCCESS;
}

UART_ERROR_state_t UART_readChar(uint8_t * character)
{
   /* making sure the driver was initialized before calling this function, 
      and an initialized pointer is sent to the function */
   if( NOT_INIT == gu8_is_UART_init)
   {
      return E_UART_NOT_INIT;
   }
   else if(NULL_PTR == character)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* Wait for data to be received */
   while ( !(UART_STATUS_R & RECEIVE_COMPLETE_BIT) );
   /* Get and return received data from buffer */
   *character = UART_DATA_R;
   
   /* return success status */
   return E_UART_SUCCESS;
}

UART_ERROR_state_t UART_sendString(uint8_t * string)
{
   uint8_t counter = STRING_COUNTER_START;
   
   /* making sure the driver was initialized before calling this function, 
      and an initialized pointer is sent to the function */
   if( NOT_INIT == gu8_is_UART_init)
   {
      return E_UART_NOT_INIT;
   }
   else if(NULL_PTR == string)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* keeps sending data until it finds an end of string character in the string */
   while(string[counter] != END_OF_STRING)
   {
      /* Wait for empty transmit buffer */
      while ( !( UART_STATUS_R & EMPTY_BUFFER_BIT) );
      
      /* Put data into buffer, sends the data */
      UART_DATA_R = string[counter];
      counter++;
   }
   
   /* return success status */
   return E_UART_SUCCESS;
}

UART_ERROR_state_t UART_readString(uint8_t * string)
{
   uint8_t counter = STRING_COUNTER_START;
   
   /* making sure the driver was initialized before calling this function, 
      and an initialized pointer is sent to the function */
   if( NOT_INIT == gu8_is_UART_init)
   {
      return E_UART_NOT_INIT;
   }
   else if(NULL_PTR == string)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   while(1)
   {
      /* Wait for data to be received */
      while ( !(UART_STATUS_R & RECEIVE_COMPLETE_BIT) );
      /* Get and return received data from buffer */
      string[counter] = UART_DATA_R;
      
      /* enters an end of string character and breaks from the loop on receiving
         a new line character */
      if(string[counter] == NEW_LINE)
      {
         string[counter + STRING_NEXT_CHAR] = END_OF_STRING;
         break;
      }
      counter++;
      
      /* return to the previous character to overwrite if the entered character 
         is backspace */
      if(string[counter - STRING_PREV_CHAR] == BACKSPACE)
      {
         if (counter - STRING_PREV_CHAR != STRING_COUNTER_START)
         {
            counter -= STRING_RETURN_TO_PREV_CHAR;
         }
         /* return to the string start if the counter is still at first character */
         else
         {
            counter = STRING_COUNTER_START;
         }
      }
   }
   
   /* return success status */
   return E_UART_SUCCESS;
}