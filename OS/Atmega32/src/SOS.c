/*
 * SOS.c
 *
 * Created: 8/28/2021 3:22:02 PM
 * Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Interrupt_Design_Pattern.h"
#include "MC_REGISTERS.h"
#include "BIT_MATH.h"
#include "SOS.h"

/*- LOCAL MACROS
------------------------------------------*/
#define  SECOND_TO_MICROSECOND      (uint32_t)( 1000000 )
#define  SYSTICK_OVERFLOW_FACTOR    (uint16_t)( 256 )
#define  IDLE_TASK                  (uint8_t)(255)
#define  SLEEP_ENABLE               (uint8_t)(0x80)
#define  SLEEP_BITS_MASK            (uint8_t)(0x70)
#define  IDLE_MODE                  (uint8_t)(0x00)

#define  CALCULATE_CPU_LOAD         (1)

#if CALCULATE_CPU_LOAD
   #define  CPU_IDLE                (uint8_t)(0)
   #define  CPU_WORKING             (uint8_t)(1)  
   #define  CPU_CALCULATION_WINDOW  (uint64_t)(200)      
#endif

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
#if CALCULATE_CPU_LOAD
   void TransmitCPULoad(void);
#endif
void Systick_ISR(void);
static void Idle_Task(void);
static void SOS_UpdateStates(void);
static ERROR_STATE_t GetFreqPrescaleRatio(float32_t * Ratio);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static STR_Task_t gastr_Tasks[MAX_TASKS_NUMBER];
static uint8_t gu8_CreatedTasks = 0;
static uint64_t gu64_Ticks = 1;
static uint64_t gu64_SYSTICK_OverflowsNeeded = 0;
static uint64_t gu64_SYSTICK_Overflows = 0;

#if CALCULATE_CPU_LOAD
   static uint8_t CPU_State = CPU_IDLE;
   static uint64_t CPU_IdleTime = 0;
   static uint64_t CPU_WorkingTime = 0;
   static uint8_t CPU_Load = 0;
#endif

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_SYSTICK_config_t gstr_SYSTICK_Config;
extern const uint16_t gu16_TICK_Interval;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
#if CALCULATE_CPU_LOAD
   #include "UART.h"
   void TransmitCPULoad(void)
   {
      UART_Init(UART_CH_0);
      CPU_Load = (uint8_t)((CPU_WorkingTime*1.0)/(CPU_IdleTime+CPU_WorkingTime) * 100);
      UART_TransmitChar(UART_CH_0, CPU_Load);
      while(1)
      {
         
      }
   }
#endif

/**
* @brief: This function is ISR of the Systick.
*/
void Systick_ISR(void)
{
   #if CALCULATE_CPU_LOAD
      /* Increment Idle and Working Overflows */
      if(CPU_IDLE == CPU_State)
      {
         CPU_IdleTime++;
      }
      else
      {
         CPU_WorkingTime++;
      }
   #endif
   /* Increment overflows */
   gu64_SYSTICK_Overflows++;
   /* If overflows is equal to the Tick */
   if(gu64_SYSTICK_Overflows == gu64_SYSTICK_OverflowsNeeded)
   {
      /* Set Overflows to zero. */
      gu64_SYSTICK_Overflows = 0;
      /* Increment system ticks. */
      gu64_Ticks++;
      #if CALCULATE_CPU_LOAD
         /* Transmit CPU load when Ticks is equal to the Calculation Window. */
         if(CPU_CALCULATION_WINDOW <= gu64_Ticks)
         {
            TransmitCPULoad();
         }
      #endif
      /* Update The Tasks States after each system tick. */
      SOS_UpdateStates();
   }
}

/**
* @brief: This function is the idle routine when no tasks are running.
*/
static void Idle_Task(void)
{
   #if CALCULATE_CPU_LOAD
      /* Set CPU state to idle. */
      CPU_State = CPU_IDLE;
   #endif
   /* Enable Sleep Mode. */
}

/**
* @brief: This function Updates the tasks states.
*/
static void SOS_UpdateStates(void)
{
   /* Loops on all tasks. */
   for(uint8_t u8_TaskCounter = 0; u8_TaskCounter< gu8_CreatedTasks; u8_TaskCounter++)
   {
      /* If a task is waiting and it's time to run. */
      if((SOS_TASK_WAITING == gastr_Tasks[u8_TaskCounter].u8_State) && (gu64_Ticks%gastr_Tasks[u8_TaskCounter].u16_Periodicity == 0))
      {
         /* Set state to ready. */
         gastr_Tasks[u8_TaskCounter].u8_State = SOS_TASK_READY;
      }
   }
}

