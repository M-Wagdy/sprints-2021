/*
 * ADC_Driver.c
 *
 * Created: 7/21/2021 6:20:24 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "Infrastructure/utils.h"
#include "Mcal/ADC/ADC.h"
#include "Firmware/Motor/Motor.h"
#include "Firmware/Keypad/Keypad.h"
#include "Firmware/LCD/LCD.h"

/*- LOCAL MACROS
------------------------------------------*/
#define ZERO_ASCII         (uint8_t)(0x30)
#define ROW_0              (uint8_t)(0)
#define ROW_1              (uint8_t)(1)
#define COL_0              (uint8_t)(0)
#define NUMBER_START_COL   (uint8_t)(10)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t * gau8_CurrentTempMessage = "Current: ";
static uint8_t * gau8_RequiredTempMessage = "Required: ";

int main(void)
{
   uint8_t u8_KPValue;

   uint16_t u8_CurrentTemp;
   uint8_t u8_CurrentTempDigit1;
   uint8_t u8_CurrentTempDigit2;
   uint8_t u8_CurrentTempDigit3;

   uint16_t u8_RequiredTemp = 0;
   uint8_t u8_RequiredTempDigit1;
   uint8_t u8_RequiredTempDigit2;
   uint8_t u8_RequiredTempDigit3;
      
   /* initialize drivers */
   ADC_Init();
   MOTOR_Init(MOTOR_CH_0);
   KP_Init(KP_CH_0);
   LCD_Init(LCD_CH_0);
   
   /* Print static strings */
   LCD_SendString(LCD_CH_0, gau8_CurrentTempMessage);
   LCD_SetToRowCol(LCD_CH_0, ROW_1, COL_0);
   LCD_SendString(LCD_CH_0, gau8_RequiredTempMessage);
   
   while (1)
   {
      /* get pressed button on keypad */
      KP_GetPressedValue(KP_CH_0, &u8_KPValue);
      
      /* if a button is pressed */
      if(u8_KPValue != 0)
      {
         /* add it to the current required temprature */
         u8_RequiredTemp = (u8_RequiredTemp*10)+ (u8_KPValue - ZERO_ASCII);
         
         /* set required temp to zero if it exceeds 150 */
         if(u8_RequiredTemp > 150)
         {
            u8_RequiredTemp = 0;
         }   
      }
      
      /* get ADC readings */
      ADC_Read(ADC_CH_0, &u8_CurrentTemp);
      
      /* map ADC resolution to the current temprature */
      u8_CurrentTemp = (u8_CurrentTemp * 150 / 308);
      
      /* check if current is higher or equal required temp for motor to start */
      if(u8_CurrentTemp >= u8_RequiredTemp)
      {
         MOTOR_Start(MOTOR_CH_0);
      }
      else
      {
         MOTOR_Stop(MOTOR_CH_0);
      }
      
      /* get each number of current temp in single character */
      u8_CurrentTempDigit1 = (u8_CurrentTemp/100);
      u8_CurrentTempDigit2 = ((u8_CurrentTemp - (u8_CurrentTempDigit1*100)) / 10);
      u8_CurrentTempDigit3 = (u8_CurrentTemp - (u8_CurrentTempDigit1*100+u8_CurrentTempDigit2*10));
      
      /* get each number of required temp in single character */
      u8_RequiredTempDigit1 = (u8_RequiredTemp/100);
      u8_RequiredTempDigit2 = ((u8_RequiredTemp - (u8_RequiredTempDigit1*100)) / 10);
      u8_RequiredTempDigit3 = (u8_RequiredTemp - (u8_RequiredTempDigit1*100+u8_RequiredTempDigit2*10));
      
      /* print current temp on LCD */
      LCD_SetToRowCol(LCD_CH_0, ROW_0, NUMBER_START_COL);
      LCD_SendCharacter(LCD_CH_0, u8_CurrentTempDigit1 + ZERO_ASCII);
      LCD_SendCharacter(LCD_CH_0, u8_CurrentTempDigit2 + ZERO_ASCII);
      LCD_SendCharacter(LCD_CH_0, u8_CurrentTempDigit3 + ZERO_ASCII);
      
      /* print required temp on LCD */
      LCD_SetToRowCol(LCD_CH_0, ROW_1, NUMBER_START_COL);
      LCD_SendCharacter(LCD_CH_0, u8_RequiredTempDigit1 + ZERO_ASCII);
      LCD_SendCharacter(LCD_CH_0, u8_RequiredTempDigit2 + ZERO_ASCII);
      LCD_SendCharacter(LCD_CH_0, u8_RequiredTempDigit3 + ZERO_ASCII);
   }
}

