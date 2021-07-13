/*
 * DIO.c
 *
 * Created: 7/7/2021 1:49:03 PM
 *  Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "DIO.h"

/*- LOCAL MACROS
------------------------------------------*/
#define HIGH      (uint8_t)(1)
#define LOW       (uint8_t)(0)
#define NOT_INIT  (uint8_t)(0)
#define INIT      (uint8_t)(1)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t gu8_is_DIO_init = NOT_INIT;

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function configures all DIO pins.
*
* @param [in]  configurations -  array containing the configurations for all the pins.
*
* @return function error state.
*/
DIO_ERROR_state_t DIO_init(const STR_DIO_config_t * configurations)
{
   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_data = NULL_PTR;
   volatile uint8_t * prt_port_dir = NULL_PTR;
   
   /* check if DIO pins are initialized before. */
   if(INIT == gu8_is_DIO_init)
   {
      return E_DIO_INIT_BEFORE;
   }
   /* check if configurations is a null pointer. */
   else if(NULL_PTR == configurations)
   {
      return E_DIO_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* loops through the configuration array to initialize all pins. */
   for(uint8_t i = 0; i<PINS_NUMBERS; i++)
   {
      /* sets the data and direction pointers according to the required port. */
      switch(configurations[i].port_no)
      {
         case PORTA:
            prt_port_data = &PORTA_DATA;
            prt_port_dir = &PORTA_DIR;
            break;
         case PORTB:
            prt_port_data = &PORTB_DATA;
            prt_port_dir = &PORTB_DIR;
            break;
         case PORTC:
            prt_port_data = &PORTC_DATA;
            prt_port_dir = &PORTC_DIR;
            break;
         case PORTD:
            prt_port_data = &PORTD_DATA;
            prt_port_dir = &PORTD_DIR;
            break;
         default:
            return E_DIO_INVALID_PORT;
      }
      /* initialize output pin. */
      if(OUTPUT == configurations[i].direction)
      {
         /* set pin direction */
         SET_BIT(*prt_port_dir,configurations[i].pin_no);
         /* set initial value */
         if(INITIAL_HIGH == configurations[i].initial_value)
         {
            SET_BIT(*prt_port_data,configurations[i].pin_no);
         }
         else if(INITIAL_LOW == configurations[i].initial_value)
         {
            CLEAR_BIT(*prt_port_data,configurations[i].pin_no);
         }
         else
         {
            /* do nothing */
         }
      }
      /* initialize input pin. */
      else if(INPUT == configurations[i].direction)
      {
         /* set pin direction */
         CLEAR_BIT(*prt_port_dir,configurations[i].pin_no);
         /* set pin resistor type. */
         if(PULL_UP == configurations[i].resistor)
         {
            SET_BIT(*prt_port_data,configurations[i].pin_no);
         }
         else if(OPEN_DRAIN == configurations[i].resistor)
         {
            CLEAR_BIT(*prt_port_data,configurations[i].pin_no);
         }
         else
         {
            /* do nothing */
         }
      }
      else
      {
         /* do nothing */
      }
   }
   /* set global variable to INIT. */
   gu8_is_DIO_init = INIT;
   /* return success message. */
   return E_DIO_SUCCESS;
}

/**
* @brief: This function write data in the pin of the given port.
*
* @param [in]  port     -  Port number.
* @param [in]  pin      -  Pin number.
* @param [in]  data     -  Data to be written in the pin.
*
* @return function error state.
*/
DIO_ERROR_state_t DIO_write(uint8_t port, ENU_pins pin, uint8_t data)
{
   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_data = NULL_PTR;
   
   /* check if DIO pins are not initialized. */
   if(NOT_INIT == gu8_is_DIO_init)
   {
      return E_DIO_NOT_INIT;
   }
   
   /* sets the data pointer according to the required port. */
   switch(port)
   {
      case PORTA:
         prt_port_data = &PORTA_DATA;
         break;
      case PORTB:
         prt_port_data = &PORTB_DATA;
         break;
      case PORTC:
         prt_port_data = &PORTC_DATA;
         break;
      case PORTD:
         prt_port_data = &PORTD_DATA;
         break;
      default:
         return E_DIO_INVALID_PORT;
   }
   /* set or clear value in the pin. */
   if(HIGH == data)
   {
      SET_BIT(*prt_port_data,pin);
   }
   else if(LOW == data)
   {
      CLEAR_BIT(*prt_port_data,pin);
   }
   /* if data is invalid. */
   else
   {
      return E_DIO_INVALID_WRITE_DATA;
   }
   
   /* return success message. */
   return E_DIO_SUCCESS;
}

/**
* @brief: This function returns value of the pin in the given port.
*
* @param [in]  port     -  Port number.
* @param [in]  pin      -  Pin number.
* @param [out] data     -  pointer to the variable to save the pin value in it.
*
* @return function error state.
*/
DIO_ERROR_state_t DIO_read(uint8_t port, ENU_pins pin, uint8_t * data)
{
   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_stat = NULL_PTR;
   
   /* check if DIO pins are not initialized. */
   if(NOT_INIT == gu8_is_DIO_init)
   {
      return E_DIO_NOT_INIT;
   }
   /* check if address of data to put the read value in is not null pointer. */
   else if(NULL_PTR == data)
   {
      return E_DIO_NULL_PTR;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the stat pointer according to the required port. */
   switch(port)
   {
      case PORTA:
         prt_port_stat = &PORTA_STAT;
         break;
      case PORTB:
         prt_port_stat = &PORTB_STAT;
         break;
      case PORTC:
         prt_port_stat = &PORTC_STAT;
         break;
      case PORTD:
         prt_port_stat = &PORTD_STAT;
         break;
      default:
         return E_DIO_INVALID_PORT;
   }
   
   /* read the pin value and put it in the data. */
   if(BIT_IS_SET(*prt_port_stat,pin))
   {
      *data = HIGH;
   }
   else
   {
      *data = LOW;
   }
   
   /* return success message. */
   return E_DIO_SUCCESS;
}

/**
* @brief: This function toggles the value of the pin in the given port.
*
* @param [in]  port     -  Port number.
* @param [in]  pin      -  Pin number.
*
* @return function error state.
*/
DIO_ERROR_state_t DIO_toggle(uint8_t port, ENU_pins pin)
{
   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_data = NULL_PTR;
   
   /* check if DIO pins are not initialized. */
   if(NOT_INIT == gu8_is_DIO_init)
   {
      return E_DIO_NOT_INIT;
   }
   else
   {
      /* do nothing */
   }
   
   /* sets the stat pointer according to the required port. */
   switch(port)
   {
      case PORTA:
         prt_port_data = &PORTA_DATA;
         break;
      case PORTB:
         prt_port_data = &PORTB_DATA;
         break;
      case PORTC:
         prt_port_data = &PORTC_DATA;
         break;
      case PORTD:
         prt_port_data = &PORTD_DATA;
         break;
      default:
         return E_DIO_INVALID_PORT;
   }
   
   /* toggles the pin value. */
   TOGGLE_BIT(*prt_port_data, pin);
   
   /* return success message. */
   return E_DIO_SUCCESS;
}