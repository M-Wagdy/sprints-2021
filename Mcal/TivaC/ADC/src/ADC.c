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
static const Adc_ConfigType * ADCConfig;
static uint8_t u8_SS0count = 0, u8_SS1count = 0, u8_SS2count = 0, u8_SS3count = 0;

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

            /* Configure channel in Sequencer. */
            switch(ConfigPtr[u8_InitCounter].AdcGroupId)
            {
                case ADC_GROUP0:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*u8_SS0count));
                    u8_SS0count++;
                    break;
                case ADC_GROUP1:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*u8_SS1count));
                    u8_SS1count++;
                    break;
                case ADC_GROUP2:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*u8_SS2count));
                    u8_SS2count++;
                    break;
                case ADC_GROUP3:
                    (*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_MUX_OFFSET)) |= (ConfigPtr[u8_InitCounter].AdcChannelId << (4*u8_SS3count));
                    u8_SS3count++;
                    break;
                default:
                    /* Invalid group. */
                    return;
            }
        }

        /* Configure end of sequencers. */
        if(u8_SS0count > 0)
        {
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS0_CTL_OFFSET)), (4*(u8_SS0count-1) + 1));
        }
        if(u8_SS1count > 0)
        {
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS1_CTL_OFFSET)), (4*(u8_SS1count-1) + 1));
        }
        if(u8_SS2count > 0)
        {
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS2_CTL_OFFSET)), (4*(u8_SS2count-1) + 1));
        }
        if(u8_SS3count > 0)
        {
            SET_BIT((*(volatile uint32_t *)(u32_BaseAddr + ADC_SS3_CTL_OFFSET)), (4*(u8_SS3count-1) + 1));
        }

        /* Save Config Params in static variable */
        ADCConfig = ConfigPtr;

        /* Set initialized flag. */
        u8_Init = STD_INIT;
    }

    return;
}
