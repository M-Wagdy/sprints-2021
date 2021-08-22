#ifndef UNIT_TESTING_TOOL_H_
#define UNIT_TESTING_TOOL_H_

#include <stdio.h>
#include <stdlib.h>
#include "../STD_TYPES.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#define TEST_GROUP(group)\
    static const char* TEST_GROUP_##group = #group

#define TEST_SETUP(group) void TEST_##group##_SETUP(void);\
    void TEST_##group##_SETUP(void)

#define TEST_TEAR_DOWN(group) void TEST_##group##_TEAR_DOWN(void);\
    void TEST_##group##_TEAR_DOWN(void)


#define TEST(group, name) \
    void TEST_##group##_##name##_(void);\
    void TEST_##group##_##name##_run(void);\
    void TEST_##group##_##name##_run(void)\
    {\
        UnitTestRunner(TEST_##group##_SETUP,\
            TEST_##group##_##name##_,\
            TEST_##group##_TEAR_DOWN,\
            "TEST(" #group ", " #name ")");\
    }\
    void  TEST_##group##_##name##_(void)
	
/* Call this for each test, insider the group runner */
#define RUN_TEST_CASE(group, name) \
    { void TEST_##group##_##name##_run(void);\
      TEST_##group##_##name##_run(); }
	  
/* This goes at the bottom of each test file or in a separate c file */
#define TEST_GROUP_RUNNER(group)\
    void TEST_##group##_GROUP_RUNNER(void);\
    void TEST_##group##_GROUP_RUNNER(void)

/* Call this from main */
#define RUN_TEST_GROUP(group)\
    { void TEST_##group##_GROUP_RUNNER(void);\
      TEST_##group##_GROUP_RUNNER(); }	
	
#define TEST_ASSERT_EQUAL_INT(expected,actual) UnitAssertEqualNumber((int64_t)(expected),(int64_t)(actual),__FILE__,__LINE__)	


void UnitTestRunner(	Ptr_VoidFuncVoid_t setup, 
						Ptr_VoidFuncVoid_t testBody, 
						Ptr_VoidFuncVoid_t teardown,
						const ptr_int8_t printableName);
						
void UnitAssertEqualNumber(const int64_t expected, const int64_t actual,ptr_uint8_t file,uint32_t line);

void UnitTestingRun(Ptr_VoidFuncVoid_t Callback);	
#endif 