/*
 * I2C_w_EEPROM.c
 *
 * Created: 7/20/2021 10:49:18 AM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Infrastructure/utils.h"
#include "Firmware/EEPROM/EEPROM.h"
#include "Mcal/UART/UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MAX_STRING_SIZE       (uint8_t)(200)
#define TRUE                  (uint8_t)(1)
#define FALSE                 (uint8_t)(0)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t * gu8_WriteMessage = "WRITE";
static uint8_t * gu8_ReadMessage = "READ";
static uint8_t * gu8_UARTMessageReply = "\rOK \r";
static uint8_t * gu8_ReadMessageReply = "the data stored is: \r";
static uint8_t * gu8_InvalidMessageReply = "Invalid Command \r";

int main(void)
{
   EEPROM_Init(EEPROM_CH_0);
   UART_Init(UART_CH_0);
   
   while(1)
   {
      uint8_t string[MAX_STRING_SIZE];
      uint8_t data;
      uint8_t address;
      UART_ReceiveString(UART_CH_0, string);
      
      UART_ReceiveChar(UART_CH_0, &address);
      
      UART_TransmitString(UART_CH_0, gu8_UARTMessageReply);
      
      if (StringCompare(string,gu8_WriteMessage) == TRUE)
      {
         UART_ReceiveChar(UART_CH_0, &data);
         
         EEPROM_Write(EEPROM_CH_0, address, data);
         
         UART_TransmitString(UART_CH_0, gu8_UARTMessageReply);
      }
      else if(StringCompare(string,gu8_ReadMessage) == TRUE)
      {
         EEPROM_Read(EEPROM_CH_0, address, &data);
         
         UART_TransmitString(UART_CH_0, gu8_ReadMessageReply);
         
         UART_TransmitChar(UART_CH_0, data);
      }
      else
      {
         UART_TransmitString(UART_CH_0, gu8_InvalidMessageReply);
      }
   }
}

