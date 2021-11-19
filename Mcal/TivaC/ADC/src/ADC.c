/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ADC.c
 *       Module:  ADC
 *
 *  Description:  source file for ADC module.
 *  
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "ADC.h"
#include "ADC_Cfg.h"
#include "ADC_Lcfg.h"
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
static uint8_t au8_SSCount[4] = {0,0,0,0};
static Adc_ValueGroupType * aSS_Buffer[4] = {NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR};
static Adc_StreamNumSampleType aSS_BufferMaxSize[4] = {0,0,0,0}, aSS_BufferSize[4] = {0,0,0,0};
static Ptr_VoidFuncVoid_t aSS_notification[4] = {NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR};
static uint8_t aSS_EnNotification[4] = {STD_OFF,STD_OFF,STD_OFF,STD_OFF};
static Adc_StreamBufferModeType aSS_BufferMode[4];

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
/************************************************************************************
* Service Name: Adc_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Struct containing the configuration parameters of ADC channels.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the ADC module.
************************************************************************************/
void Adc_Init(const Adc_ConfigType* ConfigPtr)
{
    /* Validate Module not init before. */
    if(STD_NOT_INIT != u8_Init)
    {
        /* Do Nothing. */
    }
    else
    {
        uint32_t u32_BaseAddr = ADC0_BASE_ADDRESS;

        /* Disable all Sample Sequencers. */
        (*(volatile uint32_t *)(u32_BaseAddr + ADC_ACTIVE_OFFSET)) &= ~0xF;


        uint8_t u8_InitCounter;
        for(u8_InitCounter = 0; u8_InitCounter < ADC_CONFIGURED_CHS; u8_InitCounter++)
        {
            /* Configure Trigger Source. */
            if(ADC_TRIGG_SRC_SW == ConfigPtr[u8_InitCounter].AdcGroupTriggSrc)
            {
                /* Configure Conversion Mode */
                if(ADC_CONV_MODE_ONESHOT == ConfigPtr[u8_InitCounter].AdcGroupConversionMode)
                {
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_MUX_OFFSET)) &= ~(0xF << (4*ConfigPtr[u8_InitCounter].AdcGroupId));
                }
                else if(ADC_CONV_MODE_CONTINUOUS == ConfigPtr[u8_InitCounter].AdcGroupConversionMode)
                {
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_MUX_OFFSET)) |= (0xF << (4*ConfigPtr[u8_InitCounter].AdcGroupId));
                }
                else
                {
                    /* Invalid Mode. */
                    return;
                }

            }
            else
            {
                /* Do nothing */
            }

            /* Configure Group priority. */
            (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS_PRI_OFFSET)) &= ~(0x3 << (4*ConfigPtr[u8_InitCounter].AdcGroupId));
            (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS_PRI_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcGroupPriority << (4*ConfigPtr[u8_InitCounter].AdcGroupId));
            /* Set Buffer size. */
            aSS_BufferMaxSize[ConfigPtr[u8_InitCounter].AdcGroupId] = ConfigPtr[u8_InitCounter].AdcStreamingNumSamples;
            /* Set Buffer Mode size. */
            aSS_BufferMode[ConfigPtr[u8_InitCounter].AdcGroupId] = ConfigPtr[u8_InitCounter].AdcStreamingBufferMode;
            /* Set Notifcation function */
            aSS_notification[ConfigPtr[u8_InitCounter].AdcGroupId] = ConfigPtr[u8_InitCounter].AdcNotification;

            /* Configure channel in Sequencer. */
            switch(ConfigPtr[u8_InitCounter].AdcGroupId)
            {
                case ADC_GROUP0:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*au8_SSCount[ADC_GROUP0]));
                    au8_SSCount[ADC_GROUP0]++;
                    break;
                case ADC_GROUP1:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS1_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*au8_SSCount[ADC_GROUP1]));
                    au8_SSCount[ADC_GROUP1]++;
                    break;
                case ADC_GROUP2:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS2_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*au8_SSCount[ADC_GROUP2]));
                    au8_SSCount[ADC_GROUP2]++;
                    break;
                case ADC_GROUP3:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS3_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*au8_SSCount[ADC_GROUP3]));
                    au8_SSCount[ADC_GROUP3]++;
                    break;
                default:
                    /* Invalid group. */
                    return;
            }
        }

        if(au8_SSCount[ADC_GROUP0] > 0)
        {
            /* Configure end of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP0]-1) + 1));
            /* Configure interrupt assertion of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP0]-1) + 2));
            /* Enable sequencer Interrupt mask. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_IM_OFFSET)), ADC_GROUP0);
        }
        if(au8_SSCount[ADC_GROUP1] > 0)
        {
            /* Configure end of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS1_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP1]-1) + 1));
            /* Configure interrupt assertion of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS1_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP1]-1) + 2));
            /* Enable sequencer Interrupt mask. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_IM_OFFSET)), ADC_GROUP1);
        }
        if(au8_SSCount[ADC_GROUP2] > 0)
        {
            /* Configure end of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS2_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP2]-1) + 1));
            /* Configure interrupt assertion of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS2_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP2]-1) + 2));
            /* Enable sequencer Interrupt mask. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_IM_OFFSET)), ADC_GROUP2);
        }
        if(au8_SSCount[ADC_GROUP3] > 0)
        {
            /* Configure end of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS3_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP3]-1) + 1));
            /* Configure interrupt assertion of sequencer. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS3_CTL_OFFSET)), (4*(au8_SSCount[ADC_GROUP3]-1) + 2));
            /* Enable sequencer Interrupt mask. */
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_IM_OFFSET)), ADC_GROUP3);
        }

        /* Set initialized flag. */
        u8_Init = STD_INIT;
    }

    return;
}

