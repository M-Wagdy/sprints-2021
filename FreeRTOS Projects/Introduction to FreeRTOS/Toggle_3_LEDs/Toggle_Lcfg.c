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

TaskHandle_t ToggleTask100MSHandler = NULL;
TaskHandle_t ToggleTask500MSHandler = NULL;
TaskHandle_t ToggleTask1000MSHandler = NULL;

const char * TOGGLE_TASK_100_NAME = "Toggle 100 MS Task";
const uint16_t TOGGLE_TASK_100_STACK_DEPTH = 100;
const UBaseType_t TOGGLE_TASK_100_PRIORITY = 1;

const char * TOGGLE_TASK_500_NAME = "Toggle 500 MS Task";
const uint16_t TOGGLE_TASK_500_STACK_DEPTH = 100;
const UBaseType_t TOGGLE_TASK_500_PRIORITY = 1;

const char * TOGGLE_TASK_1000_NAME = "Toggle 1000 MS Task";
const uint16_t TOGGLE_TASK_1000_STACK_DEPTH = 100;
const UBaseType_t TOGGLE_TASK_1000_PRIORITY = 1;

const portX_t LED_1_PORT = PORT_0;
const pinX_t LED_1_PIN = PIN0;

const portX_t LED_2_PORT = PORT_0;
const pinX_t LED_2_PIN = PIN1;

const portX_t LED_3_PORT = PORT_0;
const pinX_t LED_3_PIN = PIN2;
