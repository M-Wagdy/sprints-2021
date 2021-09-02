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
#define HIGH                        (uint8_t)(1)
#define LOW                         (uint8_t)(0)

#define DATA_COUNTER_START          (uint8_t)(0)
#define DATA_SIZE                   (uint8_t)(1)
#define DATA_RETURN_TO_PREV_INDEX   (uint8_t)(2)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
#if !TEST
static Ptr_VoidFuncVoid_t g_Callback[SPI_NUMBERS];
#else
Ptr_VoidFuncVoid_t g_Callback[SPI_NUMBERS];
#endif

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t SPI_CH_0_CONTROL_MASK;
extern const uint8_t SPI_CH_0_DOUBLE_SPEED;
extern const uint8_t SPI_CH_0_MOSI_PORT;
extern const uint8_t SPI_CH_0_MOSI_PIN;
extern const uint8_t SPI_CH_0_MISO_PORT;
extern const uint8_t SPI_CH_0_MISO_PIN;
extern const uint8_t SPI_CH_0_SCK_PORT;
extern const uint8_t SPI_CH_0_SCK_PIN;
extern const uint8_t SPI_CH_0_SS_CH_0_PORT;
extern const uint8_t SPI_CH_0_SS_CH_0_PIN;

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function initialize SPI channel.
*
* @param [in]  SpiNumber   -  SPI channel number.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_Init(uint8_t SpiNumber)
{
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         /* initialize master node */
         if( (SPI_CH_0_CONTROL_MASK & MASTER_SELECT) )
         {
            /* initialize slave select pins */
            #ifdef SPI_CH_0_SS_CH_0
               DIO_SetPinDirection(SPI_CH_0_SS_CH_0_PORT, SPI_CH_0_SS_CH_0_PIN, OUTPUT);
               DIO_WritePin(SPI_CH_0_SS_CH_0_PORT, SPI_CH_0_SS_CH_0_PIN, HIGH);
            #endif
            /* initialize MOSI and clock source pins */
            DIO_SetPinDirection(SPI_CH_0_MOSI_PORT, SPI_CH_0_MOSI_PIN, OUTPUT);
            DIO_SetPinDirection(SPI_CH_0_SCK_PORT, SPI_CH_0_SCK_PIN, OUTPUT);
            /* sets SPI control register */
            SPI_STATUS_R |= SPI_CH_0_DOUBLE_SPEED;
            SPI_CONTROL_R = SPI_CH_0_CONTROL_MASK;
         }
         /* initialize slave node */
         else
         {
            /* initialize MISO pins */
            DIO_SetPinDirection(SPI_CH_0_MISO_PORT, SPI_CH_0_MISO_PIN, OUTPUT);
            /* sets SPI control register */
            SPI_CONTROL_R = SPI_EN;
         }
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
      
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function sends a character through SPI.
*
* @param [in]  SpiNumber   -  SPI channel number.
* @param [in]  TxChar      -  character to send.
* @param [in]  slave_CH    -  slave select line.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_TransmitChar(uint8_t SpiNumber, uint8_t TxChar, uint8_t slave_CH)
{
   volatile uint8_t * ptr_SPIDataR;
   volatile uint8_t * ptr_SPIStatusR;
   uint8_t u8_SSPort;
   uint8_t u8_SSPin;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIDataR = &SPI_DATA_R;
         ptr_SPIStatusR = &SPI_STATUS_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* get the required slave select port and pin */
   switch(slave_CH)
   {
      #ifdef SPI_CH_0_SS_CH_0
      case SPI_CH_0_SS_CH_0:
         u8_SSPort = SPI_CH_0_SS_CH_0_PORT;
         u8_SSPin = SPI_CH_0_SS_CH_0_PIN;
         break;
      #endif
      case SLAVE_SS_CH:
         break;
      default:
         return E_SPI_INVALID_SS_CH;
   }
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* select slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, LOW);
   }
   
   /* sets character in the SPI register */
   *ptr_SPIDataR = TxChar;
   
   /* loops until transmitting is complete */
   while(!(*ptr_SPIStatusR & SPI_TRANSMIT_COMPLETE_BIT ));
   /* check if there is a write collision error flag */
   if( (*ptr_SPIStatusR & SPI_WRITE_COLLISION_BIT ) )
   {
      return E_SPI_WRITE_COLLISION;
   }
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* unselect slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, HIGH);
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function receives a character through SPI.
*
* @param [in]  SpiNumber   -  SPI channel number.
* @param [in]  slave_CH    -  slave select line.
* @param [out] RxData      -  address to where to store the received character.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_ReceiveChar(uint8_t SpiNumber,uint8_t * RxData,uint8_t slave_CH)
{
   /* make sure a null pointer isn't passed to the function */
   if(NULL_PTR == RxData)
   {
      return E_SPI_NULL_PTR;
   }
   
   volatile uint8_t * ptr_SPIDataR;
   volatile uint8_t * ptr_SPIStatusR;
   uint8_t u8_SSPort;
   uint8_t u8_SSPin;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIDataR = &SPI_DATA_R;
         ptr_SPIStatusR = &SPI_STATUS_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* get the required slave select port and pin */
   switch(slave_CH)
   {
      #ifdef SPI_CH_0_SS_CH_0
      case SPI_CH_0_SS_CH_0:
         u8_SSPort = SPI_CH_0_SS_CH_0_PORT;
         u8_SSPin = SPI_CH_0_SS_CH_0_PIN;
         break;
      #endif
      case SLAVE_SS_CH:
         break;
      default:
         return E_SPI_INVALID_SS_CH;
   }
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* select slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, LOW);
   }
   
   /* loops until transmitting is complete */
   while(!(*ptr_SPIStatusR & SPI_TRANSMIT_COMPLETE_BIT ))
   {
      /* check if there is a write collision error flag */
      if( (*ptr_SPIStatusR & SPI_WRITE_COLLISION_BIT ) )
      {
         return E_SPI_WRITE_COLLISION;
      }
   }
   
   /* get data */
   *RxData = *ptr_SPIDataR;
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* unselect slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, HIGH);
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
   
}

