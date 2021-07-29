/*
 * TIMER_DRIVER.c
 *
 *  Created on: Jul 9, 2021
 *      Author: zoldeyck
 */
#include "../../Infrastructure/STD_types.h"
#include "../../Infrastructure/Bit Operations.h"
#include "../DIO/DIO.h"
#include "TIMER_DRIVER_PRIV.h"
#include "TIMER_DRIVER.h"



void __vector_11(void)__attribute__((signal,used));
void __vector_10(void)__attribute__((signal,used));
void __vector_4(void)__attribute__((signal,used));
void __vector_5(void)__attribute__((signal,used));

TIM_ERROR_t TIM_Init(TIM_SELECT_t Timer, TIM_CLK_SELECT_t clock,
		TIMER_MODE_t timer_mode, TIM_CMPMATCH_OUTPUT_t compareMatch_output_mode,
		uint16_t counterValue, uint16_t compareValue) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	if (Timer <= 2 && clock <= 7 && timer_mode <= 3
			&& compareMatch_output_mode <= 3) {
		TIM_MODE_SLCT(Timer, timer_mode);

		TIM_SetTimerPreLoadVal(Timer, counterValue);

		TIM_OC_MODE_SLCT(Timer, compareMatch_output_mode, timer_mode);

		TIM_SetTimerOCVal(Timer, compareValue);

		TIM_CLK_SLCT(Timer, clock);
	} else {
		retVal = EXIT_FAILURE;
	}
	return retVal;
}

TIM_ERROR_t TIM_Delay_US(TIM_SELECT_t Timer, Delay_value_t delayVal) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	uint8_t i = 0;
	uint8_t quotant = delayVal / 256;
	uint8_t remainder = delayVal % 256;
	switch (Timer) {
	case TIMER0:
		if (remainder != 0) {
			TIM_SetTimerPreLoadVal(Timer, 255 - remainder);
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM0OVF) != 1) {
				while (i <= quotant) {
					if (TIM_Flag_Get(Timer, TIM0OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM0OVF);
						i++;
					}
				}
				break;
			}
		} else if (remainder == 0) {
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM0OVF) != 1) {
				while (i < quotant) {
					if (TIM_Flag_Get(Timer, TIM0OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM0OVF);
						i++;
					}
				}
				break;
			}

		}
		break;
	case TIMER2:
		if (remainder != 0) {
			TIM_SetTimerPreLoadVal(Timer, 255 - remainder);
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM2OVF) != 1) {
				while (i <= quotant) {
					if (TIM_Flag_Get(Timer, TIM2OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM2OVF);
						i++;
					}
				}
				break;
			}
		} else if (remainder == 0) {
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM2OVF) != 1) {
				while (i < quotant) {
					if (TIM_Flag_Get(Timer, TIM2OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM2OVF);
						i++;
					}
				}
				break;
			}

		}
		break;

	}
	return retVal;
}
TIM_ERROR_t TIM_Delay_MS(TIM_SELECT_t Timer, Delay_value_t delayVal) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	uint32_t i = 0;
	volatile uint32_t quotant = (delayVal*1000) / 256;
	volatile uint8_t remainder = (delayVal*1000) % 256;
	switch (Timer) {
	case TIMER0:
		if (remainder != 0) {
			TIM_SetTimerPreLoadVal(Timer, 255 - remainder);
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM0OVF) != 1) {
				while (i <= quotant) {
					if (TIM_Flag_Get(Timer, TIM0OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM0OVF);
						i++;
					}
				}
				break;
			}
		} else if (remainder == 0) {
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM0OVF) != 1) {
				while (i < quotant) {
					if (TIM_Flag_Get(Timer, TIM0OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM0OVF);
						i++;
					}
				}
				break;
			}

		}
		break;
	case TIMER2:
		if (remainder != 0) {
			TIM_SetTimerPreLoadVal(Timer, 255 - remainder);
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM2OVF) != 1) {
				while (i <= quotant) {
					if (TIM_Flag_Get(Timer, TIM2OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM2OVF);
						i++;
					}
				}
				break;
			}
		} else if (remainder == 0) {
			TIM_CLK_SLCT(Timer, _SYSCLK_DivideBy8);
			while (TIM_Flag_Get(Timer, TIM2OVF) != 1) {
				while (i < quotant) {
					if (TIM_Flag_Get(Timer, TIM2OVF) == 1) {
						TIM_Flag_Reset(Timer, TIM2OVF);
						i++;
					}
				}
				break;
			}

		}
		break;

	}
	return retVal;
}

