/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  WDT.c
 *       Module:  WDT
 *
 *  Description:  source file for WDT module.
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "WDT.h"
#include "WDT_Cfg.h"
#include "WDT_Lcfg.h"
#include "Bit_Math.h"
#include "Mcu_Hw.h"

/*- LOCAL MACROS
------------------------------------------*/
#define TICKS_1_MS          (uint32_t)(16000)
#define WDT_LOCK_VAL        (uint32_t)(0x1A1A1A1A)
#define WDT_UNLOCK_VAL      (uint32_t)(0x1ACCE551)

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static uint32_t WDT_GetTicks(uint16_t Time);
static void WDT_WrtieComplete(void);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t u8_Init = STD_NOT_INIT;
static uint16_t u16_MaxTimeout;
static Ptr_VoidFuncVoid_t CallBack = NULL_PTR;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Service Name: WDT_GetTicks
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Time - Time in Ms.
* Parameters (inout): None
* Parameters (out): None
* Return value: Ticks needed to reach that time.
* Description: Calculate the needed ticks for a given time.
************************************************************************************/
static uint32_t WDT_GetTicks(uint16_t Time)
{
    return (Time*TICKS_1_MS);
}

/************************************************************************************
* Service Name: WDT_WrtieComplete
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Wait until WDT write in Ctrl reg is complete.
************************************************************************************/
static void WDT_WrtieComplete(void)
{
    while(!BIT_IS_SET(WDT1_CTL, WDT_WRITE_COMPLETE_BIT));
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Wdg_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Struct containing WDT configurations.
* Parameters (inout): None
* Parameters (out): None
* Return value: Function Error State (E_OK or E_NOK)
* Description: Initializes the WDT module.
************************************************************************************/
Std_ReturnType Wdg_Init(const Wdg_ConfigType * ConfigPtr)
{
    /* Variable to store function error state. */
    Std_ReturnType E_WDT_Init;

    /* Validate valid Parameters are passed. */
    if(STD_NOT_INIT != u8_Init)
    {
        /* Set init before error. */
        E_WDT_Init = (E_WDT_ID | E_WDT_INIT_BEFORE);
    }
    else if(NULL_PTR == ConfigPtr)
    {
        /* Set null pointer error. */
        E_WDT_Init = (E_WDT_ID | E_WDT_NULL_POINTER);
    }
    else
    {
        /* Set error ok. */
        E_WDT_Init = E_OK;

        /* Wait for write complete. */
        WDT_WrtieComplete();

        /* Set WDT Initial value. */
        WDT1_LOAD = WDT_GetTicks(ConfigPtr->u16_WdgInitialTimeout);

        /* Wait for write complete. */
        WDT_WrtieComplete();

        /* Set Max Timeout. */
        u16_MaxTimeout = ConfigPtr->u16_WdgMaxTimeout;

        /* Set Interrupt Type. */
        if(WDT_INT_NMI_TYPE == ConfigPtr->u8_InterruptType)
        {
            SET_BIT(WDT1_CTL, WDT_INT_NMI_BIT);
        }
        else if(WDT_INT_STD_TYPE == ConfigPtr->u8_InterruptType)
        {
            CLEAR_BIT(WDT1_CTL, WDT_INT_NMI_BIT);
        }
        else
        {
            /* Set invalid value error. */
            E_WDT_Init = (E_WDT_ID | E_WDT_INVALID_VALUE);
        }

        /* Wait for write complete. */
        WDT_WrtieComplete();

        /* Set Reset Enable. */
        SET_BIT(WDT1_CTL, WDT_RESET_EN_BIT);

        /* Wait for write complete. */
        WDT_WrtieComplete();

        /* Set Notification Function */
        if(NULL_PTR != ConfigPtr->NotificationEN)
        {
            CallBack = ConfigPtr->NotificationEN;
        }

        /* Set WDT Stall */
        SET_BIT(WDT1_TEST, WDT_STALL_BIT);
        /* Wait for write complete. */
        WDT_WrtieComplete();

        /* Start WDT */
        SET_BIT(WDT1_CTL, WDT_ENABLE_BIT);
        /* Wait for write complete. */
        WDT_WrtieComplete();
        /* Set initialized flag. */
        u8_Init = STD_INIT;
    }

    return E_WDT_Init;
}

/************************************************************************************
* Service Name: Wdg_SetTriggerCondition
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): timeout - Update value of WDT in Ms.
* Parameters (inout): None
* Parameters (out): None
* Return value: Function Error State (E_OK or E_NOK)
* Description: Update the WDT value.
************************************************************************************/
Std_ReturnType Wdg_SetTriggerCondition(uint16_t timeout)
{
    /* Variable to store function error state. */
    Std_ReturnType E_WDT_Trig;

    /* Validate valid Parameters are passed. */
    if(timeout > u16_MaxTimeout)
    {
        /* Set invalid value error. */
        E_WDT_Trig = (E_WDT_ID | E_WDT_INVALID_VALUE);
    }
    else
    {
        /* Set new Value. */
        WDT1_LOAD = WDT_GetTicks(timeout);
        /* Wait for write complete. */
        WDT_WrtieComplete();
        /* Set error ok. */
        E_WDT_Trig = E_OK;
    }

    return E_WDT_Trig;
}

/************************************************************************************
* Service Name: WDT_ISR
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: WDT ISR Function.
************************************************************************************/
void WDT_ISR(void)
{
    /* Clear Interrupt State */
    WDT1_ICR = 1;

    /* Call Notification function if set. */
    if(NULL_PTR != CallBack)
    {
        CallBack();
    }
}
