#include <stdio.h>
#include <stdlib.h>
#include "../../../../ATM_ECU/App/ATM/ATM.h"
//Macros

#define FAIL 1
#define PASS 0
//global variables
uint8_t ATM_SelectModeTestCaseCounter = 0;
uint8_t TestResult = FAIL;
uint8_t* Mock_UserStringEntry = NULL;
uint8_t* ArrayForTestingData[3]={(uint8_t*)"ADMIN",(uint8_t*)"USER",(uint8_t*)"ADEL"};
//functions declarations
void ATM_SelectMode_Test();

int main()
{
    printf("Start ATM_SelectMode() testing\n");
    ATM_SelectMode_Test();
    printf("End of ATM_SelectMode() testing\n");
    return 0;
}

void ATM_SelectMode_Test()
{
    uint8_t iterator = 0;
    for(;iterator<3;iterator++)
    {
        Mock_UserStringEntry = ArrayForTestingData[iterator];
        ATM_SelectModeTestCaseCounter++;
        printf("TEST CASE %d\n",ATM_SelectModeTestCaseCounter);
        printf("The User Enters: %s\n",Mock_UserStringEntry);
        ATM_SelectMode();
        if(TestResult==PASS)
        {

            switch(ATM_SelectModeTestCaseCounter)
            {
            case 1:
                printf("The user enters the ADMIN Mode\n");
                break;
            case 2:
                printf("The user enters the USER Mode\n");
                break;
            case 3:
                printf("The Terminal displays Invalid input Please enter a valid choice\n");
                break;
            default:
                break;
            }
            printf("Test Case %d Passed\n\n",ATM_SelectModeTestCaseCounter);
        }
        else
            printf("Test Case %d Failed\n\n",ATM_SelectModeTestCaseCounter);
    }

}
