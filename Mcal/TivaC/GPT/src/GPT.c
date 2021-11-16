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

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t u8_Init = STD_NOT_INIT;
static const Gpt_ConfigType * GptConfig;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

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
            switch(ConfigPtr[u8_InitCounter].GptChannelId)
            {
                case GPT_CH0:
                    u32_BaseAddr = GPT0_BASE_ADDRESS;
                    break;
                case GPT_CH1:
                    u32_BaseAddr = GPT1_BASE_ADDRESS;
                    break;
                case GPT_CH2:
                    u32_BaseAddr = GPT2_BASE_ADDRESS;
                    break;
                case GPT_CH3:
                    u32_BaseAddr = GPT3_BASE_ADDRESS;
                    break;
                case GPT_CH4:
                    u32_BaseAddr = GPT4_BASE_ADDRESS;
                    break;
                case GPT_CH5:
                    u32_BaseAddr = GPT5_BASE_ADDRESS;
                    break;
                case GPT_CH6:
                    u32_BaseAddr = WGPT0_BASE_ADDRESS;
                    break;
                case GPT_CH7:
                    u32_BaseAddr = WGPT1_BASE_ADDRESS;
                    break;
                case GPT_CH8:
                    u32_BaseAddr = WGPT2_BASE_ADDRESS;
                    break;
                case GPT_CH9:
                    u32_BaseAddr = WGPT3_BASE_ADDRESS;
                    break;
                case GPT_CH10:
                    u32_BaseAddr = WGPT4_BASE_ADDRESS;
                    break;
                case GPT_CH11:
                    u32_BaseAddr = WGPT5_BASE_ADDRESS;
                    break;
                default:
                    /* Wrong Parameter. */
                    return;
            }

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

        #if(GPT_PREDEF_TIMER_100US_32BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0X7F;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #elif(GPT_PREDEF_TIMER_1US_16BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0xF;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #elif(GPT_PREDEF_TIMER_1US_24BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_CONTINUOUS_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_TAMR_OFFSET)) , GPT_DIR_BIT);
            *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_OFFSET)) = 0XF;
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_STALL_BIT);
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
        #elif(GPT_PREDEF_TIMER_1US_32BIT_EN)
            SET_BIT(*((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_CFG_OFFSET)) , GPT_CFG_NOT_CONCAT_BIT);
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

void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    if(STD_NOT_INIT == u8_Init)
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr;

        switch(Channel)
        {
            case GPT_CH0:
                u32_BaseAddr = GPT0_BASE_ADDRESS;
                break;
            case GPT_CH1:
                u32_BaseAddr = GPT1_BASE_ADDRESS;
                break;
            case GPT_CH2:
                u32_BaseAddr = GPT2_BASE_ADDRESS;
                break;
            case GPT_CH3:
                u32_BaseAddr = GPT3_BASE_ADDRESS;
                break;
            case GPT_CH4:
                u32_BaseAddr = GPT4_BASE_ADDRESS;
                break;
            case GPT_CH5:
                u32_BaseAddr = GPT5_BASE_ADDRESS;
                break;
            case GPT_CH6:
                u32_BaseAddr = WGPT0_BASE_ADDRESS;
                break;
            case GPT_CH7:
                u32_BaseAddr = WGPT1_BASE_ADDRESS;
                break;
            case GPT_CH8:
                u32_BaseAddr = WGPT2_BASE_ADDRESS;
                break;
            case GPT_CH9:
                u32_BaseAddr = WGPT3_BASE_ADDRESS;
                break;
            case GPT_CH10:
                u32_BaseAddr = WGPT4_BASE_ADDRESS;
                break;
            case GPT_CH11:
                u32_BaseAddr = WGPT5_BASE_ADDRESS;
                break;
            default:
                /* Wrong Parameter. */
                return;
        }
        CLEAR_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_IMR_OFFSET)) , GPT_INT_EN_BIT);
    }
}

