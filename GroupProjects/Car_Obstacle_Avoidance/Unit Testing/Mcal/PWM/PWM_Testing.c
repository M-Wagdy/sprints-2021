#include "Unit_Testing_Tool/UNIT_TESTING_TOOL.h"
#include "MC_REGISTERS.h"
#include "PWM.h"

#define INVALID_PWM_CH1 5
#define INVALID_PWM_CH2 -5

extern Str_PWMConfig_t gastr_PWMConfig[PWM_CHANNEL_NUMBERS];

/***************************************PWM_Init API Testng********************************/
TEST_GROUP(PWM_Init);

TEST_SETUP(PWM_Init)
{
	TCCR0=0b00000000;
	TCCR1A=0b00000000;
	TCCR1B=0b00000000;
	TCCR2=0b00000000;
}

TEST_TEAR_DOWN(PWM_Init)
{

}

TEST(PWM_Init, INVALID_PWM_CH1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Init(INVALID_PWM_CH1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Init, INVALID_PWM_CH2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Init(INVALID_PWM_CH2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Init, PWM_CHANNEL_OC0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Init(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Init, PWM_CHANNEL_OC1A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Init(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Init, PWM_CHANNEL_OC1B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Init(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Init, PWM_CHANNEL_OC2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Init(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Init, RegisterUpdate_CH0)
{
	uint8_t Expected = 0b00000000;
	BIT_WRITE(Expected,BIT6,BIT_GET(gastr_PWMConfig[PWM_CHANNEL_OC0].PWMMode,BIT0));
	BIT_WRITE(Expected,BIT3,BIT_GET(gastr_PWMConfig[PWM_CHANNEL_OC0].PWMMode,BIT1));
	TWO_BITS_WRITE(Expected,BIT4,gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode);
	PWM_Init(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR0));
}

TEST(PWM_Init, RegisterUpdate_TCCR1A_CH1A)
{
	uint8_t Expected = 0b00000000;
	TWO_BITS_WRITE(Expected,BIT0,TWO_BITS_GET(gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMMode,BIT0));
	TWO_BITS_WRITE(Expected,BIT6,gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode);
	PWM_Init(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1A));
}

TEST(PWM_Init, RegisterUpdate_TCCR1B_CH1A)
{
	uint8_t Expected = 0b00000000;
	TWO_BITS_WRITE(Expected,BIT3,TWO_BITS_GET(gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMMode,BIT2));
	PWM_Init(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1B));
}

TEST(PWM_Init, RegisterUpdate_TCCR1A_CH1B)
{
	uint8_t Expected = 0b00000000;
	TWO_BITS_WRITE(Expected,BIT0,TWO_BITS_GET(gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMMode,BIT0));
	TWO_BITS_WRITE(Expected,BIT4,gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode);
	PWM_Init(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1A));
}

TEST(PWM_Init, RegisterUpdate_TCCR1B_CH1B)
{
	uint8_t Expected = 0b00000000;
	TWO_BITS_WRITE(Expected,BIT3,TWO_BITS_GET(gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMMode,BIT2));
	PWM_Init(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1B));
}

TEST(PWM_Init, RegisterUpdate_CH2)
{
	uint8_t Expected = 0b00000000;
	BIT_WRITE(Expected,BIT6,BIT_GET(gastr_PWMConfig[PWM_CHANNEL_OC2].PWMMode,BIT0));
	BIT_WRITE(Expected,BIT3,BIT_GET(gastr_PWMConfig[PWM_CHANNEL_OC2].PWMMode,BIT1));
	TWO_BITS_WRITE(Expected,BIT4,gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode);
	PWM_Init(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR2));
}

