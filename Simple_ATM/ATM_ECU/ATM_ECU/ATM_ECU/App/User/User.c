#include "User.h"

void USER_Mode() //Adel
{
   USER_Interface(); //Adel
}

uint8_t USER_Interface()
{
   uint8_t ErrRetVal = OperationStarted;
   uint8_t PressedKey = 0;
   uint8_t AuthenticationResult = 0;
   uint8_t CheckAmountResult = 0;
   uint8_t CounterWrongPinEntries = 0;
   uint8_t Dummy = 0;
   /*Clear LCD and set cursor to the first position in the top row*/
   LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
   LCD_SendCommand(LCD_RETURN_HOME); //Rehab
   LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
   /*printing string on LCD*/
   LCD_SendString("1-Insert Card"); //Rehab
   /*Set cursor to the first position in the Lower row*/
   LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
   /*printing string on LCD*/
   LCD_SendString("2-Display temperature"); //Rehab
   /*pull on keypad until we get a Key Press*/
   while(PressedKey==0)
   {
      KEYPAD_ReadKey(&PressedKey); //Rehab
   }
   /*Clear LCD and set cursor to the first position in the top row*/
   LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
   LCD_SendCommand(LCD_RETURN_HOME); //Rehab
   /*check the pressed key*/
   if(PressedKey=='1')
   {
      /*Hold program until card is inserted*/
      while(!(PSHBTTN_Status(PORTB, PIN2)));//Adel
      /*Get PAN from the card MCU*/
      USER_GetCardData(); //Essam
      if(USER_GetServerData()==EXIST)//Essam
      {
         do{
            /*get PIN from user For Authentication*/
            USER_Authenticate(&AuthenticationResult); //Rehab
            if(AuthenticationResult == CORRECT_PIN)
            {
               CounterWrongPinEntries=0;
               /*pull on Get amount until user enters the amount in a right format*/
               do{
                  /*get amount from user and check it*/
                  USER_CheckAmount(&CheckAmountResult); //Rehab
               }while(CheckAmountResult==ERROR_FORMAT);

               if(CheckAmountResult==APPROVED)
               {
                  LCD_SendString("APPROVED"); //Rehab
                  /*Start of Press any key to continue*/
                  LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                  LCD_SendString("Press any key to continue"); //Rehab
                  while(Dummy==0)
                  {
                     KEYPAD_ReadKey(&Dummy); //Rehab
                  }
                  /*End of Press any key to continue*/
                  MOTOR_START(); //Marco
                  //						TIM_Delay_MS(1000);//Adel
                  for(volatile uint8_t k=0; k<255;k++)
                  for(volatile uint8_t i=0; i<255;i++)
                  for(volatile uint8_t l=0; l<11;l++);
                  MOTOR_STOP();//Marco
                  USER_UpdateBalance();//Rehab
                  ErrRetVal = OperationSuccess;
               }
               else if(CheckAmountResult==INSUFFICIENT_FUND)
               {
                  LCD_SendString("Insufficient Fund"); //Rehab
                  /*Start of Press any key to continue*/
                  LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                  LCD_SendString("Press any key to continue"); //Rehab
                  while(Dummy==0)
                  {
                     KEYPAD_ReadKey(&Dummy); //Rehab
                  }
                  /*End of Press any key to continue*/
                  ErrRetVal = OperationSuccess;
               }
               else if(CheckAmountResult==EXCEED_MAX_AMOUNT)
               {
                  LCD_SendString("Max Amount Exceeded"); //Rehab
                  /*Start of Press any key to continue*/
                  LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                  LCD_SendString("Press any key to continue"); //Rehab
                  while(Dummy==0)
                  {
                     KEYPAD_ReadKey(&Dummy); //Rehab
                  }
                  /*End of Press any key to continue*/
                  ErrRetVal = OperationSuccess;
               }
               else
               {
                  ErrRetVal=OperationFail;
               }
            }
            else if (AuthenticationResult == WRONG_PIN)
            {
               CounterWrongPinEntries++;
               LCD_SendString("Wrong PIN"); //Rehab
               /*Start of Press any key to continue*/
               LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
               LCD_SendString("Press any key to continue"); //Rehab
               while(Dummy==0)
               {
                  KEYPAD_ReadKey(&Dummy); //Rehab
               }
               /*End of Press any key to continue*/
               if(CounterWrongPinEntries >= 3)
               {
                  LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
                  LCD_SendCommand(LCD_RETURN_HOME); //Rehab
                  LCD_SendString("You Have Entered Wrong PIN For 3 Times");//Rehab
                  CounterWrongPinEntries=0;
                  /*Start of Press any key to continue*/
                  LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                  LCD_SendString("Press any key to continue"); //Rehab
                  while(Dummy==0)
                  {
                     KEYPAD_ReadKey(&Dummy); //Rehab
                  }
                  /*End of Press any key to continue*/
                  ErrRetVal = OperationSuccess;
                  break;
               }
            }
            else
            {
               ErrRetVal=OperationFail;
            }
         }while(AuthenticationResult!=CORRECT_PIN);
      }
      else if(USER_GetServerData()==NOTEXIST)
      {
         LCD_SendString("Card Declined");
         /*Start of Press any key to continue*/
         LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
         LCD_SendString("Press any key to continue"); //Rehab
         while(Dummy==0)
         {
            KEYPAD_ReadKey(&Dummy); //Rehab
         }
         /*End of Press any key to continue*/
         ErrRetVal = OperationSuccess;
      }
      else
      {
         ErrRetVal=OperationFail;
      }
   }
   else if (PressedKey=='2')
   {
      USER_PrintTemp();
      /*Start of Press any key to continue*/
      LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
      LCD_SendString("Press any key to continue"); //Rehab
      while(Dummy==0)
      {
         KEYPAD_ReadKey(&Dummy); //Rehab
      }
      /*End of Press any key to continue*/
      ErrRetVal = OperationSuccess;
   }
   else{
      LCD_SendString("please enter a valid choice"); //Rehab
      /*Start of Press any key to continue*/
      LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
      LCD_SendString("Press any key to continue"); //Rehab
      while(Dummy==0)
      {
         KEYPAD_ReadKey(&Dummy); //Rehab
      }
      /*End of Press any key to continue*/
      ErrRetVal = OperationSuccess;
   }
   return ErrRetVal;
}
