/*******************************************************************************
* File Name: CE.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CE_H) /* Pins CE_H */
#define CY_PINS_CE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CE_Write(uint8 value) ;
void    CE_SetDriveMode(uint8 mode) ;
uint8   CE_ReadDataReg(void) ;
uint8   CE_Read(void) ;
uint8   CE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CE_DRIVE_MODE_BITS        (3)
#define CE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CE_DRIVE_MODE_BITS))
#define CE_DRIVE_MODE_SHIFT       (0x00u)
#define CE_DRIVE_MODE_MASK        (0x07u << CE_DRIVE_MODE_SHIFT)

#define CE_DM_ALG_HIZ         (0x00u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_DIG_HIZ         (0x01u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_RES_UP          (0x02u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_RES_DWN         (0x03u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_OD_LO           (0x04u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_OD_HI           (0x05u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_STRONG          (0x06u << CE_DRIVE_MODE_SHIFT)
#define CE_DM_RES_UPDWN       (0x07u << CE_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define CE_MASK               CE__MASK
#define CE_SHIFT              CE__SHIFT
#define CE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CE_PS                     (* (reg32 *) CE__PS)
/* Port Configuration */
#define CE_PC                     (* (reg32 *) CE__PC)
/* Data Register */
#define CE_DR                     (* (reg32 *) CE__DR)
/* Input Buffer Disable Override */
#define CE_INP_DIS                (* (reg32 *) CE__PC2)


#if defined(CE__INTSTAT)  /* Interrupt Registers */

    #define CE_INTSTAT                (* (reg32 *) CE__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins CE_H */


/* [] END OF FILE */
