/*
 * REALTIMEMONITORING.c
 *
 * Created: 9/1/2021 1:52:14 PM
 *  Author: vetmo
 */ 
#include "MC_REGISTERS.h"
#include "REALTIMEMONITORING.h"
uint32_t Counter = 0;
uint32_t CPU_LOAD = 0;
uint32_t Average_CPU_LOAD = 0;
uint32_t AverageCounter = 0;
uint32_t AccumlationOfCPULoad = 0;
void __vector_5(void)__attribute__((signal,used));
void REALTIMEMONITORING_MainFunction(void)
{
	static uint8_t State = OperationStarted;
	switch(State)
	{
		case OperationStarted:
		TIMSK |= 1<<6;/*Enable interrupt*/
		TCCR2 = 0X03;/*prescalar 32*/
		State = CALCULATION;
		break;
		case CALCULATION:
		Counter += TCNT2*2;
		CPU_LOAD = (uint32_t)((uint32_t)(Counter*100) / (uint32_t)WINDOWTIMEINMICROSEC);
		AccumlationOfCPULoad += CPU_LOAD;
		AverageCounter++;
		if(AverageCounter == NUMBEROFITERATIONSFORAVERAGE)
		{
			AverageCounter = 0;
			Average_CPU_LOAD = AccumlationOfCPULoad/NUMBEROFITERATIONSFORAVERAGE;
			AccumlationOfCPULoad = 0;
		} 
		Counter = 0;
		TCNT2 = 0;
		break;
		default:
		break;
	}
}
void __vector_5(void) {
	Counter += 256*2;
}