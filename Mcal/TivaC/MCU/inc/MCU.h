/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MCU.h
 *       Module:  MCU
 *
 *  Description:  header file for MCU module.
 *
 *********************************************************************************************************************/
#ifndef __MCU_H__
#define __MCU_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
/* Errors Definitions */

/**
* @brief: Module ID.
*/
#define           E_MCU_ID                      (Std_ReturnType)( 0x20 )

/**
* @brief: This return value indicate that the configurations have an
* invalid value.
*/
#define           E_MCU_INVALID_CONFIG          (Std_ReturnType)( 1 )

/**
* @brief: This return value indicate that the module was
* initialized before.
*/
#define           E_MCU_INIT_BEFORE             (Std_ReturnType)( 2 )

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize module. */
extern Std_ReturnType MCU_Init(void);

#endif  /* __MCU_H__ */
