#define Test    1
#include "LCD.h"
/*Local Macros*/
/*functions states*/
#define Sending_First_Nibble										      (1)
#define First_Nibble_Sent											      (2)
#define Sending_Second_Nibble										      (3)
#define Second_Nibble_Sent											      (4)
#define LCD_Pin_Initializing										      (5)
#define LCD_Start_Sending_Initialization_Sequence					      (6)
#define LCD_Sent_Initialization_Sequence							      (7)
#define First_Cmd_In_Initialization_Sequence_Is_Sent			          (8)
#define Second_Cmd_In_Initialization_Sequence_Is_Sent				      (9)
#define Third_Cmd_In_Initialization_Sequence_Is_Sent				      (10)
#define Fourth_Cmd_In_Initialization_Sequence_Is_Sent					  (11)
#define Fifth_Cmd_In_Initialization_Sequence_Is_Sent					  (12)
#define Sixth_Cmd_In_Initialization_Sequence_Is_Sent			          (13)
#define Seventh_Cmd_In_Initialization_Sequence_Is_Sent			          (14)
#define Final_Cmd_In_Initialization_Sequence_Is_Sent				      (15)

/*Externed global variables*/
extern const STR_LCD_config_t gastr_LCD_Config[LCD_NUMBER];
extern uint8_t TimerRetVal_MOCK;
extern uint8_t LCD_FunctionState;
extern uint8_t LCD_FunctionLCD_InitStatesSequence[255];
uint8_t* LCD_Ptr = LCD_FunctionLCD_InitStatesSequence;
extern uint8_t LCD_FunctionLCD_SendStatesSequence[255];
uint8_t* LCD_Ptr1 = LCD_FunctionLCD_SendStatesSequence;
extern uint8_t LCD_FunctionLCD_SendDataStatesSequence[255];
uint8_t* LCD_Ptr2 = LCD_FunctionLCD_SendDataStatesSequence;

