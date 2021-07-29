/*
 * ATM_ECU.c
 *
 * Created: 7/28/2021 3:54:21 PM
 * Author : Dr. Sahar
 */ 

#include "Mcal/UART/uart.h"
#include "Mcal/SPI/SPI.h"

uint8_t PAN[10];
uint8_t PIN[5];

int main(void)
{
   SPI_Init(SPIChannel_1);
   UART_Init(UART_1);
   
   dummy_delay();
   dummy_delay();
   dummy_delay();
   dummy_delay();
   
   UART_TransmitString(UART_1, "Starting SPI Transmission");
   
   /*SPI_ReceiveString(SPIChannel_1, PAN, SlaveID_1);
   SPI_ReceiveString(SPIChannel_1, PIN, SlaveID_1);

   UART_TransmitString(UART_1, "Received PAN:");
   UART_TransmitString(UART_1, PAN);
   UART_TransmitString(UART_1, "Received PIN:");
   UART_TransmitString(UART_1, PIN);*/

   /* Replace with your application code */
   while (1) 
   {
   }
}