void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    if(STD_NOT_INIT == u8_Init)
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr;

        switch(Channel)
        {
            case GPT_CH0:
                u32_BaseAddr = GPT0_BASE_ADDRESS;
                break;
            case GPT_CH1:
                u32_BaseAddr = GPT1_BASE_ADDRESS;
                break;
            case GPT_CH2:
                u32_BaseAddr = GPT2_BASE_ADDRESS;
                break;
            case GPT_CH3:
                u32_BaseAddr = GPT3_BASE_ADDRESS;
                break;
            case GPT_CH4:
                u32_BaseAddr = GPT4_BASE_ADDRESS;
                break;
            case GPT_CH5:
                u32_BaseAddr = GPT5_BASE_ADDRESS;
                break;
            case GPT_CH6:
                u32_BaseAddr = WGPT0_BASE_ADDRESS;
                break;
            case GPT_CH7:
                u32_BaseAddr = WGPT1_BASE_ADDRESS;
                break;
            case GPT_CH8:
                u32_BaseAddr = WGPT2_BASE_ADDRESS;
                break;
            case GPT_CH9:
                u32_BaseAddr = WGPT3_BASE_ADDRESS;
                break;
            case GPT_CH10:
                u32_BaseAddr = WGPT4_BASE_ADDRESS;
                break;
            case GPT_CH11:
                u32_BaseAddr = WGPT5_BASE_ADDRESS;
                break;
            default:
                /* Wrong Parameter. */
                return;
        }
        SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_IMR_OFFSET)) , GPT_INT_EN_BIT);
    }
}

void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    if((STD_NOT_INIT == u8_Init) && (GPT_INVALID_CH > Value))
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr;

        switch(Channel)
        {
            case GPT_CH0:
                u32_BaseAddr = GPT0_BASE_ADDRESS;
                break;
            case GPT_CH1:
                u32_BaseAddr = GPT1_BASE_ADDRESS;
                break;
            case GPT_CH2:
                u32_BaseAddr = GPT2_BASE_ADDRESS;
                break;
            case GPT_CH3:
                u32_BaseAddr = GPT3_BASE_ADDRESS;
                break;
            case GPT_CH4:
                u32_BaseAddr = GPT4_BASE_ADDRESS;
                break;
            case GPT_CH5:
                u32_BaseAddr = GPT5_BASE_ADDRESS;
                break;
            case GPT_CH6:
                u32_BaseAddr = WGPT0_BASE_ADDRESS;
                break;
            case GPT_CH7:
                u32_BaseAddr = WGPT1_BASE_ADDRESS;
                break;
            case GPT_CH8:
                u32_BaseAddr = WGPT2_BASE_ADDRESS;
                break;
            case GPT_CH9:
                u32_BaseAddr = WGPT3_BASE_ADDRESS;
                break;
            case GPT_CH10:
                u32_BaseAddr = WGPT4_BASE_ADDRESS;
                break;
            case GPT_CH11:
                u32_BaseAddr = WGPT5_BASE_ADDRESS;
                break;
            default:
                /* Wrong Parameter. */
                return;
        }
        /* TODO: Set Value */
        *((volatile uint32_t *)(u32_BaseAddr + GPT_LOAD_OFFSET)) = Value;

        /* Start GPT. */
        SET_BIT(*((volatile uint32_t *)(u32_BaseAddr + GPT_CTL_OFFSET)) , GPT_CTL_EN_BIT);
    }
}

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
        case GPT_PREDEF_TIMER_100US_32BIT:
            #if(GPT_PREDEF_TIMER_100US_32BIT_EN)
                *TimeValuePtr = *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_VAL_OFFSET)) >> 11;
                *TimeValuePtr |= *((volatile uint32_t *)(WGPT5_BASE_ADDRESS + GPT_PRESCALER_VAL_OFFSET)) << 21;
                ErrorState = E_OK;
            #else
                ErrorState = E_NOK;
            #endif
            break;
        default:
            ErrorState = E_NOK;
            break;
        }
    }

    return ErrorState;
}

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