TEST_GROUP_RUNNER(PWM_Init)
{
	RUN_TEST_CASE(PWM_Init, INVALID_PWM_CH1);
	RUN_TEST_CASE(PWM_Init, INVALID_PWM_CH2);
	RUN_TEST_CASE(PWM_Init, PWM_CHANNEL_OC0);
	RUN_TEST_CASE(PWM_Init, PWM_CHANNEL_OC1A);
	RUN_TEST_CASE(PWM_Init, PWM_CHANNEL_OC1B);
	RUN_TEST_CASE(PWM_Init, PWM_CHANNEL_OC2);

	RUN_TEST_CASE(PWM_Init, RegisterUpdate_CH0);
	RUN_TEST_CASE(PWM_Init, RegisterUpdate_TCCR1A_CH1A);
	RUN_TEST_CASE(PWM_Init, RegisterUpdate_TCCR1B_CH1A);
	RUN_TEST_CASE(PWM_Init, RegisterUpdate_TCCR1A_CH1B);
	RUN_TEST_CASE(PWM_Init, RegisterUpdate_TCCR1B_CH1B);
	RUN_TEST_CASE(PWM_Init, RegisterUpdate_CH2);
}
/*****************************************************************************************************/

/***************************************PWM_Start API Testng********************************/
TEST_GROUP(PWM_Start);

TEST_SETUP(PWM_Start)
{
	TCCR0=0b00000000;
	TCCR1B=0b00000000;
	TCCR2=0b00000000;
}

TEST_TEAR_DOWN(PWM_Start)
{

}

TEST(PWM_Start, INVALID_PWM_CH1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Start(INVALID_PWM_CH1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Start, INVALID_PWM_CH2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Start(INVALID_PWM_CH2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Start, PWM_CHANNEL_OC0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Start(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Start, PWM_CHANNEL_OC1A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Start(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Start, PWM_CHANNEL_OC1B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Start(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Start, PWM_CHANNEL_OC2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Start(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Start, RegisterUpdate_CH0)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,gastr_PWMConfig[PWM_CHANNEL_OC0].PWMFrequancy);	
	PWM_Start(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR0));
}

TEST(PWM_Start, RegisterUpdate_CH1A)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMFrequancy);	
	PWM_Start(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1B));
}

TEST(PWM_Start, RegisterUpdate_CH1B)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMFrequancy);	
	PWM_Start(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1B));
}

TEST(PWM_Start, RegisterUpdate_CH2)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,gastr_PWMConfig[PWM_CHANNEL_OC2].PWMFrequancy);	
	PWM_Start(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR2));
}

TEST_GROUP_RUNNER(PWM_Start)
{
	RUN_TEST_CASE(PWM_Start, INVALID_PWM_CH1);
	RUN_TEST_CASE(PWM_Start, INVALID_PWM_CH2);
	RUN_TEST_CASE(PWM_Start, PWM_CHANNEL_OC0);
	RUN_TEST_CASE(PWM_Start, PWM_CHANNEL_OC1A);
	RUN_TEST_CASE(PWM_Start, PWM_CHANNEL_OC1B);
	RUN_TEST_CASE(PWM_Start, PWM_CHANNEL_OC2);
	
	RUN_TEST_CASE(PWM_Start, RegisterUpdate_CH0);
	RUN_TEST_CASE(PWM_Start, RegisterUpdate_CH1A);
	RUN_TEST_CASE(PWM_Start, RegisterUpdate_CH1B);
	RUN_TEST_CASE(PWM_Start, RegisterUpdate_CH2);	
}
/*****************************************************************************************************/

/***************************************PWM_Stop API Testng********************************/
TEST_GROUP(PWM_Stop);

TEST_SETUP(PWM_Stop)
{
	TCCR0=0b00000000;
	TCCR1B=0b00000000;
	TCCR2=0b00000000;
}

TEST_TEAR_DOWN(PWM_Stop)
{

}

TEST(PWM_Stop, INVALID_PWM_CH1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Stop(INVALID_PWM_CH1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Stop, INVALID_PWM_CH2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Stop(INVALID_PWM_CH2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Stop, PWM_CHANNEL_OC0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Stop(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Stop, PWM_CHANNEL_OC1A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Stop(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Stop, PWM_CHANNEL_OC1B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Stop(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Stop, PWM_CHANNEL_OC2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Stop(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Stop, RegisterUpdate_CH0)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,OC0_NO_CLK);	
	PWM_Stop(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR0));
}

TEST(PWM_Stop, RegisterUpdate_CH1A)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,OC0_NO_CLK);	
	PWM_Stop(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1B));
}

