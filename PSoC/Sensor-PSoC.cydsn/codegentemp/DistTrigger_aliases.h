/*******************************************************************************
* File Name: DistTrigger.h  
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

#if !defined(CY_PINS_DistTrigger_ALIASES_H) /* Pins DistTrigger_ALIASES_H */
#define CY_PINS_DistTrigger_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DistTrigger_0			(DistTrigger__0__PC)
#define DistTrigger_0_PS		(DistTrigger__0__PS)
#define DistTrigger_0_PC		(DistTrigger__0__PC)
#define DistTrigger_0_DR		(DistTrigger__0__DR)
#define DistTrigger_0_SHIFT	(DistTrigger__0__SHIFT)
#define DistTrigger_0_INTR	((uint16)((uint16)0x0003u << (DistTrigger__0__SHIFT*2u)))

#define DistTrigger_INTR_ALL	 ((uint16)(DistTrigger_0_INTR))


#endif /* End Pins DistTrigger_ALIASES_H */


/* [] END OF FILE */
