/*
 * File Name: ICU.c
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for ICU peripheral....
 */ 
#include "../../LIB/MC_REGISTERS.h"
#include "ICU.h"

#define ICU1_MAX_COUNT 		((uint16_t)65535)
#define ICU1_PORT			PORT_D
#define ICU1_PIN			PIN6
	
#define OVERFLOW_FLAG_UP	1
#define OVERFLOW_FLAG_DOWN	0

#define ICU_FLAG_UP			1
#define ICU_FLAG_DOWN		0

#define CLEAR_REGISTER      (0x0000)

enum Enu_ICU1EdgeDetector
{
	ICU1_FALLING_EDGE = 0,
	ICU1_RISING_EDGE = 1
};

static ERROR_STATE_t ICU_Reset(uint8_t ICUNumber,uint8_t ICUEdgeDetector);
static ERROR_STATE_t ICU_CalculateTimeOn(uint8_t ICUNumber,ptr_double64_t TimeOnValue);

static uint32_t OverflowCounter = 0;
extern Str_ICUConfig_t gastr_ICUConfig[ICU_CHANNEL_NUMBERS];

static ERROR_STATE_t ICU_Reset(uint8_t ICUNumber,uint8_t ICUEdgeDetector)
{
	uint8_t u8_ErrorState=ERROR_OK;
	if((ICU1_FALLING_EDGE!=ICUEdgeDetector )&&(ICU1_RISING_EDGE!=ICUEdgeDetector ))
	{
		u8_ErrorState = ERROR_NOK;
	}
	else
	{
		switch(ICUNumber)
		{
			#if  ICU1
				case ICU_1:
					REG_WRITE(TCNT1,CLEAR_REGISTER);
					BIT_WRITE(TCCR1B,ICES1,ICUEdgeDetector);
					BIT_WRITE(TIFR,TOV1,BIT_HIGH);
					BIT_WRITE(TIFR,ICF1,BIT_HIGH);
					u8_ErrorState = ERROR_OK;
					break;
			#endif
			default:
				u8_ErrorState = ERROR_NOK;
				break;
		}			
	}
	return u8_ErrorState;
}

static ERROR_STATE_t ICU_CalculateTimeOn(uint8_t ICUNumber,ptr_double64_t TimeOnValue)
{
	uint64_t CounterNumber;
	uint8_t u8_ErrorState=ERROR_OK;
	
	if(NULL_PTR==TimeOnValue)
	{
		u8_ErrorState = ERROR_NOK;
	}
	
	else if(0==F_CPU)
	{
		u8_ErrorState = ERROR_NOK;
	}	
	else
	{
		switch(ICUNumber)
		{
			#if  ICU1
				case ICU_1:
					CounterNumber=(uint64_t)(REG_GET(ICR1)+(OverflowCounter*ICU1_MAX_COUNT));
					*TimeOnValue = (CounterNumber*((double)gastr_ICUConfig[ICU_1].ICUPrescaler/F_CPU));
					u8_ErrorState = ERROR_OK;
				break;
			#endif
			default:
				u8_ErrorState = ERROR_NOK;
				break;
		}
	}

	return u8_ErrorState;
}

ERROR_STATE_t ICU_Init(uint8_t ICUNumber)
{	
	uint8_t u8_ErrorState = ERROR_OK;
	switch(ICUNumber)
	{
		#if  ICU1
			case ICU_1:
				DIO_SetPinDirection(ICU1_PORT,ICU1_PIN,PIN_INPUT);
				TWO_BITS_WRITE(TCCR1A,WGM10,TWO_BITS_GET(gastr_ICUConfig[ICU_1].ICUMode,BIT_0));
				TWO_BITS_WRITE(TCCR1B,WGM12,TWO_BITS_GET(gastr_ICUConfig[ICU_1].ICUMode,BIT_2));
				THREE_BITS_WRITE(TCCR1B,CS10,gastr_ICUConfig[ICU_1].ICUClkSource);
				u8_ErrorState=ERROR_OK;
				break;
		#endif
		default:
			u8_ErrorState=ERROR_NOK;
			break;
	}	
	return u8_ErrorState;
}

ERROR_STATE_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t TimeOnValue)
{
	uint8_t u8_ErrorState=ERROR_OK;
	if((NULL_PTR==ICUState) || (NULL_PTR==TimeOnValue))
	{
		u8_ErrorState = ERROR_NOK;
	}
	else
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
							if(ERROR_OK != ICU_Reset(ICU_1,ICU1_RISING_EDGE))
							{
								u8_ErrorState = ERROR_NOK;
							}
							else
							{
								*ICUState=WAITING_RISING_EDGE_STATE;
								u8_ErrorState = ERROR_OK;															
							}
							break;
						}
						case WAITING_RISING_EDGE_STATE:
						{
							if(ICU_FLAG_UP==(BIT_GET(TIFR,ICF1)))
							{
								if(ERROR_OK!=ICU_Reset(ICU_1,ICU1_FALLING_EDGE))
								{
									u8_ErrorState = ERROR_NOK;
								}
								else
								{
									OverflowCounter=0;
									*ICUState=WAITING_FALLING_EDGE_STATE;
									u8_ErrorState = ERROR_OK;									
								}
							}
							break;
						}
						case WAITING_FALLING_EDGE_STATE:
						{
							if(OVERFLOW_FLAG_UP==(BIT_GET(TIFR,TOV1)))
							{
								OverflowCounter++;
								BIT_WRITE(TIFR,TOV1,BIT_HIGH);
								u8_ErrorState = ERROR_OK;
							}
							
							if(ICU_FLAG_UP==(BIT_GET(TIFR,ICF1)))
							{
								if(ERROR_OK!=ICU_CalculateTimeOn(ICU_1,TimeOnValue))
								{
									u8_ErrorState = ERROR_NOK;
								}
								else
								{
									*ICUState=END_STATE;
									u8_ErrorState = ERROR_OK;	
								}
								
							}
							break;
						}
						default:
							u8_ErrorState = ERROR_NOK;
							break;
					}
					break;
				}
			#endif
			default:
				u8_ErrorState= ERROR_NOK;
				break;
		}
	}
	return u8_ErrorState;
}