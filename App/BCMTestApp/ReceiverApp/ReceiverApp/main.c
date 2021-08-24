/*
 * ReceiverApp.c
 *
 * Created: 8/23/2021 2:09:31 PM
 * Author : Mohamed Wagdy
 */ 

#include "UART.h"
#include "SPI.h"
#include "I2C.h"
#include "Interrupt_Design_Pattern.h"

#define I2C_SLAVE_ADDR (uint8_t)(0xA0)

static uint8_t x = 'A';
static uint8_t status;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void GetRxUART(void)
{
   UART_GetData(UART_CH_0, &x);
}

void GetRxSPI(void)
{
   SPI_GetData(UART_CH_0, &x);
}

void GetRxI2C(void)
{
   I2C_Status(I2C_CH_0, &status);
   
   switch(status)
   {
      case I2C_STATUS_R_ACK_ADDR:
      case I2C_STATUS_R_GENERAL_ADDR:
         I2C_ClearIntFlag(I2C_CH_0);
         break;
      case I2C_STATUS_R_ACK_DATA:
      case I2C_STATUS_R_GACK_DATA:
         I2C_ReadAck(I2C_CH_0, &x);
         break;
      case I2C_STATUS_R_NACK_DATA:
      case I2C_STATUS_R_GNACK_DATA:
         I2C_ReadNoAck(I2C_CH_0, &x);
         break;
      case I2C_STATUS_R_STOP:
         I2C_ClearIntFlag(I2C_CH_0);
         break;
   }
}

int main(void)
{
   /*UART_Init(UART_CH_0);
   
   UART_EnableInterrupt(UART_CH_0, RX_INT);

   Interrupt_Install(USART_RXC_VECTOR_NUMBER, GetRxUART);*/
   
   /*SPI_Init(SPI_CH_0);
   
   SPI_EnableInterrupt(SPI_CH_0);
   
   Interrupt_Install(SPI_STC_VECTOR_NUMBER, GetRxSPI);*/
   
   I2C_Init(I2C_CH_0);
   
   I2C_SetSlaveAddress(I2C_CH_0, I2C_SLAVE_ADDR);
   
   I2C_EnableInterrupt(I2C_CH_0);
   
   Interrupt_Install(TWI_VECTOR_NUMBER, GetRxI2C);
   
   /* Enable Globale Interrupt */
   INTERRUPTS_Enable();
   
   /* Replace with your application code */
   while (1)
   {
      
   }
}