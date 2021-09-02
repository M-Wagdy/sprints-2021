/*
 * COMMProxy.c
 *
 * Created: 8/24/2021 1:50:18 PM
 * Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Interrupt_Design_Pattern.h"
#include "UART.h"
#include "SPI.h"
#include "I2C.h"
#include "COMMProxy.h"

/*- LOCAL MACROS
------------------------------------------*/
#define I2C_SLAVE_ADDR     (uint8_t)(0XCC)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
/* ISR Functions */
static void UART_TX_ISR(void);
static void UART_RX_ISR(void);
static void SPI_ISR(void);
static void I2C_ISR(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
/* Array Containing Initialization Status of Channels. */
static uint8_t gu8_COMMInitCh[COMM_NUMBERS] = {NOT_INIT, NOT_INIT, NOT_INIT};
/* Array Containing Tx CallBack Functions. */
static Ptr_VoidFuncVoid_t gptr_TxCallback[COMM_NUMBERS] = {NULL_PTR, NULL_PTR, NULL_PTR};
/* Array Containing Rx CallBack Functions. */
static Ptr_VoidFuncU8_t gptr_RxCallback[COMM_NUMBERS] = {NULL_PTR, NULL_PTR, NULL_PTR};
/* UART Data Variables. */
static uint8_t gu8_UARTData;
/* SPI Data Variables. */
static uint8_t gu8_SPIData;
/* I2C Data Variables. */
static uint8_t gu8_I2CStatus;
static uint8_t gu8_I2CData;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t SPI_CH_0_SS_CH_0_PORT;
extern const uint8_t SPI_CH_0_SS_CH_0_PIN;
extern const uint8_t SPI_CH_0_CONTROL_MASK;
extern const uint8_t I2C_CH_0_SLAVE_ADDR;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function is ISR Function for UART Transmit.
*/
void UART_TX_ISR(void)
{
   /* Call Callback Function if set. */
   if(NULL_PTR != gptr_TxCallback[COMM_UART_CH])
   {
      gptr_TxCallback[COMM_UART_CH]();
   }
}

/**
* @brief: This function is ISR Function for UART Receive.
*/
void UART_RX_ISR(void)
{
   /* Get Data From Uart Receive Buffer. */
   UART_GetData(UART_CH_0, &gu8_UARTData);
   /* Call Callback Function if set. */
   if(NULL_PTR != gptr_RxCallback[COMM_UART_CH])
   {
      gptr_RxCallback[COMM_UART_CH](gu8_UARTData);
   }
}

/**
* @brief: This function is ISR Function for SPI.
*/
void SPI_ISR(void)
{
   if( (SPI_CH_0_CONTROL_MASK & MASTER_SELECT) )
   {
      /* Unselect slave line */
      DIO_WritePin(SPI_CH_0_SS_CH_0_PORT, SPI_CH_0_SS_CH_0_PIN, PIN_HIGH);
      /* Call Callback Function if set. */
      if(NULL_PTR != gptr_TxCallback[COMM_SPI_CH])
      {
         gptr_TxCallback[COMM_SPI_CH]();
      }
   }
   else
   {
      /* Get Data From SPI Buffer. */
      SPI_GetData(SPI_CH_0, &gu8_SPIData);
      /* Call Callback Function if set. */
      if(NULL_PTR != gptr_RxCallback[COMM_SPI_CH])
      {
         gptr_RxCallback[COMM_SPI_CH](gu8_SPIData);
      }
   }
   
}

/**
* @brief: This function is ISR Function for I2C.
*/
void I2C_ISR(void)
{
   /* Get I2C Status */
   I2C_Status(I2C_CH_0, &gu8_I2CStatus);
   
   switch(gu8_I2CStatus)
   {
      case I2C_STATUS_START:
         /* Send Slave Address */
         I2C_Write(I2C_CH_0, I2C_SLAVE_ADDR);
         break;
      case I2C_STATUS_T_ACK_ADDR:
         /* Write Data */
         I2C_Write(I2C_CH_0, gu8_I2CData);
         break;
      case I2C_STATUS_T_ACK_DATA:
         /* Send Stop Condition */
         I2C_Stop(I2C_CH_0);
         /* Call Callback Function if set. */
         if(NULL_PTR != gptr_TxCallback[COMM_I2C_CH])
         {
            gptr_TxCallback[COMM_I2C_CH]();
         }
         break;
      case I2C_STATUS_R_ACK_ADDR:
      case I2C_STATUS_R_GENERAL_ADDR:
         I2C_ClearIntFlag(I2C_CH_0);
         break;
      case I2C_STATUS_R_ACK_DATA:
      case I2C_STATUS_R_GACK_DATA:
         /* Get Data From I2C Buffer. */
         
         I2C_ReadAck(I2C_CH_0, &gu8_I2CData);
         /* Call Callback Function if set. */
         if(NULL_PTR != gptr_RxCallback[COMM_I2C_CH])
         {
            gptr_RxCallback[COMM_I2C_CH](gu8_I2CData);
         }
         break;
      case I2C_STATUS_R_STOP:
         I2C_ClearIntFlag(I2C_CH_0);
         break;
   }
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initialize a communication channel.
*
* @param [in]  COMM_CH     -  Communication Channel Number.
*
* @return function error state.
*/
ERROR_STATE_t COMMProxy_Init(uint8_t COMM_CH)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(COMM_CH >= COMM_INVALID_CH)
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   /* Validate that Channel is not initialized before. */
   else if(NOT_INIT != gu8_COMMInitCh[COMM_CH])
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   else
   {
      switch(COMM_CH)
      {
         case COMM_UART_CH:
            UART_Init(UART_CH_0);
            Interrupt_Install(USART_TXC_VECTOR_NUMBER, UART_TX_ISR);
            Interrupt_Install(USART_RXC_VECTOR_NUMBER, UART_RX_ISR);
            UART_EnableInterrupt(UART_CH_0, TX_INT);
            UART_EnableInterrupt(UART_CH_0, RX_INT);
            gu8_COMMInitCh[COMM_UART_CH] = INIT;
            break;
         case COMM_SPI_CH:
            SPI_Init(SPI_CH_0);
            Interrupt_Install(SPI_STC_VECTOR_NUMBER, SPI_ISR);
            SPI_EnableInterrupt(SPI_CH_0);
            gu8_COMMInitCh[COMM_SPI_CH] = INIT;
            break;
         case COMM_I2C_CH:
            I2C_Init(I2C_CH_0);
            I2C_SetSlaveAddress(I2C_CH_0, I2C_CH_0_SLAVE_ADDR);
            Interrupt_Install(TWI_VECTOR_NUMBER, I2C_ISR);
            I2C_EnableInterrupt(I2C_CH_0);
            gu8_COMMInitCh[COMM_I2C_CH] = INIT;
            break;
      }
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_OK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Sends a Byte on a COMM Channel.
*
* @param [in]  COMM_CH  -  Communication Channel Number.
* @param [in]  Data     -  Byte to send.
*
* @return function error state.
*/
ERROR_STATE_t COMMProxy_Send(uint8_t COMM_CH, uint8_t Data)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(COMM_CH >= COMM_INVALID_CH)
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   /* Validate that Channel is Initialized. */
   else if(INIT != gu8_COMMInitCh[COMM_CH])
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   else
   {
      switch(COMM_CH)
      {
         /* Set Data On Bus */
         case COMM_UART_CH:
            UART_SetData(UART_CH_0, Data);
            break;
         case COMM_SPI_CH:
            /* select slave line */
            DIO_WritePin(SPI_CH_0_SS_CH_0_PORT, SPI_CH_0_SS_CH_0_PIN, PIN_LOW);
            SPI_SetData(SPI_CH_0, Data);
            break;
         case COMM_I2C_CH:
            gu8_I2CData = Data;
            I2C_Start(I2C_CH_0);
            break;
      }
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_OK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Sets Callback Function After Finishing sending a byte.
*
* @param [in]  Callback  -  Callback Function to call after sending a byte.
*
* @return function error state.
*/
ERROR_STATE_t COMMProxy_SetTxCallback(uint8_t COMM_CH, Ptr_VoidFuncVoid_t Callback)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(COMM_CH >= COMM_INVALID_CH)
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   else if(NULL_PTR == Callback)
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   else
   {  
      /* Set Callback Function */
      gptr_TxCallback[COMM_CH] = Callback;
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_OK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}

/**
* @brief: This function Sets Callback Function After Finishing Receiving a byte.
*
* @param [in]  Callback  -  Callback Function to call after receiving a byte.
*
* @return function error state.
*/
ERROR_STATE_t COMMProxy_SetRxCallback(uint8_t COMM_CH, Ptr_VoidFuncU8_t Callback)
{
   /* Variable to store function error state. */
   ERROR_STATE_t Proxy_ErrorState;
   
   /* Validate that Valid Parameters are passed. */
   if(COMM_CH >= COMM_INVALID_CH)
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   else if(NULL_PTR == Callback)
   {
      /* Set Function Error State to Not OK */
      Proxy_ErrorState = ERROR_NOK;
   }
   else
   {
      /* Set Callback Function */
      gptr_RxCallback[COMM_CH] = Callback;
      /* Set Function Error State to OK */
      Proxy_ErrorState = ERROR_OK;
   }
   
   /* Return function error state. */
   return Proxy_ErrorState;
}