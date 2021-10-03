/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT_Lcfg.c
 *       Module:  PORT
 *
 *  Description:  source file for PORT module linking configurations.
 *
 *********************************************************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "PORT_Lcfg.h"

const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM] = {
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_0},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_1},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_2},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_3},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_4},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_5},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_6},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_A, PORT_PIN_7},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_0},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_1},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_2},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_3},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_4},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_5},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_6},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_B, PORT_PIN_7},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_0},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_1},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_2},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_3},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_4},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_5},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_6},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_OUTPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_C, PORT_PIN_7},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_0},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_1},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_2},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_3},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_4},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_5},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_6},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_D, PORT_PIN_7},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_E, PORT_PIN_0},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_E, PORT_PIN_1},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_E, PORT_PIN_2},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_E, PORT_PIN_3},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_E, PORT_PIN_4},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_E, PORT_PIN_5},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_F, PORT_PIN_0},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_F, PORT_PIN_1},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_F, PORT_PIN_2},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_F, PORT_PIN_3},
    {PORT_PIN_DEN, PORT_PIN_LOW, PORT_PIN_INPUT, PORT_PIN_PUR, PORT_PIN_CUR_8MA, PORT_F, PORT_PIN_4},
};
