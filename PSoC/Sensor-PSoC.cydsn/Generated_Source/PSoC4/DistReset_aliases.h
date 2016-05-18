/*******************************************************************************
* File Name: DistReset.h  
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

#if !defined(CY_PINS_DistReset_ALIASES_H) /* Pins DistReset_ALIASES_H */
#define CY_PINS_DistReset_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DistReset_0			(DistReset__0__PC)
#define DistReset_0_PS		(DistReset__0__PS)
#define DistReset_0_PC		(DistReset__0__PC)
#define DistReset_0_DR		(DistReset__0__DR)
#define DistReset_0_SHIFT	(DistReset__0__SHIFT)
#define DistReset_0_INTR	((uint16)((uint16)0x0003u << (DistReset__0__SHIFT*2u)))

#define DistReset_INTR_ALL	 ((uint16)(DistReset_0_INTR))


#endif /* End Pins DistReset_ALIASES_H */


/* [] END OF FILE */
