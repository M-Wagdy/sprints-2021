/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  DIO.c
 *       Module:  DIO
 *
 *  Description:  source file for DIO module.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "DIO.h"
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

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of the DIO Channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Read a DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    volatile uint32_t * ptru32_Port = NULL_PTR;
    Dio_LevelType RetVal = STD_LOW;

    uint8_t u8_PortID = ChannelId/0xF;
    uint8_t u8_PinID = ChannelId & 0xF;

    /* In-case there are no errors */
    if(u8_PortID > 5)
    {
        /* invalid port */
    }
    else if(u8_PinID > 7)
    {
        /* invalid pin */
    }
    else
    {
        /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
        switch(u8_PortID)
        {
            case DIO_PORT_A:
                ptru32_Port = &PORTA_DATA;
                break;
            case DIO_PORT_B:
                ptru32_Port = &PORTB_DATA;
                break;
            case DIO_PORT_C:
                ptru32_Port = &PORTC_DATA;
                break;
            case DIO_PORT_D:
                ptru32_Port = &PORTD_DATA;
                break;
            case DIO_PORT_E:
                ptru32_Port = &PORTE_DATA;
                break;
            case DIO_PORT_F:
                ptru32_Port = &PORTF_DATA;
                break;
        }

        /* Read the required channel */
        if(BIT_IS_SET(*((volatile uint8_t *)ptru32_Port + (STD_HIGH << (u8_PinID + 2))),u8_PinID))
        {
            RetVal = STD_HIGH;
        }
        else
        {
            RetVal = STD_LOW;
        }
    }
    return RetVal;
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of the DIO Channel.
* Parameters (in): Level     - Level to write on the DIO Channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Write a level on a DIO channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    volatile uint32_t * ptru32_Port = NULL_PTR;

    uint8_t u8_PortID = ChannelId/0xF;
    uint8_t u8_PinID = ChannelId & 0xF;

    /* In-case there are no errors */
    if(u8_PortID > 5)
    {
        /* invalid port */
    }
    else if(u8_PinID > 7)
    {
        /* invalid pin */
    }
    else
    {
        /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
        switch(u8_PortID)
        {
            case DIO_PORT_A:
                ptru32_Port = &PORTA_DATA;
                break;
            case DIO_PORT_B:
                ptru32_Port = &PORTB_DATA;
                break;
            case DIO_PORT_C:
                ptru32_Port = &PORTC_DATA;
                break;
            case DIO_PORT_D:
                ptru32_Port = &PORTD_DATA;
                break;
            case DIO_PORT_E:
                ptru32_Port = &PORTE_DATA;
                break;
            case DIO_PORT_F:
                ptru32_Port = &PORTF_DATA;
                break;
        }

        /* Write the required value */
        if(Level == STD_HIGH)
        {
            /* Write Logic High */
            SET_BIT(*((volatile uint8_t *)ptru32_Port + (STD_HIGH << (u8_PinID + 2))),u8_PinID);
        }
        else if(Level == STD_LOW)
        {
            /* Write Logic Low */
            CLEAR_BIT(*((volatile uint8_t *)ptru32_Port + (STD_HIGH << (u8_PinID + 2))),u8_PinID);
        }
        else
        {
            /* Invalid level. */
        }
    }
}

/************************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of the DIO Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Read a DIO Port.
************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    volatile uint32_t * ptru32_Port = NULL_PTR;
    Dio_LevelType RetVal = STD_LOW;

    /* In-case there are no errors */
    if(PortId > 5)
    {
        /* invalid port */
    }
    else
    {
        /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
        switch(PortId)
        {
            case DIO_PORT_A:
                ptru32_Port = &PORTA_DATA;
                break;
            case DIO_PORT_B:
                ptru32_Port = &PORTB_DATA;
                break;
            case DIO_PORT_C:
                ptru32_Port = &PORTC_DATA;
                break;
            case DIO_PORT_D:
                ptru32_Port = &PORTD_DATA;
                break;
            case DIO_PORT_E:
                ptru32_Port = &PORTE_DATA;
                break;
            case DIO_PORT_F:
                ptru32_Port = &PORTF_DATA;
                break;
        }

        RetVal = *((volatile uint8_t *)ptru32_Port + (0xFF << 2));
    }
    return RetVal;
}

/************************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of the DIO Port.
* Parameters (in): Level  - Level to write on the DIO Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Write a value on a DIO Port.
************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    volatile uint32_t * ptru32_Port = NULL_PTR;

    /* In-case there are no errors */
    if(PortId > 5)
    {
        /* invalid port */
    }
    else
    {
        /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
        switch(PortId)
        {
            case DIO_PORT_A:
                ptru32_Port = &PORTA_DATA;
                break;
            case DIO_PORT_B:
                ptru32_Port = &PORTB_DATA;
                break;
            case DIO_PORT_C:
                ptru32_Port = &PORTC_DATA;
                break;
            case DIO_PORT_D:
                ptru32_Port = &PORTD_DATA;
                break;
            case DIO_PORT_E:
                ptru32_Port = &PORTE_DATA;
                break;
            case DIO_PORT_F:
                ptru32_Port = &PORTF_DATA;
                break;
        }

        /* Write the required value */
        *((volatile uint8_t *)ptru32_Port + (0xFF << 2)) = Level;
    }
}

/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of the DIO Channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Toggle a DIO Channel.
************************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    volatile uint32_t * ptru32_Port = NULL_PTR;
    Dio_LevelType RetVal = STD_LOW;

    uint8_t u8_PortID = ChannelId/0xF;
    uint8_t u8_PinID = ChannelId & 0xF;

    /* In-case there are no errors */
    if(u8_PortID > 5)
    {
        /* invalid port */
    }
    else if(u8_PinID > 7)
    {
        /* invalid pin */
    }
    else
    {
        /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
        switch(u8_PortID)
        {
            case DIO_PORT_A:
                ptru32_Port = &PORTA_DATA;
                break;
            case DIO_PORT_B:
                ptru32_Port = &PORTB_DATA;
                break;
            case DIO_PORT_C:
                ptru32_Port = &PORTC_DATA;
                break;
            case DIO_PORT_D:
                ptru32_Port = &PORTD_DATA;
                break;
            case DIO_PORT_E:
                ptru32_Port = &PORTE_DATA;
                break;
            case DIO_PORT_F:
                ptru32_Port = &PORTF_DATA;
                break;
        }

        /* Toggle the required Channel */
        if(BIT_IS_SET(*((volatile uint8_t *)ptru32_Port + (STD_HIGH << (u8_PinID + 2))),u8_PinID))
        {
            CLEAR_BIT(*((volatile uint8_t *)ptru32_Port + (STD_HIGH << (u8_PinID + 2))),u8_PinID);
            RetVal = STD_LOW;
        }
        else
        {
            SET_BIT(*((volatile uint8_t *)ptru32_Port + (STD_HIGH << (u8_PinID + 2))),u8_PinID);
            RetVal = STD_HIGH;
        }
    }
    return RetVal;
}
