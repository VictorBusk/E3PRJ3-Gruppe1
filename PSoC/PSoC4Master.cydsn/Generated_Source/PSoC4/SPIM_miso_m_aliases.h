/*******************************************************************************
* File Name: SPIM_miso_m.h  
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

#if !defined(CY_PINS_SPIM_miso_m_ALIASES_H) /* Pins SPIM_miso_m_ALIASES_H */
#define CY_PINS_SPIM_miso_m_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SPIM_miso_m_0			(SPIM_miso_m__0__PC)
#define SPIM_miso_m_0_PS		(SPIM_miso_m__0__PS)
#define SPIM_miso_m_0_PC		(SPIM_miso_m__0__PC)
#define SPIM_miso_m_0_DR		(SPIM_miso_m__0__DR)
#define SPIM_miso_m_0_SHIFT	(SPIM_miso_m__0__SHIFT)
#define SPIM_miso_m_0_INTR	((uint16)((uint16)0x0003u << (SPIM_miso_m__0__SHIFT*2u)))

#define SPIM_miso_m_INTR_ALL	 ((uint16)(SPIM_miso_m_0_INTR))


#endif /* End Pins SPIM_miso_m_ALIASES_H */


/* [] END OF FILE */
