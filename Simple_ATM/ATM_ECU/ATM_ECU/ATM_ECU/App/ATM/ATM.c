#include "ATM.h"

#define TRUE      (uint8_t)(1)

uint8_t ATM_Init()
{
   uint8_t ErrRetVal = OperationStarted;
   /*initializing the UART Module*/
   UART_Init(UART_1); //Essam
   /*initializing the SPI*/
   SPI_Init(SPIChannel_1); //Adel
   /*initializing the push button*/
   PSHBTTN_Init(PORT_B, PIN2, PULLED_DWN); //Adel
   /*initializing the keypad*/
   KEYPAD_Init(); //Rehab
   /*initializing the ATM LCD*/
   LCD_Init(); //Rehab
   /*initializing the motor*/
   MOTOR_INIT(); //Marco
   /*initializing the EEPROM*/
   EEPROM_Init(EEPROM_CH_0); //Wagdy
   /*initializing temperature sensor*/
   /*this line could require further modification*/
   TEMP_Init(TEMP_CH_0); //Essam
   ErrRetVal=OperationSuccess;
   return ErrRetVal;
}

uint8_t ATM_SelectMode() //Adel
{
   uint8_t ErrRetVal = OperationStarted;
   /*local buffer for receiving user input from terminal*/
   uint8_t Character[255];
   /*Receiving user input from terminal*/
   UART_ReceiveString(UART_1, Character); //Essam
   /*Check if entered string is "ADMIN"*/
   if(StringCompare(Character,(uint8_t*)"ADMIN")==TRUE) //Wagdy
   {
      /*Entering programming mode*/
      ADMIN_Mode(); //Marco
      ErrRetVal=OperationSuccess;
   }
   /*check if entered string is "USER"*/
   else if (StringCompare(Character,(uint8_t*)"USER")==TRUE)//Wagdy
   {
      /*Entering user mode*/
      USER_Mode(); //Adel
      ErrRetVal=OperationSuccess;
   }
   else
   {
      /*letting the user know that he have entered an invalid input*/
      UART_TransmitString(UART_1,(uint8_t*)"Invalid input Please enter a valid choice"); //Essam
   }
   return ErrRetVal;
}