TEST(PWM_Stop, RegisterUpdate_CH1B)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,OC0_NO_CLK);	
	PWM_Stop(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1B));
}

TEST(PWM_Stop, RegisterUpdate_CH2)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT0,OC0_NO_CLK);	
	PWM_Stop(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR2));
}

TEST_GROUP_RUNNER(PWM_Stop)
{
	RUN_TEST_CASE(PWM_Stop, INVALID_PWM_CH1);
	RUN_TEST_CASE(PWM_Stop, INVALID_PWM_CH2);
	RUN_TEST_CASE(PWM_Stop, PWM_CHANNEL_OC0);
	RUN_TEST_CASE(PWM_Stop, PWM_CHANNEL_OC1A);
	RUN_TEST_CASE(PWM_Stop, PWM_CHANNEL_OC1B);
	RUN_TEST_CASE(PWM_Stop, PWM_CHANNEL_OC2);
	
	RUN_TEST_CASE(PWM_Stop, RegisterUpdate_CH0);
	RUN_TEST_CASE(PWM_Stop, RegisterUpdate_CH1A);
	RUN_TEST_CASE(PWM_Stop, RegisterUpdate_CH1B);
	RUN_TEST_CASE(PWM_Stop, RegisterUpdate_CH2);
}
/*****************************************************************************************************/

/***************************************PWM_Connect API Testng********************************/
TEST_GROUP(PWM_Connect);

TEST_SETUP(PWM_Connect)
{
	TCCR0=0b00000000;
	TCCR1A=0b00000000;
	TCCR2=0b00000000;
}

TEST_TEAR_DOWN(PWM_Connect)
{

}

TEST(PWM_Connect, INVALID_PWM_CH1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Connect(INVALID_PWM_CH1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Connect, INVALID_PWM_CH2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Connect(INVALID_PWM_CH2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Connect, PWM_CHANNEL_OC0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Connect(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Connect, PWM_CHANNEL_OC1A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Connect(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Connect, PWM_CHANNEL_OC1B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Connect(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Connect, PWM_CHANNEL_OC2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Connect(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Connect, RegisterUpdate_CH0)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT4,gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode);	
	PWM_Connect(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR0));
}

TEST(PWM_Connect, RegisterUpdate_CH1A)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT6,gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode);	
	PWM_Connect(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1A));
}

TEST(PWM_Connect, RegisterUpdate_CH1B)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT4,gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode);	
	PWM_Connect(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1A));
}

TEST(PWM_Connect, RegisterUpdate_CH2)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT4,gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode);	
	PWM_Connect(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR2));
}

TEST_GROUP_RUNNER(PWM_Connect)
{
	RUN_TEST_CASE(PWM_Connect, INVALID_PWM_CH1);
	RUN_TEST_CASE(PWM_Connect, INVALID_PWM_CH2);
	RUN_TEST_CASE(PWM_Connect, PWM_CHANNEL_OC0);
	RUN_TEST_CASE(PWM_Connect, PWM_CHANNEL_OC1A);
	RUN_TEST_CASE(PWM_Connect, PWM_CHANNEL_OC1B);
	RUN_TEST_CASE(PWM_Connect, PWM_CHANNEL_OC2);

	RUN_TEST_CASE(PWM_Connect, RegisterUpdate_CH0);
	RUN_TEST_CASE(PWM_Connect, RegisterUpdate_CH1A);
	RUN_TEST_CASE(PWM_Connect, RegisterUpdate_CH1B);
	RUN_TEST_CASE(PWM_Connect, RegisterUpdate_CH2);	

}
/*****************************************************************************************************/

/***************************************PWM_Disconnect API Testng********************************/
TEST_GROUP(PWM_Disconnect);

TEST_SETUP(PWM_Disconnect)
{
	TCCR0=0b00000000;
	TCCR1A=0b00000000;
	TCCR2=0b00000000;
}

