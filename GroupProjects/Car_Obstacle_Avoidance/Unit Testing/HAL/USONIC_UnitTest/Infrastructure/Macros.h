#ifndef Macros_H_
#define Macros_H_


/* Set_Bit --> Sets any bit ( ON )*/
/* To set a bit, We use (Inclusive OR) as ( 0 --> Makes No change ) and ( 1 --> Sets ON )   */
#define Set_Bit(reg,bit)             (reg|=((uint8_t)1<<bit))
#define Set_Low_Nibble(reg)          (reg|=((uint8_t)0x0f))
#define Set_High_Nibble(reg)         (reg|=((uint8_t)0xf0))
#define Set_Byte(reg)                (reg=((uint8_t)0xff))

/* Clr_Bit --> Sets any bit ( OFF ) == ( Clear any bit )*/
/* To clear a bit, We use ( And ) as ( 1 --> Makes No change ) and ( 0 --> Sets OFF )   */
#define Clr_Bit(reg,bit)             (reg&=~((uint8_t)1<<bit))
#define Clr_Low_Nibble(reg)          (reg&=((uint8_t)0xf0))
#define Clr_High_Nibble(reg)         (reg&=((uint8_t)0x0f))
#define Clr_Byte(reg)                (reg=((uint8_t)0x00))


/* Toggle_Bit --> Flip any bit  */
/* To Flip a bit, We use ( Exclusive OR ) as ( 0 --> Makes No change ) and ( 1 --> Toggle )   */
#define Toggle_Bit(reg,bit)         (reg^=((uint8_t)1<<bit))
#define Toggle_Low_Nibble(reg)      (reg^=((uint8_t)0x0f))
#define Toggle_High_Nibble(reg)     (reg^=((uint8_t)0xf0))
#define Toggle_Byte(reg)            (reg^=((uint8_t)0xff))


/* Get_Bit --> Gets any bit */
/* To get a bit, We use ( AND ) as ( 1 --> Makes No change ) and ( 0 --> Sets OFF )  */
#define Get_Bit(reg,bit)            (((reg>>bit)&(uint8_t)(0x01)))
#define Get_Low_Nibble(reg)         ((reg&(uint8_t)0x0f))
#define Get_High_Nibble(reg)        ((reg>>(uint8_t)4))


#endif /* Macros_H_ */
