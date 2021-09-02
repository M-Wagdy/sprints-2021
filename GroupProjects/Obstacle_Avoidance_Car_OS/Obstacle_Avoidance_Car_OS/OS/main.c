/*
 * OS.c
 *
 * Created: 08/29/2021 7:56:24 PM
 *  Author: REHAB
 */ 

#include "SENSING.h"
#include "CRASH.h"
#include "STEERING.h"

#include "OS.h"

#define SENSING_TASK_PRIORITY			0
#define CARSHING_TASK_PRIORITY			1	
#define STEERING_TASK_PRIORITY			2

#define SENSING_TASK_FIREST_DELAY		0
#define CARSHING_TASK_FIREST_DELAY		1
#define STEERING_TASK_FIREST_DELAY		1

#define SENSING_TASK_PERIODICITY		1
#define CARSHING_TASK_PERIODICITY		2
#define STEERING_TASK_PERIODICITY		2



TaskHandler_t SensingTaskHandler;
TaskHandler_t CrashingTaskHandler;
TaskHandler_t SteeringTaskHandler;

void SensingTask(void);
void CrashingTask(void);
void SteeringTask(void);

void SensingTask(void)
{
	SENSING_MainFunction();	
}

void CrashingTask(void)
{
	CRASH_MainFunction();
}

void SteeringTask(void)
{
	STEERING_MainFunction();
}

int main(void)
{
	OS_Init();

	OS_CreateTask(SENSING_TASK_PRIORITY,SENSING_TASK_FIREST_DELAY,SENSING_TASK_PERIODICITY,SensingTask,&SensingTaskHandler);	
	OS_CreateTask(CARSHING_TASK_PRIORITY,CARSHING_TASK_FIREST_DELAY,CARSHING_TASK_PERIODICITY,CrashingTask,&CrashingTaskHandler);	
	OS_CreateTask(STEERING_TASK_PRIORITY,STEERING_TASK_FIREST_DELAY,STEERING_TASK_PERIODICITY,SteeringTask,&SteeringTaskHandler);

	OS_Run();
	
    while(1)
    {
        //TODO:: Please write your application code
    }
}