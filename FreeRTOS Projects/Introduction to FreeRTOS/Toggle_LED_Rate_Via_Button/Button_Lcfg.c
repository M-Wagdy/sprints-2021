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

TaskHandle_t ButtonTaskHandler = NULL;
const char * BUTTON_TASK_NAME = "Button Task";
const uint16_t BUTTON_TASK_STACK_DEPTH = 100;
const UBaseType_t BUTTON_TASK_PRIORITY = 2;
const portX_t BUTTON_PORT = PORT_0;
const pinX_t BUTTON_PIN = PIN0;