#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HAL/LCD/LCD.h"
uint8_t TimerRetVal_MOCK = ERROR_OK;
uint8_t LCD_FunctionState = OperationStarted;
uint8_t LCD_FunctionReturn = OperationStarted;
uint8_t LCD_FunctionLCD_InitStatesSequence[255]= {0};
uint8_t LCD_FunctionLCD_SendStatesSequence[255]= {0};
uint8_t LCD_FunctionLCD_SendDataStatesSequence[255]= {0};
uint8_t LCD_InitSequence[] = {5,6,8,9,10,11,12,13,14,7,15,255};
uint8_t LCD_SendSequence[] = {1,2,3,4,255};
uint8_t Test_String[] = "Ahmed";
uint8_t Test_Number = 255;
int main()
{
    printf("Start Testing of LCD_Init() function \n");
    while(OperationSuccess != LCD_FunctionReturn)
    {
        LCD_FunctionReturn = LCD_Init();

    }
    printf("Expected Sequence     Actual Sequence\n");
    for(uint8_t i = 0; i<sizeof(LCD_InitSequence)/sizeof(LCD_InitSequence[0]); i++)
    {
        printf("    %d                        %d\n",LCD_FunctionLCD_InitStatesSequence[i],LCD_InitSequence[i]);
    }
    if(OperationSuccess == LCD_FunctionReturn)
        printf("Test Success\n");

    LCD_FunctionReturn=OperationStarted;
    printf("Start Testing of LCD_SendCommand() function \n");
        while(OperationSuccess != LCD_FunctionReturn)
    {
        LCD_FunctionReturn = LCD_SendCommand(0x00);

    }
    printf("Expected Sequence     Actual Sequence\n");
    for(uint8_t i = 0; i<sizeof(LCD_SendSequence)/sizeof(LCD_SendSequence[0]); i++)
    {
        printf("    %d                        %d\n",LCD_FunctionLCD_SendStatesSequence[i],LCD_SendSequence[i]);
    }
    if(OperationSuccess == LCD_FunctionReturn)
        printf("Test Success\n");

    LCD_FunctionReturn=OperationStarted;
    printf("Start Testing of LCD_SendData() function \n");
    while(OperationSuccess != LCD_FunctionReturn)
    {
        LCD_FunctionReturn = LCD_SendData(0x00);

    }
    printf("Expected Sequence     Actual Sequence\n");
    for(uint8_t i = 0; i<sizeof(LCD_SendSequence)/sizeof(LCD_SendSequence[0]); i++)
    {
        printf("    %d                        %d\n",LCD_FunctionLCD_SendDataStatesSequence[i],LCD_SendSequence[i]);
    }
    if(OperationSuccess == LCD_FunctionReturn)
        printf("Test Success\n");
    LCD_FunctionReturn=OperationStarted;
    printf("Start Testing of LCD_SendString() function \n");
    LCD_FunctionReturn=LCD_SendString(Test_String);
    if(OperationSuccess == LCD_FunctionReturn)
        printf("Test Success\n");
    LCD_FunctionReturn=OperationStarted;
    printf("Start Testing of LCD_SendNumber() function \n");
    LCD_FunctionReturn=LCD_SendNumber(Test_Number);
    if(OperationSuccess == LCD_FunctionReturn)
        printf("Test Success\n");

    return 0;
}
