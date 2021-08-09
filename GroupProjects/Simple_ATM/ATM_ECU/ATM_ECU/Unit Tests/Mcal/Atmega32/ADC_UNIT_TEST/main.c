/*- INCLUDES----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "Mcal/ADC/adc.h"
#include "Mcal/ADC/adcReg.h"
/*- LOCAL MACROS------------------------------------------*/
#define RANDMON_VAL  40
/*- GLOBAL EXTERN VARIABLES-------------------------------*/
extern Ptr_VoidFuncVoid_t G_ADC_CALLBACK;
/*- LOCAL FUNCTIONS PROTOTYPES----------------------------*/
void Dummy_function(void);
void TEST1_NOT_INIT(void);
void TEST2_ADC_INIT(void);
void TEST3_ADC_ST_CON(void);
void TEST4_ADC_READ(void);
void TEST5_ADC_EN_INTERRUPT(void);
void TEST6_ADC_DIS_INTERRUPT(void);
void TEST7_ADC_SET_CALL(void);
/*- MAIN------------------------*/
int main()
{
    printf("*********************************\n");
    printf("TEST NO.1\n");
    printf("TESTING CALLING ALL APIs BEFORE INITIALIZTION\n");
    TEST1_NOT_INIT();
    printf("*********************************\n");
    printf("TEST NO.2\n");
    printf("TESTING INITIALIZTION\n");
    TEST2_ADC_INIT();
    printf("*********************************\n");
    printf("TEST NO.3\n");
    printf("TESTING START CONDITION\n");
    TEST3_ADC_ST_CON();
    printf("*********************************\n");
    printf("TEST NO.4\n");
    printf("TESTING READ ADC REGISTER\n");
    TEST4_ADC_READ();
    printf("*********************************\n");
    printf("TEST NO.5\n");
    printf("TESTING ENABLE ADC INTERRRUPT\n");
    TEST5_ADC_EN_INTERRUPT();
    printf("*********************************\n");
    printf("TEST NO.6\n");
    printf("TESTING DISABLE ADC INTERRRUPT\n");
    TEST6_ADC_DIS_INTERRUPT();
    printf("*********************************\n");
    printf("TEST NO.7\n");
    printf("TESTING SET CALL BACK FUNCTION\n");
    TEST7_ADC_SET_CALL();
    printf("*********************************\n");
    return 0;
}
/*- LOCAL FUNCTIONS IMPLEMENTATION------------------------*/
/*
*@brief: TEST NO.1 This function tests all APIs before initializing ADC
*/
void TEST1_NOT_INIT(void){
    uint16_t dummy=0;
    /*START CONVERSION BEFORE INIT*/
    if(ADC_NOT_INIT==ADC_StartSingleConversion(ADC0_CH0)){
        printf("TEST 1-1 PASSED\n");
    }
    else{
       printf("TEST 1-1 FAILED\n");
    }
    /*READ BEFORE INIT*/
    if(ADC_NOT_INIT==ADC_Read(ADC0_CH0,&dummy)){
        printf("TEST 1-2 PASSED\n");
    }
    else{
       printf("TEST 1-2 FAILED\n");
    }
    /*ENABLE INTERRRUPT BEFORE INIT */
    if(ADC_NOT_INIT==ADC_EnInterrupt()){
        printf("TEST 1-3 PASSED\n");
    }
    else{
       printf("TEST 1-3 FAILED\n");
    }
    /*DISABLE INTERRRUPT BEFORE INIT */
    if(ADC_NOT_INIT==ADC_DisInterrupt()){
        printf("TEST 1-4 PASSED\n");
    }
    else{
       printf("TEST 1-4 PASSED\n");
    }
    /*SET CALL BACK FUNCTIONS BEFORE INIT */
    if(ADC_NOT_INIT==ADC_SetCallback(Dummy_function)){
        printf("TEST 1-5 PASSED\n");
    }
    else{
       printf("TEST 1-5 FAILED\n");
    }
}
/*
*@brief: TEST NO.2 This function tests initializing ADC
*/
void TEST2_ADC_INIT(void){
    ADC_ERROR_state_t au8_ERROR_STAT = ADC_SUCCESS;
    au8_ERROR_STAT=ADC_Init(ADC0_CH0);
    /*CHECK IF IT RETURNS SUCESS*/
    if(au8_ERROR_STAT==ADC_SUCCESS){
        printf("TEST 2-1 PASSED\n");
    }
    else{
       printf("TEST 2-1 FAILED\n");
    }
    /*CHECK IS API SETS THE RIGHT BITS*/
    if((ADMUX==ADC_Voltage_Ref|ADC_ADJUST)&&(ADCSRA=ADC_PRESCALER|(1<<ADEN))){
        printf("TEST 2-2 PASSED\n");
    }
    else{
       printf("TEST 2-2 FAILED\n");
    }
    /*RESET REGISTERS VALUS*/
    ADMUX=0;
    ADCSRA=0;
}
/*
*@brief: TEST NO.3 This function tests start single conversion
*/
void TEST3_ADC_ST_CON(void){
    ADC_ERROR_state_t au8_ERROR_STAT = ADC_SUCCESS;
    au8_ERROR_STAT==ADC_StartSingleConversion(ADC0_CH0);
    /*CHECK IF IT RETURNS SUCESS*/
    if(ADC_SUCCESS==au8_ERROR_STAT){
         printf("TEST 3-1 PASSED\n");
    }
    else{
       printf("TEST 3-1 FAILED\n");
    }
    /*CHECK IS API SETS THE RIGHT BITS*/
    if((ADMUX==ADC0_CH0)&&(ADCSRA==(1<<ADSC))){
        printf("TEST 3-2 PASSED\n");
    }
    else{
       printf("TEST 3-1 FAILED\n");
    }
    /*RESET REGISTERS VALUS*/
    ADMUX=0;
    ADCSRA=0;

}
/*
*@brief: TEST NO.4 This function tests read ADC reg.
*/
void TEST4_ADC_READ(void){
    uint16_t dummy=0;
    ADC_ERROR_state_t au8_ERROR_STAT = ADC_SUCCESS;
    Set_Bit(ADCSRA, ADIF);//PRE-CONDITION
    ADC=RANDMON_VAL;//PRE-CONDITION(RANDOM VALUE)
    ADC_Read(ADC0_CH0,&dummy);
    /*CHECK IF IT RETURNS SUCESS*/
    if(au8_ERROR_STAT==ADC_SUCCESS){
        printf("TEST 4-1 PASSED\n");
    }
    else{
       printf("TEST 4-1 FAILED\n");
    }
    /*CHECK IF THE IT RETURNS THE RIGHT VALUE AND IT SET THE CH RIGHT */
    if((ADMUX==ADC0_CH0)&&(RANDMON_VAL==dummy)){
        printf("TEST 4-2 PASSED\n");
    }
    else{
       printf("TEST 4-1 FAILED\n");
    }
    /*RESET REGISTERS VALUS*/
    ADMUX=0;
    ADCSRA=0;
}
/*
*@brief: TEST NO.5 This function tests enable interrupt
*/
void TEST5_ADC_EN_INTERRUPT(void){
    ADC_ERROR_state_t au8_ERROR_STAT = ADC_SUCCESS;
    Clr_Bit(ADCSRA, ADIE);//PRE-CONDITION(CLEAR INTERRUPT BIT)
    au8_ERROR_STAT=ADC_EnInterrupt();
    /*CHECK IF IT RETURNS SUCESS*/
    if(au8_ERROR_STAT==ADC_SUCCESS){
        printf("TEST 5-1 PASSED\n");
    }
    else{
        printf("TEST 5-1 FAILED\n");
    }
    /*CHECK IF IT SETS THE INTERRUPT BIT  */
    if(1==Get_Bit(ADCSRA, ADIE)){
        printf("TEST 5-2 PASSED\n");
    }
    else{
        printf("TEST 5-2 FAILED\n");
    }
}
/*
*@brief: TEST NO.6 This function tests disable interrupt
*/
void TEST6_ADC_DIS_INTERRUPT(void){
    ADC_ERROR_state_t au8_ERROR_STAT = ADC_SUCCESS;
    Set_Bit(ADCSRA, ADIE);//PRE-CONDITION(SET THE INTERRUPT BIT)
    au8_ERROR_STAT=ADC_DisInterrupt();
    /*CHECK IF IT RETURNS SUCESS*/
    if(au8_ERROR_STAT==ADC_SUCCESS){
        printf("TEST 6-1 PASSED\n");
    }
    else{
       printf("TEST 6-1 FAILED\n");
    }
    /*CHECK IF IT CLEARED THE INTERRUPT BIT  */
    if(0==Get_Bit(ADCSRA, ADIE)){
        printf("TEST 6-2 PASSED\n");
    }
    else{
        printf("TEST 6-2 FAILED\n");
    }

}
/*
*@brief: TEST NO.7 This function tests set call back function
*/
void TEST7_ADC_SET_CALL(void){
    ADC_ERROR_state_t au8_ERROR_STAT = ADC_SUCCESS;
    /*PASSING NULL POINTER TO SET AS CALL BACK FUNCTIONS*/
    au8_ERROR_STAT=ADC_SetCallback(NULL_PTR);
    /*CHECK IF ERRORR STAT IS ADC_NULL POINTER*/
    if(ADC_NULL_POINTER==au8_ERROR_STAT){
        printf("TEST 7-1 PASSED\n");
    }
    else{
        printf("TEST 7-1 FAILED\n");
    }
    /*PASSING FUNCTION TO SET AS CALL BACK FUNCTIONS*/
    au8_ERROR_STAT=ADC_SetCallback(Dummy_function);
    /*CHECK IF STAT NOW BECAME SUCESS*/
    if(ADC_SUCCESS==au8_ERROR_STAT){
        printf("TEST 7-2 PASSED\n");
    }
    else{
        printf("TEST 7-2 FAILED\n");
    }
    /*CHECK IF POINTER HAVE THE ADDRRESS OF THE FUNCTION*/
    if(Dummy_function==G_ADC_CALLBACK){
        printf("TEST 7-3 PASSED\n");
    }
    else{
        printf("TEST 7-3 FAILED\n");
    }
}
void Dummy_function(void){
    /*THIS FUNCTION ONLY TO PASS IT TO CALL BACK UNCTIOS*/
}

void TEST2_ADC_INIT(void);
