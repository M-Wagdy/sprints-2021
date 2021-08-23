/*
 * ReceiverApp.c
 *
 * Created: 8/23/2021 2:09:31 PM
 * Author : Mohamed Wagdy
 */ 

#include "UART.h"
#include "SPI.h"
#include "Interrupt_Design_Pattern.h"

static uint8_t x = 'A';

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


int main(void)
{
   UART_Init(UART_CH_0);
   
   UART_EnableInterrupt(UART_CH_0, RX_INT);

   Interrupt_Install(USART_RXC_VECTOR_NUMBER, GetRxUART);
   
   /*SPI_Init(SPI_CH_0);
   
   SPI_EnableInterrupt(SPI_CH_0);
   
   Interrupt_Install(SPI_STC_VECTOR_NUMBER, GetRxSPI);*/
   
   /* Enable Globale Interrupt */
   INTERRUPTS_Enable();
   
   /* Replace with your application code */
   while (1)
   {
      
   }
}