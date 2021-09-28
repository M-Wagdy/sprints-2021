/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT.c
 *       Module:  PORT
 *
 *  Description:  source file for PORT module.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "PORT.h"
#include "Mcu_Hw.h"
#include "Bit_Math.h"

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

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ConfigPtr - Ports configuration address.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the MCU Ports.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
    uint32_t * u32_PortBaseAddr;
    uint8_t u8_PinCounter;
    uint8_t u8_PinNum;

    for(u8_PinCounter = 0; u8_PinCounter < PORT_PINS_NUM; u8_PinCounter++)
    {
        /* Get Port Base Address */
        switch(u8_PinCounter)
        {
            case 0:
                u32_PortBaseAddr = (uint32_t *)PORTA_APB_BASE_ADDRESS;
                u8_PinNum = 0;
                break;
            case 8:
                u32_PortBaseAddr = (uint32_t *)PORTB_APB_BASE_ADDRESS;
                u8_PinNum = 0;
                break;
            case 16:
                u32_PortBaseAddr = (uint32_t *)PORTC_APB_BASE_ADDRESS;
                u8_PinNum = 0;
                break;
            case 24:
                u32_PortBaseAddr = (uint32_t *)PORTD_APB_BASE_ADDRESS;
                u8_PinNum = 0;
                break;
            case 32:
                u32_PortBaseAddr = (uint32_t *)PORTE_APB_BASE_ADDRESS;
                u8_PinNum = 0;
                break;
            case 38:
                u32_PortBaseAddr = (uint32_t *)PORTF_APB_BASE_ADDRESS;
                u8_PinNum = 0;
                break;
            default:
                break;
        }

        /* Protect JTAG Pins in PORTC. */
        if(20 > u8_PinCounter  && 15 < u8_PinCounter)
        {
            u8_PinNum++;
            continue;
        }
        /* Unlock changes to protected pins. */
        else if(31 == u8_PinCounter || 38 == u8_PinCounter)
        {
            *((volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_LOCK_OFFSET)) = 0x4C4F434B;
            SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_CR_OFFSET) , u8_PinNum);
        }
        else
        {
            /* Do Nothing. */
        }

        /* Configure Pin Direction */
        if(PORT_PIN_OUTPUT == ConfigPtr[u8_PinCounter].PortPinDirection)
        {
            SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DIR_OFFSET) , u8_PinNum);
            SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DEN_OFFSET) , u8_PinNum);
            /* Configure Pin Level */
            if(PORT_PIN_HIGH == ConfigPtr[u8_PinCounter].PortPinLevelValue)
            {
                SET_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DATA_OFFSET + (1<<u8_PinNum+2)) , u8_PinNum);
            }
            else if(PORT_PIN_LOW == ConfigPtr[u8_PinCounter].PortPinLevelValue)
            {
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DATA_OFFSET + (1<<u8_PinNum+2)) , u8_PinNum);
            }
            else
            {
                /* Invalid Config error. */
                break;
            }
            /* Configure Pin Output Current */


        }
        else if(PORT_PIN_INPUT == ConfigPtr[u8_PinCounter].PortPinDirection)
        {
            CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DIR_OFFSET) , u8_PinNum);
            /* Configure Pin Resistance */

        }
        else
        {
            /* Invalid Config error. */
            break;
        }


        /* Configure Pin Mode */
        u8_PinNum++;
    }

    u8_Init = STD_INIT;
}
