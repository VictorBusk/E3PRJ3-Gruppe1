/*******************************************************************************
* File Name: Debug_tx.h  
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

#if !defined(CY_PINS_Debug_tx_ALIASES_H) /* Pins Debug_tx_ALIASES_H */
#define CY_PINS_Debug_tx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Debug_tx_0			(Debug_tx__0__PC)
#define Debug_tx_0_PS		(Debug_tx__0__PS)
#define Debug_tx_0_PC		(Debug_tx__0__PC)
#define Debug_tx_0_DR		(Debug_tx__0__DR)
#define Debug_tx_0_SHIFT	(Debug_tx__0__SHIFT)
#define Debug_tx_0_INTR	((uint16)((uint16)0x0003u << (Debug_tx__0__SHIFT*2u)))

#define Debug_tx_INTR_ALL	 ((uint16)(Debug_tx_0_INTR))


#endif /* End Pins Debug_tx_ALIASES_H */


/* [] END OF FILE */
