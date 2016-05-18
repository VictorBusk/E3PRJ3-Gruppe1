/*******************************************************************************
* File Name: Y_interrupt.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Y_interrupt_ALIASES_H) /* Pins Y_interrupt_ALIASES_H */
#define CY_PINS_Y_interrupt_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Y_interrupt_0			(Y_interrupt__0__PC)
#define Y_interrupt_0_PS		(Y_interrupt__0__PS)
#define Y_interrupt_0_PC		(Y_interrupt__0__PC)
#define Y_interrupt_0_DR		(Y_interrupt__0__DR)
#define Y_interrupt_0_SHIFT	(Y_interrupt__0__SHIFT)
#define Y_interrupt_0_INTR	((uint16)((uint16)0x0003u << (Y_interrupt__0__SHIFT*2u)))

#define Y_interrupt_INTR_ALL	 ((uint16)(Y_interrupt_0_INTR))


#endif /* End Pins Y_interrupt_ALIASES_H */


/* [] END OF FILE */
