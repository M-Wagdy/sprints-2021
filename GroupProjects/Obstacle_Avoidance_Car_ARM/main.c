/*
 * OS.c
 *
 * Created: 08/29/2021 7:56:24 PM
 *  Author: REHAB
 */ 

#include "MONITORING.h"
#include "PORT.h"
#include "OS.h"
#include "Mcu_Hw.h"

TaskHandler_t MonitoringTaskHandler;

extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];

Std_ReturnType SENSING_Get(float64_t * Num)
{
    static uint8_t num = 1;
    *Num = num;
    num++;
    if(num == 255)
    {
        num = 1;
    }
    return E_OK;
}

void MonitoringTask(void);

void MonitoringTask(void)
{
	MONITOR_MainFunction();
}

int main(void)
{
    /* Start PortF Clock */
    SYSCTL_RCGCGPIO |= 0x3F;
    /* Wait till clock is running */
    while((SYSCTL_PRGPIO & 0x3F) != 0x3F);

    Port_Init(STR_PortsConfig);

	OS_Init();

	OS_CreateTask(0,0,20,MonitoringTask,&MonitoringTaskHandler);

	OS_Run();

    while(1)
    {
        //TODO:: Please write your application code
    }
}

//#include "LCD.h"
//#include "PORT.h"
//#include "Mcu_Hw.h"
//
//extern const Port_ConfigType STR_PortsConfig[PORT_PINS_NUM];
//
//void main(void) {
//
//    /* Start PortF Clock */
//    SYSCTL_RCGCGPIO |= 0x3F;
//    /* Wait till clock is running */
//    while((SYSCTL_PRGPIO & 0x3F) != 0x3F);
//
//    Port_Init(STR_PortsConfig);
//
//    while(0 != LCD_Init());
//
//    while(0 != LCD_SendString("ya rab !"));
//
//    while(1);
//}

