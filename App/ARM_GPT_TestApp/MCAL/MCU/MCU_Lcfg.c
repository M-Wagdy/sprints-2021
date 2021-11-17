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

const STR_Mcu_ConfigType STR_MCUClockConfig[CLOCK_SETTINGS_NUM] = {
    {STD_OFF, OSCSRC_PIOSC, 16000},
    {STD_OFF, OSCSRC_PIOSC_DIV_4, 1000},
    {STD_ON, OSCSRC_MOSC, 60000},
};

const uint16_t au16_ClockGates[CONFIGURED_CLOCK_GATES] = {
    CG_PORTA,
    CG_PORTB,
    CG_PORTC,
    CG_PORTD,
    CG_PORTE,
    CG_PORTF,
    CG_T0,
    CG_T1,
    CG_T2,
    CG_T3,
    CG_T4,
    CG_T5,
    CG_WT0,
    CG_WT1,
    CG_WT2,
    CG_WT3,
    CG_WT4,
    CG_WT5,
};