TIM_ERROR_t TIM_SetTimerPreLoadVal(TIM_SELECT_t Timer, uint16_t counterValue) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		WRITE_REG(TIM0_CurrCount_REG, (uint8_t )counterValue);
		break;
	case TIMER1:
		break;
	case TIMER2:
		WRITE_REG(TIM2_CurrCount_REG, (uint8_t )counterValue);
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_SetTimerOCVal(TIM_SELECT_t Timer, uint16_t compareValue) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		WRITE_REG(TIM0_OutputComp_REG, (uint8_t )compareValue);
		break;
	case TIMER1:
		break;
	case TIMER2:
		WRITE_REG(TIM2_OutputComp_REG, (uint8_t )compareValue);
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_SetTimerOVFAction(TIM_SELECT_t Timer, void (*callback)(void)) {
	TIM_ERROR_t retVal;
	switch (Timer) {
	case TIMER0:
		if (callback != NULL_PTR) {
			TIM0_OVFAction_callback = callback;
		} else {
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:
		break;
	case TIMER2:
		if (callback != NULL_PTR) {
			TIM2_OVFAction_callback = callback;
		} else {
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_SetTimerOCAction(TIM_SELECT_t Timer, void (*callback)(void)) {
	TIM_ERROR_t retVal;
	switch (Timer) {
	case TIMER0:
		if (callback != NULL_PTR) {
			TIM0_OCAction_callback = callback;
		} else {
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:
		break;
	case TIMER2:
		if (callback != NULL_PTR) {
			TIM2_OCAction_callback = callback;
		} else {
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_MODE_SLCT(TIM_SELECT_t Timer, TIMER_MODE_t mode) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		switch (mode) {
		case Normal:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_MODE_SELECT_CLRMSK,
					TIM0_Normal_SETMSK);
			break;
		case CLR_Timer_OnCompare:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_MODE_SELECT_CLRMSK,
					TIM0_CLR_Timer_OnCompare_SETMSK);
			break;
		case PWM_PhaseCorrect:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_MODE_SELECT_CLRMSK,
					TIM0_PWM_PhaseCorrect_SETMSK);
			break;
		case Fast_PWM:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_MODE_SELECT_CLRMSK,
					TIM0_Fast_PWM_SETMSK);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:

		break;
	case TIMER2:
		switch (mode) {
		case Normal:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_MODE_SELECT_CLRMSK,
					TIM2_Normal_SETMSK);
			break;
		case CLR_Timer_OnCompare:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_MODE_SELECT_CLRMSK,
					TIM2_CLR_Timer_OnCompare_SETMSK);
			break;
		case PWM_PhaseCorrect:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_MODE_SELECT_CLRMSK,
					TIM2_PWM_PhaseCorrect_SETMSK);
			break;
		case Fast_PWM:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_MODE_SELECT_CLRMSK,
					TIM2_Fast_PWM_SETMSK);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_CLK_SLCT(TIM_SELECT_t Timer, TIM_CLK_SELECT_t clock) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		switch (clock) {
		case _NoCLK:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_NoCLK_SETMSK);
			break;
		case _SYSCLK:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_SYSCLK_SETMSK);
			break;
		case _SYSCLK_DivideBy8:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_SYSCLK_DivideBy8_SETMSK);
			break;
		case _SYSCLK_DivideBy64:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_SYSCLK_DivideBy64_SETMSK);
			break;
		case _SYSCLK_DivideBy256:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_SYSCLK_DivideBy256_SETMSK);
			break;
		case _SYSCLK_DivideBy1024:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_SYSCLK_DivideBy1024_SETMSK);
			break;
		case _EXTCLK_FallingEdge:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_EXTCLK_FallingEdge_SETMSK);
			break;
		case _EXTCLK_RisingEdge:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_CLK_PRSCLR_CTRL_CLRMSK,
					TIM0_EXTCLK_RisingEdge_SETMSK);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break; //end case TIMER0
	case TIMER1:

		break; //end case TIMER1
	case TIMER2:
		switch (clock) {
		case _NoCLK:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_NoCLK_SETMSK);
			break;
		case _SYSCLK:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_SYSCLK_SETMSK);
			break;
		case _SYSCLK_DivideBy8:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_SYSCLK_DivideBy8_SETMSK);
			break;
		case _SYSCLK_DivideBy64:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_SYSCLK_DivideBy64_SETMSK);
			break;
		case _SYSCLK_DivideBy256:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_SYSCLK_DivideBy256_SETMSK);
			break;
		case _SYSCLK_DivideBy1024:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_SYSCLK_DivideBy1024_SETMSK);
			break;
		case _EXTCLK_FallingEdge:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_EXTCLK_FallingEdge_SETMSK);
			break;
		case _EXTCLK_RisingEdge:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_CLK_PRSCLR_CTRL_CLRMSK,
					TIM2_EXTCLK_RisingEdge_SETMSK);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break; //end case TIMER2
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_OC_MODE_SLCT(TIM_SELECT_t Timer,
		TIM_CMPMATCH_OUTPUT_t compareMatch_output_mode, TIMER_MODE_t mode) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	TIM_Init_OC_PIN(Timer, compareMatch_output_mode);
	switch (Timer) {
	case TIMER0:
		switch (compareMatch_output_mode) {
		case CO_DISABLED_MODE:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_OC0_OUTPUT_CTRL_CLRMSK,
					TIM0_CO_DISABLED_MODE_SETMSK);
			break;
		case CO_TOGGLE_MODE:
			if (mode == Normal || mode == CLR_Timer_OnCompare) {
				MODIFY_REG(TIM0_Ctrl_REG, TIM0_OC0_OUTPUT_CTRL_CLRMSK,
						TIM0_CO_TOGGLE_MODE_SETMSK);
			} else {
				retVal = EXIT_FAILURE;
			}
			break;
		case CO_CLEAR_MODE:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_OC0_OUTPUT_CTRL_CLRMSK,
					TIM0_CO_CLEAR_MODE_SETMSK);
			break;
		case CO_SET_MODE:
			MODIFY_REG(TIM0_Ctrl_REG, TIM0_OC0_OUTPUT_CTRL_CLRMSK,
					TIM0_CO_SET_MODE_SETMSK);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:
		break;
	case TIMER2:
		switch (compareMatch_output_mode) {
		case CO_DISABLED_MODE:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_OC2_OUTPUT_CTRL_CLRMSK,
					TIM2_CO_DISABLED_MODE_SETMSK);
			break;
		case CO_TOGGLE_MODE:
			if (mode == Normal || mode == CLR_Timer_OnCompare) {
				MODIFY_REG(TIM2_Ctrl_REG, TIM2_OC2_OUTPUT_CTRL_CLRMSK,
						TIM2_CO_TOGGLE_MODE_SETMSK);
			} else {
				retVal = EXIT_FAILURE;
			}
			break;
		case CO_CLEAR_MODE:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_OC2_OUTPUT_CTRL_CLRMSK,
					TIM2_CO_CLEAR_MODE_SETMSK);
			break;
		case CO_SET_MODE:
			MODIFY_REG(TIM2_Ctrl_REG, TIM2_OC2_OUTPUT_CTRL_CLRMSK,
					TIM2_CO_SET_MODE_SETMSK);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_Interrupt_Enable(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	SET_BIT(STATUS_REG, GLOBAL_Interrupt_Enable_BIT);

	switch (Timer) {
	case TIMER0:
		switch (interrupt) {
		case TIM0OVF:
			SET_BIT(TIMS_InterruptMask_REG, TIM0_OverFlow_Interrupt_Enable_BIT);
			break;
		case TIM0COMP:
			SET_BIT(TIMS_InterruptMask_REG,
					TIM0_OutputComp_Interrupt_Enable_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:
		break;
	case TIMER2:
		switch (interrupt) {
		case TIM2OVF:
			SET_BIT(TIMS_InterruptMask_REG, TIM2_OverFlow_Interrupt_Enable_BIT);
			break;
		case TIM2COMP:
			SET_BIT(TIMS_InterruptMask_REG,
					TIM2_OutputComp_Interrupt_Enable_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_Interrupt_Disable(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		switch (interrupt) {
		case TIM0OVF:
			CLEAR_BIT(TIMS_InterruptMask_REG,
					TIM0_OverFlow_Interrupt_Enable_BIT);
			break;
		case TIM0COMP:
			CLEAR_BIT(TIMS_InterruptMask_REG,
					TIM0_OutputComp_Interrupt_Enable_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:
		break;
	case TIMER2:
		switch (interrupt) {
		case TIM2OVF:
			CLEAR_BIT(TIMS_InterruptMask_REG,
					TIM2_OverFlow_Interrupt_Enable_BIT);
			break;
		case TIM2COMP:
			CLEAR_BIT(TIMS_InterruptMask_REG,
					TIM2_OutputComp_Interrupt_Enable_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_FLAG_STAT_t TIM_Flag_Get(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt) {
	TIM_FLAG_STAT_t retVal = TIM_FLAG_DOWN;
	switch (Timer) {
	case TIMER0:
		switch (interrupt) {
		case TIM0OVF:
			retVal = READ_BIT(TIMS_InterruptFlag_REG,
					TIM0_OVF_Interrupt_Flg_BIT);
			break;
		case TIM0COMP:
			retVal = READ_BIT(TIMS_InterruptFlag_REG,
					TIM0_OC_Interrupt_Flg_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}

		break;
	case TIMER1:
		break;
	case TIMER2:
		switch (interrupt) {
		case TIM2OVF:
			retVal = READ_BIT(TIMS_InterruptFlag_REG,
					TIM2_OVF_Interrupt_Flg_BIT);
			break;
		case TIM2COMP:
			retVal = READ_BIT(TIMS_InterruptFlag_REG,
					TIM2_OC_Interrupt_Flg_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}

	return retVal;
}
TIM_ERROR_t TIM_Flag_Reset(TIM_SELECT_t Timer, TIM_Interrupt_t interrupt) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		switch (interrupt) {
		case TIM0OVF:
			retVal = SET_BIT(TIMS_InterruptFlag_REG,
					TIM0_OVF_Interrupt_Flg_BIT);
			break;
		case TIM0COMP:
			retVal = SET_BIT(TIMS_InterruptFlag_REG, TIM0_OC_Interrupt_Flg_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}

		break;
	case TIMER1:
		break;
	case TIMER2:
		switch (interrupt) {
		case TIM2OVF:
			retVal = SET_BIT(TIMS_InterruptFlag_REG,
					TIM2_OVF_Interrupt_Flg_BIT);
			break;
		case TIM2COMP:
			retVal = SET_BIT(TIMS_InterruptFlag_REG, TIM2_OC_Interrupt_Flg_BIT);
			break;
		default:
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
TIM_ERROR_t TIM_Init_OC_PIN(TIM_SELECT_t Timer,
		TIM_CMPMATCH_OUTPUT_t compareMatch_output_mode) {
	TIM_ERROR_t retVal = EXIT_SUCCESFUL;
	switch (Timer) {
	case TIMER0:
		if (compareMatch_output_mode != CO_DISABLED_MODE) {
			retVal = DIO_SetPinDirection(PORT_B, PIN3, PIN_OUTPUT);
		} else {
			retVal = EXIT_FAILURE;
		}
		break;
	case TIMER1:
		break;
	case TIMER2:
		if (compareMatch_output_mode != CO_DISABLED_MODE) {
			retVal = DIO_SetPinDirection(PORT_D, PIN7, PIN_OUTPUT);
		} else {
			retVal = EXIT_FAILURE;
		}
		break;
	default:
		retVal = EXIT_FAILURE;
	}
	return retVal;
}
void __vector_11(void) {
	if (TIM0_OVFAction_callback != NULL_PTR)
		TIM0_OVFAction_callback();
}
void __vector_10(void) {
	if (TIM0_OCAction_callback != NULL_PTR)
		TIM0_OCAction_callback();
}
void __vector_5(void) {
	if (TIM2_OVFAction_callback != NULL_PTR)
		TIM2_OVFAction_callback();
}
void __vector_4(void) {
	if (TIM2_OCAction_callback != NULL_PTR)
		TIM2_OCAction_callback();
}