ERROR_STATE_t LCD_SendCommand(uint8_t CMD)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static State = OperationStarted;
	#if !Test
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = 1;
	#else
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = TimerRetVal_MOCK;
	#endif

	switch(State)
	{
	case OperationStarted:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rs, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rw, PIN_LOW);
		/*copying upper nibble of the command to the pins*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D4, READ_BIT(CMD, 4));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D5, READ_BIT(CMD, 5));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D6, READ_BIT(CMD, 6));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D7, READ_BIT(CMD, 7));
		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_HIGH);
		/*set status of the function*/
		State = Sending_First_Nibble;
		#if Test
        *LCD_Ptr1 = State;
        LCD_Ptr1 ++;
		#endif // Test
		break;
	case Sending_First_Nibble:
		/*start timer delay in background*/
		#if !Test
		TimerRetVal = TIM_DelayUs(TIMER_2,3);//1
		#endif
		if(TimerRetVal == ERROR_OK)
		{
			/*if timer delay function finished correctly pull enable pin low*/
			DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_LOW);
			/*update the function's state*/
			State = First_Nibble_Sent;
			#if Test
            *LCD_Ptr1 = State;
            LCD_Ptr1 ++;
            #endif // Test
		}
		break;
	case First_Nibble_Sent:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rs,PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rw,PIN_LOW);

		/*copying lower nibble of the command to the pins*/

		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_D4,READ_BIT(CMD,0));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_D5,READ_BIT(CMD,1));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_D6,READ_BIT(CMD,2));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_D7,READ_BIT(CMD,3));
		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_En,PIN_HIGH);
		/*set status of the function*/
		State = Sending_Second_Nibble;
		#if Test
        *LCD_Ptr1 = State;
        LCD_Ptr1 ++;
		#endif // Test
		break;
	case Sending_Second_Nibble:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2,3);//1
		#endif
		if(TimerRetVal == ((uint8_t)ERROR_OK))
		{
			/*if timer delay function finished correctly pull enable pin low*/
			DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port,gastr_LCD_Config[LCD_Channel_0].u8_LCD_En,PIN_LOW);
			/*reset the function's state*/
			State = Second_Nibble_Sent;
			#if Test
            *LCD_Ptr1 = State;
            LCD_Ptr1 ++;
            #endif // Test
		}
		break;
	case Second_Nibble_Sent:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2,5);//2
		#endif
		if(TimerRetVal == ((uint8_t)ERROR_OK))
		{
			/*reset the function's state*/
			State = OperationStarted;
			#if Test
            *LCD_Ptr1 = State;
            LCD_Ptr1++;
            #endif // Test
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
ERROR_STATE_t LCD_SendData(uint8_t Character)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static State = OperationStarted;
	#if !Test
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = 1;
	#else
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = TimerRetVal_MOCK;
	#endif
	switch (State) {
	case OperationStarted:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rs, PIN_HIGH);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rw, PIN_LOW);
		/*copying upper nibble of the command to the pins*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D7, READ_BIT(Character, 7));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D6, READ_BIT(Character, 6));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D5, READ_BIT(Character, 5));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D4, READ_BIT(Character, 4));

		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_HIGH);
		/*set status of the function*/
		State = Sending_First_Nibble;
		#if Test
        *LCD_Ptr2 = State;
        LCD_Ptr2 ++;
		#endif // Test
		break;
	case Sending_First_Nibble:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2, 3);//1
		#endif
		if (TimerRetVal == ERROR_OK) {
			DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_LOW);
			/*update the function's state*/
			State = First_Nibble_Sent;
		#if Test
        *LCD_Ptr2 = State;
        LCD_Ptr2 ++;
		#endif // Test
		}
		break;
	case First_Nibble_Sent:
		/*sending control signals with configurations of selection of control reg. and write process*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rs, PIN_HIGH);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rw, PIN_LOW);
		/*copying lower nibble of the command to the pins*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D7, READ_BIT(Character, 3));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D6, READ_BIT(Character, 2));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D5, READ_BIT(Character, 1));
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D4, READ_BIT(Character, 0));

		/*writing data to the register by pulling the enable pin high for 1 Us*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_HIGH);
		/*set status of the function*/
		State = Sending_Second_Nibble;
		#if Test
        *LCD_Ptr2 = State;
        LCD_Ptr2 ++;
		#endif // Test
		break;
	case Sending_Second_Nibble:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayUs(TIMER_2, 3);//1
		#endif
		if (TimerRetVal == ((uint8_t) ERROR_OK )) {
			/*if timer delay function finished correctly pull enable pin low*/
			DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_LOW);
			/*set the function's state*/
			State = Second_Nibble_Sent;
		#if Test
        *LCD_Ptr2 = State;
        LCD_Ptr2 ++;
		#endif // Test
		}
		break;
	case Second_Nibble_Sent:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2, 0);
		#endif
		if (TimerRetVal == ((uint8_t) ERROR_OK )) {
			/*reset the function's state*/
			State = OperationStarted;
		#if Test
        *LCD_Ptr2 = State;
        LCD_Ptr2 ++;
		#endif // Test
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
ERROR_STATE_t LCD_Init()
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static State = OperationStarted;
	#if !Test
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = 1;
	#else
	/*declaring a variable for the timer return*/
	uint8_t TimerRetVal = TimerRetVal_MOCK;
	#endif
	uint8_t LCD_SendCommandRetVal = OperationStarted;
	switch (State) {
	case OperationStarted:
		/*Dio Initialize for the*/
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D7, PIN_OUTPUT);
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D6, PIN_OUTPUT);
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D5, PIN_OUTPUT);
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D4, PIN_OUTPUT);
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rs, PIN_OUTPUT);
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rw, PIN_OUTPUT);
		DIO_SetPinDirection(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_OUTPUT);
		/*setting initial value for LCD Pins*/
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D7, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D6, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D5, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_D4, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rs, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_Rw, PIN_LOW);
		DIO_WritePin(gastr_LCD_Config[LCD_Channel_0].u8_LCD_Port, gastr_LCD_Config[LCD_Channel_0].u8_LCD_En, PIN_LOW);
		/*set status of the function*/
		State = LCD_Pin_Initializing;
		#if Test
        *LCD_Ptr = State;
        LCD_Ptr ++;
		#endif // Test
		break;
	case LCD_Pin_Initializing:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2, 45);
		#endif
		if (TimerRetVal == ((uint8_t) ERROR_OK )) {
			/*if timer delay function finished correctly Start the initialization sequence*/
			State = LCD_Start_Sending_Initialization_Sequence;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case LCD_Start_Sending_Initialization_Sequence:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_Init_CMD_1);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = First_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case First_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_Init_CMD_1);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Second_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Second_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_Init_CMD_1);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Third_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Third_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_HOME);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Fourth_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Fourth_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_FUNCSET_6);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Fifth_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Fifth_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_DISPON_CURSOFF);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Sixth_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Sixth_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_INCREMENTENTRYMODE);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = Seventh_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Seventh_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_CLR);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = LCD_Sent_Initialization_Sequence;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case LCD_Sent_Initialization_Sequence:
	    #if !Test
		/*start timer delay in background*/
		TimerRetVal = TIM_DelayMs(TIMER_2, 3);
		#endif
		if (TimerRetVal == ((uint8_t) ERROR_OK )) {
			/*if timer delay function finished correctly Start the initialization sequence*/
			State = Final_Cmd_In_Initialization_Sequence_Is_Sent;
			#if Test
            *LCD_Ptr = State;
            LCD_Ptr ++;
            #endif // Test
		}
		break;
	case Final_Cmd_In_Initialization_Sequence_Is_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(LCD_CURS_Position0);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			State = OperationStarted;
			#if Test
            *LCD_Ptr = State;
//            LCD_Ptr=LCD_FunctionStatesSequence;
            #endif // Test
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		ErrRetVal = OperationFail;
	}
	return ErrRetVal;
}
ERROR_STATE_t LCD_SendString(ptr_int8_t String)
{
	uint8_t ErrRetVal = OperationStarted;
	uint8_t LCD_SendDataRetVal = OperationStarted;
	if (String != NULL_PTR) {
		while (*String != NULL_TERMINATOR ) {
			ErrRetVal = OperationRunning;
			LCD_SendDataRetVal = LCD_SendData(*String);
			if(LCD_SendDataRetVal == OperationSuccess)
            {
                #if Test
                printf("character=%c\n",*String);
                #endif // Test
				String++;

            }
            else
				continue;
		}
		ErrRetVal = OperationSuccess;
	} else {
		ErrRetVal = OperationFail;
	}
	return ErrRetVal;
}
ERROR_STATE_t LCD_SendNumber(uint32_t Number)
{
	uint8_t ErrRetVal = OperationStarted;
	uint8_t String[255];
	STR_Number2String((uint32_t)Number,String);
	printf("The Number is %s\n",String);
	ErrRetVal = OperationSuccess;
	return ErrRetVal;
}
