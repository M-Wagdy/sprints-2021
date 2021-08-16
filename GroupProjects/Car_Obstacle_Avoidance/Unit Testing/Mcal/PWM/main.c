#include "Unit_Testing_Tool/UNIT_TESTING_TOOL.h"

void RunAllTests(void);

int main (void)
{
	UnitTestingRun(RunAllTests);
}

void RunAllTests(void)
{
	RUN_TEST_GROUP(PWM_Init);
	RUN_TEST_GROUP(PWM_Start);
	RUN_TEST_GROUP(PWM_Stop);
	RUN_TEST_GROUP(PWM_Connect);
	RUN_TEST_GROUP(PWM_Disconnect);
	RUN_TEST_GROUP(PWM_SetDuty);
}