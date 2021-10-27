/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Comm_Lcfg.c
 *       Module:  Comm
 *
 *  Description:  source file for Comm module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.h"

TaskHandle_t Comm1TaskHandler = NULL;
TaskHandle_t Comm2TaskHandler = NULL;
const char * COMM_1_TASK_NAME = "Communication 1 Task";
const uint16_t COMM_1_TASK_STACK_DEPTH = 100;
const UBaseType_t COMM_1_TASK_PRIORITY = 2;
const char * COMM_2_TASK_NAME = "Communication 2 Task";
const uint16_t COMM_2_TASK_STACK_DEPTH = 100;
const UBaseType_t COMM_2_TASK_PRIORITY = 1;
signed char String_1[11] = "1-( )aaaa\n";
signed char String_2[11] = "2-( )bbbb\n";