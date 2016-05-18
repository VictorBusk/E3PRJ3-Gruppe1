/*******************************************************************************
* File Name: DistEcho.h  
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

#if !defined(CY_PINS_DistEcho_ALIASES_H) /* Pins DistEcho_ALIASES_H */
#define CY_PINS_DistEcho_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DistEcho_0			(DistEcho__0__PC)
#define DistEcho_0_PS		(DistEcho__0__PS)
#define DistEcho_0_PC		(DistEcho__0__PC)
#define DistEcho_0_DR		(DistEcho__0__DR)
#define DistEcho_0_SHIFT	(DistEcho__0__SHIFT)
#define DistEcho_0_INTR	((uint16)((uint16)0x0003u << (DistEcho__0__SHIFT*2u)))

#define DistEcho_INTR_ALL	 ((uint16)(DistEcho_0_INTR))


#endif /* End Pins DistEcho_ALIASES_H */


/* [] END OF FILE */
