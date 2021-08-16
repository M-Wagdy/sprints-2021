#include "Unit_Testing_Tool/UNIT_TESTING_TOOL.h"
#include "MC_REGISTERS.h"
#include "DIO.h"


#define INVALID_PORD1 -5
#define INVALID_PORD2 10
#define INVALID_PIN1 -4
#define INVALID_PIN2 15

/***************************************DIO_SetPinDirection API Testng********************************/
#define INVALID_DIRECTION 5

TEST_GROUP(DIO_SetPinDirection);

TEST_SETUP(DIO_SetPinDirection)
{
	DDRA=0b00000000;
	DDRB=0b00000000;
	DDRC=0b00000000;
	DDRD=0b00000000;
}

TEST_TEAR_DOWN(DIO_SetPinDirection)
{

}

TEST(DIO_SetPinDirection, INVALID_PORD1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(INVALID_PORD1,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_SetPinDirection, INVALID_PORD2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(INVALID_PORD2,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_SetPinDirection, PORT_A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_A,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, PORT_B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_B,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, PORT_C)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_C,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, PORT_D)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, INVALID_PIN1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,INVALID_PIN1,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_SetPinDirection, INVALID_PIN2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,INVALID_PIN2,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_SetPinDirection, PIN0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN0,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, PIN7)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN7,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, PIN5)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN5,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, INVALID_DIRECTION)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN0,INVALID_DIRECTION);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_SetPinDirection, PIN_INPUT)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN7,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, PIN_OUTPUT)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_SetPinDirection(PORT_D,PIN5,PIN_OUTPUT);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_SetPinDirection, SettingOneBit)
{
	uint8_t Expected = 0b00001000;
	DIO_SetPinDirection(PORT_A,PIN3,PIN_OUTPUT);
	TEST_ASSERT_EQUAL_INT((Expected),(DDRA));
}

TEST(DIO_SetPinDirection, SettingTwoBits)
{
	uint8_t Expected = 0b00010010;
	DIO_SetPinDirection(PORT_A,PIN1,PIN_OUTPUT);
	DIO_SetPinDirection(PORT_A,PIN4,PIN_OUTPUT);
	TEST_ASSERT_EQUAL_INT((Expected),(DDRA));
}

TEST(DIO_SetPinDirection, SettingClearingBit)
{
	uint8_t Expected = 0b00000000;
	DIO_SetPinDirection(PORT_A,PIN1,PIN_OUTPUT);
	DIO_SetPinDirection(PORT_A,PIN1,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((Expected),(DDRA));
}

TEST_GROUP_RUNNER(DIO_SetPinDirection)
{
	RUN_TEST_CASE(DIO_SetPinDirection, INVALID_PORD1);
	RUN_TEST_CASE(DIO_SetPinDirection, INVALID_PORD2);
	RUN_TEST_CASE(DIO_SetPinDirection, PORT_A);
	RUN_TEST_CASE(DIO_SetPinDirection, PORT_B);
	RUN_TEST_CASE(DIO_SetPinDirection, PORT_C);
	RUN_TEST_CASE(DIO_SetPinDirection, PORT_D);
	
	RUN_TEST_CASE(DIO_SetPinDirection, INVALID_PIN1);
	RUN_TEST_CASE(DIO_SetPinDirection, INVALID_PIN2);
	RUN_TEST_CASE(DIO_SetPinDirection, PIN0);
	RUN_TEST_CASE(DIO_SetPinDirection, PIN7);
	RUN_TEST_CASE(DIO_SetPinDirection, PIN5);
	
	RUN_TEST_CASE(DIO_SetPinDirection, INVALID_DIRECTION);
	RUN_TEST_CASE(DIO_SetPinDirection, PIN_INPUT);
	RUN_TEST_CASE(DIO_SetPinDirection, PIN_OUTPUT);	
	
	RUN_TEST_CASE(DIO_SetPinDirection, SettingOneBit);
	RUN_TEST_CASE(DIO_SetPinDirection, SettingTwoBits);
	RUN_TEST_CASE(DIO_SetPinDirection, SettingClearingBit);
}
/*****************************************************************************************************/

/***************************************DIO_WritePin API Testng********************************/
#define INVALID_PIN_VALUE 5

TEST_GROUP(DIO_WritePin);

TEST_SETUP(DIO_WritePin)
{
	PORTA=0b00000000;
	PORTB=0b00000000;
	PORTC=0b00000000;
	PORTD=0b00000000;
}

TEST_TEAR_DOWN(DIO_WritePin)
{

}

TEST(DIO_WritePin, INVALID_PORD1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(INVALID_PORD1,PIN0,PIN_LOW);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_WritePin, INVALID_PORD2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(INVALID_PORD2,PIN0,PIN_LOW);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_WritePin, PORT_A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_A,PIN0,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, PORT_B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_B,PIN0,PIN_HIGH);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, PORT_C)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_C,PIN0,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, PORT_D)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN0,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, INVALID_PIN1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,INVALID_PIN1,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_WritePin, INVALID_PIN2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,INVALID_PIN2,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_WritePin, PIN0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN0,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, PIN7)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN7,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, PIN5)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN5,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, INVALID_PIN_VALUE)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN0,INVALID_PIN_VALUE);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_WritePin, PIN_LOW)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN7,PIN_LOW);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, PIN_HIGH)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_WritePin(PORT_D,PIN5,PIN_HIGH);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_WritePin, SettingOneBit)
{
	uint8_t Expected = 0b00001000;
	DIO_WritePin(PORT_A,PIN3,PIN_HIGH);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTA));
}

