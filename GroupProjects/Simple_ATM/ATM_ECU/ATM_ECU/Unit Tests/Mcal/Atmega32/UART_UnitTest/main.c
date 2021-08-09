/*- INCLUDES----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Mcal/UART/uart.h"
#include "Mcal/UART/uartReg.h"
/*- LOCAL MACROS------------------------------------------*/
#define UART_2        (uint8_t)2
#define DUMMY_INT     (uint8_t)3
#define RXCIE  (uint8_t)7 //READ/WRITE, INIT VALUE 0
#define TXCIE  (uint8_t)6 //READ/WRITE, INIT VALUE 0
#define UDRIE  (uint8_t)5 //READ/WRITE, INIT VALUE 0
#define RXEN   (uint8_t)4 //READ/WRITE, INIT VALUE 0
#define TXEN   (uint8_t)3 //READ/WRITE, INIT VALUE 0
#define UCSZ2  (uint8_t)2 //READ/WRITE, INIT VALUE 0
#define RXB8   (uint8_t)1 //READ ONLY , INIT VALUE 0
#define TXB8   (uint8_t)0 //READ/WRITE, INIT VALUE 0

//UART CONTROL AND STATUS REGISTER A BITS (UCSRA)
#define RXC    (uint8_t)7 //READ ONLY , INIT VALUE 0
#define TXC    (uint8_t)6 //READ/WRITE, INIT VALUE 0
#define UDRE   (uint8_t)5 //READ ONLY , INIT VALUE 1
#define FE     (uint8_t)4 //READ ONLY , INIT VALUE 0
#define DOR    (uint8_t)3 //READ ONLY , INIT VALUE 0
#define PE     (uint8_t)2 //READ ONLY , INIT VALUE 0
#define U2X    (uint8_t)1 //READ/WRITE, INIT VALUE 0
#define MPCM   (uint8_t)0 //READ/WRITE, INIT VALUE 0


#define ONE    (uint8_t)1
#define ZERO   (uint8_t)0
/*- GLOBAL EXTERN VARIABLES-------------------------------*/
extern uint8_t gu8_InitFlag ;
extern Ptr_VoidFuncVoid_t Gptr_uartRxInt;
extern Ptr_VoidFuncVoid_t Gptr_uartDataEmptyRegInt;
extern Ptr_VoidFuncVoid_t Gptr_uartTxInt;
/*- GLOBAL STATIC VARIABLES-------------------------------*/
uint8_t dummyChar;
uint8_t dummyString[5];

