/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Comm_Lcfg.h
 *       Module:  Comm
 *
 *  Description:  header file for Comm module linking configurations.
 *  
 *********************************************************************************************************************/
#ifndef __COMM_LCFG_H__
#define __COMM_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/*- CONSTANTS ----------------------------------------------*/

/*- ERRORS DEFINITIONS--------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef struct CommMessage
{
    uint8_t size;
    signed char string[25];
}CommMessage;

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __COMM_LCFG_H__ */
