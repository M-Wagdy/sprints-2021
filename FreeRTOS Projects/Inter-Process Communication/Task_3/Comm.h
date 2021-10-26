/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Comm.h
 *       Module:  Comm
 *
 *  Description:  header file for Comm module.    
 *  
 *********************************************************************************************************************/
#ifndef __COMM_H__
#define __COMM_H__

/*- INCLUDES -----------------------------------------------*/
/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "Comm_Lcfg.h"

/*- CONSTANTS ----------------------------------------------*/

/*- ERRORS DEFINITIONS--------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Creates the Comm task. */
extern void Comm_Task_Create( void );

/* Comm Task */
extern void Comm_Task( void * pvParameters );

#endif  /* __COMM_H__ */
