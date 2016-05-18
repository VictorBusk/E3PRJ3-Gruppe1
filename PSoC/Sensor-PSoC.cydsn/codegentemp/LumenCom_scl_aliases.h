/*******************************************************************************
* File Name: LumenCom_scl.h  
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

#if !defined(CY_PINS_LumenCom_scl_ALIASES_H) /* Pins LumenCom_scl_ALIASES_H */
#define CY_PINS_LumenCom_scl_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LumenCom_scl_0			(LumenCom_scl__0__PC)
#define LumenCom_scl_0_PS		(LumenCom_scl__0__PS)
#define LumenCom_scl_0_PC		(LumenCom_scl__0__PC)
#define LumenCom_scl_0_DR		(LumenCom_scl__0__DR)
#define LumenCom_scl_0_SHIFT	(LumenCom_scl__0__SHIFT)
#define LumenCom_scl_0_INTR	((uint16)((uint16)0x0003u << (LumenCom_scl__0__SHIFT*2u)))

#define LumenCom_scl_INTR_ALL	 ((uint16)(LumenCom_scl_0_INTR))


#endif /* End Pins LumenCom_scl_ALIASES_H */


/* [] END OF FILE */
