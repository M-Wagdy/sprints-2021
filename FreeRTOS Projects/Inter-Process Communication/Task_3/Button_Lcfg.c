/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Button_Lcfg.c
 *       Module:  Button
 *
 *  Description:  source file for Button module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.h"
#include "Comm_Lcfg.h"

TaskHandle_t Button1TaskHandler = NULL;
TaskHandle_t Button2TaskHandler = NULL;
const char * BUTTON_1_TASK_NAME = "Button 1 Task";
const uint16_t BUTTON_1_TASK_STACK_DEPTH = 100;
const UBaseType_t BUTTON_1_TASK_PRIORITY = 2;
const char * BUTTON_2_TASK_NAME = "Button 2 Task";
const uint16_t BUTTON_2_TASK_STACK_DEPTH = 100;
const UBaseType_t BUTTON_2_TASK_PRIORITY = 2;
const portX_t BUTTON_1_PORT = PORT_0;
const pinX_t BUTTON_1_PIN = PIN0;
const portX_t BUTTON_2_PORT = PORT_0;
const pinX_t BUTTON_2_PIN = PIN1;
const CommMessage BTN1_RisingMessage = {22, "Button 1 Rising Edge.\n"};
const CommMessage BTN1_FallingMessage = {23, "Button 1 Falling Edge.\n"};
const CommMessage BTN2_RisingMessage = {22, "Button 2 Rising Edge.\n"};
const CommMessage BTN2_FallingMessage = {23, "Button 2 Falling Edge.\n"};
