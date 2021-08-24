/*
 * TransmitterApp.c
 *
 * Created: 8/23/2021 2:08:52 PM
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
void IncrementTxUART(void)
{
   if(x == 'Z')
   {
      x = 'A';
   }
   else
   {
      x++;
   }
   
   UART_SetData(UART_CH_0, x);
}

void IncrementTxSPI(void)
{
   if(x == 'Z')
   {
      x = 'A';
   }
   else
   {
      x++;
   }
   
   SPI_SetData(SPI_CH_0, x);
}

void IncrementTxI2C(void)
{
   I2C_Status(I2C_CH_0, &status);
   
   switch(status)
   {
      case I2C_STATUS_START:
         I2C_Write(I2C_CH_0, I2C_SLAVE_ADDR);
         break;
      case I2C_STATUS_T_ACK_ADDR:
         I2C_Write(I2C_CH_0, x);
         break;
      case I2C_STATUS_T_ACK_DATA:
      case I2C_STATUS_T_NACK_DATA:
         if(x == 'Z')
         {
            I2C_Stop(I2C_CH_0);
         }
         else
         {
            x++;
            I2C_Write(I2C_CH_0, x);
         }
         break;
       case I2C_STATUS_T_ARB_LOST:
         x = 'A';
         break;
   }
}

int main(void)
{
   /*UART_Init(UART_CH_0);
   
   UART_EnableInterrupt(UART_CH_0, TX_INT);
   
   Interrupt_Install(USART_TXC_VECTOR_NUMBER, IncrementTxUART);*/
   
   /*SPI_Init(SPI_CH_0);
   
   SPI_EnableInterrupt(SPI_CH_0);
   
   Interrupt_Install(SPI_STC_VECTOR_NUMBER, IncrementTxSPI);*/
   
   I2C_Init(I2C_CH_0);
   
   I2C_EnableInterrupt(I2C_CH_0);
   
   Interrupt_Install(TWI_VECTOR_NUMBER, IncrementTxI2C);
   
   /* Enable Globale Interrupt */
   INTERRUPTS_Enable();
   
   /*UART_SetData(UART_CH_0, x);*/
   /*DIO_WritePin(PORTB, PIN_4, 0);
   SPI_SetData(SPI_CH_0, x);*/
   for(volatile uint8_t counter = 0; counter<255;counter++)
   {
      
   }
   
   I2C_Start(I2C_CH_0);
   
   /* Replace with your application code */
   while (1) 
   {
      
   }
}

