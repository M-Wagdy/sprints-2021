/*
 * USonic_Car.c
 *
 * Created: 8/9/2021 11:56:36 AM
 * Author : Mohamed Wagdy
 */ 

#include "SENSING.h"
#include "STEERING.h"
#include "CRASH.h"
#include "REALTIMEMONITORING.h"

int main(void)
{  
	REALTIMEMONITORING_MainFunction();
   while(1)
   {
		
		SENSING_MainFunction();
		CRASH_MainFunction();
		STEERING_MainFunction();
		REALTIMEMONITORING_MainFunction();
		//MONITOR_MainFunction();
		
   }
}

