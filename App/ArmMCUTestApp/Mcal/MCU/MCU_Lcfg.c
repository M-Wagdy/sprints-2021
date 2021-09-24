/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MCU_Lcfg.c
 *       Module:  MCU
 *
 *  Description:  source file for MCU module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "MCU_Lcfg.h"

const STR_MCU_config_t STR_MCUConfig = {
    SYSDIV_1, USESYSDIV_DIS, XTAL_16_MHZ, OSCSRC_PIOSC, MOSC_DIS
};