TEST(DIO_WritePin, SettingTwoBits)
{
	uint8_t Expected = 0b00010010;
	DIO_WritePin(PORT_A,PIN1,PIN_HIGH);
	DIO_WritePin(PORT_A,PIN4,PIN_HIGH);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTA));
}

TEST(DIO_WritePin, SettingClearingBit)
{
	uint8_t Expected = 0b00000000;
	DIO_WritePin(PORT_A,PIN1,PIN_OUTPUT);
	DIO_WritePin(PORT_A,PIN1,PIN_INPUT);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTA));
}

TEST_GROUP_RUNNER(DIO_WritePin)
{
	RUN_TEST_CASE(DIO_WritePin, INVALID_PORD1);
	RUN_TEST_CASE(DIO_WritePin, INVALID_PORD2);
	RUN_TEST_CASE(DIO_WritePin, PORT_A);
	RUN_TEST_CASE(DIO_WritePin, PORT_B);
	RUN_TEST_CASE(DIO_WritePin, PORT_C);
	RUN_TEST_CASE(DIO_WritePin, PORT_D);
	
	RUN_TEST_CASE(DIO_WritePin, INVALID_PIN1);
	RUN_TEST_CASE(DIO_WritePin, INVALID_PIN2);
	RUN_TEST_CASE(DIO_WritePin, PIN0);
	RUN_TEST_CASE(DIO_WritePin, PIN7);
	RUN_TEST_CASE(DIO_WritePin, PIN5);
	
	RUN_TEST_CASE(DIO_WritePin, INVALID_PIN_VALUE);
	RUN_TEST_CASE(DIO_WritePin, PIN_LOW);
	RUN_TEST_CASE(DIO_WritePin, PIN_HIGH);	
	
	RUN_TEST_CASE(DIO_WritePin, SettingOneBit);
	RUN_TEST_CASE(DIO_WritePin, SettingTwoBits);
	RUN_TEST_CASE(DIO_WritePin, SettingClearingBit);	
}
/*****************************************************************************************************/

/***************************************DIO_TogglePin API Testng********************************/
TEST_GROUP(DIO_TogglePin);

TEST_SETUP(DIO_TogglePin)
{
	PORTA=0b00000000;
	PORTB=0b00000000;
	PORTC=0b00000000;
	PORTD=0b00000000;
}

TEST_TEAR_DOWN(DIO_TogglePin)
{

}

