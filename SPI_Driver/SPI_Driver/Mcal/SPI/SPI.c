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

#define SPI_TRANSMIT_COMPLETE_BIT   (uint8_t)(0X80)
#define SPI_WRITE_COLLISION_BIT     (uint8_t)(0X40)

#define DATA_COUNTER_START          (uint8_t)(0)
#define DATA_SIZE                   (uint8_t)(1)
#define DATA_RETURN_TO_PREV_INDEX   (uint8_t)(2)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_IsDriverInit = NOT_INIT;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initialize SPI.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_Init(void)
{
   if(INIT == gu8_IsDriverInit)
   {
      return E_SPI_INIT_BEFORE;
   }
   
   if( (SPI_CONTROL_MASK & MASTER_SELECT) )
   {
      #ifdef SS_CH_0
         DIO_SetPinDirection(SS_CH_0_PORT, SS_CH_0_PIN, OUTPUT);
         DIO_WritePin(SS_CH_0_PORT, SS_CH_0_PIN, HIGH);
      #endif
      DIO_SetPinDirection(MOSI_PORT, MOSI_PIN, OUTPUT);
      DIO_SetPinDirection(SCK_PORT, SCK_PIN, OUTPUT);
      SPI_CONTROL_R = SPI_CONTROL_MASK;   
   }
   else
   {
      DIO_SetPinDirection(MISO_PORT, MISO_PIN, OUTPUT);
      SPI_CONTROL_R = SPI_EN;
   }
   
   gu8_IsDriverInit = INIT;
   
   return E_SPI_SUCCESS;
}

SPI_ERROR_state_t SPI_SendChar(uint8_t character)
{
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   
   SPI_DATA_R = character;
   
   while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
   {
      
   }
   if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
   {
      return E_SPI_WRITE_COLLISION;
   }

   return E_SPI_SUCCESS;
}

SPI_ERROR_state_t SPI_ReadChar(uint8_t * character)
{
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   else if(NULL_PTR == character)
   {
      return E_SPI_NULL_PTR;
   }
   
   while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
   {
      if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
      {
         return E_SPI_WRITE_COLLISION;
      }
   }
   
   *character = SPI_DATA_R;
   
   return E_SPI_SUCCESS;
}

SPI_ERROR_state_t SPI_Send(uint8_t * data)
{
   uint8_t counter = DATA_COUNTER_START;
   
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   else if(NULL_PTR == data)
   {
      return E_SPI_NULL_PTR;
   }
   
   while(data[counter] != END_OF_STRING)
   {
      SPI_DATA_R = data[counter];
   
      while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
      {
         if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
         {
            return E_SPI_WRITE_COLLISION;
         }
      }
      counter++;
   }      
   
   return E_SPI_SUCCESS;
}

SPI_ERROR_state_t SPI_Read(uint8_t * data)
{
   uint8_t counter = DATA_COUNTER_START;
   
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   else if(NULL_PTR == data)
   {
      return E_SPI_NULL_PTR;
   }
   
   while(data[counter] != END_OF_STRING)
   {
      while(!(SPI_STATUS_R & SPI_TRANSMIT_COMPLETE_BIT ))
      {
         if( (SPI_STATUS_R & SPI_WRITE_COLLISION_BIT ) )
         {
            return E_SPI_WRITE_COLLISION;
         }
      }
      data[counter] = SPI_DATA_R;
      
      if(data[counter] == NEW_LINE)
      {
         data[counter + DATA_SIZE] = END_OF_STRING;
         break;
      }
      counter++;
      
      if(data[counter - DATA_SIZE] == BACKSPACE)
      {
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
   
   return E_SPI_SUCCESS;
}

SPI_ERROR_state_t SPI_SelectSlave(uint8_t slave_CH)
{
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   
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
   
   return E_SPI_SUCCESS;
   
}

SPI_ERROR_state_t SPI_UnselectSlave(uint8_t slave_CH)
{
   if(NOT_INIT == gu8_IsDriverInit)
   {
      return E_SPI_NOT_INIT;
   }
   
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
   
   return E_SPI_SUCCESS;
}