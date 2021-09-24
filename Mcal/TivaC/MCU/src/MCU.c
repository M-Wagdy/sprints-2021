/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MCU.c
 *       Module:  MCU
 *
 *  Description:  source file for MCU module.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "MCU.h"
#include "MCU_Cfg.h"
#include "MCU_Lcfg.h"
#include "Mcu_Hw.h"

/*- LOCAL MACROS
------------------------------------------*/

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t u8_Init = STD_NOT_INIT;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const STR_MCU_config_t STR_MCUConfig;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/

/************************************************************************************
* Service Name: MCU_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Function Error State
* Description: Initializes the MCU module.
************************************************************************************/
Std_ReturnType MCU_Init(void)
{
    /* Variable to store function error state. */
    Std_ReturnType E_MCU_Init;

    /* Validate valid Parameters are passed. */
    if(STD_NOT_INIT != u8_Init)
    {
        /* Set init before error. */
        E_MCU_Init = (E_MCU_ID | E_MCU_INIT_BEFORE);
    }
    else if(
            (SYSDIV_INVALID <= STR_MCUConfig.u8_SYSDIV) || (USESYSDIV_INVALID <= STR_MCUConfig.u8_USESYSDIV) ||
            (OSCSRC_INVALID_VAL <= STR_MCUConfig.u8_OSCSRC) || (MOSC_INVALID <= STR_MCUConfig.u8_MOSCDIS) ||
            (XTAL_MAX_VAL < STR_MCUConfig.u8_XTAL) || (XTAL_MIN_VAL > STR_MCUConfig.u8_XTAL)
            )
    {
        /* Set invalid config error. */
        E_MCU_Init = (E_MCU_ID | E_MCU_INVALID_CONFIG);
    }
    else
    {
        uint32_t u32_RCCVal = SYSCTL_RCC;

        /* Clear Temp RCC Configurations */
        u32_RCCVal &= ~(MOSCDIS_MASK<<MOSCDIS_START_BIT);
        u32_RCCVal &= ~(OSCSRC_MASK<<OSCSRC_START_BIT);
        u32_RCCVal &= ~(XTAL_MASK<<XTAL_START_BIT);
        u32_RCCVal &= ~(USESYSDIV_MASK << USESYSDIV_START_BIT);
        u32_RCCVal &= ~(SYSDIV_MASK << SYSDIV_START_BIT);

        /* Configure Temp RCC */
        u32_RCCVal |= (
                (STR_MCUConfig.u8_SYSDIV << SYSDIV_START_BIT) | (STR_MCUConfig.u8_USESYSDIV << USESYSDIV_START_BIT) |
                (STR_MCUConfig.u8_OSCSRC << OSCSRC_START_BIT) | (STR_MCUConfig.u8_MOSCDIS << MOSCDIS_START_BIT) |
                (STR_MCUConfig.u8_XTAL << XTAL_START_BIT)
            );

        /* Set Required Value to RCC Register */
        SYSCTL_RCC = u32_RCCVal;

        /* Set initialized flag. */
        u8_Init = STD_INIT;

        /* Set error ok value. */
        E_MCU_Init = E_OK;
    }

    /* Return function error state. */
    return E_MCU_Init;
}