TEST(DIO_TogglePin, INVALID_PORD1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(INVALID_PORD1,PIN0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_TogglePin, INVALID_PORD2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(INVALID_PORD2,PIN0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_TogglePin, PORT_A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_A,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, PORT_B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_B,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, PORT_C)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_C,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, PORT_D)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_D,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, INVALID_PIN1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_D,INVALID_PIN1);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_TogglePin, INVALID_PIN2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_D,INVALID_PIN2);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_TogglePin, PIN0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_D,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, PIN7)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_D,PIN7);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, PIN5)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_TogglePin(PORT_D,PIN5);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_TogglePin, TogglingFrom0To1)
{
	uint8_t Expected = 0b10000000;
	DIO_TogglePin(PORT_C,PIN7);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTC));
}

TEST(DIO_TogglePin, TogglingFrom1To0)
{
	uint8_t Expected = 0b01000000;
	DIO_TogglePin(PORT_C,PIN5);
	DIO_TogglePin(PORT_C,PIN6);
	DIO_TogglePin(PORT_C,PIN5);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTC));
}

TEST(DIO_TogglePin, TogglingMultipleBits)
{
	uint8_t Expected = 0b01000100;
	DIO_TogglePin(PORT_C,PIN2);
	DIO_TogglePin(PORT_C,PIN6);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTC));
}

TEST_GROUP_RUNNER(DIO_TogglePin)
{
	RUN_TEST_CASE(DIO_TogglePin, INVALID_PORD1);
	RUN_TEST_CASE(DIO_TogglePin, INVALID_PORD2);
	RUN_TEST_CASE(DIO_TogglePin, PORT_A);
	RUN_TEST_CASE(DIO_TogglePin, PORT_B);
	RUN_TEST_CASE(DIO_TogglePin, PORT_C);
	RUN_TEST_CASE(DIO_TogglePin, PORT_D);
	
	RUN_TEST_CASE(DIO_TogglePin, INVALID_PIN1);
	RUN_TEST_CASE(DIO_TogglePin, INVALID_PIN2);
	RUN_TEST_CASE(DIO_TogglePin, PIN0);
	RUN_TEST_CASE(DIO_TogglePin, PIN7);
	RUN_TEST_CASE(DIO_TogglePin, PIN5);
	
	RUN_TEST_CASE(DIO_TogglePin, TogglingFrom0To1);
	RUN_TEST_CASE(DIO_TogglePin, TogglingFrom1To0);
	RUN_TEST_CASE(DIO_TogglePin, TogglingMultipleBits);
}
/*****************************************************************************************************/

/***************************************DIO_ReadPin API Testng********************************/
TEST_GROUP(DIO_ReadPin);

TEST_SETUP(DIO_ReadPin)
{
	PINA=0b00000000;
	PINB=0b00000000;
	PINC=0b00000000;
	PIND=0b00000000;
}

TEST_TEAR_DOWN(DIO_ReadPin)
{

}

TEST(DIO_ReadPin, INVALID_PORD1)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(INVALID_PORD1,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_ReadPin, INVALID_PORD2)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(INVALID_PORD2,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_ReadPin, PORT_A)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_A,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, PORT_B)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_B,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, PORT_C)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_C,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, PORT_D)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, INVALID_PIN1)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,INVALID_PIN1,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_ReadPin, INVALID_PIN2)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,INVALID_PIN2,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_ReadPin, PIN0)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,PIN0,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, PIN7)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,PIN7,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, PIN5)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,PIN5,&PinData);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_ReadPin, INVALID_POINTER)
{
	uint8_t u8_ErrorState;
	uint8_t PinData;
	u8_ErrorState = DIO_ReadPin(PORT_D,PIN5,NULL_PTR);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_ReadPin, ReadingOneBit)
{
	PINB = 0b00100000;
	uint8_t Expected = PINB>>PIN5;
	uint8_t PinData;
	DIO_ReadPin(PORT_B,PIN5,&PinData);
	TEST_ASSERT_EQUAL_INT((Expected),(PinData));
}

