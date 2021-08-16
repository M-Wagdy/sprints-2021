#include "UNIT_TESTING_TOOL.h"

uint32_t TestCasesCounter=0;
uint32_t FailedTestCasesCounter=0;
uint32_t PassedTestCasesCounter=0;

void UnitTestRunner(	Ptr_VoidFuncVoid_t setup, 
						Ptr_VoidFuncVoid_t testBody, 
						Ptr_VoidFuncVoid_t teardown,
						const ptr_int8_t printableName)											
{
	printf("%s\n",printableName);
	setup();
	testBody();
	teardown();
	TestCasesCounter++;	
}

void UnitAssertEqualNumber(const int64_t expected, const int64_t actual,ptr_uint8_t file,uint32_t line)
{
	printf("\tPath: %s\n",file);
	printf("\tLine: %d\n",line);
	
	if (expected != actual)
    {
		printf("\tState: "ANSI_COLOR_RED"%s\n","FAIL"ANSI_COLOR_RESET);
		FailedTestCasesCounter++;
    }
	else
	{
		printf("\tState: "ANSI_COLOR_GREEN"%s\n","PASS"ANSI_COLOR_RESET);
		PassedTestCasesCounter++;
	}
}

void UnitTestingRun(Ptr_VoidFuncVoid_t Callback)
{
	system("clear");
	printf("\n/**********************************Unit Testing Running**********************************/\n\n");
	Callback();
	printf("All Test Cases Number: %d\n",TestCasesCounter);
	printf("Failed Test Cases Number: %d\n",FailedTestCasesCounter);
	printf("Passed Test Cases Number: %d\n",PassedTestCasesCounter);
	system("pause");
}