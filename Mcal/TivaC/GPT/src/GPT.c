/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT.c
 *       Module:  GPT
 *
 *  Description:  source file for GPT module.
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "GPT.h"
#include "GPT_Cfg.h"
#include "GPT_Lcfg.h"
#include "Bit_Math.h"
#include "Mcu_Hw.h"

/*- LOCAL MACROS
------------------------------------------*/

/*- LOCAL Dataypes
----------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static uint32_t Gpt_GetChannelBaseAddr(Gpt_ChannelType Channel);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t u8_Init = STD_NOT_INIT;
static const Gpt_ConfigType * GptConfig;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Service Name: Gpt_GetChannelBaseAddr
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel - Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Return Register base address of Gpt channel.
************************************************************************************/
static uint32_t Gpt_GetChannelBaseAddr(Gpt_ChannelType Channel)
{
    switch(Channel)
    {
        case GPT_CH0:
            return GPT0_BASE_ADDRESS;
        case GPT_CH1:
            return GPT1_BASE_ADDRESS;
        case GPT_CH2:
            return GPT2_BASE_ADDRESS;
        case GPT_CH3:
            return GPT3_BASE_ADDRESS;
        case GPT_CH4:
            return GPT4_BASE_ADDRESS;
        case GPT_CH5:
            return GPT5_BASE_ADDRESS;
        case GPT_CH6:
            return WGPT0_BASE_ADDRESS;
        case GPT_CH7:
            return WGPT1_BASE_ADDRESS;
        case GPT_CH8:
            return WGPT2_BASE_ADDRESS;
        case GPT_CH9:
            return WGPT3_BASE_ADDRESS;
        case GPT_CH10:
            return WGPT4_BASE_ADDRESS;
        case GPT_CH11:
            return WGPT5_BASE_ADDRESS;
        default:
            return NULL_PTR;
    }
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Gpt_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Struct containing the configuration parameters of GPT channels.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the GPT module and Start Preconfig timers.
************************************************************************************/
void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
    uint32_t u32_BaseAddr;
    /* Validate Module not init before. */
    if(STD_NOT_INIT != u8_Init)
    {
        /* Do Nothing. */
    }
    else
    {
        uint8_t u8_InitCounter;
        for(u8_InitCounter = 0; u8_InitCounter < GPT_CONFIGURED_GPT_CHS; u8_InitCounter++)
        {
            u32_BaseAddr = Gpt_GetChannelBaseAddr(ConfigPtr[u8_InitCounter].GptChannelId);
            /* Set Don't Concatenate timer A & B. */
            SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            /* Set TimerA Mode */
            if(GPT_CH_MODE_ONESHOT == ConfigPtr[u8_InitCounter].ChannelMode)
            {
                SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_TAMR_OFFSET)) , GPT_ONESHOT_BIT);
            }
            else if(GPT_CH_MODE_CONTINUOUS == ConfigPtr[u8_InitCounter].ChannelMode)
            {
                SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            }
            else
            {
                /* Wrong Parameter */
                return;
            }
            /* Set Count Direction Up. */
            SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            /* Enable GPT Stall */
            SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
        }
        /* Save Config Params in static variable */
        GptConfig = ConfigPtr;

        /* Config Predefined Gpt. */
        #if(GPT_PREDEF_TIMER_100US_32BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            CLEAR_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_ONESHOT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0X7FF;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #elif(GPT_PREDEF_TIMER_1US_16BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            CLEAR_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_ONESHOT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0xF;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #elif(GPT_PREDEF_TIMER_1US_24BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            CLEAR_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_ONESHOT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0XF;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #elif(GPT_PREDEF_TIMER_1US_32BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            CLEAR_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_ONESHOT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0XF;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #endif

        /* Set initialized flag. */
        u8_Init = STD_INIT;
    }

    return;
}

/************************************************************************************
* Service Name: Gpt_DisableNotification
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel - Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disable notification of gpt channel.
************************************************************************************/
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    if(STD_NOT_INIT == u8_Init)
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = Gpt_GetChannelBaseAddr(Channel);
        CLEAR_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_IMR_OFFSET)) , GPT_INT_EN_BIT);
    }
}

/************************************************************************************
* Service Name: Gpt_EnableNotification
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel - Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enable notification of gpt channel.
************************************************************************************/
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    if(STD_NOT_INIT == u8_Init)
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = Gpt_GetChannelBaseAddr(Channel);
        SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_IMR_OFFSET)) , GPT_INT_EN_BIT);
    }
}