TEST_GROUP_RUNNER(DIO_ReadPin)
{
	RUN_TEST_CASE(DIO_ReadPin, INVALID_PORD1);
	RUN_TEST_CASE(DIO_ReadPin, INVALID_PORD2);
	RUN_TEST_CASE(DIO_ReadPin, PORT_A);
	RUN_TEST_CASE(DIO_ReadPin, PORT_B);
	RUN_TEST_CASE(DIO_ReadPin, PORT_C);
	RUN_TEST_CASE(DIO_ReadPin, PORT_D);
	
	RUN_TEST_CASE(DIO_ReadPin, INVALID_PIN1);
	RUN_TEST_CASE(DIO_ReadPin, INVALID_PIN2);
	RUN_TEST_CASE(DIO_ReadPin, PIN0);
	RUN_TEST_CASE(DIO_ReadPin, PIN7);
	RUN_TEST_CASE(DIO_ReadPin, PIN5);

	RUN_TEST_CASE(DIO_ReadPin, INVALID_POINTER);

	RUN_TEST_CASE(DIO_ReadPin, ReadingOneBit);	
}
/*****************************************************************************************************/

/***************************************DIO_EnablePinPullup API Testng********************************/
TEST_GROUP(DIO_EnablePinPullup);

TEST_SETUP(DIO_EnablePinPullup)
{
	PORTA=0b00000000;
	PORTB=0b00000000;
	PORTC=0b00000000;
	PORTD=0b00000000;
}

TEST_TEAR_DOWN(DIO_EnablePinPullup)
{

}

TEST(DIO_EnablePinPullup, INVALID_PORD1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(INVALID_PORD1,PIN0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_EnablePinPullup, INVALID_PORD2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(INVALID_PORD2,PIN0);
	TEST_ASSERT_EQUAL_INT(u8_ErrorState,ERROR_NOK);
}

TEST(DIO_EnablePinPullup, PORT_A)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_A,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, PORT_B)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_B,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, PORT_C)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_C,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, PORT_D)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_D,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, INVALID_PIN1)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_D,INVALID_PIN1);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_EnablePinPullup, INVALID_PIN2)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_D,INVALID_PIN2);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_NOK));
}

TEST(DIO_EnablePinPullup, PIN0)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_D,PIN0);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, PIN7)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_D,PIN7);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, PIN5)
{
	uint8_t u8_ErrorState;
	u8_ErrorState = DIO_EnablePinPullup(PORT_D,PIN5);
	TEST_ASSERT_EQUAL_INT((u8_ErrorState),(ERROR_OK));
}

TEST(DIO_EnablePinPullup, EnablingPullupOneBit)
{
	uint8_t Expected = 0b00001000;
	DIO_EnablePinPullup(PORT_B,PIN3);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTB));
}

TEST(DIO_EnablePinPullup, EnablingPullupTwoBit)
{
	uint8_t Expected = 0b01100000;
	DIO_EnablePinPullup(PORT_B,PIN5);
	DIO_EnablePinPullup(PORT_B,PIN6);
	TEST_ASSERT_EQUAL_INT((Expected),(PORTB));
}

TEST_GROUP_RUNNER(DIO_EnablePinPullup)
{
	RUN_TEST_CASE(DIO_EnablePinPullup, INVALID_PORD1);
	RUN_TEST_CASE(DIO_EnablePinPullup, INVALID_PORD2);
	RUN_TEST_CASE(DIO_EnablePinPullup, PORT_A);
	RUN_TEST_CASE(DIO_EnablePinPullup, PORT_B);
	RUN_TEST_CASE(DIO_EnablePinPullup, PORT_C);
	RUN_TEST_CASE(DIO_EnablePinPullup, PORT_D);
	
	RUN_TEST_CASE(DIO_EnablePinPullup, INVALID_PIN1);
	RUN_TEST_CASE(DIO_EnablePinPullup, INVALID_PIN2);
	RUN_TEST_CASE(DIO_EnablePinPullup, PIN0);
	RUN_TEST_CASE(DIO_EnablePinPullup, PIN7);
	RUN_TEST_CASE(DIO_EnablePinPullup, PIN5);
	
	RUN_TEST_CASE(DIO_EnablePinPullup, EnablingPullupOneBit);
	RUN_TEST_CASE(DIO_EnablePinPullup, EnablingPullupTwoBit);
}
/*****************************************************************************************************/