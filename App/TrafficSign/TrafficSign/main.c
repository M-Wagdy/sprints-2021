/*
 * MCU_OVER_UART.c
 *
 * Created: 7/13/2021 7:35:53 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES 
-----------------------------------------------*/
#include "App/TrafficSign/TrafficSign.h"

int main(void)
{
   Traffic_init();
   while (1) 
   {
      Traffic_update();
   }
}

