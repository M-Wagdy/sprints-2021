/*INCLUDES-------------------------------*/
#include "uartRetVal.h"
#include"uartReg.h"
#include"uart.h"

/*LOCAL MACROS--------------------------*/
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
static uint8_t gu8_InitFlag = NOT_INIT;

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
        gu8_InitFlag=INIT;
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
    if(NULL_PTR==TxString){//CHECK IF THE POINTER IS NOT = NULL
        au8_ERROR_STAT=UART_NULL_POINTER;//IF IT IS NULL POINTER STORE NULL POINTERR TO THE ERROR STAT
    }
    else{
        if (UartNumber>UART_1){//CHECK IF USER ENTERED RIGHT UART CHANNEL
            au8_ERROR_STAT=UART_INVALID_CHANNEL;
        }
        else{
            if(NOT_INIT==gu8_InitFlag){
                au8_ERROR_STAT=UART_NOT_INIT;
            }
            else if (INIT==gu8_InitFlag){//CHECK IF THE UART HAS BEEN INITIALIZED
            uint8_t au8_counter = 0;
            while ((*(TxString + au8_counter)) != NULL_TERMINATOR) {
                UDR = *(TxString + au8_counter);//TxString[au8_counter]
                while ((Get_Bit(UCSRA, UDRE)) != 1) ;
                au8_counter++;
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
    if(NULL_PTR==RxChar){//CHECK IF THE POINTER IS NOT = NULL
        au8_ERROR_STAT=UART_NULL_POINTER;
    }
    else{
        if (UartNumber>UART_1){//CHECK IF USER ENTERED RIGHT UART CHANNEL
            au8_ERROR_STAT=UART_INVALID_CHANNEL;
        }//if
        else{
            if(NOT_INIT==gu8_InitFlag){//CHECK IF THE UART HAS BEEN INITIALIZED
                au8_ERROR_STAT=UART_NOT_INIT;
            }//if
            else if (INIT==gu8_InitFlag){
            while ( !(UCSRA & (1<<RXC)) );//WAIT FOR THE FLAG
            *(RxChar) = (uint8_t)UDR;//STORE DATA CAME BY UART
            }//else if
            else{
                //DO NOTHING
            }//else
        }//else
    }
	return au8_ERROR_STAT;
}
UART_ERROR_state_t UART_ReceiveString(uint8_t UartNumber, ptr_uint8_t RxString) {
	uint8_t au8_ERROR_STAT = UART_SUCCESS; //ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	if (NULL_PTR == RxString) {//CHECK IF THE POINTER IS NOT = NULL
		au8_ERROR_STAT = UART_NULL_POINTER;
	} else {
		if (UartNumber > UART_1) {//CHECK IF USER ENTERED RIGHT UART CHANNEL
			au8_ERROR_STAT = UART_INVALID_CHANNEL;
		} else {
			if (NOT_INIT == gu8_InitFlag) {//CHECK IF THE UART HAS BEEN INITIALIZED
				au8_ERROR_STAT = UART_NOT_INIT;
			} //if
			else {
				uint8_t au8_counter = 0;//THIS COUNTER FOR THE ARRAY INDEX
				while (1) {
					while (!(UCSRA & (1 << RXC )));//WAIT FOR THE FLAG
					RxString[au8_counter] = UDR;//STORE DATA IN THE ARRAY
					if (RxString[au8_counter] == (NEW_LINE)) {//CHECK IF THE USER ENTERED NEW LINE CHAR '\r'
						RxString[au8_counter] = NULL_TERMINATOR;//REPLACE THE NEW LINE CHAR WITH NULL TERMINATOR
						break;//BREAK FROM THE WHILE(1)
					}
					au8_counter++;//GO TO THE NEXT PLACE IN THE ARRAY
					if ((RxString[au8_counter - 1] == (BACKSPACE)) && au8_counter > 1) {//CHECK IF USER ENTERED BACK SPACE AND IT IS NOT THE FIRST PLACE IN THE ARRAY
						au8_counter = au8_counter - 2;
					} else if ((RxString[au8_counter - 1] == (BACKSPACE))//CHECK IF USER ENTERED BACK SPACE AND IT IS THE FIRST PLACE IN THE ARRAY
							&& au8_counter <= 1) {
						au8_counter = 0;//RETURN TO THE FIRST PLACE
					} else {
						//DO NOTHING
					}//ELSE
				}//WHILE
			}//ELSE
		}//ELSE
	}//ELSE
	return au8_ERROR_STAT;//RETURN THE ERROR STAT
}
/*THIS API ENABLE CHOSEN INTERRUPT*/
UART_ERROR_state_t UART_EnableInterrupt(uint8_t UartNumber, uint8_t UartInterruptType) {
    uint8_t au8_ERROR_STAT=UART_SUCCESS;//ERRROR STAT HAS A SUCCESS VALUE AS DEFAULT
	if(NOT_INIT==gu8_InitFlag){//CHECK IF THE UART HAS BEEN INITIALIZED
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
                au8_ERROR_STAT=UART_INTERRUPT_CHANNEL;//THIS HAPPENS WHEN USER ENTER WRONG INTRRUPT TYPE
                break;
            }//switch
            break;
        default:
            au8_ERROR_STAT=UART_INVALID_CHANNEL;//THIS HAPPENS WHEN USER ENTER WRONG UART CHANNEL
            break;
        }//switch
	}//else if
	else{
        //DO NOTHING
	}
	return au8_ERROR_STAT;
}
/*THIS API DISABLE CHOSEN INTERRUPT*/
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
