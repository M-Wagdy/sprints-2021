/*
* admin.c
*
* Created: 7/15/2021 1:05:37 AM
*  Author: Marco
*/

/******************************************************************************
*                              Includes													*
*******************************************************************************/
#include "admin.h"


#if !TEST_ADMIN
volatile static uint8_t au8_PANNumbers[MAX_ACCOUNT_NO][PAN_BYTES_GUARD_NO];
volatile static uint8_t au8_PANNumber[PAN_BYTES_GUARD_NO], au8_AccountBalance[MAX_ACCOUNT_BYTES_NO];
volatile static uint8_t au8_PANAddress, au8_SPACEAddress, au8_AccountBalanceAddress;
volatile static uint8_t pin[PASS_BYTES_GUARD_NO];
volatile static uint8_t user_pin[USER_PASS_BYTES_NO];
volatile static uint8_t gau8_PIN[PASS_BYTES_GUARD_NO] = "1234";
volatile static f32_t ufloat_AccountBalance;
volatile static uint8_t u8_choice;


#else
uint8_t au8_PANNumbers[MAX_ACCOUNT_NO][PAN_BYTES_GUARD_NO];
uint8_t au8_PANNumber[PAN_BYTES_GUARD_NO];
uint8_t au8_AccountBalance[MAX_ACCOUNT_BYTES_NO];
uint8_t au8_PANAddress, au8_SPACEAddress, au8_AccountBalanceAddress;
uint8_t pin[PASS_BYTES_GUARD_NO];
uint8_t user_pin[USER_PASS_BYTES_NO];
uint8_t gau8_PIN[PASS_BYTES_GUARD_NO] = "1234";
uint8_t u8_choice;
f32_t ufloat_AccountBalance;
#endif

