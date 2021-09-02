/*
 * File Name: OS.c
 * Creation Date: 08/09/2021
 * Author: Ahmed&Rehab
 * Description: C File for OS Module....
 */ 

#include "MC_REGISTERS.h"
#include "OS.h"

extern Str_OS_SchedulerCfg_t gstr_OS_SchedulerCfg;
extern volatile uint8_t gu8_OS_ReadyTasksCounter;

TaskHandler_t gpstr_Task=NULL_PTR;
static uint32_t gu32_OS_TicksNumber=ZERO;

#define OS_RES_5U_PRESCALER_8             	(uint8_t)10
#define OS_RES_10U_PRESCALER_8             	(uint8_t)20
#define OS_RES_20U_PRESCALER_8            	(uint8_t)40

#define OS_T0_PRESCALER_8				  	(uint8_t)2				
#define OS_T1_PRESCALER_8				  	(uint8_t)2				
#define OS_T2_PRESCALER_8				  	(uint8_t)2

#define TIMER0_COMP_VECTOR_NUMBER			10
#define TIMER1_COMPA_VECTOR_NUMBER			7
#define TIMER2_COMP_VECTOR_NUMBER			4

#define ISR(VECTOR_NUMBER)	 __vector_##VECTOR_NUMBER
		
static void OS_IdealTask(void);
static void OS_Start(void);	

static void OS_IdealTask(void)
{
	while(TRUE)
	{
		if(ZERO!=gu8_OS_ReadyTasksCounter)
		{
			break;
		}
		else
		{
			/*Do Nothing*/
		}
			
	}	
}
	
static void OS_Start(void)
{
	#if OS_TIMER_0
		REG_WRITE(TCNT0,ZERO);
	#endif
		
	#if OS_TIMER_1
		REG_WRITE(TCNT1,ZERO);
	#endif
		
	#if OS_TIMER_2
		REG_WRITE(TCNT2,ZERO);
	#endif
	
	SET_BIT(SREG,I);
}

extern ERROR_STATE_t OS_Init(void)
{	
	ERROR_STATE_t u8_ErrorState = ERROR_OK;
	
	#if OS_TIMER_0
		switch(gstr_OS_SchedulerCfg.u8_OS_TimerResolution)
		{
			case OS_TIMER_RESOLUATION_5U:
				REG_WRITE(OCR0,OS_RES_5U_PRESCALER_8);
				break;	
			case OS_TIMER_RESOLUATION_10U:
				REG_WRITE(OCR0,OS_RES_10U_PRESCALER_8);
				break;
			case OS_TIMER_RESOLUATION_20U:
				REG_WRITE(OCR0,OS_RES_20U_PRESCALER_8);
				break;
			default:
				u8_ErrorState=OS_UNSUPPORTED_RESOLUTION;
				break;
		}
		if(ERROR_OK==u8_ErrorState)
		{		
			SET_BIT(TCCR0,WGM01);
			CLR_BIT(TCCR0,WGM00);
			THREE_BITS_WRITE(TCCR0,CS00,OS_T0_PRESCALER_8);		
			SET_BIT(TIMSK,OCIE0); 				
		}
		else
		{
			/*Do Nothing*/
		}
	#endif
	
	#if OS_TIMER_1		
		switch(gstr_OS_SchedulerCfg.u8_OS_TimerResolution)
		{
			case OS_TIMER_RESOLUATION_5U:
				REG_WRITE(OCR1A,OS_RES_5U_PRESCALER_8);
				break;	
			case OS_TIMER_RESOLUATION_10U:
				REG_WRITE(OCR1A,OS_RES_10U_PRESCALER_8);
				break;
			case OS_TIMER_RESOLUATION_20U:
				REG_WRITE(OCR1A,OS_RES_20U_PRESCALER_8);
				break;
			default:
				u8_ErrorState=OS_UNSUPPORTED_RESOLUTION;
				break;
		}
		if(ERROR_OK==u8_ErrorState)
		{
			/*SET THE MODE TO CTC*/
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);				
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			/*SET THE PRESCALER TO 8*/
			THREE_BITS_WRITE(TCCR1B,CS10,OS_T1_PRESCALER_8);
			/*ENABLE CTC MODE INTERRUPT*/				
			SET_BIT(TIMSK,OCIE1A); 	
				 
		}
		else
		{
			/*Do Nothing*/
		}
	#endif
	
	#if OS_TIMER_2
		switch(gstr_OS_SchedulerCfg.u8_OS_TimerResolution)
		{
			case OS_TIMER_RESOLUATION_5U:
				REG_WRITE(OCR2,OS_RES_5U_PRESCALER_8);
				break;	
			case OS_TIMER_RESOLUATION_10U:
				REG_WRITE(OCR2,OS_RES_10U_PRESCALER_8);
				break;
			case OS_TIMER_RESOLUATION_20U:
				REG_WRITE(OCR2,OS_RES_20U_PRESCALER_8);
				break;
			default:
				u8_ErrorState=OS_UNSUPPORTED_RESOLUTION;
				break;
		}
		if(ERROR_OK==u8_ErrorState)
		{
			SET_BIT(TCCR2,WGM21);
			CLR_BIT(TCCR2,WGM20);
			THREE_BITS_WRITE(TCCR2,CS20,OS_T2_PRESCALER_8);		
			SET_BIT(TIMSK,OCIE2); 	
				 
		}
		else
		{
			/*Do Nothing*/
		}
	#endif
	u8_ErrorState=OS_Get(&gpstr_Task);
	gu32_OS_TicksNumber = gstr_OS_SchedulerCfg.u32_OS_TickTime_Us/gstr_OS_SchedulerCfg.u8_OS_TimerResolution;
	return u8_ErrorState;
}

