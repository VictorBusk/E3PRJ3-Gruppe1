/*******************************************************************************
* File Name: DC.h  
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

#if !defined(CY_PINS_DC_H) /* Pins DC_H */
#define CY_PINS_DC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DC_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    DC_Write(uint8 value) ;
void    DC_SetDriveMode(uint8 mode) ;
uint8   DC_ReadDataReg(void) ;
uint8   DC_Read(void) ;
uint8   DC_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define DC_DRIVE_MODE_BITS        (3)
#define DC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DC_DRIVE_MODE_BITS))
#define DC_DRIVE_MODE_SHIFT       (0x00u)
#define DC_DRIVE_MODE_MASK        (0x07u << DC_DRIVE_MODE_SHIFT)

#define DC_DM_ALG_HIZ         (0x00u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_DIG_HIZ         (0x01u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_RES_UP          (0x02u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_RES_DWN         (0x03u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_OD_LO           (0x04u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_OD_HI           (0x05u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_STRONG          (0x06u << DC_DRIVE_MODE_SHIFT)
#define DC_DM_RES_UPDWN       (0x07u << DC_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define DC_MASK               DC__MASK
#define DC_SHIFT              DC__SHIFT
#define DC_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DC_PS                     (* (reg32 *) DC__PS)
/* Port Configuration */
#define DC_PC                     (* (reg32 *) DC__PC)
/* Data Register */
#define DC_DR                     (* (reg32 *) DC__DR)
/* Input Buffer Disable Override */
#define DC_INP_DIS                (* (reg32 *) DC__PC2)


#if defined(DC__INTSTAT)  /* Interrupt Registers */

    #define DC_INTSTAT                (* (reg32 *) DC__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins DC_H */


/* [] END OF FILE */
