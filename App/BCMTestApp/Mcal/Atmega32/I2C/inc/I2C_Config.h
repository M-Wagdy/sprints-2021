/*
 * I2C_Config.h
 *
 * Created: 7/16/2021 9:32:31 AM
 *  Author: Mohamed Wagdy
 */ 


#ifndef __I2C_CONFIG_H__
#define __I2C_CONFIG_H__

/*- INCLUDES -----------------------------------------------*/
#include "STD_types.h"

/*- MACROS -------------------------------------------------*/
#define I2C_INTERRUPT_EN            (uint8_t)(0X01)
#define I2C_ACK_EN                  (uint8_t)(0X40)
#define I2C_EN                      (uint8_t)(0X04)

#define I2C_INTERRUPT_FLAG          (uint8_t)(0X80)
#define I2C_START_BIT               (uint8_t)(0X20)
#define I2C_STOP_BIT                (uint8_t)(0X10)
#define I2C_WRITE_COLLISION_FLAG    (uint8_t)(0X08)
#define I2C_STATUS_BITS             (uint8_t)(0xF8)

#define I2C_PRESCALAR_1             (uint8_t)(0X00)
#define I2C_PRESCALAR_4             (uint8_t)(0X01)
#define I2C_PRESCALAR_16            (uint8_t)(0X02)
#define I2C_PRESCALAR_64            (uint8_t)(0X03)

#define I2C_8_MHZ_115200_RATE_1_PRESCALAR       (uint8_t)(0X07)     
#define I2C_16_MHZ_500K_Rate_1_PRESCALAR        (uint8_t)(0x0F) 

#define I2C_STATUS_START            (uint8_t)(0x08)
#define I2C_STATUS_T_ACK_ADDR       (uint8_t)(0x18)
#define I2C_STATUS_T_ACK_DATA       (uint8_t)(0x28)
#define I2C_STATUS_T_NACK_DATA      (uint8_t)(0x30)
#define I2C_STATUS_T_ARB_LOST       (uint8_t)(0x38)
#define I2C_STATUS_R_ACK_ADDR       (uint8_t)(0x60)
#define I2C_STATUS_R_GENERAL_ADDR   (uint8_t)(0x70)
#define I2C_STATUS_R_ACK_DATA       (uint8_t)(0x80)
#define I2C_STATUS_R_NACK_DATA      (uint8_t)(0x88)
#define I2C_STATUS_R_GACK_DATA      (uint8_t)(0x90)
#define I2C_STATUS_R_GNACK_DATA     (uint8_t)(0x98)
#define I2C_STATUS_R_STOP           (uint8_t)(0xA0)

#define I2C_NUMBERS                 (uint8_t)(1)

#define I2C_CH_0                    (uint8_t)(0)

#endif /* __I2C_CONFIG_H__ */