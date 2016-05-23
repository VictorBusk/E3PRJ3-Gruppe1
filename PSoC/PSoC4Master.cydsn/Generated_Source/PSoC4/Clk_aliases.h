/*******************************************************************************
* File Name: Clk.h  
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

#if !defined(CY_PINS_Clk_ALIASES_H) /* Pins Clk_ALIASES_H */
#define CY_PINS_Clk_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Clk_0			(Clk__0__PC)
#define Clk_0_PS		(Clk__0__PS)
#define Clk_0_PC		(Clk__0__PC)
#define Clk_0_DR		(Clk__0__DR)
#define Clk_0_SHIFT	(Clk__0__SHIFT)
#define Clk_0_INTR	((uint16)((uint16)0x0003u << (Clk__0__SHIFT*2u)))

#define Clk_INTR_ALL	 ((uint16)(Clk_0_INTR))


#endif /* End Pins Clk_ALIASES_H */


/* [] END OF FILE */
