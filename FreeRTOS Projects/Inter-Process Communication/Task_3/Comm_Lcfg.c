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
#include "Comm_Lcfg.h"

TaskHandle_t CommTaskHandler = NULL;
const char * COMM_TASK_NAME = "Communication Task";
const uint16_t COMM_TASK_STACK_DEPTH = 100;
const UBaseType_t COMM_TASK_PRIORITY = 1;
