/*******************************************************************************
* File Name: Gnd.h  
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

#if !defined(CY_PINS_Gnd_ALIASES_H) /* Pins Gnd_ALIASES_H */
#define CY_PINS_Gnd_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Gnd_0			(Gnd__0__PC)
#define Gnd_0_PS		(Gnd__0__PS)
#define Gnd_0_PC		(Gnd__0__PC)
#define Gnd_0_DR		(Gnd__0__DR)
#define Gnd_0_SHIFT	(Gnd__0__SHIFT)
#define Gnd_0_INTR	((uint16)((uint16)0x0003u << (Gnd__0__SHIFT*2u)))

#define Gnd_INTR_ALL	 ((uint16)(Gnd_0_INTR))


#endif /* End Pins Gnd_ALIASES_H */


/* [] END OF FILE */
