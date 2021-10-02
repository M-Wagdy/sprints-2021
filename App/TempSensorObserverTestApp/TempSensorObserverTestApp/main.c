/*
 * ADC_Driver.c
 *
 * Created: 7/21/2021 6:20:24 PM
 * Author : Mohamed Wagdy
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "utils.h"
#include "Motor.h"
#include "LCD.h"
#include "TempSensor.h"
#include "TempObserver.h"

/*- LOCAL MACROS
------------------------------------------*/
#define ZERO_ASCII            (uint8_t)(0x30)
#define ROW_0                 (uint8_t)(0)
#define ROW_1                 (uint8_t)(1)
#define COL_0                 (uint8_t)(0)
#define MOTOR_REQUIRED_TEMP   (uint8_t)(100)
#define NUMBER_START_COL      (uint8_t)(10)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
ERROR_STATE_t MOTORLogic_Accept(uint8_t * Temp);
ERROR_STATE_t LCDLogic_Accept(uint8_t * Temp);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t * gau8_CurrentTempMessage = "Current: ";
static uint8_t * gau8_RequiredTempMessage = "Required: ";
static STR_TEMPSensor_t gstr_TempSensorObserver;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
* @brief: This function is acceptor to safely stop motor on high temprature.
*
* @param [in]  Temp -  Temperature value.
*
* @return function error state.
*/
ERROR_STATE_t MOTORLogic_Accept(uint8_t * Temp)
{
   if(*Temp <= MOTOR_REQUIRED_TEMP)
   {
      MOTOR_Start(MOTOR_CH_0);
   }
   else
   {
      MOTOR_Stop(MOTOR_CH_0);
   }
}

/**
* @brief: This function is acceptor to print new temperature on LCD.
*
* @param [in]  Temp -  Temperature value.
*
* @return function error state.
*/
ERROR_STATE_t LCDLogic_Accept(uint8_t * Temp)
{
   uint8_t u8_CurrentTempDigit1;
   uint8_t u8_CurrentTempDigit2;
   uint8_t u8_CurrentTempDigit3;
   
   /* get each number of current temp in single character */
   u8_CurrentTempDigit1 = (*Temp/100);
   u8_CurrentTempDigit2 = ((*Temp - (u8_CurrentTempDigit1*100)) / 10);
   u8_CurrentTempDigit3 = (*Temp - (u8_CurrentTempDigit1*100+u8_CurrentTempDigit2*10));
   
   /* print current temp on LCD */
   LCD_SetToRowCol(LCD_CH_0, ROW_0, NUMBER_START_COL);
   LCD_SendCharacter(LCD_CH_0, u8_CurrentTempDigit1 + ZERO_ASCII);
   LCD_SendCharacter(LCD_CH_0, u8_CurrentTempDigit2 + ZERO_ASCII);
   LCD_SendCharacter(LCD_CH_0, u8_CurrentTempDigit3 + ZERO_ASCII);
}

/*- APIs IMPLEMENTATION
-----------------------------------*/
int main(void)
{
   /* Varibales to store old and new tempratures. */
   uint8_t u8_OldTemp;
   uint8_t u8_NewTemp;
   
   /* initialize drivers */
   TEMP_Init(TEMP_0);
   MOTOR_Init(MOTOR_CH_0);
   LCD_Init(LCD_CH_0);
   
   /* Print static strings */
   LCD_SendString(LCD_CH_0, gau8_CurrentTempMessage);
   LCD_SetToRowCol(LCD_CH_0, ROW_1, COL_0);
   LCD_SendString(LCD_CH_0, gau8_RequiredTempMessage);
   
   /* Print required Temprature on LCD. */
   /* get each number of required temp in single character */
   uint8_t u8_RequiredTempDigit1;
   uint8_t u8_RequiredTempDigit2;
   uint8_t u8_RequiredTempDigit3;
   u8_RequiredTempDigit1 = (MOTOR_REQUIRED_TEMP/100);
   u8_RequiredTempDigit2 = ((MOTOR_REQUIRED_TEMP - (u8_RequiredTempDigit1*100)) / 10);
   u8_RequiredTempDigit3 = (MOTOR_REQUIRED_TEMP - (u8_RequiredTempDigit1*100+u8_RequiredTempDigit2*10));
   
   /* print required temp on LCD */
   LCD_SetToRowCol(LCD_CH_0, ROW_1, NUMBER_START_COL);
   LCD_SendCharacter(LCD_CH_0, u8_RequiredTempDigit1 + ZERO_ASCII);
   LCD_SendCharacter(LCD_CH_0, u8_RequiredTempDigit2 + ZERO_ASCII);
   LCD_SendCharacter(LCD_CH_0, u8_RequiredTempDigit3 + ZERO_ASCII);
   
   /* Init Observer */
   TEMPObserver_Init(&gstr_TempSensorObserver);
   /* Subscribe Motor Acceptor Function to Observer. */
   TEMPObserver_Subscribe(&gstr_TempSensorObserver, MOTORLogic_Accept);
   /* Subscribe LCD Acceptor Function to Observer. */
   TEMPObserver_Subscribe(&gstr_TempSensorObserver, LCDLogic_Accept);
   
   while (1)
   {
      /* Get Temperature from Temperature Sensor. */
      TEMP_Read(TEMP_0, &u8_NewTemp);
      /* If a new temperature. */
      if(u8_OldTemp != u8_NewTemp)
      {
         /* Update Observer Data. */
         TEMPObserver_SetNewData(&gstr_TempSensorObserver, u8_NewTemp);
      }
      /* Update Old Temprature. */
      u8_OldTemp = u8_NewTemp;
   }
}

