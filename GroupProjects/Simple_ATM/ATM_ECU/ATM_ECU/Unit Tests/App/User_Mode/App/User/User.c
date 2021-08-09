#include "User.h"

#define Float_Size   (uint8_t)4
#define PAN_Size     (uint8_t)10
#define TRUE         (uint8_t)(1)
#define test  1
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern uint8_t Mock_PressedKey;
extern uint8_t Mock_AuthenticationResult;
extern uint8_t Mock_ExistanceofPAN;
extern uint8_t Mock_CheckAmountResult;
extern uint8_t Mock_CounterOfWrongEntries;
extern uint8_t Mock_Card_Entry;
extern uint8_t USER_InterfaceTestCaseCounter;
extern uint8_t USER_InterfaceTestResult;

ST_cardData_t ST_CurrrentCardDATA;
f32_t f32_EnteredAmount;
uint8_t BTN_Flag=0;
uint8_t StringCmpr(ptr_uint8_t STRING_1, ptr_uint8_t STRING_2) {
	uint8_t i = 0;
	while ((STRING_1[i] != NULL_TERMINATOR) || (STRING_2[i] != NULL_TERMINATOR)) {
		if (STRING_1[i] != STRING_2[i]) {
			return 0;
		} else {
		}
		i++;
	}
	return 1;
}
static uint32_t findLength(ptr_uint8_t str){
	uint32_t size = 0;
	while (str[size])
	{
		size ++;
	}

	return size;
}
static f32_t stof(ptr_uint8_t str){
	uint32_t i=0;
	f32_t result= 0.0;
	uint32_t len = findLength(str);
	uint32_t dotPosition = 0;

	for ( i = 0; i < len; i++)
	{
		if (str[i] == '.')
		{
			dotPosition = len - i  - 1;
		}
		else
		{
			result = result * 10.0 + (str[i]-'0');
		}
	}

	while (dotPosition--)
	{
		result /= 10.0;
	}

	return result;

}
void USER_Mode(){
   while(1)
   {
	   USER_Interface(); //Adel
   }
}
void display_CardRemoved(void){
   uint8_t Dummy;
   LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
   LCD_SendCommand(LCD_RETURN_HOME); //Rehab
   LCD_SendString((ptr_int8_t) "Card Removed"); //Rehab
   /*Start of Press any key...*/
   LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
   LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
   KEYPAD_MustPressed(&Dummy);//Rehab
   while(Dummy != 0)
   {
      KEYPAD_ReadKey(&Dummy);//Rehab
   }
}
void display_WaitingData(){
    #if !test
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Waiting for"); //Rehab
	LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Card"); //Rehab
	#endif
	while(!(PSHBTTN_Status(PORT_A, PIN3)));//Adel
	/*Get PAN from the card MCU*/
	USER_GetCardData(); //Essam
	 #if !test
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "LOADING DATA...");
	#endif
}
void display_ShowMenu(){
	/*Clear LCD and set cursor to the first position in the top row*/
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	//LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	/*printing string on LCD*/
	LCD_SendString( (ptr_int8_t)"1-Insert Card"); //Rehab
	/*Set cursor to the first position in the Lower row*/
	LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
	/*printing string on LCD*/
	LCD_SendString((ptr_int8_t)"2-Display Temp"); //Rehab
	/*pull on keypad until we get a Key Press*/
}
void display_CheckAmount( ptr_uint8_t CheckAmountResult ){
    volatile uint16_t i,j;
	do{
      if(!PSHBTTN_Status(PORT_A, PIN3))
      {
         display_CardRemoved();
         return OperationSuccess;
      }
		/*get amount from user and check it*/
		User_CheckAmount(CheckAmountResult);
		if(*CheckAmountResult == ERROR_FORMAT)
		{
			LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
			LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
			LCD_SendString((ptr_int8_t) "Wrong format");
			/*Start of Press any key...*/
			LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
			LCD_SendString((ptr_int8_t) "Format: xxxx.xx"); //Rehab
			for( i = 0; i< 500; i++)
			{
				for( j = 0; j<2666; j++);
			}
		}
	}while(*CheckAmountResult==ERROR_FORMAT);
}
void display_CheckAmountApproved( uint8_t Dummy, ptr_uint8_t ErrRetVal ){
    volatile uint8_t k,i,l;
	uint8_t au8_UpdatedBalance[10];
   if(!PSHBTTN_Status(PORT_A, PIN3))
   {
      display_CardRemoved();
      return OperationSuccess;
   }
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "APPROVED"); //Rehab
	/*End of Press any key...*/
   User_UpdateBalance();//Rehab
	MOTOR_START(); //Marco
	//						TIM_Delay_MS(1000);//Adel
	for( k=0; k<255;k++)
	for( i=0; i<255;i++)
	for( l=0; l<11;l++);
	MOTOR_STOP();//Marco
	//ftos(ST_CurrrentCardDATA.balance, au8_UpdatedBalance, 2);//I CAN'T FIND THIS FUNCTION ANYWHERE(REHAB)
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Balance: "); //Rehab
	LCD_SendString(au8_UpdatedBalance);
	/*Start of Press any key...*/
	LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Remove Card..."); //Rehab
	while(PSHBTTN_Status(PORT_A, PIN3))
	{

	}
   uint8_t u8_StartAddress=ST_CurrrentCardDATA.index+10;
	EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_4, u8_StartAddress, (uint8_t *)&ST_CurrrentCardDATA.balance,sizeof(f32_t));
   /*KEYPAD_MustPressed(&Dummy);//Rehab
	while(Dummy != 0)
	{
		KEYPAD_ReadKey(&Dummy);//Rehab
	}*/

	*ErrRetVal = OperationSuccess;
}
void diplay_PANNotExist( uint8_t Dummy, ptr_uint8_t ErrRetVal ){
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Card Declined");
	/*Start of Press any key...*/
	LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
	KEYPAD_MustPressed(&Dummy);//Rehab
	while(Dummy != 0)
	{
		KEYPAD_ReadKey(&Dummy);//Rehab
	}
	/*End of Press any key...*/
	*ErrRetVal = OperationSuccess;
}
void display_CheckAmountInsufficient( uint8_t Dummy, ptr_uint8_t ErrRetVal ){
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Not enough Fund"); //Rehab
	/*Start of Press any key...*/
	LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
	LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
	KEYPAD_MustPressed(&Dummy);//Rehab
	while(Dummy != 0)
	{
		KEYPAD_ReadKey(&Dummy);//Rehab
	}
	/*End of Press any key...*/
	*ErrRetVal = OperationSuccess;
}
uint8_t USER_Interface(){
	uint8_t ErrRetVal = OperationStarted;
	uint8_t Flag = 0;
while(1)
{
	#if !test
	uint8_t PressedKey = 0;
	uint8_t AuthenticationResult = 0;
	uint8_t CheckAmountResult = 0;
	uint8_t CounterWrongPinEntries = 0;
	uint8_t Dummy = 0;
	uint8_t u8_IsExist = NOTEXIST;
	uint8_t Push_Button = 0;

	display_ShowMenu();
	#else

	if(Flag==1)
    {
        break;
    }
	Flag = 1;
	uint8_t Dummy = 0;
	uint8_t PressedKey = Mock_PressedKey;
	uint8_t AuthenticationResult = Mock_AuthenticationResult;
	uint8_t u8_IsExist = Mock_ExistanceofPAN;
	uint8_t CheckAmountResult = Mock_CheckAmountResult;
	uint8_t CounterWrongPinEntries = Mock_CounterOfWrongEntries;
    uint8_t Push_Button = Mock_Card_Entry;
	#endif

	while(PressedKey==0)
	{
		KEYPAD_ReadKey(&PressedKey); //Rehab

	}
#if !test
	/*Clear LCD and set cursor to the first position in the top row*/
	LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
	/*check the pressed key*/

#endif // test


	if(PressedKey=='1')
	{

		#if !test
		while(PressedKey == '1')
		{
			KEYPAD_ReadKey(&PressedKey);//Rehab
		}

		/*Hold program until card is inserted*/
		display_WaitingData();

		u8_IsExist = USER_GetServerData();
        #endif
		if(u8_IsExist==EXIST)//Essam
		{

			do{
                #if !test
                Push_Button = PSHBTTN_Status(PORT_A, PIN3);
                #endif
                if(!Push_Button)
                {
                   #if !test
                   display_CardRemoved();
                   #else
                   if(USER_InterfaceTestCaseCounter == 10)
                        USER_InterfaceTestResult = 0;
                    break;
                   #endif

                   return OperationSuccess;
                }
                /*get PIN from user For Authentication*/
                #if !test
                User_Authenticate(&AuthenticationResult); //Rehab
                #endif
                if(AuthenticationResult == CORRECT_PIN)
                {
                    CounterWrongPinEntries=0;
                    /*pull on Get amount until user enters the amount in a right format*/
                    #if !test
                    display_CheckAmount(&CheckAmountResult);
                    #endif


                    if(CheckAmountResult==APPROVED)
                    {
                        #if !test
                        display_CheckAmountApproved(Dummy, &ErrRetVal);
                        #else
                        if(USER_InterfaceTestCaseCounter == 1)
                            USER_InterfaceTestResult = 0;
                            break;
                        #endif
                    }
                    else if(CheckAmountResult==INSUFFICIENT_FUND)
                    {
                        #if !test
                        display_CheckAmountInsufficient(Dummy, &ErrRetVal);
                        #else
                        if(USER_InterfaceTestCaseCounter == 9)
                            USER_InterfaceTestResult = 0;
                        break;
                        #endif
                    }
                    else if(CheckAmountResult==EXCEED_MAX_AMOUNT)
                    {
                        #if !test
                        LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
                        LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
                        LCD_SendString((ptr_int8_t) "Max Val Exceeded"); //Rehab
                        /*Start of Press any key...*/
                        LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                        LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
                        KEYPAD_MustPressed(&Dummy);//Rehab
                        while(Dummy != 0)
                        {
                            KEYPAD_ReadKey(&Dummy);//Rehab
                        }
                        /*End of Press any key...*/
                        #else
                        if(USER_InterfaceTestCaseCounter == 8)
                            USER_InterfaceTestResult = 0;
                        break;
                        #endif
                        ErrRetVal = OperationSuccess;
                    }
                    else
                    {
                        ErrRetVal=OperationFailed;
                    }
                }
                else if (AuthenticationResult == WRONG_PIN)
                {
                    #if !test
                    LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
                    LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
                    #endif
                    CounterWrongPinEntries++;
                    #if !test
                    LCD_SendString((ptr_int8_t) "Wrong PIN"); //Rehab
                    /*Start of Press any key...*/
                    LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                    LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
                    KEYPAD_MustPressed(&Dummy);//Rehab
                    while(Dummy != 0)
                    {
                        KEYPAD_ReadKey(&Dummy);//Rehab
                    }
                    /*End of Press any key...*/
                    #else
                    if(USER_InterfaceTestCaseCounter == 6)
                        USER_InterfaceTestResult = 0;
                        break;
                    #endif

                    if(CounterWrongPinEntries >= 3)
                    {

                        #if !test
                        LCD_SendCommand(LCD_CLEAR_DISPALY); //Rehab
                        LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0)); //Rehab
                        LCD_SendString((ptr_int8_t) "3 wrong PINs");//Rehab
                        CounterWrongPinEntries=0;
                        /*Start of Press any key...*/
                        LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
                        LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
                        KEYPAD_MustPressed(&Dummy);//Rehab
                        while(Dummy != 0)
                        {
                            KEYPAD_ReadKey(&Dummy);//Rehab
                        }
                        /*End of Press any key...*/
                        #else
                        if(USER_InterfaceTestCaseCounter == 11)
                            USER_InterfaceTestResult = 0;
                        break;
                        #endif
                        ErrRetVal = OperationSuccess;
                        break;
                    }
                }
                else
                {

                    #if test
                    if(USER_InterfaceTestCaseCounter == 7)
                        USER_InterfaceTestResult = 0;
                        break;
                    #endif
                    ErrRetVal=OperationFail;
                }
			}while(AuthenticationResult!=CORRECT_PIN);
		}
		else if(u8_IsExist==NOTEXIST)
		{
		    #if !test
			diplay_PANNotExist(Dummy, &ErrRetVal);
			#else
			if(USER_InterfaceTestCaseCounter == 4)
                USER_InterfaceTestResult = 0;
                break;
            #endif
		}
		else
		{
		    #if test
		    if(USER_InterfaceTestCaseCounter == 5)
                USER_InterfaceTestResult = 0;
                break;
		    #endif // test
			ErrRetVal=OperationFail;
		}
	}
	else if (PressedKey=='2')
	{
        #if !test
		USER_PrintTemp(TEMP_CH_0);//Essam

		while(PressedKey == '2')
		{
			KEYPAD_ReadKey(&PressedKey);//Rehab
		}
		/*Start of Press any key...*/
		LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
		LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab

		KEYPAD_MustPressed(&Dummy);//Rehab
		while(Dummy != 0)
		{
			KEYPAD_ReadKey(&Dummy);//Rehab
		}
		/*End of Press any key...*/
		#else
        if(USER_InterfaceTestCaseCounter == 2)
            USER_InterfaceTestResult = 0;
            break;
		#endif

		ErrRetVal = OperationSuccess;
	}
	else{
        #if test
        if(USER_InterfaceTestCaseCounter == 3)
            USER_InterfaceTestResult = 0;
            break;
        #endif // test
		//LCD_SendString((ptr_int8_t) "Set valid choice"); //Rehab
		/*Start of Press any key...*/
		//LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(0)); //Rehab
		//LCD_SendString((ptr_int8_t) "Press any key..."); //Rehab
		//KEYPAD_MustPressed(&Dummy);//Rehab
		//while(Dummy != 0)
		//{
			//   KEYPAD_ReadKey(&Dummy);//Rehab
		//}
		/*End of Press any key...*/
		//ErrRetVal = OperationSuccess;
   }
}
	return ErrRetVal;

}
uint8_t USER_GetCardData(void) {
#if !test

	uint8_t Dummy;
	SPI_TransmitChar(SPIChannel_1,'K',SlaveID_1);
	while(!(SPI_StatusReg & 0x80));
	Dummy = SPI_DataReg;
	dummy_delay();
	dummy_delay();
	dummy_delay();
#endif // test

	/* Get Primary Account Number */
	SPI_ReceiveString(SPIChannel_1, ST_CurrrentCardDATA.primaryAccountNumber, SlaveID_1);
	/* Get PIN */
	SPI_ReceiveString(SPIChannel_1,ST_CurrrentCardDATA.pin, SlaveID_1);
	return 0;
}
EN_inServer_t USER_GetServerData(void) {
	/* FLAG IF THE PAN EXIST */
	/* EEPROM ADDRRESS COUNTER */
	uint8_t EEPROM_COUNTER = 0;
	/* EEPROM BLOCK COUNTER */
	//	uint8_t EEPROM_BLOCK=0;
	/* BUFFER TO STORE THE PAN FROM SERVER AND COMPARE */
	uint8_t PAN_FROM_SERVER[PAN_Size ];

	uint8_t u8_AccountsNumber=0;
	uint8_t u8_AccountNumberCounter = 0;
	EEPROM_Read(EEPROM_CH_0,MEMORY_BLOCK_3,0x00,&u8_AccountsNumber);
	if (u8_AccountsNumber == 'N')
	{
		return NOTEXIST;
	}
	/* GET PAN(10 byte including NULL)  */
	EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_4, EEPROM_COUNTER,PAN_FROM_SERVER, PAN_Size);
	/*STUCK IN THIS WHILE TILL YOU FIND A STRING MATCH */
	while (StringCmpr(PAN_FROM_SERVER, ST_CurrrentCardDATA.primaryAccountNumber)
	!= TRUE) {
		/*EVERY USER DATA STORED IN 14 BYTES IN EEPROM SO THE FIRST CHAR OF PAN EXIST IN 0,14,28,42,56,70,84.....252  */
		EEPROM_COUNTER = EEPROM_COUNTER + 14;
		u8_AccountNumberCounter++;
		if (EEPROM_COUNTER >= 252 || u8_AccountNumberCounter >= u8_AccountsNumber) {
			/* IF NO MATCH RETURN 0 */
			ST_CurrrentCardDATA.index=0;
			/* matched = 0;*/
			//			break;
			return NOTEXIST;
		}
        EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_4, EEPROM_COUNTER,
		PAN_FROM_SERVER, PAN_Size);

	}
	/* READ BALANCE FROM SERVER */
	EEPROM_ReadBytes(EEPROM_CH_0, MEMORY_BLOCK_4, (EEPROM_COUNTER + 10), (ptr_uint8_t) &(ST_CurrrentCardDATA.balance), sizeof(f32_t));

	ST_CurrrentCardDATA.index = EEPROM_COUNTER;
	return EXIST;
}
uint8_t USER_PrintTemp(uint8_t Temp_Ch){
	/*VARIABLE TO STORE TEMPRETURE*/
	uint8_t temperture=0;
	/*GET TEMPERTURE AND STORE IT IN TERPRETURE*/
	TEMP_GetTemp(Temp_Ch,&temperture);
	/*PRINT IN LCD "TEMP IS ..."*/
	LCD_SendString((ptr_int8_t) "Temp is ");
	LCD_SendNumber(temperture);
	return 0;//SUCCESS
}
uint8_t User_Authenticate(ptr_uint8_t PINState){
	uint8_t au8_EnteredPIN[PIN_LENGTH],i;
	sint32_t int32_StringState;

	//1-print on LCD Please enter the pin number
	LCD_SendCommand(LCD_CLEAR_DISPALY);
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0));
	LCD_SendString((ptr_int8_t) "Enter PIN");

	//2-read pin from keypad till enter 5 numbers
	for( i=0;i<PIN_LENGTH;i++)
	{
		LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(i));
		if(i==4)
		{
			au8_EnteredPIN[i]='\0';
			break;
		}
		KEYPAD_MustPressed(&au8_EnteredPIN[i]);
		LCD_SendData('*');
		while(1)
		{
			uint8_t u8_Key;
			KEYPAD_ReadKey(&u8_Key);
			if(u8_Key!=au8_EnteredPIN[i])
			{
				break;
			}
		}

	}

	//3-check if entered PIN equal Saved PIN or not
	int32_StringState=StringCompare(au8_EnteredPIN,ST_CurrrentCardDATA.pin);

	//4-update PINState and return
	if(int32_StringState==TRUE)
	{
		*PINState=CORRECT_PIN;
	}
	else
	{
		*PINState=WRONG_PIN;
	}
	return OperationSuccess;
}
uint8_t User_CheckAmount(ptr_uint8_t AmountState){
	uint8_t au8_EnteredAmount[AMOUNT_LENGTH],i;
	f32_t f32_MaxAmount;

	//1-print on LCD Please enter the required Amount
	LCD_SendCommand(LCD_CLEAR_DISPALY);
	LCD_SendCommand(LCD_LINE1_DDRAM_ADDRESS(0));
	LCD_SendString((ptr_int8_t) "Enter Amount");

	//2-read amount from keypad till enter 7 numbers
	for( i=0;i<AMOUNT_LENGTH;i++)
	{
		LCD_SendCommand(LCD_LINE2_DDRAM_ADDRESS(i));
		if(i==7)
		{
			au8_EnteredAmount[i]='\0';
			break;
		}
		KEYPAD_MustPressed(&au8_EnteredAmount[i]);
		while(1)
		{
			uint8_t u8_Key;
			KEYPAD_ReadKey(&u8_Key);
			if(u8_Key!=au8_EnteredAmount[i])
			{
				break;
			}
		}
		if(au8_EnteredAmount[i]=='*')
		{
			au8_EnteredAmount[i]='.';
		}

		LCD_SendData(au8_EnteredAmount[i]);
		if(i==4)
		{
			if(au8_EnteredAmount[i]!='.')
			{
				*AmountState=ERROR_FORMAT;
				return;
			}
		}
		else
		{
			if((au8_EnteredAmount[i]=='.') || (au8_EnteredAmount[i]=='#'))
			{
				*AmountState=ERROR_FORMAT;
				return;
			}
		}
	}

	//3- Convert from string to float
	f32_EnteredAmount=stof(au8_EnteredAmount);

	//4-Read Max Amount
	EEPROM_ReadBytes(EEPROM_CH_0,MEMORY_BLOCK_2,0x0,(ptr_uint8_t) &f32_MaxAmount,sizeof(f32_t));

	//5-check if the entered Amount >max amount (Read EEPROM)
	//then update AmountState=EXCEED_MAX_AMOUNT, print on LCD notification message and return
	//else go t0 step 6

	if(f32_EnteredAmount>f32_MaxAmount)
	{
		*AmountState=EXCEED_MAX_AMOUNT;
	}
	else if(f32_EnteredAmount>ST_CurrrentCardDATA.balance)
	{
		*AmountState=INSUFFICIENT_FUND;
	}
	else
	{
		*AmountState=APPROVED;
	}

}
uint8_t User_UpdateBalance(void){
	//1-update the balance
	ST_CurrrentCardDATA.balance -= f32_EnteredAmount;
	//2-update the Server by the new balance(write EEPROM)
	/*uint8_t u8_StartAddress=ST_CurrrentCardDATA.index+10;
	EEPROM_WriteBytes(EEPROM_CH_0, MEMORY_BLOCK_4, u8_StartAddress, (uint8_t *)&ST_CurrrentCardDATA.balance,sizeof(f32_t));*/

   return OperationSuccess;
}
