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

    if(STD_INIT == u8_Init)
    {
        /* Init before error. */
    }
    else
    {
        for(u8_PinCounter = 0; u8_PinCounter < PORT_PINS_NUM; u8_PinCounter++)
        {
            /* Get Port Base Address */
            switch(ConfigPtr[u8_PinCounter].PortNum)
            {
                case PORT_A:
                    u32_PortBaseAddr = (uint32_t *)PORTA_APB_BASE_ADDRESS;
                    break;
                case PORT_B:
                    u32_PortBaseAddr = (uint32_t *)PORTB_APB_BASE_ADDRESS;
                    break;
                case PORT_C:
                    u32_PortBaseAddr = (uint32_t *)PORTC_APB_BASE_ADDRESS;
                    break;
                case PORT_D:
                    u32_PortBaseAddr = (uint32_t *)PORTD_APB_BASE_ADDRESS;
                    break;
                case PORT_E:
                    u32_PortBaseAddr = (uint32_t *)PORTE_APB_BASE_ADDRESS;
                    break;
                case PORT_F:
                    u32_PortBaseAddr = (uint32_t *)PORTF_APB_BASE_ADDRESS;
                    break;
                default:
                    break;
            }

            /* Protect JTAG Pins in PORTC. */
            if((PORT_C == ConfigPtr[u8_PinCounter].PortNum) && (PORT_PIN_3 >= ConfigPtr[u8_PinCounter].PortPinNum))
            {
                continue;
            }
            /* Unlock changes to protected pins. */
            else if(( (PORT_D == ConfigPtr[u8_PinCounter].PortNum) && (PORT_PIN_7 == ConfigPtr[u8_PinCounter].PortPinNum) ) ||
                    ( (PORT_F == ConfigPtr[u8_PinCounter].PortNum) && (PORT_PIN_0 == ConfigPtr[u8_PinCounter].PortPinNum) )
                   )
            {
                *((volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_LOCK_OFFSET)) = 0x4C4F434B;
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_CR_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
            }
            else
            {
                /* Do Nothing. */
            }

            /* Configure Pin Direction */
            if(PORT_PIN_OUTPUT == ConfigPtr[u8_PinCounter].PortPinDirection)
            {
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DIR_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Configure Pin Level */
                if(PORT_PIN_HIGH == ConfigPtr[u8_PinCounter].PortPinLevelValue)
                {
                    SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DATA_OFFSET + (1<<ConfigPtr[u8_PinCounter].PortPinNum+2))), ConfigPtr[u8_PinCounter].PortPinNum);
                }
                else if(PORT_PIN_LOW == ConfigPtr[u8_PinCounter].PortPinLevelValue)
                {
                    CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DATA_OFFSET + (1<<ConfigPtr[u8_PinCounter].PortPinNum+2)) , ConfigPtr[u8_PinCounter].PortPinNum);
                }
                else
                {
                    /* Invalid Config error. */
                    break;
                }

                /* Configure Pin Output Current */
                switch(ConfigPtr[u8_PinCounter].PortPinOutputCurrent)
                {
                    case PORT_PIN_CUR_2MA:
                        SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DR2R_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                        break;
                    case PORT_PIN_CUR_4MA:
                        SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DR4R_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                        break;
                    case PORT_PIN_CUR_8MA:
                        SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DR8R_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                        break;
                    default:
                        /* Invalid config error. */
                        u8_PinCounter = PORT_PINS_NUM;
                        continue;
                }

            }
            else if(PORT_PIN_INPUT == ConfigPtr[u8_PinCounter].PortPinDirection)
            {
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DIR_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Configure Pin Resistance */
                switch(ConfigPtr[u8_PinCounter].PortPinInternalAttach)
                {
                    case PORT_PIN_PUR:
                        SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_PUR_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                        break;
                    case PORT_PIN_PDR:
                        SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_PDR_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                        break;
                    case PORT_PIN_ODR:
                        SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_ODR_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                        CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_PUR_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                        CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_PDR_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                        break;
                    default:
                        /* Invalid config error. */
                        u8_PinCounter = PORT_PINS_NUM;
                        continue;
                }
            }
            else
            {
                /* Invalid Config error. */
                break;
            }


            /* Configure Pin Mode */
            /* Clear the PMCx bits for this pin */
            *(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_PCTL_OFFSET) &= ~(0x0000000F << (ConfigPtr[u8_PinCounter].PortPinNum * 4));
            if(PORT_PIN_DEN == ConfigPtr[u8_PinCounter].PortPinMode)
            {
                /* Clear the corresponding bit in the GPIOAFSEL register to disable the alternative functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AFSEL_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DEN_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AMSEL_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
            }
            else if(PORT_PIN_AMSEL == ConfigPtr[u8_PinCounter].PortPinMode)
            {
                /* Clear the corresponding bit in the GPIOAFSEL register to disable the alternative functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AFSEL_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DEN_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AMSEL_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
            }
            else if(PORT_PIN_EXTI == ConfigPtr[u8_PinCounter].PortPinMode)
            {
                /* Clear the corresponding bit in the GPIOAFSEL register to disable the alternative functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AFSEL_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DEN_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AMSEL_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Detect edges */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_IS_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Detect Both edges */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_IBE_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Clear Interupt Flag */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_ICR_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Enable Interrupt for pin */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_IM_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
            }
            else if((ConfigPtr[u8_PinCounter].PortPinMode >= 1) && (ConfigPtr[u8_PinCounter].PortPinMode <= 15))
            {
                /* Set the corresponding bit in the GPIOAFSEL register to disable the alternative functionality on this pin */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AFSEL_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT_PER_BB((*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_DEN_OFFSET)), ConfigPtr[u8_PinCounter].PortPinNum);
                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_AMSEL_OFFSET) , ConfigPtr[u8_PinCounter].PortPinNum);
                /* Set the corresponding bit in the GPIOPCTL register to select the alternative functionality on this pin */
                *(volatile uint32_t *)((volatile uint8_t *)u32_PortBaseAddr + PORT_PCTL_OFFSET) |= (ConfigPtr[u8_PinCounter].PortPinMode << (ConfigPtr[u8_PinCounter].PortPinNum * 4));
            }
            else
            {
                /* Invalid Config error. */
                break;
            }
        }

        u8_Init = STD_INIT;
    }
}