/************************************************************************************
* Service Name: Gpt_StartTimer
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel  - Gpt Channel ID.
*                  Value    - Tick Value.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Start Gpt Channel.
************************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    if((STD_NOT_INIT == u8_Init) || (GPT_INVALID_CH < Channel))
    {
        /* Do Nothing. */
    }
    else if(GptConfig[Channel].GptChannelTickValueMax < Value)
    {
        /* Do nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = Gpt_GetChannelBaseAddr(Channel);
        if(Channel < GPT_CH6)
        {
            /* Shift load value with respect to prescaler. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) = (Value << GptConfig[Channel].GptGptChannelTickFrequency) & 0xFFFF;
            /* Set the rest of the value in prescaler. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_OFFSET)) = ((Value << GptConfig[Channel].GptGptChannelTickFrequency) & 0xFF0000 ) >> 16;
        }
        else
        {
            /* Shift value with respect to prescaler. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) = (Value << GptConfig[Channel].GptGptChannelTickFrequency) & 0xFFFFFFFF;
            /* Set the rest of the value in prescaler. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_OFFSET)) = ((Value << GptConfig[Channel].GptGptChannelTickFrequency) & 0xFFFF00000000 ) >> 32;
        }
        /* Start GPT. */
        SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
    }
}

/************************************************************************************
* Service Name: Gpt_StopTimer
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel  - Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stop Gpt Channel.
************************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel)
{
    if((STD_NOT_INIT == u8_Init) || (GPT_INVALID_CH < Channel))
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = Gpt_GetChannelBaseAddr(Channel);
        /* Stop GPT. */
        CLEAR_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        if(Channel < GPT_CH6)
        {
            /* Clear Load Value. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) &= ~(0xFFFF);
            /* Clear Prescaler extension value. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_OFFSET)) &= ~(0xFF);
        }
        else
        {
            /* Clear Load Value. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) &= ~(0xFFFFFFFF);
            /* Clear Prescaler extension value. */
            *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_OFFSET)) &= ~(0xFFFF);
        }
    }
}

