/*
 * I2C_Config.c
 *
 * Created: 8/3/2021 10:58:20 AM
 *  Author: Mohamed Wagdy
 */

/*- INCLUDES
----------------------------------------------*/
#include "../../Mcal/I2C/I2C_Config.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
/* I2C_CH_0 */
const uint8_t I2C_CH_0_PRESCALER = I2C_PRESCALAR_64;
const uint8_t I2C_CH_0_CONTROL_MASK = (I2C_EN);
const uint8_t I2C_CH_0_BIT_RATE = I2C_8_MHZ_115200_RATE_1_PRESCALAR;
