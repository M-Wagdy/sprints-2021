#include "PORT.h"
#include "DIO.h"
#include "MCU.h"
#include "IntCtrl.h"
#include "GPT.h"
#include "Mcu_Hw.h"

extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];
extern const Gpt_ConfigType STR_GptConfig[GPT_CONFIGURED_GPT_CHS];
extern const STR_Mcu_ConfigType STR_MCUClockConfig[CLOCK_SETTINGS_NUM];

void T0_Callback(void)
{
    Dio_WriteChannel(DIO_CH_PF1, DIO_CH_VAL_HIGH);
}

uint32_t u32_PreDefVal = 0;

void main(void)
{
    /* Init MCU */
    Mcu_Init(STR_MCUClockConfig);
    Mcu_InitClock(0);

    /* Init Interrupts */
    IntCtrl_Init();
    IntCtrl_EnableGlobal();

    /* Init Pins. */
    Port_Init(STR_PortsConfig);

    /* Init Timers */
    Gpt_Init(STR_GptConfig);

    Gpt_EnableNotification(GPT_CH0);

    Gpt_StartTimer(GPT_CH0, 16000);

    /* Superloop */
    while(1)
    {
        Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_100US_32BIT, &u32_PreDefVal);

        if(u32_PreDefVal > 23437)
        {
            Dio_WriteChannel(DIO_CH_PF2, DIO_CH_VAL_HIGH);
        }
    }

}