extern void OS_Run(void)
{
	uint8_t u8_TaskCounter;
	OS_Start();
	while(1)
	{	
		for(u8_TaskCounter=ZERO;u8_TaskCounter<OS_TASKS_NUMBER;u8_TaskCounter++)
		{
			if(NULL_PTR==(gpstr_Task[u8_TaskCounter].ptr_OS_TaskCallback))
			{
				continue ;
			}
			else if(OS_TASKREADY==gpstr_Task[u8_TaskCounter].u8_OS_TaskState)
			{
				gpstr_Task[u8_TaskCounter].u8_OS_TaskState=OS_TASKRUNING;
				(gpstr_Task[u8_TaskCounter].ptr_OS_TaskCallback)();
				gu8_OS_ReadyTasksCounter--;
				
				if(ZERO!=gpstr_Task[u8_TaskCounter].u32_OS_TaskPeriodicity)
				{
					if(OS_TASKRUNING==gpstr_Task[u8_TaskCounter].u8_OS_TaskState)
					{
						gpstr_Task[u8_TaskCounter].u8_OS_TaskState=OS_TASKWAIT;						
					}
					else
					{
						/*Do Nothing*/
					}
				}
				else
				{
					OS_DeleteTask((gpstr_Task+u8_TaskCounter));
				}
				break;
			}
			else
			{
				/*Do Nothing*/
			}
		}
		if(ZERO==gu8_OS_ReadyTasksCounter)
		{
			OS_IdealTask();
		}
		else
		{
			/*Do Nothing*/
		}
	}
}

#if OS_TIMER_0
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static volatile uint32_t u32_ISRsCounter=ZERO;
	uint8_t u8_TaskCounter;
	u32_ISRsCounter++;
	if(gu32_OS_TicksNumber==u32_ISRsCounter)
	{
		for(u8_TaskCounter=ZERO;u8_TaskCounter<OS_TASKS_NUMBER;u8_TaskCounter++)
		{
			if(NULL_PTR==gpstr_Task[u8_TaskCounter].ptr_OS_TaskCallback)
			{
				continue ;
			}
			else if((OS_TASKWAIT==gpstr_Task[u8_TaskCounter].u8_OS_TaskState)||(OS_TASKRUNING==gpstr_Task[u8_TaskCounter].u8_OS_TaskState))
			{
				if(ZERO==gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay)
				{
					gpstr_Task[u8_TaskCounter].u8_OS_TaskState=OS_TASKREADY;
					gu8_OS_ReadyTasksCounter++;
					gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay=gpstr_Task[u8_TaskCounter].u32_OS_TaskPeriodicity-1;
				}
				else
				{
					gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay--;
				}
			}
			else
			{
				/*Do Nothing*/
			}
		}
		u32_ISRsCounter=ZERO;
	}
	else
	{
		/*Do Nothing*/
	}
}
#endif

#if OS_TIMER_1
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	static volatile uint32_t u32_ISRsCounter=ZERO;
	uint8_t u8_TaskCounter;
	u32_ISRsCounter++;
	if(gu32_OS_TicksNumber==u32_ISRsCounter)
	{
		for(u8_TaskCounter=ZERO;u8_TaskCounter<OS_TASKS_NUMBER;u8_TaskCounter++)
		{
			if(NULL_PTR==gpstr_Task[u8_TaskCounter].ptr_OS_TaskCallback)
			{
				continue ;
			}
			else if((OS_TASKWAIT==gpstr_Task[u8_TaskCounter].u8_OS_TaskState)||(OS_TASKRUNING==gpstr_Task[u8_TaskCounter].u8_OS_TaskState))
			{
				if(ZERO==gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay)
				{
					gpstr_Task[u8_TaskCounter].u8_OS_TaskState=OS_TASKREADY;
					gu8_OS_ReadyTasksCounter++;
					gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay=gpstr_Task[u8_TaskCounter].u32_OS_TaskPeriodicity-1;
				}
				else
				{
					gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay--;
				}
			}
			else
			{
				/*Do Nothing*/
			}
		}
		u32_ISRsCounter=ZERO;
	}
	else
	{
		/*Do Nothing*/
	}
}
#endif

#if OS_TIMER_2
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	static volatile uint32_t u32_ISRsCounter=ZERO;
	uint8_t u8_TaskCounter;
	u32_ISRsCounter++;
	if(gu32_OS_TicksNumber==u32_ISRsCounter)
	{
		for(u8_TaskCounter=ZERO;u8_TaskCounter<OS_TASKS_NUMBER;u8_TaskCounter++)
		{
			if(NULL_PTR==gpstr_Task[u8_TaskCounter].ptr_OS_TaskCallback)
			{
				continue ;
			}
			else if((OS_TASKWAIT==gpstr_Task[u8_TaskCounter].u8_OS_TaskState)||(OS_TASKRUNING==gpstr_Task[u8_TaskCounter].u8_OS_TaskState))
			{
				if(ZERO==gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay)
				{
					gpstr_Task[u8_TaskCounter].u8_OS_TaskState=OS_TASKREADY;
					gu8_OS_ReadyTasksCounter++;
					gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay=gpstr_Task[u8_TaskCounter].u32_OS_TaskPeriodicity-1;
				}
				else
				{
					gpstr_Task[u8_TaskCounter].u8_OS_TaskDelay--;
				}				
			}
			else
			{
				/*Do Nothing*/
			}
		}
		u32_ISRsCounter=ZERO;
	}
	else
	{
		/*Do Nothing*/
	}   
}
#endif