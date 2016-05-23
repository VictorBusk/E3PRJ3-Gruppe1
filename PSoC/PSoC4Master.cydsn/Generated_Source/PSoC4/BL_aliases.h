/*******************************************************************************
* File Name: BL.h  
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

#if !defined(CY_PINS_BL_ALIASES_H) /* Pins BL_ALIASES_H */
#define CY_PINS_BL_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define BL_0			(BL__0__PC)
#define BL_0_PS		(BL__0__PS)
#define BL_0_PC		(BL__0__PC)
#define BL_0_DR		(BL__0__DR)
#define BL_0_SHIFT	(BL__0__SHIFT)
#define BL_0_INTR	((uint16)((uint16)0x0003u << (BL__0__SHIFT*2u)))

#define BL_INTR_ALL	 ((uint16)(BL_0_INTR))


#endif /* End Pins BL_ALIASES_H */


/* [] END OF FILE */