TEST_TEAR_DOWN(PWM_Disconnect)
{

}

TEST(PWM_Disconnect, INVALID_PWM_CH1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Disconnect(INVALID_PWM_CH1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Disconnect, INVALID_PWM_CH2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Disconnect(INVALID_PWM_CH2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_Disconnect, PWM_CHANNEL_OC0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Disconnect(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Disconnect, PWM_CHANNEL_OC1A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Disconnect(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Disconnect, PWM_CHANNEL_OC1B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Disconnect(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Disconnect, PWM_CHANNEL_OC2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_Disconnect(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_Disconnect, RegisterUpdate_CH0)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT4,DISCONNECT);	
	PWM_Disconnect(PWM_CHANNEL_OC0);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR0));
}

TEST(PWM_Disconnect, RegisterUpdate_CH1A)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT6,DISCONNECT);	
	PWM_Disconnect(PWM_CHANNEL_OC1A);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1A));
}

TEST(PWM_Disconnect, RegisterUpdate_CH1B)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT4,DISCONNECT);	
	PWM_Disconnect(PWM_CHANNEL_OC1B);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR1A));
}

TEST(PWM_Disconnect, RegisterUpdate_CH2)
{
	uint8_t Expected = 0b00000000;
	THREE_BITS_WRITE(Expected,BIT4,DISCONNECT);	
	PWM_Disconnect(PWM_CHANNEL_OC2);
	TEST_ASSERT_EQUAL_INT((Expected),(TCCR2));
}

TEST_GROUP_RUNNER(PWM_Disconnect)
{
	RUN_TEST_CASE(PWM_Disconnect, INVALID_PWM_CH1);
	RUN_TEST_CASE(PWM_Disconnect, INVALID_PWM_CH2);
	RUN_TEST_CASE(PWM_Disconnect, PWM_CHANNEL_OC0);
	RUN_TEST_CASE(PWM_Disconnect, PWM_CHANNEL_OC1A);
	RUN_TEST_CASE(PWM_Disconnect, PWM_CHANNEL_OC1B);
	RUN_TEST_CASE(PWM_Disconnect, PWM_CHANNEL_OC2);
	
	RUN_TEST_CASE(PWM_Disconnect, RegisterUpdate_CH0);
	RUN_TEST_CASE(PWM_Disconnect, RegisterUpdate_CH1A);
	RUN_TEST_CASE(PWM_Disconnect, RegisterUpdate_CH1B);
	RUN_TEST_CASE(PWM_Disconnect, RegisterUpdate_CH2);		
}
/*****************************************************************************************************/

/***************************************PWM_SetDuty API Testng********************************/
#define INVALID_DUTY1 0
#define INVALID_DUTY2 150
#define VALID_DUTY1 1
#define VALID_DUTY2 100
#define VALID_DUTY3 50
#define INVALID_PWM_WAVEFORM_MODE DISCONNECT

TEST_GROUP(PWM_SetDuty);

TEST_SETUP(PWM_SetDuty)
{
	OCR0=0x0000;
	OCR1A=0x0000;
	OCR1B=0x0000;
	OCR2=0x0000;
}

TEST_TEAR_DOWN(PWM_SetDuty)
{

}

TEST(PWM_SetDuty, INVALID_PWM_CH1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(INVALID_PWM_CH1,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_SetDuty, INVALID_PWM_CH2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(INVALID_PWM_CH2,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_SetDuty, PWM_CHANNEL_OC0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC0,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, PWM_CHANNEL_OC1A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1A,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, PWM_CHANNEL_OC1B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1B,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, PWM_CHANNEL_OC2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC2,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, INVALID_DUTY1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1A,INVALID_DUTY1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_SetDuty, INVALID_DUTY2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC0,INVALID_DUTY2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(PWM_SetDuty, VALID_DUTY1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1A,VALID_DUTY1);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, VALID_DUTY2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1B,VALID_DUTY2);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, VALID_DUTY3)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC2,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_OK);
}

