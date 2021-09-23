/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl.c
 *       Module:  IntCtrl
 *
 *  Description:  source file for IntCtrl module.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "IntCtrl.h"
#include "IntCtrl_Cfg.h"
#include "IntCtrl_Lcfg.h"
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
extern const STR_IntCtrl_config_t STR_IntCtrlConfig;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: IntCtrl_EnableGlobal
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enable Global Interrupts.
************************************************************************************/
void IntCtrl_EnableGlobal(void)
{
    Enable_Interrupts();
}

/************************************************************************************
* Service Name: IntCtrl_DisableGlobal
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disable Global Interrupts.
************************************************************************************/
void IntCtrl_DisableGlobal(void)
{
    Disable_Interrupts();
}

/************************************************************************************
* Service Name: IntCtrl_Init
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: Function Error State
* Description: Initializes the IntCtrl module.
************************************************************************************/
Std_ReturnType IntCtrl_Init(void)
{
    /* Variable to store function error state. */
    Std_ReturnType E_IntCtrl_Init = E_OK;

    /* Validate valid Parameters are passed. */
    if(STD_NOT_INIT != u8_Init)
    {
        /* Set init before error. */
        E_IntCtrl_Init = (E_INTCTRL_ID | E_INTCTRL_INIT_BEFORE);
    }
    else
    {
        /* Set Base Priority. */
        volatile uint8_t u8_BasePRI = (STR_IntCtrlConfig.u8_BasePriority << INT_BASEPRI_START_BIT);
        Set_BasePRI();

        /* Set Group and Subgroup Priorities. */
        APINT |= (INT_APINT_KEY | (STR_IntCtrlConfig.u8_GroupAndSubgroup << INT_PRIGROUP_START_BIT) );

        /* Loop on all Interrupts */
        uint8_t u8_IntCounter;
        for(u8_IntCounter = 0; u8_IntCounter < INT_NUMBERS; u8_IntCounter++)
        {
            /* Set Priority. */

            /* Enable/Disable Interrupt. */
        }

        /* Set initialized flag. */
        u8_Init = STD_INIT;
    }

    /* Return function error state. */
    return E_IntCtrl_Init;
}
