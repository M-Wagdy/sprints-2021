#include "../../Infrastructure/infrastructure.h"
#include "../DIO/DIO_DRIVER.h"
#include "../DIO/DIO_DRIVER_Priv.h"

DIO_ERROR_RETVAL_t DIO_PortInit(DIO_PORT_ID_t DIO_port,
		DIO_DIRECTION_t DIO_direction) {
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;

	if ((DIO_port <= PORTD)
			&& (DIO_direction == PORT_INPUT || DIO_direction == PORT_OUTPUT)) {
		switch (DIO_port) {
		case PORTA:
			WRITE_REG(DDRA_Register, DIO_direction);
			break;
		case PORTB:
			WRITE_REG(DDRB_Register, DIO_direction);
			break;
		case PORTC:
			WRITE_REG(DDRC_Register, DIO_direction);
			break;
		case PORTD:
			WRITE_REG(DDRD_Register, DIO_direction);
			break;
		default:
			ErrorValue = EXIT_FAILURE;
			break;
		}
	} else {
		ErrorValue = EXIT_FAILURE;
	}
	return ErrorValue;
}
DIO_ERROR_RETVAL_t DIO_SetPortVal(DIO_PORT_ID_t DIO_port, uint8_t value) {
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;
	if ((DIO_port <= PORTD)) {
		switch (DIO_port) {
		case PORTA:

			MODIFY_REG(PORTA_Register, value, value);

			break;
		case PORTB:

			MODIFY_REG(PORTB_Register, value, value);

			break;
		case PORTC:

			MODIFY_REG(PORTC_Register, value, value);

			break;
		case PORTD:

			MODIFY_REG(PORTD_Register, value, value);

			break;
		default:
			ErrorValue = EXIT_FAILURE;
			break;
		}
	} else {
		ErrorValue = EXIT_FAILURE;
	}
	return ErrorValue;
}
DIO_ERROR_RETVAL_t DIO_ClrPortVal(DIO_PORT_ID_t DIO_port, uint8_t value) {
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;
	if ((DIO_port <= PORTD)) {
		switch (DIO_port) {
		case PORTA:

			MODIFY_REG(PORTA_Register, value, ~value);

			break;
		case PORTB:

			MODIFY_REG(PORTB_Register, value, ~value);

			break;
		case PORTC:

			MODIFY_REG(PORTC_Register, value, ~value);

			break;
		case PORTD:

			MODIFY_REG(PORTD_Register, value, ~value);

			break;
		default:
			ErrorValue = EXIT_FAILURE;
			break;
		}
	} else {
		ErrorValue = EXIT_FAILURE;
	}
	return ErrorValue;
}
uint8_t DIO_GetPortVal(DIO_PORT_ID_t DIO_port) {
	uint8_t RETVAL = EXIT_FAILURE;
	if ((DIO_port <= PORTD)) {
		/* Check on the Required PORT Number */
		switch (DIO_port) {
		case PORTA:
			RETVAL = READ_REG(PINA_Register);
			break;
		case PORTB:
			RETVAL = READ_REG(PINB_Register);
			break;
		case PORTC:
			RETVAL = READ_REG(PINC_Register);
			break;
		case PORTD:
			RETVAL = READ_REG(PIND_Register);
			break;
		default:
			RETVAL = EXIT_FAILURE;
			break;
		}
	} else {
		RETVAL = EXIT_FAILURE;
	}
	return RETVAL;
}
DIO_ERROR_RETVAL_t DIO_TogPortVal(DIO_PORT_ID_t DIO_port, uint8_t value) {
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;
	if ((DIO_port <= PORTD)) {
		switch (DIO_port) {
		case PORTA:
			if (READ_REG(DDRA_Register) == PORT_OUTPUT) {
				TOG_REG(PORTA_Register, value);
			} else {
				ErrorValue = EXIT_FAILURE;
			}
			break;
		case PORTB:
			if (READ_REG(DDRB_Register) == PORT_OUTPUT) {
				TOG_REG(PORTB_Register, value);
			} else {
				ErrorValue = EXIT_FAILURE;
			}
			break;
		case PORTC:
			if (READ_REG(DDRC_Register) == PORT_OUTPUT) {
				TOG_REG(PORTC_Register, value);
			} else {
				ErrorValue = EXIT_FAILURE;
			}
			break;
		case PORTD:
			if (READ_REG(DDRD_Register) == PORT_OUTPUT) {
				TOG_REG(PORTD_Register, value);
			} else {
				ErrorValue = EXIT_FAILURE;
			}
			break;
		default:
			ErrorValue = EXIT_FAILURE;
			break;
		}
	} else {
		ErrorValue = EXIT_FAILURE;
	}
	return ErrorValue;
}
/*main APIs*/
uint8_t DIO_SetPinDirection(uint8_t PortName, uint8_t PinNo,
		uint8_t PinDirection) {
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;

	if ((PortName <= PORTD) && (PinNo <= PIN7)) {
		if (PinDirection == PIN_OUTPUT) {

			switch (PortName) {
			case PORTA:
				SET_BIT(DDRA_Register, PinNo);
				break;
			case PORTB:
				SET_BIT(DDRB_Register, PinNo);
				break;
			case PORTC:
				SET_BIT(DDRC_Register, PinNo);
				break;
			case PORTD:
				SET_BIT(DDRD_Register, PinNo);
				break;
			default:
				ErrorValue = EXIT_FAILURE;
				break;
			}
		} else if (PinDirection == PIN_INPUT) {

			switch (PortName) {
			case PORTA:
				CLEAR_BIT(DDRA_Register, PinNo);
				break;
			case PORTB:
				CLEAR_BIT(DDRB_Register, PinNo);
				break;
			case PORTC:
				CLEAR_BIT(DDRC_Register, PinNo);
				break;
			case PORTD:
				CLEAR_BIT(DDRD_Register, PinNo);
				break;
			default:
				ErrorValue = EXIT_FAILURE;
				break;
			}
		}

		else {
			ErrorValue = EXIT_FAILURE;
		}
	}

	else {
		ErrorValue = EXIT_FAILURE;
	}
	return ErrorValue;
}
uint8_t DIO_WritePin(uint8_t PortName , uint8_t PinNo ,uint8_t PinValue)
{
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;
		if ((PortName <= PORTD) && (PinNo <= PIN7)) {
			if (PinValue == PIN_HIGH) {

				switch (PortName) {
				case PORTA:
					if (READ_BIT(DDRA_Register, PinNo) == PIN_OUTPUT) {
						SET_BIT(PORTA_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				case PORTB:
					if (READ_BIT(DDRB_Register, PinNo) == PIN_OUTPUT) {
						SET_BIT(PORTB_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				case PORTC:
					if (READ_BIT(DDRC_Register, PinNo) == PIN_OUTPUT) {
						SET_BIT(PORTC_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				case PORTD:
					if (READ_BIT(DDRD_Register, PinNo) == PIN_OUTPUT) {
						SET_BIT(PORTD_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				default:
					ErrorValue = EXIT_FAILURE;
					break;
				}
			} else if (PinValue == PIN_LOW) {

				switch (PortName) {
				case PORTA:
					if (READ_BIT(DDRA_Register, PinNo) == PIN_OUTPUT) {
						CLEAR_BIT(PORTA_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				case PORTB:
					if (READ_BIT(DDRB_Register, PinNo) == PIN_OUTPUT) {
						CLEAR_BIT(PORTB_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				case PORTC:
					if (READ_BIT(DDRC_Register, PinNo) == PIN_OUTPUT) {
						CLEAR_BIT(PORTC_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				case PORTD:
					if (READ_BIT(DDRD_Register, PinNo) == PIN_OUTPUT) {
						CLEAR_BIT(PORTD_Register, PinNo);
					} else {
						ErrorValue = EXIT_FAILURE;
					}
					break;
				default:
					ErrorValue = EXIT_FAILURE;
					break;
				}
			} else {
				ErrorValue = EXIT_FAILURE;
			}
		} else {
			ErrorValue = EXIT_FAILURE;
		}
		return ErrorValue;
}
uint8_t DIO_TogglePin(uint8_t PortName,uint8_t PinNo)
{
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;
		if ((PortName <= PORTD) && (PinNo <= PIN7)) {
			switch (PortName) {
			case PORTA:
				if (READ_BIT(DDRA_Register, PinNo) == PIN_OUTPUT) {
					TOG_BIT(PORTA_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			case PORTB:
				if (READ_BIT(DDRB_Register, PinNo) == PIN_OUTPUT) {
					TOG_BIT(PORTB_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			case PORTC:
				if (READ_BIT(DDRC_Register, PinNo) == PIN_OUTPUT) {
					TOG_BIT(PORTC_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			case PORTD:
				if (READ_BIT(DDRD_Register, PinNo) == PIN_OUTPUT) {
					TOG_BIT(PORTD_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			default:
				ErrorValue = EXIT_FAILURE;
				break;
			}
		} else {
			ErrorValue = EXIT_FAILURE;
		}
		return ErrorValue;
}
uint8_t DIO_ReadPin(uint8_t PortName,uint8_t PinNo,ptr_uint8_t PinData)
{
	uint8_t RETVAL = EXIT_SUCCESFUL;
		if ((PortName <= PORTD) && (PinNo <= PIN7)) {

			switch (PortName) {
			case PORTA:
				*PinData = READ_BIT(PINA_Register, PinNo);
				break;
			case PORTB:
				*PinData = READ_BIT(PINB_Register, PinNo);
				break;
			case PORTC:
				*PinData = READ_BIT(PINC_Register, PinNo);
				break;
			case PORTD:
				*PinData = READ_BIT(PIND_Register, PinNo);
				break;
			default:
				RETVAL = EXIT_FAILURE;
			}
		} else {
			RETVAL = EXIT_FAILURE;
		}

		return RETVAL;
}
uint8_t DIO_EnablePinPullup(uint8_t PortName,uint8_t PinNo)
{
	DIO_ERROR_RETVAL_t ErrorValue = EXIT_SUCCESFUL;
		if ((PortName <= PORTD) && (PinNo <= PIN7)) {
			/* Check on the Required PORT Number */
			switch (PortName) {
			case PORTA:
				if (READ_REG(DDRA_Register) == PIN_INPUT) {
					SET_BIT(PORTA_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			case PORTB:
				if (READ_REG(DDRB_Register) == PIN_INPUT) {
					SET_BIT(PORTB_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			case PORTC:
				if (READ_REG(DDRC_Register) == PIN_INPUT) {
					SET_BIT(PORTC_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			case PORTD:
				if (READ_REG(DDRD_Register) == PIN_INPUT) {
					SET_BIT(PORTD_Register, PinNo);
				} else {
					ErrorValue = EXIT_FAILURE;
				}
				break;
			default:
				ErrorValue = EXIT_FAILURE;
				break;
			}
		} else {
			ErrorValue = EXIT_FAILURE;
		}
		return ErrorValue;
}
