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

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function configures a pin direction.
*
* @param [in]  port        -  port number.
* @param [in]  pin         -  pin number.
* @param [in]  direction   -  OUTPUT or INPUT direction.
*
* @return function error state.
*/
DIO_ERROR_state_t DIO_SetPinDirection(uint8_t port, uint8_t pin, uint8_t direction)
{
   /* check if invalid pin is given. */
   if(PIN_7 < pin)
   {
      return E_DIO_INVALID_PIN;
   }

   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_dir = NULL_PTR;
   
   /* sets the data and direction pointers according to the required port. */
   switch(port)
   {
      case PORTA:
         prt_port_dir = &PORTA_DIR;
         break;
      case PORTB:
         prt_port_dir = &PORTB_DIR;
         break;
      case PORTC:
         prt_port_dir = &PORTC_DIR;
         break;
      case PORTD:
         prt_port_dir = &PORTD_DIR;
         break;
      default:
         return E_DIO_INVALID_PORT;
   }
   
   /* initialize output pin. */
   if(OUTPUT == direction)
   {
      /* set pin direction */
      SET_BIT(*prt_port_dir, pin);
   }
   /* initialize input pin. */
   else if(INPUT == direction)
   {
      /* set pin direction */
      CLEAR_BIT(*prt_port_dir, pin);
   }
   else
   {
      return E_DIO_INVALID_DIRECTION;
   }

   return E_DIO_SUCCESS;
}

/**
* @brief: This function configures a pin direction.
*
* @param [in]  port        -  port number.
* @param [in]  pin         -  pin number.
*
* @return function error state.
*/
DIO_ERROR_state_t DIO_EnablePinPullup(uint8_t port,uint8_t pin)
{
   /* check if invalid pin is given. */
   if(PIN_7 < pin)
   {
      return E_DIO_INVALID_PIN;
   }
   
   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_data = NULL_PTR;
   
   /* sets the data and direction pointers according to the required port. */
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
   
   /* set pin resistor to pull up. */
   SET_BIT(*prt_port_data, pin);
   
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
DIO_ERROR_state_t DIO_WritePin(uint8_t port, uint8_t pin, uint8_t data)
{
   /* check if invalid pin is given. */
   if(PIN_7 < pin)
   {
      return E_DIO_INVALID_PIN;
   }

   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_data = NULL_PTR;
   
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
DIO_ERROR_state_t DIO_ReadPin(uint8_t port, uint8_t pin, uint8_t * data)
{
   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_stat = NULL_PTR;
   
   /* check if address of data to put the read value in is not null pointer. */
   if(NULL_PTR == data)
   {
      return E_DIO_NULL_PTR;
   }
   /* check if invalid pin is given. */
   else if(PIN_7 < pin)
   {
      return E_DIO_INVALID_PIN;
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
DIO_ERROR_state_t DIO_TogglePin(uint8_t port, uint8_t pin)
{
   /* check if invalid pin is given. */
   if(PIN_7 < pin)
   {
      return E_DIO_INVALID_PIN;
   }

   /* pointers to carry the required port registers address. */
   volatile uint8_t * prt_port_data = NULL_PTR;
   
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