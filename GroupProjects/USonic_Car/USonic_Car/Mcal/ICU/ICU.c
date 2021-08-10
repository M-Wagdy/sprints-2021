/*
 * File Name: ICU.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for ICU peripheral....
 */ 

#include "ICU.h"

static uint8_t ICU_Reset(uint8_t ICUNumber,uint8_t ICUEdgeDetector);
static uint8_t ICU_CalculateTimeOn(uint8_t ICUNumber,ptr_double64_t TimeOnValue);
static uint32_t OverflowCounter = 0;



static uint8_t ICU_Reset(uint8_t ICUNumber,uint8_t ICUEdgeDetector)
{
	switch(ICUNumber)
	{
		#if  ICU1
			case ICU_1:
				REG_WRITE(TCNT1,0x0000);
				BIT_WRITE(TCCR1B,ICES1,ICUEdgeDetector);
				BIT_WRITE(TIFR,TOV1,BIT_HIGH);
				BIT_WRITE(TIFR,ICF1,BIT_HIGH);
				break;
		#endif
		default:
			break;
	}		
}

static uint8_t ICU_CalculateTimeOn(uint8_t ICUNumber,ptr_double64_t TimeOnValue)
{
	uint64_t CounterNumber;
	switch(ICUNumber)
	{
		#if  ICU1
			case ICU_1:
				CounterNumber=(uint64_t)(REG_GET(ICR1)+(OverflowCounter*ICU1_MAX_COUNT));
				*TimeOnValue = (CounterNumber*((double)ICU1_PRESCALER/F_CPU));
            
				break;
		#endif
		default:
			break;
	}	
}

uint8_t ICU_Init(uint8_t ICUNumber)
{
	switch(ICUNumber)
	{
		#if  ICU1
			case ICU_1:
				DIO_SetPinDirection(ICU1_PORT,ICU1_PIN,PIN_INPUT);
				TWO_BITS_WRITE(TCCR1A,WGM10,TWO_BITS_GET(ICU1_MODE,BIT0));
				TWO_BITS_WRITE(TCCR1B,WGM12,TWO_BITS_GET(ICU1_MODE,BIT2));
				THREE_BITS_WRITE(TCCR1B,CS10,ICU1_CLK_SOURCE);
				break;
		#endif
		default:
			break;
	}	
}

uint8_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t TimeOnValue)
{
	switch(ICUNumber)
	{
		#if  ICU1
			case ICU_1:
			{
				switch(*ICUState)
				{
					case START_STATE:
					{
						ICU_Reset(ICU_1,ICU1_RISING_EDGE);
						*ICUState=WAITING_RISING_EDGE_STATE;
						break;
					}
					case WAITING_RISING_EDGE_STATE:
					{
						if(1==(BIT_GET(TIFR,ICF1)))
						{
							ICU_Reset(ICU_1,ICU1_FALLING_EDGE);
							OverflowCounter=0;
							*ICUState=WAITING_FALLING_EDGE_STATE;
						}
						break;
					}
					case WAITING_FALLING_EDGE_STATE:
					{
						if(1==(BIT_GET(TIFR,TOV1)))
						{
							OverflowCounter++;
							BIT_WRITE(TIFR,TOV1,BIT_HIGH);
						}	
						
						if(1==(BIT_GET(TIFR,ICF1)))
						{
							ICU_CalculateTimeOn(ICU_1,TimeOnValue);
							*ICUState=END_STATE;
						}
						break;
					}
					default:
						break;
				}
				break;
			}
		#endif
		default:
			break;
	}		
}