/************************************************************************************
* Service Name: Adc_SetupResultBuffer
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
*                  DataBufferPtr    - pointer to ADC data buffer.
* Parameters (inout): None
* Parameters (out): None
* Return value: Return function error state.
* Description: Initialize the ADC data buffer location.
************************************************************************************/
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr)
{
    Std_ReturnType SetupBufferRet;

    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
        SetupBufferRet = (E_ADC_ID | E_ADC_NOT_INIT);
    }
    else if(NULL_PTR == DataBufferPtr)
    {
        /* null pointer error */
        SetupBufferRet = (E_ADC_ID | E_ADC_NULL_PTR);
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group error. */
        SetupBufferRet = (E_ADC_ID | E_ADC_INVALID_VALUE);
    }
    else
    {
        aSS_Buffer[Group] = DataBufferPtr;
        SetupBufferRet = E_OK;
    }

    return SetupBufferRet;
}

/************************************************************************************
* Service Name: Adc_StartGroupConversion
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Starts ADC conversion.
************************************************************************************/
void Adc_StartGroupConversion(Adc_GroupType Group)
{
    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
        return;
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group. */
        return;
    }
    else
    {
        uint32_t u32_BaseAddr = ADC0_BASE_ADDRESS;
        SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_ACTIVE_OFFSET)), Group);
        SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_PSSI_OFFSET)), Group);
    }

    return;
}

/************************************************************************************
* Service Name: Adc_StopGroupConversion
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stops ADC conversion.
************************************************************************************/
void Adc_StopGroupConversion(Adc_GroupType Group)
{
    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
        return;
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group. */
        return;
    }
    else
    {
        uint32_t u32_BaseAddr = ADC0_BASE_ADDRESS;
        CLEAR_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_PSSI_OFFSET)), Group);
        CLEAR_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_ACTIVE_OFFSET)), Group);
    }

    return;
}

/************************************************************************************
* Service Name: Adc_ReadGroup
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): DataBufferPtr    - pointer to ADC data buffer.
* Return value: Return function error state.
* Description: Get the ADC Data buffer.
************************************************************************************/
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr)
{
    Std_ReturnType ReadGroupRet;

    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
        ReadGroupRet = (E_ADC_ID | E_ADC_NOT_INIT);
    }
    else if(NULL_PTR == DataBufferPtr)
    {
        /* null pointer error */
        ReadGroupRet = (E_ADC_ID | E_ADC_NULL_PTR);
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group error. */
        ReadGroupRet = (E_ADC_ID | E_ADC_INVALID_VALUE);
    }
    else
    {
        DataBufferPtr = aSS_Buffer[Group];
        ReadGroupRet = E_OK;
    }

    return ReadGroupRet;
}

/************************************************************************************
* Service Name: Adc_ReadGroup
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: Return ADC Status.
* Description: Get ADC Status.
************************************************************************************/
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group)
{
    Adc_StatusType ADCState;

    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        ADCState = ADC_STATUS_NOT_INIT;
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        ADCState = ADC_STATUS_INVALID_GROUP;
    }
    else
    {
        uint32_t u32_BaseAddr = ADC0_BASE_ADDRESS;
        if(BIT_IS_SET((*(volatile uint32_t *)(u32_BaseAddr + ADC_ACTIVE_OFFSET)), ADC_BUSY_BIT))
        {
            ADCState = ADC_STATUS_BUSY;
        }
        else
        {
            if(BIT_IS_SET((*(volatile uint32_t *)(u32_BaseAddr + ADC_ACTIVE_OFFSET)), Group))
            {
                ADCState = ADC_STATUS_READY;
            }
            else
            {
                ADCState = ADC_STATUS_NOT_RUNNING;
            }
        }
    }

    return ADCState;
}

