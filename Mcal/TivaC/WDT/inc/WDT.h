/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  WDT.h
 *       Module:  WDT
 *
 *  Description:  header file for WDT module.
 *  
 *********************************************************************************************************************/
#ifndef __WDT_H__
#define __WDT_H__

/*- INCLUDES -----------------------------------------------*/
#include "WDT_Lcfg.h"
#include "Std_Types.h"

/*- CONSTANTS ----------------------------------------------*/
/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: Module ID.
*/
#define           E_WDT_ID                      (Std_ReturnType)( 0x00 )


/**
* @brief: This return value indicate that a function got an
* invalid value.
*/
#define           E_WDT_INVALID_VALUE           (Std_ReturnType)( 1 )

/**
* @brief: This return value indicate that the module was
* initialized before.
*/
#define           E_WDT_INIT_BEFORE             (Std_ReturnType)( 2 )

/**
* @brief: This return value indicate that the module got
* an uninitialized pointer.
*/
#define           E_WDT_NULL_POINTER            (Std_ReturnType)( 2 )

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/* Initializes the WDT module. */
extern Std_ReturnType Wdg_Init(const Wdg_ConfigType * ConfigPtr);

/* Update the WDT value */
extern Std_ReturnType Wdg_SetTriggerCondition(uint16_t timeout);

#endif  /* __WDT_H__ */
