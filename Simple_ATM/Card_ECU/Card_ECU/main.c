/*
 * Card_ECU.c
 *
 * Created: 7/24/2021 5:14:42 PM
 * Author : Mohamed Wagdy
 */ 

#include "App/Card/Card.h"

/*- LOCAL MACROS
------------------------------------------*/
#define TRUE                  (uint8_t)(1)
#define FALSE                 (uint8_t)(0)
#define PROGRAMMING_MODE      (uint8_t)(0)
#define USER_MODE             (uint8_t)(1)

static uint8_t * gu8_AdminCommand = "ADMIN";
static uint8_t gu8_Mode = PROGRAMMING_MODE;
uint8_t TerminalData[255];

STR_cardData_t CardData;

int main(void)
{
   CARD_Init();
   
   CARD_GetUserData(&CardData);
   
   if(CardData.au8_PIN[0] == 0xFF)
   {
      CARD_SetUserData();
   }

   /* Replace with your application code */
   while (1) 
   {
      Terminal_Read(TerminalData);
      if(StringCompare(TerminalData, gu8_AdminCommand) == TRUE)
      {
         CARD_SetUserData();
      }
   }
}

