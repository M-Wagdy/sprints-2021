#include "../../Infrastructure/infrastructure.h"

#include "../../Mcal/DIO/DIO.h"
#include "../../MCAL/Timer/Timer.h"
#include "LCD.h"

uint8_t LCD_SendCommand(uint8_t CMD)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static State = OperationStarted;
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = 1;
	switch(State)
	{
	case OperationStarted:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(LCD_PORT, LCD_RS, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_RW, PIN_LOW);

		/*copying upper nibble of the command to the pins*/
		DIO_WritePin(LCD_PORT, LCD_D4, READ_BIT(CMD, 4));
		DIO_WritePin(LCD_PORT, LCD_D5, READ_BIT(CMD, 5));
		DIO_WritePin(LCD_PORT, LCD_D6, READ_BIT(CMD, 6));
		DIO_WritePin(LCD_PORT, LCD_D7, READ_BIT(CMD, 7));


		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(LCD_PORT, LCD_EN, PIN_HIGH);
		/*set status of the function*/
		State = Sending_First_Nibble;
		break;
	case Sending_First_Nibble:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2,3);//1
		if(TimerRetVal == TIMER_E_SUCCESS)
		{
			/*if timer delay function finished correctly pull enable pin low*/
			DIO_WritePin(LCD_PORT, LCD_EN, PIN_LOW);
			/*update the function's state*/
			State = First_Nibble_Sent;
		}
		break;
	case First_Nibble_Sent:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(LCD_PORT,LCD_RS,PIN_LOW);
		DIO_WritePin(LCD_PORT,LCD_RW,PIN_LOW);

		/*copying lower nibble of the command to the pins*/

		DIO_WritePin(LCD_PORT,LCD_D4,READ_BIT(CMD,0));
		DIO_WritePin(LCD_PORT,LCD_D5,READ_BIT(CMD,1));
		DIO_WritePin(LCD_PORT,LCD_D6,READ_BIT(CMD,2));
		DIO_WritePin(LCD_PORT,LCD_D7,READ_BIT(CMD,3));
		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(LCD_PORT,LCD_EN,PIN_HIGH);
		/*set status of the function*/
		State = Sending_Second_Nibble;
		break;
	case Sending_Second_Nibble:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2,3);//1
		if(TimerRetVal == ((uint8_t)TIMER_E_SUCCESS))
		{
			/*if timer delay function finished correctly pull enable pin low*/
			DIO_WritePin(LCD_PORT,LCD_EN,PIN_LOW);
			/*reset the function's state*/
			State = Second_Nibble_Sent;
		}
		break;
	case Second_Nibble_Sent:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2,5);//2
		if(TimerRetVal == ((uint8_t)TIMER_E_SUCCESS))
		{
			/*reset the function's state*/
			State = OperationStarted;
			/*process finished successfully*/
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		ErrRetVal = OperationFail;
	}
	/*return from function*/
