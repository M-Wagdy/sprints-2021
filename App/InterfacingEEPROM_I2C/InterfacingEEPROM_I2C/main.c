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
#include "Mcal/Atmega32/UART/UART.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MAX_STRING_SIZE       (uint8_t)(200)
#define TRUE                  (uint8_t)(1)
#define FALSE                 (uint8_t)(0)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t * gu8_CommandMessage = (uint8_t *)"Please enter a READ/WRITE Command: \r";
static uint8_t * gu8_AddressMessage = (uint8_t *)"Please enter an Address: \r";
static uint8_t * gu8_DataMessage = (uint8_t *)"Please enter data: \r";

static uint8_t * gu8_WriteMessage = (uint8_t *)"WRITE";
static uint8_t * gu8_ReadMessage = (uint8_t *)"READ";
static uint8_t * gu8_UARTMessageReply = (uint8_t *)"\rOK \r";
static uint8_t * gu8_ReadMessageReply = (uint8_t *)"the data stored is: \r";
static uint8_t * gu8_InvalidMessageReply = (uint8_t *)"Invalid Command \r";

int main(void)
{
   /* initialize needed drivers */
   EEPROM_Init(EEPROM_CH_0);
   UART_Init(UART_CH_0);
   
   while(1)
   {
      uint8_t string[MAX_STRING_SIZE];
      uint8_t data;
      uint8_t address;
      
      /* get command message */
      UART_TransmitString(UART_CH_0, gu8_CommandMessage);
      
      /* get command */
      UART_ReceiveString(UART_CH_0, string);
      
      if (StringCompare(string,gu8_WriteMessage) == TRUE)
      {
         /* get address message */
         UART_TransmitString(UART_CH_0, gu8_AddressMessage);
         
         /* get address */
         UART_ReceiveChar(UART_CH_0, &address);
         
         /* respond "OK" */
         UART_TransmitString(UART_CH_0, gu8_UARTMessageReply);
         
         /* get data message */
         UART_TransmitString(UART_CH_0, gu8_DataMessage);
         
         /* get data to write */
         UART_ReceiveChar(UART_CH_0, &data);
         
         /* write data in the given address in the EEPROM */
         EEPROM_Write(EEPROM_CH_0, MEMORY_BLOCK_1, address, data);
         
         /* respond "OK" */
         UART_TransmitString(UART_CH_0, gu8_UARTMessageReply);
      }
      else if(StringCompare(string,gu8_ReadMessage) == TRUE)
      {
         /* get address message */
         UART_TransmitString(UART_CH_0, gu8_AddressMessage);
         
         /* get address */
         UART_ReceiveChar(UART_CH_0, &address);
         
         /* respond "OK" */
         UART_TransmitString(UART_CH_0, gu8_UARTMessageReply);
         
         /* get data from the given address */
         EEPROM_Read(EEPROM_CH_0, MEMORY_BLOCK_1, address, &data);
         
         /* transmit a reply message before transmitting the data in the address */
         UART_TransmitString(UART_CH_0, gu8_ReadMessageReply);
         
         /* transmit the data in the address */
         UART_TransmitChar(UART_CH_0, data);
         
         /* new line */
         UART_TransmitChar(UART_CH_0, NEW_LINE);
      }
      else
      {
         /* transmit "Invalid Command" message */
         UART_TransmitString(UART_CH_0, gu8_InvalidMessageReply);
      }
   }
}