/************************************************************************************
* Service Name: Adc_GetStreamLastPointer
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): PtrToSamplePtr  - pointer to the data buffer
* Return value: Return Last entry index.
* Description: Get the address of data buffer and last entry index.
************************************************************************************/
Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType** PtrToSamplePtr)
{
    Adc_StreamNumSampleType LastEntryIndex = 0;

    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
    }
    else if(NULL_PTR == PtrToSamplePtr)
    {
        /* null pointer error */
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group error. */
    }
    else
    {

        PtrToSamplePtr = &aSS_Buffer[Group];
        LastEntryIndex = (aSS_BufferSize[Group] - 1);
    }

    return LastEntryIndex;
}

/************************************************************************************
* Service Name: Adc_EnableGroupNotification
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enable notification of a group.
************************************************************************************/
void Adc_EnableGroupNotification(Adc_GroupType Group)
{
    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
        return;
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group error */
        return;
    }
    else
    {
        aSS_EnNotification[Group] = STD_ON;
    }
    return;
}

/************************************************************************************
* Service Name: Adc_DisableGroupNotification
* Service ID[hex]: 0x09
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): Group            - ADC Group ID.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disable notification of a group.
************************************************************************************/
extern void Adc_DisableGroupNotification (Adc_GroupType Group)
{
    /* Validate Module is initialized. */
    if(STD_NOT_INIT == u8_Init)
    {
        /* Not init error. */
        return;
    }
    else if(ADC_INVALID_GROUP <= Group)
    {
        /* Invalid group error */
        return;
    }
    else
    {
        aSS_EnNotification[Group] = STD_OFF;
    }
    return;
}

/* ISR Handlers */
void Adc_SS0Handler(void)
{
    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_ISC_OFFSET)), ADC_GROUP0);

    if(aSS_BufferMaxSize[ADC_GROUP0] < (aSS_BufferSize[ADC_GROUP0] +au8_SSCount[ADC_GROUP0]))
    {
        if(aSS_BufferMode[ADC_GROUP0] == ADC_STREAM_BUFFER_CIRCULAR)
        {
            aSS_BufferSize[ADC_GROUP0] = 0;
            Adc_StreamNumSampleType BufferCounter;

            for(BufferCounter = au8_SSCount[ADC_GROUP0] - 1; BufferCounter < au8_SSCount[ADC_GROUP0]; BufferCounter--)
            {
                aSS_Buffer[ADC_GROUP0][aSS_BufferSize[ADC_GROUP0] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS0_FIFO_OFFSET));
            }

            aSS_BufferSize[ADC_GROUP0] += au8_SSCount[ADC_GROUP0];
        }
        else
        {
            /* Do nothing. */
        }
    }
    else
    {
        Adc_StreamNumSampleType BufferCounter;

        for(BufferCounter = au8_SSCount[ADC_GROUP0] - 1; BufferCounter < au8_SSCount[ADC_GROUP0]; BufferCounter--)
        {
            aSS_Buffer[ADC_GROUP0][aSS_BufferSize[ADC_GROUP0] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS0_FIFO_OFFSET));
        }

        aSS_BufferSize[ADC_GROUP0] += au8_SSCount[ADC_GROUP0];
    }

    if(aSS_EnNotification[ADC_GROUP0] && NULL_PTR != aSS_notification[ADC_GROUP0])
    {
        aSS_notification[ADC_GROUP0]();
    }
}