/******************************************************************************
*                         LOCAL FUNCTION IMPLEMENTATION								*
*******************************************************************************/
void reverse(ptr_uint8_t str, uint8_t len)
{
	uint8_t u8_iterator = 0, j = len - 1, temp;
	while (u8_iterator < j) {
		temp = str[u8_iterator];
		str[u8_iterator] = str[j];
		str[j] = temp;
		u8_iterator++;
		j--;
	}
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
uint8_t intToStr(uint32_t x, uint8_t str[], uint32_t d)
{
	uint32_t u8_iterator = 0;
	while (x) {
		str[u8_iterator++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (u8_iterator < d)
	str[u8_iterator++] = '0';

	reverse(str, u8_iterator);
	str[u8_iterator] = END_OF_STRING;
	return u8_iterator;
}

// Converts a floating-point/double number to a string.
void ftos(f32_t n, ptr_uint8_t res, uint8_t afterpoint)
{
	// Extract integer part
	uint32_t ipart = (uint32_t)n;

	// Extract floating part
	f32_t fpart = n - (f32_t)ipart;

	// convert integer part to string
	uint32_t u32_iterator = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0) {
		res[u32_iterator] = '.'; // add dot

		// Get the value of fraction part up to given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((uint32_t)fpart, res + u32_iterator + 1, afterpoint);
	}
}

uint32_t findLength(ptr_uint8_t str) {
	uint32_t size = 0;
	while (str[size])
	{
		size++;
	}

	return size;
}

f32_t stof(ptr_uint8_t str)
{

	f32_t result = 0.0;
	uint32_t len = findLength(str);
	uint32_t dotPosition = 0;

	for (uint8_t u8_iterator = 0; u8_iterator < len; u8_iterator++)
	{
		if (str[u8_iterator] == '.')
		{
			dotPosition = len - u8_iterator - 1;
		}
		else
		{
			result = result * 10.0 + (str[u8_iterator] - '0');
		}
	}

	while (dotPosition--)
	{
		result /= 10.0;
	}

	return result;

}

static uint8_t Validate_PAN(void)
{
	if (findLength(au8_PANNumber) != PAN_BYTES_NO)
	{
		return FALSE;
	}

	for (uint8_t u8_ValidatorCounter = 0; u8_ValidatorCounter < PAN_BYTES_NO; u8_ValidatorCounter++)
	{
		if ((au8_PANNumber[u8_ValidatorCounter] < ZERO_ASCII) || (au8_PANNumber[u8_ValidatorCounter] > NINE_ASCII))
		{
			return FALSE;
		}
	}

	return TRUE;
}

void Init_Drivers()
{
	UART_Init(UART_CH);
	EEPROM_Init(EEPROM_CH);
}

void Set_PinData()
{
	#if TEST_ADMIN
	for (uint8_t u8_Counter = 0; u8_Counter < PASS_BYTES_NO; u8_Counter++)
	{
		gau8_PIN[u8_Counter] = ZERO_ASCII + u8_Counter + 1;
	}
	gau8_PIN[PASS_BYTES_NO] = END_OF_STRING;
	#endif
	if (PASS_BYTES_GUARD_NO > MAX_PASS_BYTES_NO)
	{
		return;
	}
	EEPROM_WriteBytes(EEPROM_CH, PASS_BLOCK, PASS_ADDR, (uint8_t*)gau8_PIN, PASS_BYTES_GUARD_NO);
}

void Get_PinData(uint8_t* data)
{
	if (PASS_BYTES_GUARD_NO > MAX_PASS_BYTES_NO)
	{
		return;
	}
	EEPROM_ReadBytes(EEPROM_CH, PASS_BLOCK, PASS_ADDR, data, PASS_BYTES_GUARD_NO);
}

uint8_t Check_WrittenAddresses()
{
	uint8_t count;
	EEPROM_Read(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, &count);
	if (count == AVALIABLE_ACCOUNTS_NULL)
	{
		return FALSE;
	}
	return TRUE;

}

void Display_AccountsAvaliable(void)
{
	UART_TransmitString(UART_CH, STRING_ACCOUNTS_AVALIABLE);
	UART_TransmitChar(UART_CH, BACKSPACE);
	UART_TransmitString(UART_CH, au8_PANNumber);
	UART_TransmitString(UART_CH, STRING_WELCOME_END);
}

void Reset_WrittenAddresses()
{
	EEPROM_Write(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, AVALIABLE_ACCOUNTS_NULL);
}

void Set_WrittenAddresses(uint8_t count)
{
	EEPROM_Write(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, count);
	intToStr(count, au8_PANNumber, 0);
	Display_AccountsAvaliable();
}

uint8_t Get_WrittenAddresses(void)
{
	uint8_t count = SPACE_BYTES_NO;
	EEPROM_Read(EEPROM_CH, AVALIABLE_ACCOUNTS_BLOCK, AVALIABLE_ACCOUNTS_ADDR, &count);

	if (!Check_WrittenAddresses())
	{
		return FALSE;
	}
	intToStr(count, au8_PANNumber, 0);
	Display_AccountsAvaliable();
	return count;
}

uint8_t Check_PANExists(uint8_t count)
{
	
	uint8_t u8_PANExists = FALSE;
	for (uint8_t u8_iterator = 0; u8_iterator < count; u8_iterator++)
	{
		#if TEST_ADMIN
			break;
		#endif
		au8_PANAddress = (u8_iterator * TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_PANAddress, au8_PANNumbers[u8_iterator], PAN_BYTES_GUARD_NO);
		if ((StringCompare(au8_PANNumber, au8_PANNumbers[u8_iterator])))
		{
			u8_PANExists = TRUE;
			UART_TransmitString(UART_CH, STRING_PAN_EXISTS);
			break;
		}
	}
	return u8_PANExists;
}


/******************************************************************************
*                         APIS IMPLEMENTATION											*
*******************************************************************************/

void ADMIN_Mode(void)
{
	Reset_WrittenAddresses();
	Set_PinData();
	ADMIN_Authenticate();
	#if TEST_ADMIN
	ADMIN_Interface(&u8_choice);
	if (u8_choice == OPTION_EXIT)
	{
		UART_TransmitString(UART_CH, STRING_EXIT);
	}
	else if (u8_choice == OPTION_SET_CUSTOMER_DATA) ADMIN_SetAccount();
	else if (u8_choice == OPTION_GET_CUSTOMER_DATA) ADMIN_GetAccount();
	else if (u8_choice == OPTION_SET_MAX_ACCOUNT) ADMIN_SetMaxBalance();
	else if (u8_choice == OPTION_GET_MAX_ACCOUNT) ADMIN_GetMaxBalance();
	else UART_TransmitString(UART_CH, STRING_INVALID_CHOICE);
	#else
	while (1)
	{
		ADMIN_Interface(&u8_choice);
		if (u8_choice == OPTION_EXIT)
		{
			UART_TransmitString(UART_CH, STRING_EXIT);
			break;
		}
		else if (u8_choice == OPTION_SET_CUSTOMER_DATA) ADMIN_SetAccount();
		else if (u8_choice == OPTION_GET_CUSTOMER_DATA) ADMIN_GetAccount();
		else if (u8_choice == OPTION_SET_MAX_ACCOUNT) ADMIN_SetMaxBalance();
		else if (u8_choice == OPTION_GET_MAX_ACCOUNT) ADMIN_GetMaxBalance();
		else UART_TransmitString(UART_CH, STRING_INVALID_CHOICE);
	}
	#endif
}
void ADMIN_Authenticate(void)
{
	Get_PinData(pin);
	#if TEST_ADMIN
	for (uint8_t u8_Counter = 0; u8_Counter < PASS_BYTES_NO; u8_Counter++)
	{
		pin[u8_Counter] = ZERO_ASCII + u8_Counter + 1;
	}
	pin[PASS_BYTES_NO] = END_OF_STRING;
	#endif
	while (TRUE)
	{
		UART_TransmitString(UART_CH, STRING_ENTER_PIN);
		UART_TransmitChar(UART_CH, BACKSPACE);
		UART_ReceiveString(UART_CH, user_pin);
		#if TEST_ADMIN
		for (uint8_t u8_Counter = 0; u8_Counter < PASS_BYTES_NO; u8_Counter++)
		{
			user_pin[u8_Counter] = ZERO_ASCII + u8_Counter + 1;
		}
		user_pin[PASS_BYTES_NO] = END_OF_STRING;
		#endif
		if ((StringCompare(pin, user_pin))) break;
		UART_TransmitString(UART_CH, STRING_INVALID_PIN);
	}
}

void ADMIN_Interface(ptr_uint8_t pu8_choice)
{
	while (TRUE)
	{
		UART_TransmitString(UART_CH, STRING_WELCOME_START);
		UART_TransmitString(UART_CH, STRING_MENU_SET_CUSTOMER_DATA);
		UART_TransmitString(UART_CH, STRING_MENU_GET_CUSTOMER_DATA);
		UART_TransmitString(UART_CH, STRING_MENU_SET_MAX_ACCOUNT);
		UART_TransmitString(UART_CH, STRING_MENU_GET_MAX_ACCOUNT);
		UART_TransmitString(UART_CH, STRING_MENU_EXIT);
		UART_TransmitString(UART_CH, STRING_WELCOME_END);
		UART_TransmitString(UART_CH, STRING_MENU_CHOICE);
		UART_TransmitChar(UART_CH, BACKSPACE);
		UART_ReceiveChar(UART_CH, pu8_choice);
		#if TEST_ADMIN
		* pu8_choice = '4';
		if ((*pu8_choice <= OPTION_EXIT) && (*pu8_choice >= OPTION_SET_CUSTOMER_DATA)) break;
		else return FALSE;
		#endif
		UART_TransmitChar(UART_CH, NEW_LINE);
		if ((*pu8_choice <= OPTION_EXIT) && (*pu8_choice >= OPTION_SET_CUSTOMER_DATA)) break;
		UART_TransmitString(UART_CH, STRING_INVALID_CHOICE);
	}
}
void ADMIN_GetAccount(void)
{
	uint8_t i = 0;
	uint8_t count = Get_WrittenAddresses();
	
	if (!Check_WrittenAddresses())
	{
		UART_TransmitString(UART_CH, STRING_MEMORY_EMPTY);
		return;
	}
	while (i < count)
	{
		au8_PANAddress = (i * TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
		au8_SPACEAddress = au8_PANAddress + PAN_BYTES_NO;
		au8_AccountBalanceAddress = au8_SPACEAddress + SPACE_BYTES_NO;
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_PANAddress, au8_PANNumber, PAN_BYTES_NO);
		UART_TransmitString(UART_CH, STRING_PAN);
		UART_TransmitChar(UART_CH, BACKSPACE);
		UART_TransmitString(UART_CH, au8_PANNumber);
		EEPROM_ReadBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_AccountBalanceAddress, (uint8_t*)&ufloat_AccountBalance, MAX_ACCOUNT_BYTES_NO);
		UART_TransmitString(UART_CH, STRING_ACCOUNT);
		UART_TransmitChar(UART_CH, BACKSPACE);
		ftos(ufloat_AccountBalance, au8_AccountBalance, FLOATING_POINT);
		UART_TransmitString(UART_CH, au8_AccountBalance);
		i++;
	}
	#if TEST_ADMIN
	for (uint8_t u8_Counter = 0; u8_Counter < PAN_BYTES_NO; u8_Counter++)
	{
		au8_PANNumber[u8_Counter] = ZERO_ASCII +1;
	}
	au8_PANNumber[PAN_BYTES_NO] = END_OF_STRING;
	#endif
	UART_TransmitString(UART_CH, STRING_WELCOME_END);
}



void ADMIN_SetAccount(void)
{
	uint8_t count = Get_WrittenAddresses();
	uint8_t temp = count;
	if (count == MAX_ACCOUNT_NO)
	{
		UART_TransmitString(UART_CH, STRING_MEMORY_FULL);
		return;
	}
	while (TRUE)
	{
		UART_TransmitString(UART_CH, STRING_ENTER_PAN);
		UART_TransmitChar(UART_CH, BACKSPACE);
		UART_ReceiveString(UART_CH, au8_PANNumber);
		#if TEST_ADMIN
		for (uint8_t u8_Counter = 0; u8_Counter < PAN_BYTES_NO; u8_Counter++)
		{
			au8_PANNumber[u8_Counter] = ZERO_ASCII + u8_Counter +1;
		}
		au8_PANNumber[PAN_BYTES_NO] = END_OF_STRING;
		#endif
		if (Validate_PAN() != TRUE)
		{
			UART_TransmitString(UART_CH, STRING_INVALID_PAN);
			continue;
		}
		else if (Check_PANExists(temp)) continue;
		else break;
	}
	au8_PANAddress = (count * TOTAL_FRAME_NO) + ACCOUNTS_ADDR;
	au8_SPACEAddress = au8_PANAddress + PAN_BYTES_NO;
	au8_AccountBalanceAddress = au8_SPACEAddress + SPACE_BYTES_NO;
	
	EEPROM_WriteBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_PANAddress, au8_PANNumber, PAN_BYTES_NO);
	EEPROM_Write(EEPROM_CH, ACCOUNTS_BLOCK, au8_SPACEAddress, END_OF_STRING);
	UART_TransmitString(UART_CH, STRING_ENTER_ACCOUNT);
	UART_TransmitChar(UART_CH, BACKSPACE);
	UART_ReceiveString(UART_CH, au8_AccountBalance);
	ufloat_AccountBalance = stof(au8_AccountBalance);
	EEPROM_WriteBytes(EEPROM_CH, ACCOUNTS_BLOCK, au8_AccountBalanceAddress, (uint8_t*)&ufloat_AccountBalance, MAX_ACCOUNT_BYTES_NO);
	++count;
	Set_WrittenAddresses(count);
	#if TEST_ADMIN
	for (uint8_t u8_Counter = 0; u8_Counter < PAN_BYTES_NO; u8_Counter++)
	{
		au8_PANNumber[u8_Counter] = ZERO_ASCII + u8_Counter +1;
	}
	au8_PANNumber[PAN_BYTES_NO] = END_OF_STRING;
	#endif
}
void ADMIN_SetMaxBalance(void)
{
	UART_TransmitString(UART_CH, STRING_MAX_ACCOUNT);
	UART_TransmitChar(UART_CH, BACKSPACE);
	UART_ReceiveString(UART_CH, au8_AccountBalance);
	ufloat_AccountBalance = stof(au8_AccountBalance);
	#if TEST_ADMIN
		ufloat_AccountBalance = 500.00;
	#endif
	if (ufloat_AccountBalance < MAX_BALANCE_NO)
	{
		EEPROM_WriteBytes(EEPROM_CH, MAX_ACCOUNT_BLOCK, MAX_ACCOUNT_ADDR, (uint8_t*)&ufloat_AccountBalance, MAX_ACCOUNT_BYTES_NO);
	}
	else
	{
		UART_TransmitString(UART_CH, STRING_INVALID_MAX_ACCOUNT);
	}

}

void ADMIN_GetMaxBalance(void)
{
	EEPROM_ReadBytes(EEPROM_CH, MAX_ACCOUNT_BLOCK, MAX_ACCOUNT_ADDR, (uint8_t*)&ufloat_AccountBalance, MAX_ACCOUNT_BYTES_NO);
	ftos(ufloat_AccountBalance, au8_AccountBalance, FLOATING_POINT);
	#if TEST_ADMIN
		ufloat_AccountBalance = 100.00;
	#endif
	UART_TransmitString(UART_CH, au8_AccountBalance);
	UART_TransmitString(UART_CH, STRING_WELCOME_END);
}
