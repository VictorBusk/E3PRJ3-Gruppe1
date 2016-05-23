/*******************************************************************************
* File Name: Vcc.h  
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

#if !defined(CY_PINS_Vcc_ALIASES_H) /* Pins Vcc_ALIASES_H */
#define CY_PINS_Vcc_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vcc_0			(Vcc__0__PC)
#define Vcc_0_PS		(Vcc__0__PS)
#define Vcc_0_PC		(Vcc__0__PC)
#define Vcc_0_DR		(Vcc__0__DR)
#define Vcc_0_SHIFT	(Vcc__0__SHIFT)
#define Vcc_0_INTR	((uint16)((uint16)0x0003u << (Vcc__0__SHIFT*2u)))

#define Vcc_INTR_ALL	 ((uint16)(Vcc_0_INTR))


#endif /* End Pins Vcc_ALIASES_H */


/* [] END OF FILE */