/************************************************************************************
* Service Name: Gpt_GetTimeElapsed
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel  - Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: Time Elapsed value in ticks.
* Description: Get time elapsed of a Gpt channel.
************************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
    Gpt_ValueType RetVal;
    if((STD_NOT_INIT == u8_Init) || (GPT_INVALID_CH < Channel))
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = Gpt_GetChannelBaseAddr(Channel);
        if(Channel < GPT_CH6)
        {
            RetVal = ( *((volatile uint32_t *)(u32_BaseAddr + GPT_VAL_OFFSET)) >> GptConfig[Channel].GptGptChannelTickFrequency) & 0xFFFFFF;
        }
        else
        {
            RetVal = ( *((volatile uint32_t *)(u32_BaseAddr + GPT_VAL_OFFSET)) & 0xFFFFFFFF ) >> GptConfig[Channel].GptGptChannelTickFrequency;
            RetVal |= ( *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_VAL_OFFSET)) & 0xFFFF ) << (32 - GptConfig[Channel].GptGptChannelTickFrequency);
        }
    }
    return RetVal;
}

/************************************************************************************
* Service Name: Gpt_GetTimeRemaining
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Channel  - Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: Time Remaining value in ticks.
* Description: Get time remaining of a Gpt channel.
************************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
    Gpt_ValueType RemainingTime, ElapsedTime, TotalTime;
    if((STD_NOT_INIT == u8_Init) || (GPT_INVALID_CH < Channel))
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = Gpt_GetChannelBaseAddr(Channel);
        if(Channel < GPT_CH6)
        {
            ElapsedTime = ( *((volatile uint32_t *)(u32_BaseAddr + GPT_VAL_OFFSET)) >> GptConfig[Channel].GptGptChannelTickFrequency) & 0xFFFFFF;
            TotalTime = ( *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) & 0xFFFF ) >> GptConfig[Channel].GptGptChannelTickFrequency;
            TotalTime |= ( *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_OFFSET)) & 0xFF ) << (16 - GptConfig[Channel].GptGptChannelTickFrequency);

        }
        else
        {
            ElapsedTime = ( *((volatile uint32_t *)(u32_BaseAddr + GPT_VAL_OFFSET)) & 0xFFFFFFFF ) >> GptConfig[Channel].GptGptChannelTickFrequency;
            ElapsedTime |= ( *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_VAL_OFFSET)) & 0xFFFF ) << (32 - GptConfig[Channel].GptGptChannelTickFrequency);
            TotalTime = ( *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) & 0xFFFFFFFF ) >> GptConfig[Channel].GptGptChannelTickFrequency;
            TotalTime |= ( *((volatile uint32_t *)(u32_BaseAddr + GPT_PRESCALER_OFFSET)) & 0xFFFF ) << (32 - GptConfig[Channel].GptGptChannelTickFrequency);
        }
    }

    RemainingTime = TotalTime - ElapsedTime;

    return RemainingTime;
}

/************************************************************************************
* Service Name: Gpt_GetPredefTimerValue
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): PredefTimer  - Predefined Gpt Channel ID.
* Parameters (inout): None
* Parameters (out): TimeValuePtr - Timer Tick Value.
* Return value: Function Error state E_OK/E_NOK.
* Description: Get time elapsed of a predefined Gpt channel.
************************************************************************************/
Std_ReturnType Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32_t* TimeValuePtr)
{
    Std_ReturnType ErrorState;

    if(STD_NOT_INIT == u8_Init)
    {
        ErrorState = E_NOK;
    }
    else
    {
        switch(PredefTimer)
        {
        #if(GPT_PREDEF_TIMER_100US_32BIT_EN)
        case GPT_PREDEF_TIMER_100US_32BIT:
            *TimeValuePtr = *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_VAL_OFFSET)) >> 11;
            *TimeValuePtr |= *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_VAL_OFFSET)) << 21;
            ErrorState = E_OK;
            break;
        #elif(GPT_PREDEF_TIMER_1US_16BIT_EN)
        case GPT_PREDEF_TIMER_1US_16BIT:
            *TimeValuePtr = (*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_VAL_OFFSET)) >> 4) & 0xFFFF;
            ErrorState = E_OK;
            break;
        #elif(GPT_PREDEF_TIMER_1US_24BIT_EN)
        case GPT_PREDEF_TIMER_1US_24BIT:
            *TimeValuePtr = (*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_VAL_OFFSET)) >> 4) & 0xFFFFFF;
            ErrorState = E_OK;
            break;
        #elif(GPT_PREDEF_TIMER_1US_32BIT_EN)
        case GPT_PREDEF_TIMER_1US_32BIT:
            *TimeValuePtr = (*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_VAL_OFFSET)) >> 4) & 0xFFFFFFF;
            *TimeValuePtr |= (*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_VAL_OFFSET)) & 0xF) << 28;
            ErrorState = E_OK;
            break;
        #endif
        default:
            ErrorState = E_NOK;
            break;
        }
    }

    return ErrorState;
}

/* Gpt Channels ISRs. */
void Gpt_Notification_Ch0(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(GPT0_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[0].GptNotification)
    {
        GptConfig[0].GptNotification();
    }
}

void Gpt_Notification_Ch1(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(GPT1_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[1].GptNotification)
    {
        GptConfig[1].GptNotification();
    }
}

void Gpt_Notification_Ch2(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(GPT2_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[2].GptNotification)
    {
        GptConfig[2].GptNotification();
    }
}

void Gpt_Notification_Ch3(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(GPT3_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[3].GptNotification)
    {
        GptConfig[3].GptNotification();
    }
}

void Gpt_Notification_Ch4(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(GPT4_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[4].GptNotification)
    {
        GptConfig[4].GptNotification();
    }
}

void Gpt_Notification_Ch5(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(GPT5_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[5].GptNotification)
    {
        GptConfig[5].GptNotification();
    }
}


void Gpt_Notification_Ch6(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(WGPT0_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[6].GptNotification)
    {
        GptConfig[6].GptNotification();
    }
}

void Gpt_Notification_Ch7(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(WGPT1_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[7].GptNotification)
    {
        GptConfig[7].GptNotification();
    }
}

void Gpt_Notification_Ch8(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(WGPT2_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[8].GptNotification)
    {
        GptConfig[8].GptNotification();
    }
}

void Gpt_Notification_Ch9(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(WGPT3_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[9].GptNotification)
    {
        GptConfig[9].GptNotification();
    }
}

void Gpt_Notification_Ch10(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(WGPT4_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[10].GptNotification)
    {
        GptConfig[10].GptNotification();
    }
}

void Gpt_Notification_Ch11(void)
{
    /* Clear Interrupt Flag */
    SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_ICR_OFFSET)) , GPT_INT_EN_BIT);

    /* Call Notification Function */
    if(NULL_PTR != GptConfig[11].GptNotification)
    {
        GptConfig[11].GptNotification();
    }
}
