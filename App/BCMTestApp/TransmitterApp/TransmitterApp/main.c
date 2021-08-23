/*
 * TransmitterApp.c
 *
 * Created: 8/23/2021 2:08:52 PM
 * Author : Mohamed Wagdy
 */ 

#include "UART.h"
#include "SPI.h"
#include "Interrupt_Design_Pattern.h"

static uint8_t x = 'A';

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


int main(void)
{
   UART_Init(UART_CH_0);
   
   UART_EnableInterrupt(UART_CH_0, TX_INT);
   
   Interrupt_Install(USART_TXC_VECTOR_NUMBER, IncrementTxUART);
   /*SPI_Init(SPI_CH_0);
   
   SPI_EnableInterrupt(SPI_CH_0);
   
   Interrupt_Install(SPI_STC_VECTOR_NUMBER, IncrementTxSPI);*/
   /* Enable Globale Interrupt */
   INTERRUPTS_Enable();
   
   UART_SetData(UART_CH_0, x);
   /*DIO_WritePin(PORTB, PIN_4, 0);
   SPI_SetData(SPI_CH_0, x);*/
   
   /* Replace with your application code */
   while (1) 
   {
      
   }
}

