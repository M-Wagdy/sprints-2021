/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Periodic_Lcfg.c
 *       Module:  Periodic
 *
 *  Description:  source file for Periodic module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "Comm_Lcfg.h"
#include "FreeRTOS.h"
#include "task.h"
#include "GPIO.h"

TaskHandle_t PeriodicTaskHandler = NULL;
const char * PERIODIC_TASK_NAME = "Periodic Task";
const uint16_t PERIODIC_TASK_STACK_DEPTH = 100;
const UBaseType_t PERIODIC_TASK_PRIORITY = 1;
const CommMessage PeriodicMessage = {18, "Periodic Message.\n"};
	