return ErrRetVal;
}
uint8_t LCD_SendData(uint8_t Character)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static State = OperationStarted;
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = 1;
	switch (State) {
	case OperationStarted:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(LCD_PORT, LCD_RS, PIN_HIGH);
		DIO_WritePin(LCD_PORT, LCD_RW, PIN_LOW);
		/*copying upper nibble of the command to the pins*/
		DIO_WritePin(LCD_PORT, LCD_D7, READ_BIT(Character, 7));
		DIO_WritePin(LCD_PORT, LCD_D6, READ_BIT(Character, 6));
		DIO_WritePin(LCD_PORT, LCD_D5, READ_BIT(Character, 5));
		DIO_WritePin(LCD_PORT, LCD_D4, READ_BIT(Character, 4));

		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(LCD_PORT, LCD_EN, PIN_HIGH);
		/*set status of the function*/
		State = Sending_First_Nibble;
		break;
	case Sending_First_Nibble:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2, 3);//1
		if (TimerRetVal == TIMER_E_SUCCESS) {
			DIO_WritePin(LCD_PORT, LCD_EN, PIN_LOW);
			/*update the function's state*/
			State = First_Nibble_Sent;
		}
		break;
	case First_Nibble_Sent:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(LCD_PORT, LCD_RS, PIN_HIGH);
		DIO_WritePin(LCD_PORT, LCD_RW, PIN_LOW);
		/*copying lower nibble of the command to the pins*/
		DIO_WritePin(LCD_PORT, LCD_D7, READ_BIT(Character, 3));
		DIO_WritePin(LCD_PORT, LCD_D6, READ_BIT(Character, 2));
		DIO_WritePin(LCD_PORT, LCD_D5, READ_BIT(Character, 1));
		DIO_WritePin(LCD_PORT, LCD_D4, READ_BIT(Character, 0));

		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(LCD_PORT, LCD_EN, PIN_HIGH);
		/*set status of the function*/
		State = Sending_Second_Nibble;
		break;
	case Sending_Second_Nibble:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2, 3);//1
		if (TimerRetVal == ((uint8_t) TIMER_E_SUCCESS )) {
			/*if timer delay function finished correctly pull enable pin low*/
			DIO_WritePin(LCD_PORT, LCD_EN, PIN_LOW);
			/*set the function's state*/
			State = Second_Nibble_Sent;
		}
		break;
	case Second_Nibble_Sent:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2, 0);
		if (TimerRetVal == ((uint8_t) TIMER_E_SUCCESS )) {
			/*reset the function's state*/
			State = OperationStarted;
			/*process finished successfully*/
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		ErrRetVal = OperationFail;
	}
	/*return from function*/
	return ErrRetVal;

}
uint8_t LCD_Init()
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static State = OperationStarted;
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = 1;
	uint8_t LCD_SendCommandRetVal = OperationStarted;
	switch (State) {
	case OperationStarted:
		/*Dio Initialize for the*/
		DIO_SetPinDirection(LCD_PORT, LCD_D7, PIN_OUTPUT);
		DIO_SetPinDirection(LCD_PORT, LCD_D6, PIN_OUTPUT);
		DIO_SetPinDirection(LCD_PORT, LCD_D5, PIN_OUTPUT);
		DIO_SetPinDirection(LCD_PORT, LCD_D4, PIN_OUTPUT);
		DIO_SetPinDirection(LCD_PORT, LCD_RS, PIN_OUTPUT);
		DIO_SetPinDirection(LCD_PORT, LCD_RW, PIN_OUTPUT);
		DIO_SetPinDirection(LCD_PORT, LCD_EN, PIN_OUTPUT);
		/*setting initial value for LCD Pins*/
		DIO_WritePin(LCD_PORT, LCD_D7, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_D6, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_D5, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_D4, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_RS, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_RW, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_EN, PIN_LOW);
		/*set status of the function*/
		State = LCD_Pin_Initializing;
		break;
	case LCD_Pin_Initializing:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2, 45);
		if (TimerRetVal == ((uint8_t) TIMER_E_SUCCESS )) {
			/*if timer delay function finished correctly Start the initialization sequence*/
			State = LCD_Start_Sending_Initialization_Sequence;
		}
		break;
	case LCD_Start_Sending_Initialization_Sequence:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_Init_CMD_1);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = First_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case First_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_Init_CMD_1);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Second_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case Second_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_Init_CMD_1);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Third_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case Third_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_HOME);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Fourth_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case Fourth_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_FUNCSET_6);//LCD_FUNCSET_6//LCD_FUNCSET_2
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Fifth_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case Fifth_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_DISPON_CURSOFF);//LCD_DISPON_CURSOFF
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Sixth_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case Sixth_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_INCREMENTENTRYMODE);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Seventh_Cmd_In_Initialization_Sequence_Is_Sent;
		}
		break;
	case Seventh_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_CLR);//LCD_CLR
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = LCD_Sent_Initialization_Sequence;
		}
		break;
	case LCD_Sent_Initialization_Sequence:
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2, 3);
		if (TimerRetVal == ((uint8_t) TIMER_E_SUCCESS )) {
			/*if timer delay function finished correctly Start the initialization sequence*/
//			LCD_SendCommand(LCD_CURS_Position0);
			State = Final_Cmd_In_Initialization_Sequence_Is_Sent;
//			ErrRetVal = OperationSuccess;
		}
		break;
	case Final_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_CURS_Position0);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = OperationStarted;
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		ErrRetVal = OperationFail;
	}
	return ErrRetVal;
}
uint8_t LCD_SendString(ptr_int8_t String)
{
	uint8_t ErrRetVal = OperationStarted;
	uint8_t LCD_SendDataRetVal = OperationStarted;
	if (String != NULL_PTR) {
		while (*String != NULL_TERMINATOR ) {
			ErrRetVal = OperationRunning;
			LCD_SendDataRetVal = LCD_SendData(*String);
			if(LCD_SendDataRetVal == OperationSuccess)
				String++;
			else
				continue;
		}
		ErrRetVal = OperationSuccess;
	} else {
		ErrRetVal = OperationFail;
	}
	return ErrRetVal;
}
uint8_t LCD_SendNumber(uint32_t Number)
{
	uint8_t ErrRetVal = OperationStarted;
	uint8_t String[255];
	STR_Number2String((uint32_t)Number,String);
//	LCD_NumberToString(Number,String);
	LCD_SendString((int8_t*)String);
	ErrRetVal = OperationSuccess;
	return ErrRetVal;
}

void LCD_NumberToString(uint16_t Number, uint8_t* String)
{
	uint8_t NumberOfDigits = 0;
	uint8_t* StartOfString = String;
	if(Number==0)
	{
		NumberOfDigits=1;
	}
	else
	{
		while(Number)
		{
			*String=Number%10+48;
			String++;
			Number/=10;
		}
	}
	LCD_StringReverse(StartOfString);
}
void LCD_StringReverse(uint8_t* String)
{
	uint8_t* A = String;
	uint8_t* B = String;
	uint8_t Temp = 0;
	while(*B != '\0')
	{
		B++;
	}
	B--;
	while(A<B)
	{
		//swap
		Temp=*A;
		*A=*B;
		*B=Temp;
		A++;B--;
	}

}
#if 0
uint8_t LCD_ReadBusyFlag()
{
uint8_t ErrRetVal= OperationStarted;
uint8_t D7Reading=0;
uint8_t State = OperationStarted;
switch(State)
{
	case OperationStarted:
		DIO_SetPinDirection(LCD_PORT, LCD_D7, PIN_INPUT);
		DIO_WritePin(LCD_PORT, LCD_RS, PIN_LOW);
		DIO_WritePin(LCD_PORT, LCD_RW, PIN_HIGH);
		State = OperationRunning;
		break;
	case OperationRunning:
		DIO_ReadPin(LCD_PORT, LCD_D7, &D7Reading);
		if (D7Reading) {
			ErrRetVal = OperationFail;
		} else {
			State = OperationStarted;
			ErrRetVal = OperationSuccess;
			DIO_SetPinDirection(LCD_PORT, LCD_D7, PIN_OUTPUT);
		}
		break;
	}
	return ErrRetVal;
}
#endif