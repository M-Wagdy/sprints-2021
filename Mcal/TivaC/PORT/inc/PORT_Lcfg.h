/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT_Lcfg.h
 *       Module:  PORT
 *
 *  Description:  header file for PORT module linking configurations.
 *
 *********************************************************************************************************************/
#ifndef __PORT_LCFG_H__
#define __PORT_LCFG_H__

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"
#include "PORT_Cfg.h"

/*- CONSTANTS ----------------------------------------------*/
#define PORT_PINS_NUM            (uint8_t)(43U)
/* Pin Levels Values */
#define PORT_PIN_HIGH            (Port_PinLevel)(STD_HIGH)
#define PORT_PIN_LOW             (Port_PinLevel)(STD_LOW)
#define PORT_PIN_LEVEL_INVALID   (Port_PinLevel)(2)
/* Pin Directions Values */
#define PORT_PIN_INPUT           (Port_PinDirectionType)(0)
#define PORT_PIN_OUTPUT          (Port_PinDirectionType)(1)
#define PORT_PIN_DIR_INVALID     (Port_PinDirectionType)(2)
/* Pin Internal Attach Values */
#define PORT_PIN_PUR             (Port_PinInternalAttachType)(0)
#define PORT_PIN_PDR             (Port_PinInternalAttachType)(1)
#define PORT_PIN_ODR             (Port_PinInternalAttachType)(2)
#define PORT_PIN_RES_INVALID     (Port_PinInternalAttachType)(3)
/* Pin Output Current Values */
#define PORT_PIN_CUR_2MA         (Port_PinOutputCurrentType)(0)
#define PORT_PIN_CUR_4MA         (Port_PinOutputCurrentType)(1)
#define PORT_PIN_CUR_8MA         (Port_PinOutputCurrentType)(2)
#define PORT_PIN_CUR_INVALID     (Port_PinOutputCurrentType)(3)
/* Pin Mode Values */
#define PORT_PIN_MODE_INVALID    (Port_PinModeType)(16)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
    Port_PinModeType PortPinMode;
    Port_PinLevel PortPinLevelValue;
    Port_PinDirectionType PortPinDirection;
    Port_PinInternalAttachType PortPinInternalAttach;
    Port_PinOutputCurrentType PortPinOutputCurrent;
}Port_ConfigType;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif  /* __PORT_LCFG_H__ */
