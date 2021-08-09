/*INCLUDES
 -------------------------------*/

#include"uart.h"
#include"uartReg.h"
/*LOCAL MACROS
 --------------------------*/
//UART CONTROL AND STATUS REGISTER A BITS (UCSRA)
#define RXC    (uint8_t)7 //READ ONLY , INIT VALUE 0
#define TXC    (uint8_t)6 //READ/WRITE, INIT VALUE 0
#define UDRE   (uint8_t)5 //READ ONLY , INIT VALUE 1
#define FE     (uint8_t)4 //READ ONLY , INIT VALUE 0
#define DOR    (uint8_t)3 //READ ONLY , INIT VALUE 0
#define PE     (uint8_t)2 //READ ONLY , INIT VALUE 0
#define U2X    (uint8_t)1 //READ/WRITE, INIT VALUE 0
#define MPCM   (uint8_t)0 //READ/WRITE, INIT VALUE 0

//UART CONTROL AND STATUS REGISTER B BITS (UCSRB)
#define RXCIE  (uint8_t)7 //READ/WRITE, INIT VALUE 0
#define TXCIE  (uint8_t)6 //READ/WRITE, INIT VALUE 0
#define UDRIE  (uint8_t)5 //READ/WRITE, INIT VALUE 0
#define RXEN   (uint8_t)4 //READ/WRITE, INIT VALUE 0
#define TXEN   (uint8_t)3 //READ/WRITE, INIT VALUE 0
#define UCSZ2  (uint8_t)2 //READ/WRITE, INIT VALUE 0
#define RXB8   (uint8_t)1 //READ ONLY , INIT VALUE 0
#define TXB8   (uint8_t)0 //READ/WRITE, INIT VALUE 0

//UART CONTROL AND STATUS REGISTER C BITS (UCSRC)
#define URSEL  (uint8_t)7 //READ/WRITE, INIT VALUE 1
#define UMSEL  (uint8_t)6 //READ/WRITE, INIT VALUE 0
#define UPM1   (uint8_t)5 //READ/WRITE, INIT VALUE 0
#define UPM0   (uint8_t)4 //READ/WRITE, INIT VALUE 0
#define USBS   (uint8_t)3 //READ/WRITE, INIT VALUE 0
#define UCSZ1  (uint8_t)2 //READ/WRITE, INIT VALUE 1
#define UCSZ0  (uint8_t)1 //READ/WRITE, INIT VALUE 1
#define UCPOL  (uint8_t)0 //READ/WRITE, INIT VALUE 0

/*UCSRC MODES*/
#define ASYNCHRONOUS   (uint8_t)0b10111111
#define SYNCHRONOUS    (uint8_t)0b11111111
#define ONE_STOP_BIT   (uint8_t)0b11110111
#define TWO_STOP_BIT   (uint8_t)0b11111111
#define FIVE_BITS      (uint8_t)0b11111001
#define SIX_BITS       (uint8_t)0b11111011
#define SEVEN_BITS     (uint8_t)0b11111101
#define EIGHT_BITS     (uint8_t)0b11111111
#define NINE_BITS      (uint8_t)0b11111111
#define PARITY_DISABLE (uint8_t)0b11001111
#define EVEN_PARITY    (uint8_t)0b11101111
#define ODD_PARITY     (uint8_t)0b11111111
#define DISABLE_CLOCK       (uint8_t)0b11111110
#define TRANSIMT_ON_RISING  (uint8_t)0b11111110
#define TRANSIMT_ON_FALLING (uint8_t)0b11111111

/*BAUD RATES*/
#define BT_2400_8MHz  207
#define BT_4800_8MHz  103
#define BT_9600_8MHz  51
#define BT_14400_8MHz 34
#define BT_19200_8MHz 25
#define BT_28800_8MHz 16
#define BT_38400_8MHz 12

/*UCSRB MODES*/
#define RECEIVER_EN          1
#define RECEIVER_DIS         0

#define TRANSMITTER_EN       1
#define TRANSMITTER_DIS      0

#define NORMAL_SPEED         0
#define DOUBLE_SPEED         1

