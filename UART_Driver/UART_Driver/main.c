/*
 * UART_Driver.c
 *
 * Created: 7/13/2021 2:50:00 PM
 * Author : Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Mcal/UART/UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define CLK_8_MHZ_9600_BAUD   (uint16_t)(51)
#define MAX_STRING_SIZE       (uint16_t)(200)

int main(void)
{
   uint8_t string[MAX_STRING_SIZE];
   UART_init(CLK_8_MHZ_9600_BAUD);
   
   while(1)
   {
      UART_readString(string);
      UART_sendString(string);
   }
}

