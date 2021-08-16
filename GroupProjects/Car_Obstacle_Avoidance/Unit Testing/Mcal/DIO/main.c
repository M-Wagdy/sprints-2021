#include "Unit_Testing_Tool/UNIT_TESTING_TOOL.h"

void RunAllTests(void);

int main (void)
{
	UnitTestingRun(RunAllTests);
}

void RunAllTests(void)
{
	RUN_TEST_GROUP(DIO_SetPinDirection);
	RUN_TEST_GROUP(DIO_WritePin);
	RUN_TEST_GROUP(DIO_TogglePin);
	RUN_TEST_GROUP(DIO_ReadPin);
	RUN_TEST_GROUP(DIO_EnablePinPullup);
}