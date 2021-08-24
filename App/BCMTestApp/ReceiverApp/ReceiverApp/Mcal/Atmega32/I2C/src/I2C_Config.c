/*
 * I2C_Config.c
 *
 * Created: 8/3/2021 10:58:20 AM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "I2C_Config.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* I2C_CH_0 */
const uint8_t I2C_CH_0_PRESCALER = I2C_PRESCALAR_1;
const uint8_t I2C_CH_0_CONTROL_MASK = (I2C_EN | I2C_ACK_EN);
const uint8_t I2C_CH_0_BIT_RATE = I2C_16_MHZ_500K_Rate_1_PRESCALAR;