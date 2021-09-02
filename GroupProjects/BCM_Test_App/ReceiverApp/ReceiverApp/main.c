/*
 * ReceiverApp.c
 *
 * Created: 8/23/2021 2:09:31 PM
 * Author : Mohamed Wagdy
 */ 

#include "BCM.h"
#include "Interrupt_Design_Pattern.h"

uint8_t gau8_DataBuffer1[30];
uint8_t gau8_DataBuffer2[10];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void UART_TXCallback(void)
{
   /*Do Nothing*/
}

void SPI_TXCallback(void)
{
   /*Do Nothing*/
}

void UART_RXCallback(void)
{
   BCM_Send(COMM_SPI_CH, 10, gau8_DataBuffer2, SPI_TXCallback);
}


void I2C_RXCallback(void)
{
   BCM_Send(COMM_UART_CH, 10, gau8_DataBuffer1, UART_TXCallback);
   
}

int main(void)
{
   /* Enable Globale Interrupt */
   INTERRUPTS_Enable();
   
   BCM_Receive(COMM_UART_CH, 10, gau8_DataBuffer2, UART_RXCallback);
   BCM_Receive(COMM_I2C_CH, 10, gau8_DataBuffer1, I2C_RXCallback);


   while (TRUE)
   {
      BCM_RxMainFunction();
      BCM_TxMainFunction();
   }
}