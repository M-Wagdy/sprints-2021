#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//Software Engineer Name:
/* Mohamed Hisham Wagdy */

//All inputs are unsigned character
#define PASS   ((int) 1 )
#define FAIL   ((int) 0 )

/*
- Define your global variables if needed here:
actual_result
expected_result
- Please concider the memoery optimization.
*/
int actual_result;
unsigned char guc_FirstNumber, guc_SecondNumber, guc_expected_result;

/*
- Define your functional prototypes used here:
sum
unittest
- Please concider optimum Misra C when writing your functions.
*/
int sum(unsigned char FirstNumber, unsigned char SecondNumber);
int unittest(int ActualResult, int ExpectedResult);

int main()
{
   //Please declare your initializations here.
   int TestResult;
   char* TestPass = "Passed";
   char* TestFail = "Failed";

   //Please define your infinite loop here.
   while (1)
   {
      //Please insert your screen visualization here.
      

      //Please write an expression that takes 2 numbers from the user here (concider screen readability).
      printf("Please Insert First Number: ");
      scanf("%hhud", &guc_FirstNumber);

      printf("Please Insert Second Number: ");
      scanf("%hhud", &guc_SecondNumber);

      printf("Please Insert The Expected Result: ");
      scanf("%hhud", &guc_expected_result);

      //Please write an expression that calls the two function, the activation logic function and the unit test function in sequence.
      actual_result = sum(guc_FirstNumber, guc_SecondNumber);
      TestResult = unittest(actual_result, guc_expected_result);

      if (TestResult == PASS)
      {
         printf("%s\n", TestPass);
      }
      else if (TestResult == FAIL)
      {
         printf("%s\n", TestFail);
      }
      else
      {
         /* Error in unittest function */
      }
   }
    return 0;
}

//Please write the functional description of the sum function here:
int sum(unsigned char FirstNumber, unsigned char SecondNumber)
{
   return (FirstNumber + SecondNumber);
}

//Pleas write the functional description of the unittest function here:
int unittest(int ActualResult, int ExpectedResult)
{
   int Result;
   if (ActualResult == ExpectedResult)
   {
      Result = PASS;
   }
   else
   {
      Result = FAIL;
   }
   return Result;
}