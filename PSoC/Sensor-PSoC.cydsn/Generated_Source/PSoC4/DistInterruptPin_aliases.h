/*******************************************************************************
* File Name: DistInterruptPin.h  
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

#if !defined(CY_PINS_DistInterruptPin_ALIASES_H) /* Pins DistInterruptPin_ALIASES_H */
#define CY_PINS_DistInterruptPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DistInterruptPin_0			(DistInterruptPin__0__PC)
#define DistInterruptPin_0_PS		(DistInterruptPin__0__PS)
#define DistInterruptPin_0_PC		(DistInterruptPin__0__PC)
#define DistInterruptPin_0_DR		(DistInterruptPin__0__DR)
#define DistInterruptPin_0_SHIFT	(DistInterruptPin__0__SHIFT)
#define DistInterruptPin_0_INTR	((uint16)((uint16)0x0003u << (DistInterruptPin__0__SHIFT*2u)))

#define DistInterruptPin_INTR_ALL	 ((uint16)(DistInterruptPin_0_INTR))


#endif /* End Pins DistInterruptPin_ALIASES_H */


/* [] END OF FILE */
