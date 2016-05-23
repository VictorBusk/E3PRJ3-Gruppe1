/*******************************************************************************
* File Name: RST.h  
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

#if !defined(CY_PINS_RST_H) /* Pins RST_H */
#define CY_PINS_RST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RST_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RST_Write(uint8 value) ;
void    RST_SetDriveMode(uint8 mode) ;
uint8   RST_ReadDataReg(void) ;
uint8   RST_Read(void) ;
uint8   RST_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RST_DRIVE_MODE_BITS        (3)
#define RST_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RST_DRIVE_MODE_BITS))
#define RST_DRIVE_MODE_SHIFT       (0x00u)
#define RST_DRIVE_MODE_MASK        (0x07u << RST_DRIVE_MODE_SHIFT)

#define RST_DM_ALG_HIZ         (0x00u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_DIG_HIZ         (0x01u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_RES_UP          (0x02u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_RES_DWN         (0x03u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_OD_LO           (0x04u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_OD_HI           (0x05u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_STRONG          (0x06u << RST_DRIVE_MODE_SHIFT)
#define RST_DM_RES_UPDWN       (0x07u << RST_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define RST_MASK               RST__MASK
#define RST_SHIFT              RST__SHIFT
#define RST_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RST_PS                     (* (reg32 *) RST__PS)
/* Port Configuration */
#define RST_PC                     (* (reg32 *) RST__PC)
/* Data Register */
#define RST_DR                     (* (reg32 *) RST__DR)
/* Input Buffer Disable Override */
#define RST_INP_DIS                (* (reg32 *) RST__PC2)


#if defined(RST__INTSTAT)  /* Interrupt Registers */

    #define RST_INTSTAT                (* (reg32 *) RST__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins RST_H */


/* [] END OF FILE */
