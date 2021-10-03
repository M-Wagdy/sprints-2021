/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  main.c
 *       Module:  main
 *
 *  Description:  source file for main App.
 *
 *********************************************************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "MCU.h"
#include "Mcu_Hw.h"

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
extern const STR_Mcu_ConfigType STR_MCUClockConfig[CLOCK_SETTINGS_NUM];

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/

/*- APIs IMPLEMENTATION
-----------------------------------*/
void SYSTICK_Handler(void)
{
   /* Toggles the leds */
   PORTF_DATA ^= 0x0E;
}

void main(void)

{
    Mcu_Init(STR_MCUClockConfig);
    Mcu_InitClock(0);

    /* Enable Write Access */
    PORTF_LOCK = 0x4C4F434;
    /* Set Pin 1,2,3 to output */
    PORTF_DIR |= 0x0E;
    /* Digital enable Pin 1,2,3 */
    PORTF_DEN |= 0x0E;
    /* Commit Changes */
    PORTF_CR = 0x1F;

    /* Disables the systick clock */
    STCTRL &= ~(0x07);
    /* Set the period */
    STRELOAD = 16000000;
    /* Configure the systick */
    STCTRL |= (0x07);



    /* Superloop */
    while(1);

}
