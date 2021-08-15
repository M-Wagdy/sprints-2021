#include "LCD_STUB.h"

ERROR_STATE_t LCD_SendCommand(uint8_t CMD)
{
	return OperationSuccess;
}

ERROR_STATE_t LCD_Init()
{
	return OperationSuccess;
}

ERROR_STATE_t LCD_SendString(ptr_int8_t String)
{
	return OperationSuccess;
}

ERROR_STATE_t LCD_SendNumber(uint32_t Number)
{
	return OperationSuccess;
}
