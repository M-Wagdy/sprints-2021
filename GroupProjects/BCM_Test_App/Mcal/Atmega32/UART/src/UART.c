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
#define EMPTY_BUFFER_BIT                  (uint8_t)(0x20)
#define RECEIVE_COMPLETE_BIT              (uint8_t)(0x80)

#define STRING_COUNTER_START              (uint8_t)(0)
#define STRING_NEXT_CHAR                  (uint8_t)(1)
#define STRING_PREV_CHAR                  (uint8_t)(1)
#define STRING_RETURN_TO_PREV_CHAR        (uint8_t)(2)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
#if !TEST
static Ptr_VoidFuncVoid_t g_TxCallback[UART_CH_NUMBER];
static Ptr_VoidFuncVoid_t g_RxCallback[UART_CH_NUMBER];
#else
Ptr_VoidFuncVoid_t g_TxCallback[UART_CH_NUMBER];
Ptr_VoidFuncVoid_t g_RxCallback[UART_CH_NUMBER];
#endif

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t UART_CH_0_CONTROL;
extern const uint8_t UART_CH_0_CONTROL_2;
#if !TEST
extern const uint16_t UART_CH_0_BaudRate;
#else
extern uint16_t UART_CH_0_BaudRate;
#endif

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initialize the UART pin.
*
* @return function error state.
*/
UART_ERROR_state_t UART_Init(uint8_t UartNumber)
{
   switch(UartNumber)
   {
      #ifdef UART_CH_0
      case UART_CH_0:
         /* make sure valid baud rate is given */
         if(MAX_BAUD_VALUE < UART_CH_0_BaudRate)
         {
            return E_UART_INVALID_BAUD_RATE;
         }
      
         /* Enable Receiver and Transmitter */
         UART_CONTROL_R = UART_CH_0_CONTROL;
         /* Set Odd parity, 2 stop bits and 8 bits data size */
         UART_CONTROL_2_R = UART_CH_0_CONTROL_2;
      
         /* Set Baud Rate low bits */
         UART_BAUDRATE_LOW_R = (uint8_t)UART_CH_0_BaudRate;
         /* Set Baud Rate high bits if needed */
         if(BAUD_MAX_LOW_BITS < UART_CH_0_BaudRate)
         {
            UART_BAUDRATE_HIGH_R = (uint8_t)( UART_CH_0_BaudRate >> BAUD_HIGH_BITS_SHIFT );
         }
         
         break;
      #endif
      default:
         return E_UART_INVALID_CH;
   }

   /* return success status */
   return E_UART_SUCCESS;
}
/**
* @brief: This function puts a character in the UART buffer.
*
* @param [in]  UartNumber  -  UART channel number.
* @param [in]  TxChar      -  character to be send through UART.
*
* @return function error state.
*/
UART_ERROR_state_t UART_TransmitChar(uint8_t UartNumber, uint8_t TxChar)
{
   volatile uint8_t * ptru8_UARTStatusR;
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTStatusR = &UART_STATUS_R;
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }

   /* Wait for empty transmit buffer */
   while ( !( *ptru8_UARTStatusR & EMPTY_BUFFER_BIT) );
   
   /* Put data into buffer, sends the data */
   *ptru8_UARTDataR = TxChar;
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function gets a character from the UART buffer.
*
* @param [in]  UartNumber  -  UART channel number.
* @param [out] RxChar      -  address to store the character received 
*                             from UART in.
*
* @return function error state.
*/
UART_ERROR_state_t UART_ReceiveChar(uint8_t UartNumber,uint8_t * RxChar)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == RxChar)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t * ptru8_UARTStatusR;
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTStatusR = &UART_STATUS_R;
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   /* Wait for data to be received */
   while ( !(*ptru8_UARTStatusR & RECEIVE_COMPLETE_BIT) );
   /* Get and return received data from buffer */
   *RxChar = *ptru8_UARTDataR;
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function sends a string through UART.
*
* @param [in]  UartNumber  -  UART channel number.
* @param [in]  TxString    -  pointer to string to send through UART.
*
* @return function error state.
*/
UART_ERROR_state_t UART_TransmitString(uint8_t UartNumber,uint8_t * TxString)
{
   uint8_t counter = STRING_COUNTER_START;

   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == TxString)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t * ptru8_UARTStatusR;
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTStatusR = &UART_STATUS_R;
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   /* keeps sending data until it finds an end of string character in the string */
   while(TxString[counter] != END_OF_STRING)
   {
      /* Wait for empty transmit buffer */
      while ( !( *ptru8_UARTStatusR & EMPTY_BUFFER_BIT) );
      
      /* Put data into buffer, sends the data */
      *ptru8_UARTDataR = TxString[counter];
      counter++;
   }
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function sends a string through UART.
*
* @param [in]  UartNumber  -  UART channel number.
* @param [out] RxString    -  pointer to string to save the string through UART.
*
* @return function error state.
*/
UART_ERROR_state_t UART_ReceiveString(uint8_t UartNumber, uint8_t * RxString)
{
   uint8_t counter = STRING_COUNTER_START;
   
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == RxString)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t * ptru8_UARTStatusR;
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTStatusR = &UART_STATUS_R;
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   while(1)
   {
      /* Wait for data to be received */
      while ( !(*ptru8_UARTStatusR & RECEIVE_COMPLETE_BIT) );
      /* Get and return received data from buffer */
      RxString[counter] = *ptru8_UARTDataR;
      
      /* enters an end of string character and breaks from the loop on receiving
         a new line character */
      if(RxString[counter] == NEW_LINE)
      {
         RxString[counter + STRING_NEXT_CHAR] = END_OF_STRING;
         break;
      }
      counter++;
      
      /* return to the previous character to overwrite if the entered character 
         is backspace */
      if(RxString[counter - STRING_PREV_CHAR] == BACKSPACE)
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

/**
* @brief: This function enables a UART interrupt.
*
* @param [in] UartNumber           -  UART channel number.
* @param [in] UartInterruptType    -  type of interrupt to be enabled.
*
* @return function error state.
*/
UART_ERROR_state_t UART_EnableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType)
{
   /* making sure a valid interrupt type was sent to the function */
   if (RX_INT != UartInterruptType && TX_INT != UartInterruptType)
   {
      return E_UART_INVALID_INT_TYPE;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t * ptru8_UARTControlR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTControlR = &UART_CONTROL_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   /* enable interrupt */
   *ptru8_UARTControlR |= UartInterruptType;
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function disables a UART interrupt.
*
* @param [in] UartNumber           -  UART channel number.
* @param [in] UartInterruptType    -  type of interrupt to be enabled.
*
* @return function error state.
*/
UART_ERROR_state_t UART_DisableInterrupt(uint8_t UartNumber,uint8_t UartInterruptType)
{
   /* making sure a valid interrupt type was sent to the function */
   if (RX_INT != UartInterruptType && TX_INT != UartInterruptType)
   {
      return E_UART_INVALID_INT_TYPE;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t * ptru8_UARTControlR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTControlR = &UART_CONTROL_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   
   /* disable interrupt */
   *ptru8_UARTControlR &= ~(UartInterruptType);
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function sets a UART callback function.
*
* @param [in] UartNumber            -  UART channel number.
* @param [in] UartInterruptType     -  type of interrupt to be enabled.
* @param [in] Callback              -  callback function.
*
* @return function error state.
*/
UART_ERROR_state_t UART_SetCallback(uint8_t UartNumber, uint8_t UartInterruptType, Ptr_VoidFuncVoid_t Callback)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == Callback)
   {
      return E_UART_NULL_PTR;
   }
   /* making sure a valid interrupt type was sent to the function */
   else if (RX_INT != UartInterruptType && TX_INT != UartInterruptType)
   {
      return E_UART_INVALID_INT_TYPE;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t u8_UARTIndex;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         u8_UARTIndex = UART_CH_0;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   /* set callback function */
   if(TX_INT == UartInterruptType)
   {
      g_TxCallback[u8_UARTIndex] = Callback;
   }
   else if(RX_INT == UartInterruptType)
   {
      g_RxCallback[u8_UARTIndex] = Callback;
   }
   else
   {
      return E_UART_INVALID_INT_TYPE;
   }
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function flushes a UART receive buffer.
*
* @param [in] UartNumber            -  UART channel number.
*
* @return function error state.
*/
UART_ERROR_state_t UART_FlushReceiveBuffer(uint8_t UartNumber)
{
   volatile uint8_t * ptru8_UARTStatusR;
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTStatusR = &UART_STATUS_R;
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   /* dummy variable to flush the buffer */
   uint8_t u8_dummy;
   
   /* while there is data in the buffer take it in the dummy variable */
   while ( (*ptru8_UARTStatusR & RECEIVE_COMPLETE_BIT) )
   {
      u8_dummy = *ptru8_UARTDataR;
   }
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function puts data in UART transmit buffer.
*
* @param [in] UartNumber   -  UART channel number.
* @param [in] TxChar       -  data to be put in the buffer.
*
* @return function error state.
*/
UART_ERROR_state_t UART_SetData(uint8_t UartNumber,uint8_t TxChar)
{
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }

   /* Put data into buffer, sends the data */
   *ptru8_UARTDataR = TxChar;
   
   /* return success status */
   return E_UART_SUCCESS;
}

/**
* @brief: This function puts data in UART transmit buffer.
*
* @param [in]  UartNumber   -  UART channel number.
* @param [out] RxChar       -  pointer to where put the data in 
*                             a UART receive buffer.
*
* @return function error state.
*/
UART_ERROR_state_t UART_GetData(uint8_t UartNumber,uint8_t * RxChar)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == RxChar)
   {
      return E_UART_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   volatile uint8_t * ptru8_UARTDataR;
   
   switch(UartNumber)
   {
      case UART_CH_0:
         ptru8_UARTDataR = &UART_DATA_R;
         break;
      default:
         return E_UART_INVALID_CH;
   }
   
   /* Get and return received data from buffer */
   *RxChar = *ptru8_UARTDataR;
   
   /* return success status */
   return E_UART_SUCCESS;
}