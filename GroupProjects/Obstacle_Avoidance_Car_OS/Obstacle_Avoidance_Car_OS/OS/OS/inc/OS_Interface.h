/*
 * File Name: OS_Interface.h
 * Creation Date: 08/09/2021
 * Author: Ahmed&Rehab
 * Description: Header File for OS Interface File....
 */ 

#ifndef __OS_INTERFACE__
#define __OS_INTERFACE__

#include "STD_TYPES.h"
#include "OS_Lcfg.h"
#include "OS_Cfg.h"

/*-----ERROR DEFINATIONS-----*/
#define OS_MEMORY_FULL						(ERROR_STATE_t)(-1)
#define OS_UNSUPPORTED_PRIORITY				(ERROR_STATE_t)(-2)
#define OS_INVALID_TASK_ID					(ERROR_STATE_t)(-3)
#define OS_UNSUPPORTED_RESOLUTION			(ERROR_STATE_t)(-4)


typedef enum Eum_OS_TaskState
{
	OS_TASKREADY		=0,
	OS_TASKRUNING		=1,
	OS_TASKWAIT			=2,
	OS_TASKSUSPEND		=3,
	OS_TASKDELETED		=4
	
}Eum_OS_TaskState_t;

typedef struct Str_OS_TaskCfg
{
	uint8_t u8_OS_TaskPriority;
	uint8_t u8_OS_TaskDelay;
	uint8_t u8_OS_TaskID;
	uint8_t u8_OS_TaskState;
	uint32_t u32_OS_TaskPeriodicity;
	Ptr_VoidFuncVoid_t ptr_OS_TaskCallback;
	
}Str_OS_TaskCfg_t;

typedef Str_OS_TaskCfg_t*  TaskHandler_t;

extern ERROR_STATE_t OS_CreateTask(
									uint8_t Priority,
									uint8_t Delay,
									uint32_t Periodicity,
									Ptr_VoidFuncVoid_t TaskCallback,
									TaskHandler_t* TaskHandler
								);
						
extern ERROR_STATE_t OS_DeleteTask(TaskHandler_t TaskHandler);
extern ERROR_STATE_t OS_SuspandTask(TaskHandler_t TaskHandler);
extern ERROR_STATE_t OS_UnsuspandTask(TaskHandler_t TaskHandler);
extern ERROR_STATE_t OS_Get(TaskHandler_t* Task);

#endif