/**
* @brief: This function Calculate division ratio for 1 microsecond.
*
* @param [in]  Ratio    -  Ratio between CPU clock frequency and Prescalar values.
*
* @return function error state.
*/
static ERROR_STATE_t GetFreqPrescaleRatio(float32_t * Ratio)
{
   ERROR_STATE_t FreqRatio_ErrorState = ERROR_OK;
   switch(gstr_SYSTICK_Config.u8_prescale)
   {
      case CLK_NO_PRESCALE:
         *Ratio = 1.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      case CLK_8_PRESCALE:
         *Ratio = 8.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      case CLK_32_PRESCALE:
         *Ratio = 32.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      case CLK_64_PRESCALE:
         *Ratio = 64.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      case CLK_128_PRESCALE:
         *Ratio = 128.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      case CLK_256_PRESCALE:
         *Ratio = 256.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      case CLK_1024_PRESCALE:
         *Ratio = 1024.0 * SECOND_TO_MICROSECOND / F_CPU;
         break;
      default:
         FreqRatio_ErrorState = (SOS_MODULE_ID | E_UNSUPPORTED_PRESCALE);
         break;
   }
   
   return FreqRatio_ErrorState;
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/**
* @brief: This function Initialize the os.
*/
void SOS_Init(void)
{
   ERROR_STATE_t Init_ErrorState;
   
   /* Initialize Timer Mode */
   TCCR2 = gstr_SYSTICK_Config.u8_mode;
   /* Initialize Interrupt Mode */
   TIMSK &= ~(SYSTICK_OVERFLOW_INTERRUPT | SYSTICK_COMPARE_INTERRUPT);
   TIMSK |= gstr_SYSTICK_Config.u8_interrupt_mode;
   
   /* Calculate needed frequency Ratio */
   float32_t f32_FreqRatio;
   Init_ErrorState = GetFreqPrescaleRatio(&f32_FreqRatio);
   if(ERROR_OK == Init_ErrorState)
   {
      uint16_t u16_Delay = gu16_TICK_Interval;
      if(f32_FreqRatio != 0)
      {
         u16_Delay /= f32_FreqRatio;
      }
      
      /* Calculate how many overflows needed */
      gu64_SYSTICK_OverflowsNeeded = u16_Delay / SYSTICK_OVERFLOW_FACTOR;
   }
   
   /* Install ISR */
   Interrupt_Install(TIMER2_OVF_VECTOR_NUMBER, Systick_ISR);
   
   /* Enable Global interrupts. */
   INTERRUPTS_Enable();
}

/**
* @brief: This function is the schedular of the OS.
*/
void SOS_Run(void)
{
   /* Start the OS clock. */
   TCCR2 |= gstr_SYSTICK_Config.u8_prescale;
   
   /* Updates Task states before running. */
   SOS_UpdateStates();
   
   while(1)
   {
      /* Variables to store the next running task. */
      uint8_t u8_TaskID = IDLE_TASK;
      uint8_t u8_TaskPriority = MAX_TASK_PRIORTITY;
      
      /* Loop on all tasks */
      for(uint8_t u8_TaskCounter = 0; u8_TaskCounter< gu8_CreatedTasks; u8_TaskCounter++)
      {
         /* If the task is ready and lower priority. */
         if((SOS_TASK_READY == gastr_Tasks[u8_TaskCounter].u8_State) && (u8_TaskPriority > gastr_Tasks[u8_TaskCounter].u8_Priority) )
         {
            /* Set the task id and it's priority. */
            u8_TaskID = u8_TaskCounter;
            u8_TaskPriority = gastr_Tasks[u8_TaskCounter].u8_Priority;
         }
      }
      
      /* If a Task is selected. */
      if(IDLE_TASK != u8_TaskID)
      {
         /* Change its state to running. */
         gastr_Tasks[u8_TaskID].u8_State = SOS_TASK_RUNNING;
         #if CALCULATE_CPU_LOAD
            /* Set CPU state to working. */
            CPU_State = CPU_WORKING;
         #endif
         /* Run Task. */
         gastr_Tasks[u8_TaskID].ptr_Task();
         /* Set State waiting. */
         gastr_Tasks[u8_TaskID].u8_State = SOS_TASK_WAITING;
      }
      /* If No task is selected. */
      else
      {
         /* Run Idle Task */
         Idle_Task();
      }
   }
}

/**
* @brief: This function Creates a Task.
*
* @param [in]  Task        -  Pointer to the task function.
* @param [in]  Priority    -  Priority of the Task.
* @param [in]  Periodicity -  Periodicity of the task.
* @param [out] Handler     -  Handler of the task.
*
* @return function error state.
*/
ERROR_STATE_t SOS_CreateTask(Ptr_VoidFuncVoid_t Task, uint8_t Priority, uint16_t Periodicity, STR_TaskHandler_t * Handler)
{
   /* variable to store function error state. */
   ERROR_STATE_t Create_ErrorState;
   
   /* Check if Max tasks are created. */
   if(gu8_CreatedTasks == (MAX_TASKS_NUMBER))
   {
      /* Set Function Error State To Full Task. */
      Create_ErrorState = (SOS_MODULE_ID | E_TASKS_FULL);
   }
   /* Validate valid pointer to task. */
   else if(NULL_PTR == Task)
   {
      /* Set Function Error State To Null Pointer. */
      Create_ErrorState = (SOS_MODULE_ID | E_NULL_PTR);
   }
   /* Validate Valid priority. */
   else if(MAX_TASK_PRIORTITY < Priority)
   {
      /* Set Function Error State To Invalid Priority. */
      Create_ErrorState = (SOS_MODULE_ID | E_INVALID_PRIORITY);
   }
   else
   {
      /* Initialize Task data. */
      gastr_Tasks[gu8_CreatedTasks].u8_State = SOS_TASK_WAITING;
      gastr_Tasks[gu8_CreatedTasks].u8_Priority = Priority;
      gastr_Tasks[gu8_CreatedTasks].u16_Periodicity = Periodicity;
      gastr_Tasks[gu8_CreatedTasks].ptr_Task = Task;
      
      /* If handler is given. */
      if(NULL_PTR != Handler)
      {
         /* Set Handler Data. */
         Handler->u8_ID = gu8_CreatedTasks;
      }
      else
      {
         /* Do Nothing */
      }
      /* Increment created tasks. */
      gu8_CreatedTasks++;
      Create_ErrorState = ERROR_OK;
   }
   
   /* Return Function error state. */
   return Create_ErrorState;
}

/**
* @brief: This function Deletes a Task.
*
* @param [out] TaskHandler -  Handler of the task.
*
* @return function error state.
*/
ERROR_STATE_t SOS_DeleteTask(STR_TaskHandler_t * TaskHandler)
{
   /* variable to store function error state. */
   ERROR_STATE_t Delete_ErrorState;
   
   /* Validate valid Task Handler. */
   if(NULL_PTR == TaskHandler)
   {
      /* Set Function Error State To Null Pointer. */
      Delete_ErrorState = (SOS_MODULE_ID | E_NULL_PTR);
   }
   else if((gu8_CreatedTasks-1) < TaskHandler->u8_ID)
   {
      /* Set Function Error State To Invalid ID. */
      Delete_ErrorState = (SOS_MODULE_ID | E_INVALID_ID);
   }
   else
   {
      /* Replace Task Data with the Last Task Data. */
      gastr_Tasks[TaskHandler->u8_ID] = gastr_Tasks[gu8_CreatedTasks-1];
      /* Decrement Task Numbers */
      gu8_CreatedTasks--;
      /* Delete Task Handler Data. */
      TaskHandler->u8_ID = MAX_TASKS_NUMBER;
      /* Set Function Error State To Ok. */
      Delete_ErrorState = ERROR_OK;
   }
   
   /* Return Function error state. */
   return Delete_ErrorState;
}

/**
* @brief: This function Suspends a Task.
*
* @param [out] TaskHandler -  Handler of the task.
*
* @return function error state.
*/
ERROR_STATE_t SOS_SuspendTask(STR_TaskHandler_t * TaskHandler)
{
   /* variable to store function error state. */
   ERROR_STATE_t Suspend_ErrorState;
   
   /* Validate valid Task Handler. */
   if(NULL_PTR == TaskHandler)
   {
      /* Set Function Error State To Null Pointer. */
      Suspend_ErrorState = (SOS_MODULE_ID | E_NULL_PTR);
   }
   else if((gu8_CreatedTasks-1) < TaskHandler->u8_ID)
   {
      /* Set Function Error State To Invalid ID. */
      Suspend_ErrorState = (SOS_MODULE_ID | E_INVALID_ID);
   }
   else
   {
      /* Set Task State to suspended. */
      gastr_Tasks[TaskHandler->u8_ID].u8_State = SOS_TASK_SUSPENDED;
      /* Set Function Error State To Ok. */
      Suspend_ErrorState = ERROR_OK;
   }
   
   /* Return Function error state. */
   return Suspend_ErrorState;
}

/**
* @brief: This function Unsuspend a Task.
*
* @param [out] TaskHandler -  Handler of the task.
*
* @return function error state.
*/
ERROR_STATE_t SOS_UnsuspendTask(STR_TaskHandler_t * TaskHandler)
{
   /* variable to store function error state. */
   ERROR_STATE_t Unsuspend_ErrorState;
   
   /* Validate valid Task Handler. */
   if(NULL_PTR == TaskHandler)
   {
      /* Set Function Error State To Null Pointer. */
      Unsuspend_ErrorState = (SOS_MODULE_ID | E_NULL_PTR);
   }
   else if((gu8_CreatedTasks-1) < TaskHandler->u8_ID)
   {
      /* Set Function Error State To Invalid ID. */
      Unsuspend_ErrorState = (SOS_MODULE_ID | E_INVALID_ID);
   }
   else
   {
      /* Set Task State to waiting. */
      gastr_Tasks[TaskHandler->u8_ID].u8_State = SOS_TASK_WAITING;
      /* Set Function Error State To Ok. */
      Unsuspend_ErrorState = ERROR_OK;
   }
   
   /* Return Function error state. */
   return Unsuspend_ErrorState;
}