/**
* @brief: This function sends a stream of characters through SPI.
*
* @param [in]  SpiNumber   -  SPI channel number.
* @param [in]  slave_CH    -  slave select line.
* @param [in]  TxString    -  array of characters to send.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_TransmitString(uint8_t SpiNumber, uint8_t * TxString, uint8_t slave_CH)
{
   uint8_t counter = DATA_COUNTER_START;
   
   /* make sure a null pointer isn't passed to the function */
   if(NULL_PTR == TxString)
   {
      return E_SPI_NULL_PTR;
   }
   
   volatile uint8_t * ptr_SPIDataR;
   volatile uint8_t * ptr_SPIStatusR;
   uint8_t u8_SSPort;
   uint8_t u8_SSPin;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIDataR = &SPI_DATA_R;
         ptr_SPIStatusR = &SPI_STATUS_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* get the required slave select port and pin */
   switch(slave_CH)
   {
      #ifdef SPI_CH_0_SS_CH_0
      case SPI_CH_0_SS_CH_0:
         u8_SSPort = SPI_CH_0_SS_CH_0_PORT;
         u8_SSPin = SPI_CH_0_SS_CH_0_PIN;
         break;
      #endif
      case SLAVE_SS_CH:
         break;
      default:
         return E_SPI_INVALID_SS_CH;
   }
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* select slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, LOW);
   }
   
   /* sends all characters until it finds an end of string character */
   while(TxString[counter] != END_OF_STRING)
   {
      /* puts data */
      *ptr_SPIDataR = TxString[counter];
      
      /* loops until transmitting is complete */
      while(!(*ptr_SPIStatusR & SPI_TRANSMIT_COMPLETE_BIT ))
      {
         /* check if there is a write collision error flag */
         if( (*ptr_SPIStatusR & SPI_WRITE_COLLISION_BIT ) )
         {
            return E_SPI_WRITE_COLLISION;
         }
      }
      counter++;
   }
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* unselect slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, HIGH);
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function receives a stream of characters through SPI.
*
* @param [in]  SpiNumber   -  SPI channel number.
* @param [in]  slave_CH    -  slave select line.
* @param [out] RxString    -  array of characters to receive.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_ReceiveString(uint8_t SpiNumber,uint8_t * RxString,uint8_t slave_CH)
{
   uint8_t counter = DATA_COUNTER_START;
   
   /* make sure a null pointer isn't passed to the function */
   if(NULL_PTR == RxString)
   {
      return E_SPI_NULL_PTR;
   }
   
   volatile uint8_t * ptr_SPIDataR;
   volatile uint8_t * ptr_SPIStatusR;
   uint8_t u8_SSPort;
   uint8_t u8_SSPin;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIDataR = &SPI_DATA_R;
         ptr_SPIStatusR = &SPI_STATUS_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* get the required slave select port and pin */
   switch(slave_CH)
   {
      #ifdef SPI_CH_0_SS_CH_0
      case SPI_CH_0_SS_CH_0:
         u8_SSPort = SPI_CH_0_SS_CH_0_PORT;
         u8_SSPin = SPI_CH_0_SS_CH_0_PIN;
         break;
      #endif
      case SLAVE_SS_CH:
         break;
      default:
         return E_SPI_INVALID_SS_CH;
   }
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* select slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, LOW);
   }
   
   /* receives all characters until it gets a new line character */
   while(1)
   {
      /* loops until transmitting is complete */
      while(!(*ptr_SPIStatusR & SPI_TRANSMIT_COMPLETE_BIT ))
      {
         /* check if there is a write collision error flag */
         if( (*ptr_SPIStatusR & SPI_WRITE_COLLISION_BIT ) )
         {
            return E_SPI_WRITE_COLLISION;
         }
      }
      /* get data */
      RxString[counter] = *ptr_SPIDataR;
      
      /* check if new line is received */
      if(RxString[counter] == NEW_LINE)
      {
         /* put an end of string character in the array and breaks from the loop */
         RxString[counter + DATA_SIZE] = END_OF_STRING;
         break;
      }
      counter++;
      
      /* check if it got a back space character */
      if(RxString[counter - DATA_SIZE] == BACKSPACE)
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
   
   if(SLAVE_SS_CH != slave_CH)
   {
      /* unselect slave line */
      DIO_WritePin(u8_SSPort, u8_SSPin, HIGH);
   }
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function enables SPI interrupt.
*
* @param [in]  SpiNumber   -  SPI channel number.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_EnableInterrupt(uint8_t SpiNumber)
{
   volatile uint8_t * ptr_SPIControlR;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIControlR = &SPI_CONTROL_R;
      break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* enable interrupt */
   *ptr_SPIControlR |= SPI_INTERRUPT_EN;
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function disables SPI interrupt.
*
* @param [in]  SpiNumber   -  SPI channel number.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_DisableInterrupt(uint8_t SpiNumber)
{
   volatile uint8_t * ptr_SPIControlR;
   
   /* get the required SPI data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIControlR = &SPI_CONTROL_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* enable interrupt */
   *ptr_SPIControlR &= ~(SPI_INTERRUPT_EN);
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function sets a callback function.
*
* @param [in]  SpiNumber   -  SPI channel number.
* @param [in]  Callback    -  address of the callback function.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_SetCallback(uint8_t SpiNumber, Ptr_VoidFuncVoid_t Callback)
{
   /* making sure an initialized pointer is sent to the function */
   if(NULL_PTR == Callback)
   {
      return E_SPI_NULL_PTR;
   }
   
   volatile uint8_t u8_SPIIndex;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         u8_SPIIndex = SPI_CH_0;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   g_Callback[u8_SPIIndex] = Callback;
      
   /* return success status */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function puts data in SPI transmit buffer.
*
* @param [in] SpiNumber    -  SPI channel number.
* @param [in] TxChar       -  data to be put in the buffer.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_SetData(uint8_t SpiNumber, uint8_t TxChar)
{
   volatile uint8_t * ptr_SPIDataR;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIDataR = &SPI_DATA_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
         
   /* sets character in the SPI register */
   *ptr_SPIDataR = TxChar;
   
   /* return success message */
   return E_SPI_SUCCESS;
}

/**
* @brief: This function puts data in UART transmit buffer.
*
* @param [in]  SpiNumber    -  SPI channel number.
* @param [out] RxChar       -  pointer to where put the data in
*                             a SPI receive buffer.
*
* @return function error state.
*/
SPI_ERROR_state_t SPI_GetData(uint8_t SpiNumber,uint8_t * RxData)
{
   /* make sure a null pointer isn't passed to the function */
   if(NULL_PTR == RxData)
   {
      return E_SPI_NULL_PTR;
   }
   
   volatile uint8_t * ptr_SPIDataR;
   
   /* get the required spi data */
   switch(SpiNumber)
   {
      #ifdef SPI_CH_0
      case SPI_CH_0:
         ptr_SPIDataR = &SPI_DATA_R;
         break;
      #endif
      default:
         return E_SPI_INVALID_CH;
   }
   
   /* get data */
   *RxData = *ptr_SPIDataR;
   
   /* return success message */
   return E_SPI_SUCCESS;
}