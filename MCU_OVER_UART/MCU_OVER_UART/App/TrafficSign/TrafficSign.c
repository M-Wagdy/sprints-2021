/*
 * TrafficSign.c
 *
 * Created: 7/14/2021 10:13:40 AM
 *  Author: Mohamed Wagdy
 */ 
/*- INCLUDES -----------------------------------------------*/
#include "TrafficSign.h"

/*- LOCAL MACROS
------------------------------------------*/
#define CLK_8_MHZ_9600_BAUD   (uint16_t)(51)
#define MAX_STRING_SIZE       (uint16_t)(200)
#define TRUE                  (uint8_t)(1)
#define FALSE                 (uint8_t)(0)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static uint8_t StringCompare(uint8_t * str1, uint8_t * str2);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
const static uint8_t * gu8_StartMessage = "START";
const static uint8_t * gu8_StartMessageReply = "Green LED is on \r";

const static uint8_t * gu8_WaitMessage = "WAIT";
const static uint8_t * gu8_WaitMessageReply = "Yellow LED is on \r";

const static uint8_t * gu8_StopMessage = "STOP";
const static uint8_t * gu8_StopMessageReply = "Red LED is on \r";

const static uint8_t * gu8_ATMessage = "AT";
const static uint8_t * gu8_ATMessageReply = "OK \r";

const static uint8_t * gu8_InvalidMessageReply = "Invalid Command \r";

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern STR_DIO_config_t gastr_DIO_configurations;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
static uint8_t StringCompare(uint8_t * str1, uint8_t * str2)
{
   uint8_t u8_counter = 0;
   uint8_t u8_isEqual = TRUE;
   
   while(str1[u8_counter] != END_OF_STRING && str1[u8_counter] != NEW_LINE)
   {
      if(str1[u8_counter] != str2[u8_counter])
      {
         u8_isEqual = FALSE;
         u8_counter++;
         break;
      }
      u8_counter++;
   }
   if( str2[u8_counter] != END_OF_STRING )
   {
      u8_isEqual = FALSE;
   }
   return u8_isEqual;
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
void Traffic_init(void)
{
   DIO_init(&gastr_DIO_configurations);
   UART_init(CLK_8_MHZ_9600_BAUD);
}

void Traffic_update(void)
{
   uint8_t string[MAX_STRING_SIZE];
   UART_readString(string);
   
   if(StringCompare(string,gu8_StartMessage) == TRUE)
   {
      LED_Off(LED_CH_2);
      LED_Off(LED_CH_3);
      LED_On(LED_CH_1);
      UART_sendString(gu8_StartMessageReply);
   }
   else if(StringCompare(string, gu8_WaitMessage) == TRUE)
   {
      LED_Off(LED_CH_1);
      LED_Off(LED_CH_3);
      LED_On(LED_CH_2);
      UART_sendString(gu8_WaitMessageReply);
   }
   else if(StringCompare(string, gu8_StopMessage) == TRUE)
   {
      LED_Off(LED_CH_1);
      LED_Off(LED_CH_2);
      LED_On(LED_CH_3);
      UART_sendString(gu8_StopMessageReply);
   }
   else if(StringCompare(string, gu8_ATMessage) == TRUE)
   {
      UART_sendString(gu8_ATMessageReply);
   }
   else
   {
      UART_sendString(gu8_InvalidMessageReply);
   }
}