/*GLOBAL STATIC VARIABLES
 -------------------------------*/
Ptr_VoidFuncVoid_t Gptr_uartRxInt=NULL_PTR;
Ptr_VoidFuncVoid_t Gptr_uartDataEmptyRegInt=NULL_PTR;
Ptr_VoidFuncVoid_t Gptr_uartTxInt=NULL_PTR;
uint8_t gu8_InitFlag = NOT_INIT;

/*APIs IMPLEMENTATION
 -------------------------*/
UART_ERROR_state_t UART_Init(uint8_t UartNumber) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
    if (UartNumber>UART_1){
		au8_ERROR_STAT=UART_INVALID_CHANNEL;
	}
	else{
        if (INIT==gu8_InitFlag){
            au8_ERROR_STAT=UART_SEC_INIT;
        }
        else if (NOT_INIT==gu8_InitFlag){
#if RECEIVEING
	Set_Bit(UCSRB, RXEN);
#else
	Clr_Bit(UCSRB,RXEN);
#endif
#if TRANSMITTING
	Set_Bit(UCSRB, TXEN);
#else
	Clr_Bit(UCSRB,TXEN);
#endif
#if SPEED
	Set_Bit(UCSRA,U2X);
#else
	Clr_Bit(UCSRA, U2X);
#endif
#if NINE_BIT
	Set_Bit(UCSRB, UCSZ2);
#else
	Clr_Bit(UCSRB, UCSZ2);
#endif
        UCSRC |= ((SYNCHRONIZATION ) & (STOP_BITS ) & (CHARACTER_SIZE )
                & (PARITY_MODE ) & (CLOCK_POLARITY ));
        UBRRL = BUAD_RATE;
        }
        else{
        //DO NOTHING
        }
	}
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_TransmitChar(uint8_t UartNumber, uint8_t TxChar) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
    if (UartNumber>UART_1){
		au8_ERROR_STAT=UART_INVALID_CHANNEL;
	}
	else{
        if(NOT_INIT==gu8_InitFlag){
            au8_ERROR_STAT=UART_NOT_INIT;
        }
        else if (INIT==gu8_InitFlag){
        UDR = TxChar;
        while ((Get_Bit(UCSRA, UDRE)) != 1) {
        }
        }
        else{
            //DO NOTHING
        }
	}
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_TransmitString(uint8_t UartNumber, ptr_uint8_t TxString) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
    if(NULL_PTR==TxString){
        au8_ERROR_STAT=UART_NULL_POINTER;
    }
    else{
        if (UartNumber>UART_1){
            au8_ERROR_STAT=UART_INVALID_CHANNEL;
        }
        else{
            if(NOT_INIT==gu8_InitFlag){
                au8_ERROR_STAT=UART_NOT_INIT;
            }
            else if (INIT==gu8_InitFlag){
            uint8_t counter = 0;
            while ((*(TxString + counter)) != NULL_TERMINATOR) {
                UDR = *(TxString + counter);//TxString[counter]
                while ((Get_Bit(UCSRA, UDRE)) != 1) ;
                counter++;
            }
            }
            else{
                //DO NOTHING
            }
        }
    }
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_ReceiveChar(uint8_t UartNumber, ptr_uint8_t RxChar) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
    if(NULL_PTR==RxChar){
        au8_ERROR_STAT=UART_NULL_POINTER;
    }
    else{
        if (UartNumber>UART_1){
            au8_ERROR_STAT=UART_INVALID_CHANNEL;
        }//if
        else{
            if(NOT_INIT==gu8_InitFlag){
                au8_ERROR_STAT=UART_NOT_INIT;
            }//if
            else if (INIT==gu8_InitFlag){
            while ( !(UCSRA & (1<<RXC)) );
            *(RxChar) = (uint8_t)UDR;
            }//else if
            else{
                //DO NOTHING
            }//else
        }//else
    }
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_ReceiveString(uint8_t UartNumber, ptr_uint8_t RxString) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
    if(NULL_PTR==RxString){
        au8_ERROR_STAT=UART_NULL_POINTER;
    }
    else{
        if (UartNumber>UART_1){
            au8_ERROR_STAT=UART_INVALID_CHANNEL;
        }
        else{
            if(NOT_INIT==gu8_InitFlag){
                au8_ERROR_STAT=UART_NOT_INIT;
            }//if
            else if (INIT==gu8_InitFlag){
            uint8_t counter = 0;
            while (1) {
                while ( !(UCSRA & (1<<RXC)) );
                RxString[counter] = (uint8_t)UDR;
                UART_TransmitChar(UART_1,RxString[counter]);
                counter++;
                if((UDR)==(NEW_LINE)){
                    RxString[counter-1]=NULL_TERMINATOR;
                    break;
                }//if
                else if(((UDR)==(BACKSPACE))&&counter>1){
                    counter=counter-2;
                }//else if
                else if(((UDR)==(BACKSPACE))&&counter<=1){
                    counter=0;
                }//else if
                else{
                        //DO NOTHING
                }//else
            }//while
            }//else if
            else{
                //DO NOTHING
            }//else
        }//else
    }//else
	//*(RxString+counter)='\n';
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_EnableInterrupt(uint8_t UartNumber, uint8_t UartInterruptType) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=UART_NOT_INIT;
	}
	else if (INIT==gu8_InitFlag){
        switch (UartNumber) {
        case UART_1 :
            switch (UartInterruptType) {
            case RECIVE_INT :
                Set_Bit(UCSRB, RXCIE);
                break;
            case TRANSMIT_INT :
                Set_Bit(UCSRB, TXCIE);
                break;
            case EMPTY_BUFFERR_INT :
                Set_Bit(UCSRB, UDRIE);
                break;
            default:
                au8_ERROR_STAT=UART_INTERRUPT_CHANNEL;
                break;
            }//switch
            break;
        default:

            au8_ERROR_STAT=UART_INVALID_CHANNEL;
            break;
        }//switch
	}//else if
	else{
        //DO NOTHING
	}
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_DisableInterrupt(uint8_t UartNumber, uint8_t UartInterruptType) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	if(NOT_INIT==gu8_InitFlag){
		au8_ERROR_STAT=UART_NOT_INIT;
	}
	else if (INIT==gu8_InitFlag){
        switch (UartNumber) {
        case UART_1 :
            switch (UartInterruptType) {
            case RECIVE_INT :
                Clr_Bit(UCSRB, RXCIE);
                break;
            case TRANSMIT_INT :
                Clr_Bit(UCSRB, TXCIE);
                break;
            case EMPTY_BUFFERR_INT :
                Clr_Bit(UCSRB, UDRIE);
                break;
            default:
                au8_ERROR_STAT=UART_INTERRUPT_CHANNEL;
                break;
            }
            break;
        default:
            au8_ERROR_STAT=UART_INVALID_CHANNEL;
            break;
        }//switch
	}
	else{
        //DO NOTHING
	}
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_SetCallback(uint8_t UartNumber,uint8_t UartInterruptType,Ptr_VoidFuncVoid_t Callback){
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
    if(NULL_PTR==Callback){
        au8_ERROR_STAT=UART_NULL_POINTER;
    }//if
    else{
        if(NOT_INIT==gu8_InitFlag){
            au8_ERROR_STAT=UART_NOT_INIT;
        }//if
        else if (INIT==gu8_InitFlag){
            switch (UartNumber) {
            case UART_1 :
                switch (UartInterruptType) {
                case RECIVE_INT :
                    Gptr_uartRxInt=Callback;
                    break;
                case TRANSMIT_INT :
                    Gptr_uartTxInt=Callback;
                    break;
                case EMPTY_BUFFERR_INT :
                    Gptr_uartDataEmptyRegInt=Callback;
                    break;
                default:
                    au8_ERROR_STAT=UART_INTERRUPT_CHANNEL;
                    break;
                }
                break;
            default:
                au8_ERROR_STAT=UART_INVALID_CHANNEL;
                break;
            }//switch
        }
        else{
            //DO NOTHING
        }
    }
    return au8_ERROR_STAT;
}

