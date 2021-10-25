/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Toggle.h
 *       Module:  Toggle
 *
 *  Description:  header file for Toggle module.    
 *  
 *********************************************************************************************************************/
#ifndef __Toggle_H__
#define __Toggle_H__

/*- INCLUDES -----------------------------------------------*/
/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "GPIO.h"

/*- CONSTANTS ----------------------------------------------*/

/*- ERRORS DEFINITIONS--------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Creates the toggle task. */
extern void Toggle_Task_Create( void );

/* Toggle Task */
extern void Toggle_Task( void * pvParameters );

#endif  /* __Toggle_H__ */
