/*
 * BCM_Lcgf.c
 *
 * Created: 8/24/2021
 *  Author: Ahmed Essam
 */
/*-INCLUDES-------------------------------*/
#include "STD_TYPES.h"
#include "COMMProxy.h"
/*-MACROS-------------------------------*/
#define BCM_ID  (uint8_t)0xA0
/*- GLOBAL EXTERN VARIABLES-------------------------------*/
/**THIS ARR CONTROLS THE COMM CH{UART,SPI,I2C}**/
const uint8_t au8_BCM_UsedCH[COMM_NUMBERS]={ENABLE,ENABLE,ENABLE};
const uint8_t u8_BCM_ID=BCM_ID;