/*- LOCAL FUNCTIONS PROTOTYPES----------------------------*/
void Dummy_function(void);
void TEST1_NOT_INIT(void);
void TEST2_INVALID_CHANNEL(void);
void TEST3_UART_INIT(void);
void TEST4_UART_EN_INTERRUPT(void);
void TEST5_UART_DIS_INTERRUPT(void);
void TEST6_UART_SET_CALL(void);
void TEST7_UART_RECEIVE_CHAR(void);
void TEST8_UART_TRANSMIT_CHAR(void);
/*- MAIN--------------------------------------------------*/
int main()
{
    printf("*************************************\n");
    /*TESTING CALLING APIS WITHOUT INIT*/
    printf("TEST1:TESTING CALLING APIS WITHOUT INIT\n");
    TEST1_NOT_INIT();
    printf("*************************************\n");
    /*TESTING CHOOSE INVALID UART CHANNEL*/
    printf("TEST2:TESTING CHOOSE INVALID UART CHANNEL\n");
    TEST2_INVALID_CHANNEL();
    printf("*************************************\n");
    /*TESTING INIT API*/
    printf("TEST3:TESTING INIT API\n");
    TEST3_UART_INIT();
    printf("*************************************\n");
    /*TESTING ENABLE INTERRUPT API*/
    printf("TEST4:TESTING ENABLE INTERRUPT API\n");
    TEST4_UART_EN_INTERRUPT();
    printf("*************************************\n");
    /*TESTING DISABLE INTERRUPT API*/
    printf("TEST5:TESTING DISABLE INTERRUPT API\n");
    TEST5_UART_DIS_INTERRUPT();
    printf("*************************************\n");
    /*TESTING CALL BACK FUNCTION API*/
    printf("TEST6:TESTING CALL BACK FUNCTION API\n");
    TEST6_UART_SET_CALL();
    printf("*************************************\n");
    /*TESTING RRECEIVE CHAR FUNCTION*/
    printf("TEST7:TESTING RRECEIVE CHAR FUNCTION\n");
    TEST7_UART_RECEIVE_CHAR();
    printf("*************************************\n");
    /*TESTING TRANSMIT CHAR FUNCTION*/
    printf("TEST8:TESTING TRANSMIT CHAR FUNCTION\n");
    TEST8_UART_TRANSMIT_CHAR();
    printf("*************************************\n");
    return 0;
}
/*- LOCAL FUNCTIONS IMPLEMENTATION------------------------*/
void TEST1_NOT_INIT(void){
    /*TRANSMIT STIING WITHOUT INIT*/
    if(UART_NOT_INIT==UART_TransmitString(UART_1,dummyString)){
        printf("TEST 1-1 PASSED\n");
    }
    else{
       printf("TEST 1-1 FAILED\n");
    }
    /*RECEIVE STIING WITHOUT INIT*/
    if(UART_NOT_INIT==UART_ReceiveString(UART_1,dummyString)){
        printf("TEST 1-2 PASSED\n");
    }
    else{
       printf("TEST 1-2 FAILED\n");
    }
}
void TEST2_INVALID_CHANNEL(void){

    /*INITLAZE WRRONG CHANNEL*/

    gu8_InitFlag = INIT;
    /*TRANSMIT STIING WITHOUT INIT*/
    if(UART_INVALID_CHANNEL==UART_TransmitString(UART_2,dummyString)){
        printf("TEST 2-1 PASSED\n");
    }
    else{
       printf("TEST 2-1 FAILED\n");
    }
    /*RECEIVE STIING WITHOUT INIT*/
    if(UART_INVALID_CHANNEL==UART_ReceiveString(UART_2,dummyString)){
        printf("TEST 2-2 PASSED\n");
    }
    else{
       printf("TEST 2-2 FAILED\n");
    }
    gu8_InitFlag = NOT_INIT;
}
void TEST3_UART_INIT(void){
    /*CALL INIT FUNCTION WITH WRONG CHANNEL*/
    if(UART_INVALID_CHANNEL==UART_Init(UART_2)){
        printf("TEST 3-1 PASSED\n");
    }
    else{
       printf("TEST 3-1 FAILED\n");
    }
    /*CALL INIT FUNCTION WITH ALL RIGHT PARAMETERRS */
    if(UART_SUCCESS==UART_Init(UART_1)){
        printf("TEST 3-2 PASSED\n");
    }
    else{
       printf("TEST 3-2 FAILED\n");
    }
    gu8_InitFlag = INIT;
    /*CALL INIT FUNCTION AFTER INIT BEFORE*/
    if(UART_SEC_INIT==UART_Init(UART_1)){
        printf("TEST 3-3 PASSED\n");
    }
    else{
       printf("TEST 3-3 FAILED\n");
    }
    gu8_InitFlag = NOT_INIT;
}
void TEST4_UART_EN_INTERRUPT(void){
    int8_t ERROR_STAT=UART_SUCCESS;
    /*PRE-CONDITION*/
    gu8_InitFlag = INIT;//INIT THE UART
    Clr_Bit(UCSRB, RXCIE);//CLEAR RECEIVE INTERRUPT BIT
    /*CALLING THR ENABLE INTERRUPT API*/
    ERROR_STAT=UART_EnableInterrupt(UART_1,RECIVE_INT);
    if(UART_SUCCESS==ERROR_STAT&&ONE==Get_Bit(UCSRB, RXCIE)){
        printf("TEST 4-1 PASSED\n");
    }
    else{
       printf("TEST 4-1 FAILED\n");
    }
    /*PRE-CONDITION*/
    Clr_Bit(UCSRB, TXCIE);//CLEAR TRANSMIT INTERRUPT BIT
    ERROR_STAT=UART_EnableInterrupt(UART_1,TRANSMIT_INT);
    if(UART_SUCCESS==ERROR_STAT&&ONE==Get_Bit(UCSRB, TXCIE)){
        printf("TEST 4-2 PASSED\n");
    }
    else{
       printf("TEST 4-2 FAILED\n");
    }
    /*PRE-CONDITION*/
    Clr_Bit(UCSRB, UDRIE);//CLEAR EMPTY BUFFERR INTERRUPT BIT
    ERROR_STAT=UART_EnableInterrupt(UART_1,EMPTY_BUFFERR_INT);
    if(UART_SUCCESS==ERROR_STAT&&ONE==Get_Bit(UCSRB, UDRIE)){
        printf("TEST 4-3 PASSED\n");
    }
    else{
       printf("TEST 4-3 FAILED\n");
    }





    ERROR_STAT=UART_EnableInterrupt(UART_1,DUMMY_INT);
    if(UART_INTERRUPT_CHANNEL==ERROR_STAT){
        printf("TEST 4-4 PASSED\n");
    }
    else{
       printf("TEST 4-4 FAILED\n");
    }


    ERROR_STAT=UART_EnableInterrupt(UART_2,RECIVE_INT);
    if(UART_INVALID_CHANNEL==ERROR_STAT){
        printf("TEST 4-5 PASSED\n");
    }
    else{
       printf("TEST 4-5 PASSED\n");
    }

    /*PRE-CONDITION*/
    gu8_InitFlag = NOT_INIT;//MAKE THE UART NOT INIT
    ERROR_STAT=UART_EnableInterrupt(UART_1,RECIVE_INT);
    if(UART_NOT_INIT==ERROR_STAT){
        printf("TEST 4-6 PASSED\n");
    }
    else{
       printf("TEST 4-6 FAILED\n");
    }

}
void TEST5_UART_DIS_INTERRUPT(void){
    int8_t ERROR_STAT=UART_SUCCESS;
    gu8_InitFlag = INIT;
    Set_Bit(UCSRB, RXCIE);
    ERROR_STAT=UART_DisableInterrupt(UART_1,RECIVE_INT);
    if(UART_SUCCESS==ERROR_STAT&&ZERO==Get_Bit(UCSRB, RXCIE)){
        printf("TEST 5-1 PASSED\n");
    }
    else{
       printf("TEST 5-1 FAILED\n");
    }
    Set_Bit(UCSRB, TXCIE);
    ERROR_STAT=UART_DisableInterrupt(UART_1,TRANSMIT_INT);
    if(UART_SUCCESS==ERROR_STAT&&ZERO==Get_Bit(UCSRB, TXCIE)){
        printf("TEST 5-2 PASSED\n");
    }
    else{
       printf("TEST 5-2 FAILED\n");
    }
    Set_Bit(UCSRB, UDRIE);
    ERROR_STAT=UART_DisableInterrupt(UART_1,EMPTY_BUFFERR_INT);
    if(UART_SUCCESS==ERROR_STAT&&ZERO==Get_Bit(UCSRB, UDRIE)){
        printf("TEST 5-3 PASSED\n");
    }
    else{
       printf("TEST 5-3 FAILED\n");
    }
    ERROR_STAT=UART_DisableInterrupt(UART_1,DUMMY_INT);
    if(UART_INTERRUPT_CHANNEL==ERROR_STAT){
        printf("TEST 5-4 PASSED\n");
    }
    else{
       printf("TEST 5-4 FAILED\n");
    }

            /*DISABLE INTERRRUPT BEFORE INIT */
    ERROR_STAT=UART_DisableInterrupt(UART_2,RECIVE_INT);
    if(UART_INVALID_CHANNEL==ERROR_STAT){
        printf("TEST 5-5 PASSED\n");
    }
    else{
       printf("TEST 5-5 PASSED\n");
    }


    gu8_InitFlag = NOT_INIT;
    ERROR_STAT=UART_DisableInterrupt(UART_1,RECIVE_INT);
    if(UART_NOT_INIT==ERROR_STAT){
        printf("TEST 5-6 PASSED\n");
    }
    else{
       printf("TEST 5-6 FAILED\n");
    }


}
void TEST6_UART_SET_CALL(void){
    int8_t ERROR_STAT=UART_SUCCESS;
    gu8_InitFlag = INIT;//pre-condition


    Gptr_uartRxInt=NULL_PTR;
    Gptr_uartDataEmptyRegInt=NULL_PTR;
    Gptr_uartTxInt=NULL_PTR;

    ERROR_STAT=UART_SetCallback(UART_1,RECIVE_INT,Dummy_function);
    if(UART_SUCCESS==ERROR_STAT&&Dummy_function==Gptr_uartRxInt){
        printf("TEST 6-1 PASSED\n");
    }
    else{
       printf("TEST 6-1 FAILED\n");
    }
    ERROR_STAT=UART_SetCallback(UART_1,TRANSMIT_INT,Dummy_function);
    if(UART_SUCCESS==ERROR_STAT&&Dummy_function==Gptr_uartTxInt){
        printf("TEST 6-2 PASSED\n");
    }
    else{
       printf("TEST 6-2 FAILED\n");
    }
    ERROR_STAT=UART_SetCallback(UART_1,EMPTY_BUFFERR_INT,Dummy_function);
    if(UART_SUCCESS==ERROR_STAT&&Dummy_function==Gptr_uartDataEmptyRegInt){
        printf("TEST 6-3 PASSED\n");
    }
    else{
       printf("TEST 6-3 FAILED\n");
    }

    /*PASS NULL POINTER*/
    ERROR_STAT=UART_SetCallback(UART_1,RECIVE_INT,NULL_PTR);
    if(UART_NULL_POINTER==ERROR_STAT){
        printf("TEST 6-4 PASSED\n");
    }
    else{
       printf("TEST 6-4 FAILED\n");
    }


    /*CHOOSE INVALID CHANNEL*/
    ERROR_STAT=UART_SetCallback(UART_2,RECIVE_INT,Dummy_function);
    if(UART_INVALID_CHANNEL==ERROR_STAT){
        printf("TEST 6-5 PASSED\n");
    }
    else{
       printf("TEST 6-5 FAILED\n");
    }
    /*CHOOSE INVALID INTERRRUPT*/
    ERROR_STAT=UART_SetCallback(UART_1,DUMMY_INT,Dummy_function);
    if(UART_INTERRUPT_CHANNEL==ERROR_STAT){
        printf("TEST 6-6 PASSED\n");
    }
    else{
       printf("TEST 6-6 FAILED\n");
    }
    /*PRE-CONDITION*/
    gu8_InitFlag = NOT_INIT;
    /*SET CALL BACK FUNCTIONS BEFORE INIT */
    ERROR_STAT=UART_SetCallback(UART_1,RECIVE_INT,Dummy_function);
    if(UART_NOT_INIT==ERROR_STAT){
        printf("TEST 6-7 PASSED\n");
    }
    else{
       printf("TEST 6-7 FAILED\n");
    }
}
void TEST8_UART_TRANSMIT_CHAR(void){
    int8_t ERROR_STAT=UART_SUCCESS;
    gu8_InitFlag = NOT_INIT;//pre-condition
    ERROR_STAT=UART_TransmitChar(UART_1,dummyChar);
    if(UART_NOT_INIT==ERROR_STAT){
        printf("TEST 7-1 PASSED\n");
    }
    else{
       printf("TEST 1-1 FAILED\n");
    }

    ERROR_STAT=UART_TransmitChar(UART_2,dummyChar);
    if(UART_INVALID_CHANNEL==ERROR_STAT){
        printf("TEST 7-2 PASSED\n");
    }
    else{
       printf("TEST 7-2 FAILED\n");
    }
    gu8_InitFlag = INIT;
    Set_Bit(UCSRA, UDRE);
    UDR='x';
    ERROR_STAT=UART_TransmitChar(UART_1,dummyChar);
    if(UART_SUCCESS==ERROR_STAT&&(UDR==dummyChar)){
        printf("TEST 7-3 PASSED\n");
    }
    else{
       printf("TEST 7-3 FAILED\n");
    }
}
void TEST7_UART_RECEIVE_CHAR(void){
    int8_t ERROR_STAT=UART_SUCCESS;//STORE ERROR STAT
    gu8_InitFlag = NOT_INIT;//pre-condition
    /*CALL THE FUNCTION WITHOUT INIT THE UART*/
    ERROR_STAT=UART_ReceiveChar(UART_1,&dummyChar);
    if(UART_NOT_INIT==ERROR_STAT){
        printf("TEST 8-1 PASSED\n");
    }
    else{
       printf("TEST 8-1 FAILED\n");
    }
    /*PRE-CONDITION*/
    gu8_InitFlag = INIT;
    /*INVALID UART CHANNEL*/
    ERROR_STAT=UART_ReceiveChar(UART_2,&dummyChar);
    if(UART_INVALID_CHANNEL==ERROR_STAT){
        printf("TEST 8-2 PASSED\n");
    }
    else{
       printf("TEST 8-2 FAILED\n");
    }
    /*PRE-CONDITION*/
    Set_Bit(UCSRA, RXC);
    UDR='x';//DUMMY VALUE
    ERROR_STAT=UART_ReceiveChar(UART_1,&dummyChar);
    if(UART_SUCCESS==ERROR_STAT&&(UDR==dummyChar)){
        printf("TEST 8-3 PASSED\n");
    }
    else{
       printf("TEST 8-3 FAILED\n");
    }
    /*PASSING NULL POINTER*/
    ERROR_STAT=UART_ReceiveChar(UART_1,NULL_PTR);
    if(UART_NULL_POINTER==ERROR_STAT&&(UDR==dummyChar)){
        printf("TEST 8-4 PASSED\n");
    }
    else{
       printf("TEST 8-4 FAILED\n");
    }
}


void Dummy_function(void){
}
