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
static uint8_t * gu8_StartMessage = (uint8_t *)"START";
static uint8_t * gu8_StartMessageReply = (uint8_t *)"Green LED is on \r";

static uint8_t * gu8_WaitMessage = (uint8_t *)"WAIT";
static uint8_t * gu8_WaitMessageReply = (uint8_t *)"Yellow LED is on \r";

static uint8_t * gu8_StopMessage = (uint8_t *)"STOP";
static uint8_t * gu8_StopMessageReply = (uint8_t *)"Red LED is on \r";

static uint8_t * gu8_ATMessage = (uint8_t *)"AT";
static uint8_t * gu8_ATMessageReply = (uint8_t *)"OK \r";

static uint8_t * gu8_InvalidMessageReply = (uint8_t *)"Invalid Command \r";

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
   LED_Init();
   UART_Init(UART_CH_0);
}

void Traffic_update(void)
{
   uint8_t string[MAX_STRING_SIZE];
   UART_ReceiveString(UART_CH_0, string);
   
   if(StringCompare(string,gu8_StartMessage) == TRUE)
   {
      LED_Off(LED_CH_2);
      LED_Off(LED_CH_3);
      LED_On(LED_CH_1);
      UART_TransmitString(UART_CH_0, gu8_StartMessageReply);
   }
   else if(StringCompare(string, gu8_WaitMessage) == TRUE)
   {
      LED_Off(LED_CH_1);
      LED_Off(LED_CH_3);
      LED_On(LED_CH_2);
      UART_TransmitString(UART_CH_0, gu8_WaitMessageReply);
   }
   else if(StringCompare(string, gu8_StopMessage) == TRUE)
   {
      LED_Off(LED_CH_1);
      LED_Off(LED_CH_2);
      LED_On(LED_CH_3);
      UART_TransmitString(UART_CH_0, gu8_StopMessageReply);
   }
   else if(StringCompare(string, gu8_ATMessage) == TRUE)
   {
      UART_TransmitString(UART_CH_0, gu8_ATMessageReply);
   }
   else
   {
      UART_TransmitString(UART_CH_0, gu8_InvalidMessageReply);
   }
}