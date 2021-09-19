#include "InterruptHandler.h"

static VectorPtr FunctionHandler[VECTOR_TABLE_SIZE] = {NULL_PTR};
	
uint8_t Install(uint8_t VectorNum, VectorPtr FunctionPointer)
{
	uint8_t ErrRetVal = 255;
	if(FunctionPointer != NULL_PTR)
	{
		FunctionHandler[VectorNum-1] = FunctionPointer;
		ErrRetVal = 0;		
	}
	else
	{
		ErrRetVal = 1;
	}
	return ErrRetVal;
}

uint8_t DeInstall(uint8_t VectorNum)
{
	uint8_t ErrRetVal = 0;
	FunctionHandler[VectorNum-1] = NULL_PTR;
	return ErrRetVal;
}


void InterruptHandler_1 (void)
{
	if(FunctionHandler[0] != NULL_PTR)
	{
		FunctionHandler[0]();
	}
}
void InterruptHandler_2 (void)
{
	if(FunctionHandler[1] != NULL_PTR)
	{
		FunctionHandler[1]();
	}
}
void InterruptHandler_3 (void)
{
	if(FunctionHandler[2] != NULL_PTR)
	{
		FunctionHandler[2]();
	}
}
void InterruptHandler_4 (void)
{
	if(FunctionHandler[3] != NULL_PTR)
	{
		FunctionHandler[3]();
	}
}
void InterruptHandler_5 (void)
{
	if(FunctionHandler[4] != NULL_PTR)
	{
		FunctionHandler[4]();
	}
}
void InterruptHandler_6 (void)
{
	if(FunctionHandler[5] != NULL_PTR)
	{
		FunctionHandler[5]();
	}
}
void InterruptHandler_7 (void)
{
	if(FunctionHandler[6] != NULL_PTR)
	{
		FunctionHandler[6]();
	}
}
void InterruptHandler_8 (void)
{
	if(FunctionHandler[7] != NULL_PTR)
	{
		FunctionHandler[7]();
	}
}
void InterruptHandler_9 (void)
{
	if(FunctionHandler[8] != NULL_PTR)
	{
		FunctionHandler[8]();
	}
}
void InterruptHandler_10(void)
{
	if(FunctionHandler[9] != NULL_PTR)
	{
		FunctionHandler[9]();
	}
}
void InterruptHandler_11(void)
{
	if(FunctionHandler[10] != NULL_PTR)
	{
		FunctionHandler[10]();
	}
}
void InterruptHandler_12(void)
{
	if(FunctionHandler[11] != NULL_PTR)
	{
		FunctionHandler[11]();
	}
}
void InterruptHandler_13(void)
{
	if(FunctionHandler[12] != NULL_PTR)
	{
		FunctionHandler[12]();
	}
}
void InterruptHandler_14(void)
{
	if(FunctionHandler[13] != NULL_PTR)
	{
		FunctionHandler[13]();
	}
}
void InterruptHandler_15(void)
{
	if(FunctionHandler[14] != NULL_PTR)
	{
		FunctionHandler[14]();
	}
}
void InterruptHandler_16(void)
{
	if(FunctionHandler[15] != NULL_PTR)
	{
		FunctionHandler[15]();
	}
}
void InterruptHandler_17(void)
{
	if(FunctionHandler[16] != NULL_PTR)
	{
		FunctionHandler[16]();
	}
}
void InterruptHandler_18(void)
{
	if(FunctionHandler[17] != NULL_PTR)
	{
		FunctionHandler[17]();
	}
}
void InterruptHandler_19(void)
{
	if(FunctionHandler[18] != NULL_PTR)
	{
		FunctionHandler[18]();
	}
}
void InterruptHandler_20(void)
{
	if(FunctionHandler[19] != NULL_PTR)
	{
		FunctionHandler[19]();
	}
}