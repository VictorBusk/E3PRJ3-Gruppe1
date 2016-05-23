/*******************************************************************************
* File Name: Din.h  
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

#if !defined(CY_PINS_Din_ALIASES_H) /* Pins Din_ALIASES_H */
#define CY_PINS_Din_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Din_0			(Din__0__PC)
#define Din_0_PS		(Din__0__PS)
#define Din_0_PC		(Din__0__PC)
#define Din_0_DR		(Din__0__DR)
#define Din_0_SHIFT	(Din__0__SHIFT)
#define Din_0_INTR	((uint16)((uint16)0x0003u << (Din__0__SHIFT*2u)))

#define Din_INTR_ALL	 ((uint16)(Din_0_INTR))


#endif /* End Pins Din_ALIASES_H */


/* [] END OF FILE */
