/*
 * SOS.h
 *
 * Created: 8/28/2021 3:22:02 PM
 * Author: Mohamed Wagdy
 */ 

#ifndef __SOS_H__
#define __SOS_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"
#include "SOS_Lcfg.h"

/*- MACROS -------------------------------------------------*/
/* Error Return Values */
#define SOS_MODULE_ID                  (uint8_t)(0xF0)
#define E_UNSUPPORTED_PRESCALE         (uint8_t)(0x01)
#define E_NULL_PTR                     (uint8_t)(0x02)
#define E_INVALID_PRIORITY             (uint8_t)(0x03)
#define E_TASKS_FULL                   (uint8_t)(0x04)
#define E_INVALID_ID                   (uint8_t)(0x05)

/* Task States */
#define SOS_TASK_READY                 (uint8_t)(0)
#define SOS_TASK_WAITING               (uint8_t)(1)
#define SOS_TASK_RUNNING               (uint8_t)(2)
#define SOS_TASK_SUSPENDED             (uint8_t)(3)

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct STR_Task_t{
   uint8_t              u8_Priority;      /* Task Priority */
   uint8_t              u8_State;         /* Task State */
   uint16_t             u16_Periodicity;  /* Task Periodicity */
   Ptr_VoidFuncVoid_t   ptr_Task;         /* Task Function */
} STR_Task_t;

typedef struct STR_TaskHandler_t{
   uint8_t              u8_ID;            /* Task Identifier */
} STR_TaskHandler_t;

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Initialize OS */
void SOS_Init(void);

/* Run OS Schedular */
void SOS_Run(void);

/* Create Task */
ERROR_STATE_t SOS_CreateTask(Ptr_VoidFuncVoid_t Task, uint8_t Priority, uint16_t Periodicity, STR_TaskHandler_t * Handler);

/* Delete Task */
ERROR_STATE_t SOS_DeleteTask(STR_TaskHandler_t * TaskHandler);

/* Suspend Task */
ERROR_STATE_t SOS_SuspendTask(STR_TaskHandler_t * TaskHandler);

/* Unsuspend Task */
ERROR_STATE_t SOS_UnsuspendTask(STR_TaskHandler_t * TaskHandler);

#endif /* __SOS_H__ */