/*
 * SPI.c
 *
 * Created: 7/14/2021 2:09:27 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "SPI.h"

/*- LOCAL MACROS
------------------------------------------*/
#define INIT                        (uint8_t)(1)
#define NOT_INIT                    (uint8_t)(0)
#define HIGH                        (uint8_t)(1)
#define LOW                         (uint8_t)(0)

#define DATA_COUNTER_START          (uint8_t)(0)
#define DATA_SIZE                   (uint8_t)(1)
#define DATA_RETURN_TO_PREV_INDEX   (uint8_t)(2)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_IsDriverInit = NOT_INIT;

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initialize SPI.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_Init(void)
{
   /* make sure driver wasn't initialize before */
   if(INIT == gu8_IsDriverInit)
   {
      return E_SPI_INIT_BEFORE;
   }
   
   /* initialize master node */
   if( (SPI_CONTROL_MASK & MASTER_SELECT) )
   {
      /* initialize slave select pins */
      #ifdef SS_CH_0
         DIO_SetPinDirection(SS_CH_0_PORT, SS_CH_0_PIN, OUTPUT);
         DIO_WritePin(SS_CH_0_PORT, SS_CH_0_PIN, HIGH);
      #endif
      /* initialize MOSI and clock source pins */
      DIO_SetPinDirection(MOSI_PORT, MOSI_PIN, OUTPUT);
      DIO_SetPinDirection(SCK_PORT, SCK_PIN, OUTPUT);
      /* sets SPI control register */
      SPI_CONTROL_R = SPI_CONTROL_MASK;   
   }
   /* initialize slave node */
   else
   {
      /* initialize MISO pins */
      DIO_SetPinDirection(MISO_PORT, MISO_PIN, OUTPUT);
      /* sets SPI control register */
      SPI_CONTROL_R = SPI_EN;
   }
   
   /* sets global variable to INIT */
   gu8_IsDriverInit = INIT;
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function sends a character through SPI.
*
* @param [in]  character   -  character to send.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_SendChar(uint8_t character)
{
   /* make sure driver was initialized before */
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   
   /* sets character in the SPI register */
   SPI_DATA_R = character;
   
   /* loops until transmitting is complete */
   while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ));
   /* check if there is a write collision error flag */
   if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
   {
      return E_SPI_WRITE_COLLISION;
   }

   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function receives a character through SPI.
*
* @param [out]  character   -  address to where save the received character.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_ReadChar(uint8_t * character)
{
   /* make sure driver was initialized before */
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   /* make sure a null pointer isn't passed to the function */
   else if(NULL_PTR == character)
   {
      return E_SPI_NULL_PTR;
   }
   
   /* loops until transmitting is complete */
   while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
   {
      /* check if there is a write collision error flag */
      if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
      {
         return E_SPI_WRITE_COLLISION;
      }
   }
   
   /* get data */
   *character = SPI_DATA_R;
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function sends a stream of characters through SPI.
*
* @param [in]  data   -  array of characters to send.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_Send(uint8_t * data)
{
   uint8_t counter = DATA_COUNTER_START;
   
   /* make sure driver was initialized before */
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   /* make sure a null pointer isn't passed to the function */
   else if(NULL_PTR == data)
   {
      return E_SPI_NULL_PTR;
   }
   
   /* sends all characters until it finds an end of string character */
   while(data[counter] != END_OF_STRING)
   {
      /* puts data */
      SPI_DATA_R = data[counter];
   
      /* loops until transmitting is complete */
      while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
      {
         /* check if there is a write collision error flag */
         if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
         {
            return E_SPI_WRITE_COLLISION;
         }
      }
      counter++;
   }      
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function receives a stream of characters through SPI.
*
* @param [out]  data   -  array of characters to receive.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_Read(uint8_t * data)
{
   uint8_t counter = DATA_COUNTER_START;
   
   /* make sure driver was initialized before */
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   /* make sure a null pointer isn't passed to the function */
   else if(NULL_PTR == data)
   {
      return E_SPI_NULL_PTR;
   }
   
   /* receives all characters until it gets a new line character */
   while(1)
   {
      /* loops until transmitting is complete */
      while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
      {
         /* check if there is a write collision error flag */
         if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
         {
            return E_SPI_WRITE_COLLISION;
         }
      }
      /* get data */
      data[counter] = SPI_DATA_R;
      
      /* check if new line is received */
      if(data[counter] == NEW_LINE)
      {
         /* put an end of sring character in the array and breaks from the loop */
         data[counter + DATA_SIZE] = END_OF_STRING;
         break;
      }
      counter++;
      
      /* check if it got a back space character */
      if(data[counter - DATA_SIZE] == BACKSPACE)
      {
         /* return to the previous character to overwrite it */
         if (counter - DATA_SIZE != DATA_COUNTER_START)
         {
            counter -= DATA_RETURN_TO_PREV_INDEX;
         }
         else
         {
            counter = DATA_COUNTER_START;
         }
      }
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function sets a slave line.
*
* @param [in]  slave_CH   -  slave channel number.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_SelectSlave(uint8_t slave_CH)
{
   /* make sure driver was initialized before */
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   
   /* select the slave channel pin */
   switch(slave_CH)
   {
      #ifdef SS_CH_0
      case SS_CH_0:
         DIO_WritePin(SS_CH_0_PORT, SS_CH_0_PIN, LOW);
         break;
      #endif
      default:
         return E_SPI_INVALID_SS_CH;
   
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function unselects a slave line.
*
* @param [in]  slave_CH   -  slave channel number.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_UnselectSlave(uint8_t slave_CH)
{
   /* make sure driver was initialized before */
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   
   /* unselect the slave channel pin */
   switch(slave_CH)
   {
      #ifdef SS_CH_0
      case SS_CH_0:
         DIO_WritePin(SS_CH_0_PORT, SS_CH_0_PIN, LOW);
         break;
      #endif
      default:
         return E_SPI_INVALID_SS_CH;
      
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}