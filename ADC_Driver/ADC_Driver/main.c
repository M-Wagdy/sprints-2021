/*
 * ADC_Driver.c
 *
 * Created: 7/21/2021 6:20:24 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Mcal/ADC/ADC.h"
#include "Mcal/UART/UART.h"
#include "Infrastructure/utils.h"

/*- LOCAL MACROS
------------------------------------------*/
#define ZERO_ASCII         (uint8_t)(0x30)

int main(void)
{
   uint16_t u8_data;
   
   uint8_t u8_digit1;
   uint8_t u8_digit2;
   uint8_t u8_digit3;
   
   /* initialize drivers */
   ADC_Init();
   UART_Init(UART_CH_0);
   
   /* Replace with your application code */
   while (1) 
   {
      /* get ADC readings */
      ADC_Read(ADC_CH_0, &u8_data);
      
      /* map ADC resolution to the current temprature */
      u8_data = (u8_data * 150 / 308);
      
      /* get each number in single character */
      u8_digit1 = (u8_data/100);
      u8_digit2 = ((u8_data - (u8_digit1*100)) / 10);
      u8_digit3 = (u8_data - (u8_digit1*100+u8_digit2*10));
      
      /* transmit the numbers ASCII through uart */
      UART_TransmitChar(UART_CH_0,  u8_digit1 + ZERO_ASCII);
      UART_TransmitChar(UART_CH_0,  u8_digit2 + ZERO_ASCII);
      UART_TransmitChar(UART_CH_0,  u8_digit3 + ZERO_ASCII);
      UART_TransmitChar(UART_CH_0,  '\r');
      
      /* small delay */
      dummy_delay();
   }
}

