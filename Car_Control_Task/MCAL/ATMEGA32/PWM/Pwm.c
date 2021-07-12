/*
 * File Name: Pwm.h
 * Creation Date: 09/07/2020
 * Author: Rehab
 * Description: C File for PWM peripheral....
 */ 

#include "Pwm.h"

uint8_t PwmInit(void)
{
	#if OC0
		BIT_WRITE(TCCR0,WGM00,BIT_GET(OC0_MODE,BIT0));
		BIT_WRITE(TCCR0,WGM01,BIT_GET(OC0_MODE,BIT1));
		
		TWO_BITS_WRITE(TCCR0,COM00,OC0_WAVEFORM_MODE);			
	#endif

	#if (OC1A || OC1B)
		TWO_BITS_WRITE(TCCR1A,WGM10,TWO_BITS_GET(OC1_MODE,BIT0));
		TWO_BITS_WRITE(TCCR1B,WGM12,TWO_BITS_GET(OC1_MODE,BIT2));
	#endif

	#if OC1A
		TWO_BITS_WRITE(TCCR1A,COM1A0,OC1A_WAVEFORM_MODE);			
	#endif
	
	#if OC1B		
		TWO_BITS_WRITE(TCCR1A,COM1B0,OC1B_WAVEFORM_MODE);		
	#endif

	#if OC2
		BIT_WRITE(TCCR2,WGM20,BIT_GET(OC2_MODE,BIT0));
		BIT_WRITE(TCCR2,WGM21,BIT_GET(OC2_MODE,BIT1));
		
		TWO_BITS_WRITE(TCCR2,COM20,OC2_WAVEFORM_MODE);			
	#endif	
}

uint8_t PwmStart(uint8_t PwmChannelNumber)
{
	switch(PwmChannelNumber)
	{
		case PWM_CHANNEL_OC0:
			#if OC0
				THREE_BITS_WRITE(TCCR0,CS00,OC0_FREQUANCY);	
			#endif
			break;
		case PWM_CHANNEL_OC1A:
			#if OC1A
				THREE_BITS_WRITE(TCCR1B,CS10,OC1_FREQUANCY);
			#endif
			break;
		case PWM_CHANNEL_OC1B:
			#if OC1B
				THREE_BITS_WRITE(TCCR1B,CS10,OC1_FREQUANCY);
			#endif
			break;	
		case PWM_CHANNEL_OC2:
			#if OC2
				THREE_BITS_WRITE(TCCR2,CS20,OC2_FREQUANCY);			
			#endif
			break;
		default:
			break;			
	}
}

uint8_t PwmStop(uint8_t PwmChannelNumber )
{
	switch(PwmChannelNumber)
	{
		case PWM_CHANNEL_OC0:
			#if OC0
				THREE_BITS_WRITE(TCCR0,CS00,OC0_NO_CLK);
			#endif
			break;
		case PWM_CHANNEL_OC1A:
			#if OC1A
				THREE_BITS_WRITE(TCCR1B,CS10,OC1_NO_CLK);
			#endif	
			break;
		case PWM_CHANNEL_OC1B:
			#if OC1B
				THREE_BITS_WRITE(TCCR1B,CS10,OC1_NO_CLK);
			#endif
			break;	
		case PWM_CHANNEL_OC2:
			#if OC2
				THREE_BITS_WRITE(TCCR2,CS20,OC2_NO_CLK);			
			#endif
			break;
		default:
			break;			
	}
}

uint8_t PwmConnect(uint8_t PwmChannelNumber)
{
	switch(PwmChannelNumber)
	{
		case PWM_CHANNEL_OC0:
			#if OC0
				TWO_BITS_WRITE(TCCR0,COM00,OC0_WAVEFORM_MODE);
			#endif
			break;
		case PWM_CHANNEL_OC1A:
			#if OC1A
				TWO_BITS_WRITE(TCCR1A,COM1A0,OC1A_WAVEFORM_MODE);
			#endif
			break;
		case PWM_CHANNEL_OC1B:
			#if OC1B
				TWO_BITS_WRITE(TCCR1A,COM1B0,OC1B_WAVEFORM_MODE);
			#endif
			break;	
		case PWM_CHANNEL_OC2:
			#if OC2
				TWO_BITS_WRITE(TCCR2,COM20,OC2_WAVEFORM_MODE);			
			#endif
			break;
		default:
			break;			
	}	
}

uint8_t PwmDisconnect(uint8_t PwmChannelNumber)
{
	switch(PwmChannelNumber)
	{
		case PWM_CHANNEL_OC0:
			#if OC0
				TWO_BITS_WRITE(TCCR0,COM00,DISCONNECT);	
			#endif
			break;
		case PWM_CHANNEL_OC1A:
			#if OC1A
				TWO_BITS_WRITE(TCCR1A,COM1A0,DISCONNECT);
			#endif
			break;
		case PWM_CHANNEL_OC1B:
			#if OC1B
				TWO_BITS_WRITE(TCCR1A,COM1B0,DISCONNECT);
			#endif
			break;	
		case PWM_CHANNEL_OC2:
			#if OC2
				TWO_BITS_WRITE(TCCR2,COM20,DISCONNECT);			
			#endif
			break;
		default:
			break;			
	}	
}

uint8_t PwmSetDuty(uint8_t PwmChannelNumber,uint8_t PwmDuty )
{
	switch(PwmChannelNumber)
	{
		case PWM_CHANNEL_OC0:
			#if OC0
				#if OC0_WAVEFORM_MODE == NON_INVERTING	
					OCR0 = (uint8_t)(((PwmDuty/100.0)*256.0)-1);
				#endif
			#endif	
			break;
		case PWM_CHANNEL_OC1A:
			#if OC1A
				#if ((OC1_MODE==OC1_PHASE_CORRECT_8BITS)||(OC1_MODE==OC1_FAST_PWM_8BITS))
					#if OC1A_WAVEFORM_MODE == NON_INVERTING	
						OCR1A = (uint16_t)(((PwmDuty/100.0)*256.0)-1);
					#endif
				#endif
			#endif
			break;
		case PWM_CHANNEL_OC1B:
			#if OC1B
				#if ((OC1_MODE==OC1_PHASE_CORRECT_8BITS)||(OC1_MODE==OC1_FAST_PWM_8BITS))				
					#if OC1B_WAVEFORM_MODE == NON_INVERTING	
						OCR1B = (uint16_t)(((PwmDuty/100.0)*256.0)-1);
					#endif
				#endif
			#endif
			break;	
		case PWM_CHANNEL_OC2:
			#if OC2
				#if OC2_WAVEFORM_MODE == NON_INVERTING	
					OCR2 = (uint8_t)(((PwmDuty/100.0)*256.0)-1);
				#endif
			#endif
			break;
		default:
			break;			
	}
}