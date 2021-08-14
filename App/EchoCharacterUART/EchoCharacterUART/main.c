/*
 * UART_Driver.c
 *
 * Created: 7/13/2021 2:50:00 PM
 * Author : Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Mcal/Atmega32/UART/UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MAX_STRING_SIZE       (uint16_t)(200)

int main(void)
{
   uint8_t string[MAX_STRING_SIZE];
   UART_Init(UART_CH_0);
   
   while(1)
   {
      UART_ReceiveString(UART_CH_0, string);
      UART_TransmitString(UART_CH_0, string);
   }
}

