/*
 * Interrupt_Design_Pattern.c
 *
 * Created: 8/19/2021 12:22:29 PM
 * Author: Mohamed Wagdy
 */ 

/*- INCLUDES
----------------------------------------------*/
#include "Interrupt_Design_Pattern.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static Ptr_VoidFuncVoid_t aptr_OldVectors[TABLE_SIZE];

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern Ptr_VoidFuncVoid_t aptr_ISRAddress[TABLE_SIZE];

/*- APIs IMPLEMENTATION
-----------------------------------*/

/**
* @brief: This function Installs a new Callback to ISR.
*
* @param [in]  Vector_No   -  ISR Vector Number.
* @param [in]  Callback    -  New Callback Function of ISR.
*/
void Interrupt_Install(uint8_t Vector_No, Ptr_VoidFuncVoid_t Callback)
{
   /* Validate Before Changing ISR Vector Table */
	if( 
      (NULL_PTR == aptr_OldVectors[Vector_No]) && (NULL_PTR != Callback) && 
      (Vector_No >= IRQ_MIN_VECTOR_NUMBER) &&  (Vector_No <= IRQ_MAX_VECTOR_NUMBER)
     )
	{
      /* Store The Current ISR in a History Table. */
		aptr_OldVectors[Vector_No] = aptr_ISRAddress[Vector_No];
      /* Set the new Callback in the ISR. */
      aptr_ISRAddress[Vector_No] = Callback;
	}
}

/**
* @brief: This function Deinstalls the Callback of ISR 
*         and Returns the old ISR Callback.
*
* @param [in]  Vector_No   -  ISR Vector Number.
*/
void Interrupt_Deinstall(uint8_t Vector_No)
{
   /* Validate Before Changing ISR Vector Table */
	if( (Vector_No >= IRQ_MIN_VECTOR_NUMBER) &&  (Vector_No <= IRQ_MAX_VECTOR_NUMBER))
	{
      /* Revert Old ISR Callback to the ISR Vector Table. */
		aptr_ISRAddress[Vector_No] = aptr_OldVectors[Vector_No];
      /* Clear The Old ISR Callback from the History Table */
      aptr_OldVectors[Vector_No] = NULL_PTR;
	}
}