void Adc_SS1Handler(void)
{
    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_ISC_OFFSET)), ADC_GROUP1);

    if(aSS_BufferMaxSize[ADC_GROUP1] < (aSS_BufferSize[ADC_GROUP1] +au8_SSCount[ADC_GROUP1]))
    {
        if(aSS_BufferMode[ADC_GROUP1] == ADC_STREAM_BUFFER_CIRCULAR)
        {
            aSS_BufferSize[ADC_GROUP1] = 0;
            Adc_StreamNumSampleType BufferCounter;

            for(BufferCounter = au8_SSCount[ADC_GROUP1] - 1; BufferCounter < au8_SSCount[ADC_GROUP1]; BufferCounter--)
            {
                aSS_Buffer[ADC_GROUP1][aSS_BufferSize[ADC_GROUP1] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS1_FIFO_OFFSET));
            }

            aSS_BufferSize[ADC_GROUP1] += au8_SSCount[ADC_GROUP1];
        }
        else
        {
            /* Do nothing. */
        }
    }
    else
    {
        Adc_StreamNumSampleType BufferCounter;

        for(BufferCounter = au8_SSCount[ADC_GROUP1] - 1; BufferCounter < au8_SSCount[ADC_GROUP1]; BufferCounter--)
        {
            aSS_Buffer[ADC_GROUP1][aSS_BufferSize[ADC_GROUP1] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS1_FIFO_OFFSET));
        }

        aSS_BufferSize[ADC_GROUP1] += au8_SSCount[ADC_GROUP1];
    }

    if(aSS_EnNotification[ADC_GROUP1] && NULL_PTR != aSS_notification[ADC_GROUP1])
    {
        aSS_notification[ADC_GROUP1]();
    }
}

void Adc_SS2Handler(void)
{
    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_ISC_OFFSET)), ADC_GROUP2);

    if(aSS_BufferMaxSize[ADC_GROUP2] < (aSS_BufferSize[ADC_GROUP2] +au8_SSCount[ADC_GROUP2]))
    {
        if(aSS_BufferMode[ADC_GROUP2] == ADC_STREAM_BUFFER_CIRCULAR)
        {
            aSS_BufferSize[ADC_GROUP2] = 0;
            Adc_StreamNumSampleType BufferCounter;

            for(BufferCounter = au8_SSCount[ADC_GROUP2] - 1; BufferCounter < au8_SSCount[ADC_GROUP2]; BufferCounter--)
            {
                aSS_Buffer[ADC_GROUP2][aSS_BufferSize[ADC_GROUP2] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS2_FIFO_OFFSET));
            }

            aSS_BufferSize[ADC_GROUP2] += au8_SSCount[ADC_GROUP2];
        }
        else
        {
            /* Do nothing. */
        }
    }
    else
    {
        Adc_StreamNumSampleType BufferCounter;

        for(BufferCounter = au8_SSCount[ADC_GROUP2] - 1; BufferCounter < au8_SSCount[ADC_GROUP2]; BufferCounter--)
        {
            aSS_Buffer[ADC_GROUP2][aSS_BufferSize[ADC_GROUP2] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS2_FIFO_OFFSET));
        }

        aSS_BufferSize[ADC_GROUP2] += au8_SSCount[ADC_GROUP2];
    }

    if(aSS_EnNotification[ADC_GROUP2] && NULL_PTR != aSS_notification[ADC_GROUP2])
    {
        aSS_notification[ADC_GROUP2]();
    }
}

void Adc_SS3Handler(void)
{
    SET_BIT((*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_ISC_OFFSET)), ADC_GROUP3);

    if(aSS_BufferMaxSize[ADC_GROUP3] < (aSS_BufferSize[ADC_GROUP3] + au8_SSCount[ADC_GROUP3]))
    {
        if(aSS_BufferMode[ADC_GROUP3] == ADC_STREAM_BUFFER_CIRCULAR)
        {
            aSS_BufferSize[ADC_GROUP3] = 0;
            Adc_StreamNumSampleType BufferCounter;

            for(BufferCounter = au8_SSCount[ADC_GROUP3] - 1; BufferCounter < au8_SSCount[ADC_GROUP3]; BufferCounter--)
            {
                aSS_Buffer[ADC_GROUP3][aSS_BufferSize[ADC_GROUP3] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS3_FIFO_OFFSET));
            }

            aSS_BufferSize[ADC_GROUP3] += au8_SSCount[ADC_GROUP3];
        }
        else
        {
            /* Do nothing. */
        }
    }
    else
    {
        Adc_StreamNumSampleType BufferCounter;

        for(BufferCounter = au8_SSCount[ADC_GROUP3] - 1; BufferCounter < au8_SSCount[ADC_GROUP3]; BufferCounter--)
        {
            aSS_Buffer[ADC_GROUP3][aSS_BufferSize[ADC_GROUP3] + BufferCounter] = (*(volatile uint32_t *)(ADC0_BASE_ADDRESS + ADC_SS3_FIFO_OFFSET));
        }

        aSS_BufferSize[ADC_GROUP3] += au8_SSCount[ADC_GROUP3];
    }

    if(aSS_EnNotification[ADC_GROUP3] && NULL_PTR != aSS_notification[ADC_GROUP3])
    {
        aSS_notification[ADC_GROUP3]();
    }
}
