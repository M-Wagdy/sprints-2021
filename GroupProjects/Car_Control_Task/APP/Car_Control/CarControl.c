/*
 * CarControl.c
 *
 * Created: 7/12/2021 6:54:35 AM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "CarControl.h"

/*- LOCAL MACROS
------------------------------------------*/
#define MOTOR_1               (uint8_t)(0)
#define MOTOR_2               (uint8_t)(1)

#define MOTOR_SPEED_1	      (uint8_t)(30)
#define MOTOR_SPEED_2	      (uint8_t)(60)
#define MOTOR_SPEED_3	      (uint8_t)(90)

#define MOTOR_FORWARD         (uint8_t)(1)
#define MOTOR_BACKWARD        (uint8_t)(0)

#define PIN_0                 (uint8_t)(0)
#define PIN_1                 (uint8_t)(1)
#define PIN_2                 (uint8_t)(2)
#define PIN_3                 (uint8_t)(3)
#define PIN_4                 (uint8_t)(4)
#define PIN_5                 (uint8_t)(5)
#define PIN_6                 (uint8_t)(6)
#define PIN_7                 (uint8_t)(7)

#define PRESSED               (uint8_t)(0)
#define NOT_PRESSED           (uint8_t)(1)

#define BUTTON_FORWARD_PORT   (uint8_t)(1)
#define BUTTON_FORWARD_PIN    (uint8_t)(2)
#define BUTTON_RIGHT_PORT     (uint8_t)(2)
#define BUTTON_RIGHT_PIN      (uint8_t)(5)
#define BUTTON_LEFT_PORT      (uint8_t)(2)
#define BUTTON_LEFT_PIN       (uint8_t)(6)
#define BUTTON_GEAR_PORT      (uint8_t)(2)
#define BUTTON_GEAR_PIN       (uint8_t)(7)

#define ROW_MATRIX_PORT       (uint8_t)(2)
#define ROW_MATRIX_PIN        (uint8_t)(2)

#define F_STATE               (uint8_t)(0)
#define R_STATE               (uint8_t)(1)
#define L_STATE               (uint8_t)(2)
#define G_STATE               (uint8_t)(3)
#define S_STATE               (uint8_t)(4)

/*- LOCAL FUNCTIONS PROTOTYPES
----------------------------*/
static uint8_t CAR_GetButtonState( void );

static void CAR_SetMotorState(uint8_t state);

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_dutyCycle = MOTOR_SPEED_1;
static uint8_t gu8_direction = MOTOR_FORWARD;
static uint8_t gu8_state = S_STATE;
static uint8_t gu8_previousState = S_STATE;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
static uint8_t CAR_GetButtonState( void )
{
   uint8_t u8_IsPressed;

   u8_IsPressed = PSHBTTN_Status(BUTTON_FORWARD_PORT, BUTTON_FORWARD_PIN);
   if (PRESSED == u8_IsPressed)
   {
      return F_STATE;
   }
   
   u8_IsPressed = PSHBTTN_Status(BUTTON_RIGHT_PORT, BUTTON_RIGHT_PIN);
   if (PRESSED == u8_IsPressed)
   {
      return R_STATE;
   }

   u8_IsPressed = PSHBTTN_Status(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN);
   if (PRESSED == u8_IsPressed)
   {
      return L_STATE;
   }

   u8_IsPressed = PSHBTTN_Status(BUTTON_GEAR_PORT, BUTTON_GEAR_PIN);
   if (PRESSED == u8_IsPressed)
   {
      return G_STATE;
   }

   return S_STATE;
}

static void CAR_SetMotorState(uint8_t state)
{
   switch (state)
   {
      case F_STATE:
         if(MOTOR_BACKWARD == gu8_direction)
         {
            MOTOR_start(MOTOR_1, MOTOR_SPEED_1, MOTOR_BACKWARD);
            MOTOR_start(MOTOR_2, MOTOR_SPEED_1, MOTOR_BACKWARD);
         }
         else
         {
            MOTOR_start(MOTOR_1, gu8_dutyCycle, MOTOR_FORWARD);
            MOTOR_start(MOTOR_2, gu8_dutyCycle, MOTOR_FORWARD);
         }
         break;
      case R_STATE:
         MOTOR_start(MOTOR_1, MOTOR_SPEED_1,MOTOR_FORWARD);
         MOTOR_start(MOTOR_2, MOTOR_SPEED_1,MOTOR_BACKWARD);
         break;
      case L_STATE:
         MOTOR_start(MOTOR_1, MOTOR_SPEED_1,MOTOR_BACKWARD);
         MOTOR_start(MOTOR_2, MOTOR_SPEED_1,MOTOR_FORWARD);
         break;
      case G_STATE:
         if(MOTOR_SPEED_1 == gu8_dutyCycle && gu8_direction == MOTOR_FORWARD)
         {
            gu8_dutyCycle = MOTOR_SPEED_2;
         }
         else if(MOTOR_SPEED_2 == gu8_dutyCycle)
         {
            gu8_dutyCycle = MOTOR_SPEED_3;
         }
         else if(MOTOR_SPEED_3 == gu8_dutyCycle)
         {
            gu8_dutyCycle = MOTOR_SPEED_1;
            gu8_direction = MOTOR_BACKWARD;
         }
         else if(MOTOR_SPEED_1 == gu8_dutyCycle && gu8_direction == MOTOR_BACKWARD)
         {
            gu8_direction = MOTOR_FORWARD;
         }
         else
         {
            gu8_state = S_STATE;
         }

         break;
      case S_STATE:
         MOTOR_stop(MOTOR_1);
         MOTOR_stop(MOTOR_2);
         break;
      default:
         return;
   }
}

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function initialize all car drivers.
*
* @return function error state.
*/
CAR_ERROR_state_t CAR_Init(void)
{
   /* initialize motors */
   MOTOR_init();
   /* set row in the matrix output */
   GpioSetPinDirection(ROW_MATRIX_PORT, ROW_MATRIX_PIN, PIN_OUTPUT);
   
   /* initialize buttons */
   PSHBTTN_ERROR_RETVAL_t PSHBTTN_errorState;   
   PSHBTTN_errorState = PSHBTTN_Init(BUTTON_FORWARD_PORT, BUTTON_FORWARD_PIN, PULLED_UP);
   PSHBTTN_errorState |= PSHBTTN_Init(BUTTON_RIGHT_PORT, BUTTON_RIGHT_PIN, PULLED_UP);
   PSHBTTN_errorState |= PSHBTTN_Init(BUTTON_LEFT_PORT, BUTTON_LEFT_PIN, PULLED_UP);
   PSHBTTN_errorState |= PSHBTTN_Init(BUTTON_GEAR_PORT, BUTTON_GEAR_PIN, PULLED_UP);
   
   if(EXIT_SUCCESFUL != PSHBTTN_errorState)
   {
      return E_CAR_INIT_ERROR;
   }
   
   return E_CAR_SUCCESS;
}

/**
* @brief: This function updates the car state.
*
* @return function error state.
*/
CAR_ERROR_state_t CAR_Update(void)
{
   gu8_state = CAR_GetButtonState();
   
   if(gu8_previousState != gu8_state)
   {
      CAR_SetMotorState(gu8_state);
   }
   gu8_previousState = gu8_state;
   
   return E_CAR_SUCCESS;
}