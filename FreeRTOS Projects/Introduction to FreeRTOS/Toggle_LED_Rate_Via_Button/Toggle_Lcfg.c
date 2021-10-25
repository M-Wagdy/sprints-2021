/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Toggle_Lcfg.c
 *       Module:  Toggle
 *
 *  Description:  source file for Toggle module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.h"

TaskHandle_t ToggleTaskHandler = NULL;
const char * TOGGLE_TASK_NAME = "Toggle Task";
const uint16_t TOGGLE_TASK_STACK_DEPTH = 100;
const UBaseType_t TOGGLE_TASK_PRIORITY = 1;

const portX_t LED_PORT = PORT_0;
const pinX_t LED_PIN = PIN1;
