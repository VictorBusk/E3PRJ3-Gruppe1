/*******************************************************************************
* File Name: BL.h  
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

#if !defined(CY_PINS_BL_H) /* Pins BL_H */
#define CY_PINS_BL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BL_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BL_Write(uint8 value) ;
void    BL_SetDriveMode(uint8 mode) ;
uint8   BL_ReadDataReg(void) ;
uint8   BL_Read(void) ;
uint8   BL_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BL_DRIVE_MODE_BITS        (3)
#define BL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BL_DRIVE_MODE_BITS))
#define BL_DRIVE_MODE_SHIFT       (0x00u)
#define BL_DRIVE_MODE_MASK        (0x07u << BL_DRIVE_MODE_SHIFT)

#define BL_DM_ALG_HIZ         (0x00u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_DIG_HIZ         (0x01u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_RES_UP          (0x02u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_RES_DWN         (0x03u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_OD_LO           (0x04u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_OD_HI           (0x05u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_STRONG          (0x06u << BL_DRIVE_MODE_SHIFT)
#define BL_DM_RES_UPDWN       (0x07u << BL_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define BL_MASK               BL__MASK
#define BL_SHIFT              BL__SHIFT
#define BL_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BL_PS                     (* (reg32 *) BL__PS)
/* Port Configuration */
#define BL_PC                     (* (reg32 *) BL__PC)
/* Data Register */
#define BL_DR                     (* (reg32 *) BL__DR)
/* Input Buffer Disable Override */
#define BL_INP_DIS                (* (reg32 *) BL__PC2)


#if defined(BL__INTSTAT)  /* Interrupt Registers */

    #define BL_INTSTAT                (* (reg32 *) BL__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins BL_H */


/* [] END OF FILE */
