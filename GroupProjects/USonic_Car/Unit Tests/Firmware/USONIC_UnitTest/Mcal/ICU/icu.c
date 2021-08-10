#include"icu.h"



uint8_t ICU_Init(uint8_t ICUNumber){
    //do nothing
}
uint8_t ICU_UpdateTimeOn(uint8_t ICUNumber,ptr_uint8_t ICUState,ptr_double64_t OnTime){
    if (*(ICUState)==3){
        *OnTime=0.00029154518950437;//TIME FOR 5 CM
    }
    *(ICUState) =*(ICUState)+1;
}