TEST(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH0)
{
	uint8_t u8_ErrorState;
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode=INVALID_PWM_WAVEFORM_MODE;
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC0,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
	gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH1A)
{
	uint8_t u8_ErrorState;
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode=INVALID_PWM_WAVEFORM_MODE;	
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1A,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
	gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH1B)
{
	uint8_t u8_ErrorState;
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode=INVALID_PWM_WAVEFORM_MODE;	
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC1B,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
	gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH2)
{
	uint8_t u8_ErrorState;
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode=INVALID_PWM_WAVEFORM_MODE;	
	u8_ErrorState = PWM_SetDuty(PWM_CHANNEL_OC2,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
	gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, RegisterUpdate_CH0)
{
	uint8_t Expected = (uint8_t)(((VALID_DUTY3/100.0)*256.0)-1);
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode=NON_INVERTING;		
	PWM_SetDuty(PWM_CHANNEL_OC0,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT((Expected),(OCR0));
	gastr_PWMConfig[PWM_CHANNEL_OC0].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, RegisterUpdate_CH1A)
{
	uint16_t Expected = (uint16_t)(((VALID_DUTY3/100.0)*256.0)-1);
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode=NON_INVERTING;		
	PWM_SetDuty(PWM_CHANNEL_OC1A,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT((Expected),(OCR1A));
	gastr_PWMConfig[PWM_CHANNEL_OC1A].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, RegisterUpdate_CH1B)
{
	uint16_t Expected = (uint16_t)(((VALID_DUTY3/100.0)*256.0)-1);
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode=NON_INVERTING;			
	PWM_SetDuty(PWM_CHANNEL_OC1B,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT((Expected),(OCR1B));
	gastr_PWMConfig[PWM_CHANNEL_OC1B].PWMWaveformMode=Temp;
}

TEST(PWM_SetDuty, RegisterUpdate_CH2)
{
	uint8_t Expected = (uint8_t)(((VALID_DUTY3/100.0)*256.0)-1);
	uint8_t Temp = gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode;
	gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode=NON_INVERTING;		
	PWM_SetDuty(PWM_CHANNEL_OC2,VALID_DUTY3);
	TEST_ASSERT_EQUAL_INT((Expected),(OCR2));
	gastr_PWMConfig[PWM_CHANNEL_OC2].PWMWaveformMode=Temp;
}

TEST_GROUP_RUNNER(PWM_SetDuty)
{
	RUN_TEST_CASE(PWM_SetDuty, INVALID_PWM_CH1);
	RUN_TEST_CASE(PWM_SetDuty, INVALID_PWM_CH2);
	RUN_TEST_CASE(PWM_SetDuty, PWM_CHANNEL_OC0);
	RUN_TEST_CASE(PWM_SetDuty, PWM_CHANNEL_OC1A);
	RUN_TEST_CASE(PWM_SetDuty, PWM_CHANNEL_OC1B);
	RUN_TEST_CASE(PWM_SetDuty, PWM_CHANNEL_OC2);
	
	RUN_TEST_CASE(PWM_SetDuty, INVALID_DUTY1);
	RUN_TEST_CASE(PWM_SetDuty, INVALID_DUTY2);
	RUN_TEST_CASE(PWM_SetDuty, VALID_DUTY1);
	RUN_TEST_CASE(PWM_SetDuty, VALID_DUTY2);
	RUN_TEST_CASE(PWM_SetDuty, VALID_DUTY3);
	
	RUN_TEST_CASE(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH0);
	RUN_TEST_CASE(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH1A);
	RUN_TEST_CASE(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH1B);
	RUN_TEST_CASE(PWM_SetDuty, INVALID_PWM_WAVEFORM_MODE_CH2);	

	RUN_TEST_CASE(PWM_SetDuty, RegisterUpdate_CH0);
	RUN_TEST_CASE(PWM_SetDuty, RegisterUpdate_CH1A);
	RUN_TEST_CASE(PWM_SetDuty, RegisterUpdate_CH1B);
	RUN_TEST_CASE(PWM_SetDuty, RegisterUpdate_CH2);	
}
/*****************************************************************************************************/