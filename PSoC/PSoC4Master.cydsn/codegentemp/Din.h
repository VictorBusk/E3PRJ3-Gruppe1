/*******************************************************************************
* File Name: Din.h  
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

#if !defined(CY_PINS_Din_H) /* Pins Din_H */
#define CY_PINS_Din_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Din_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Din_Write(uint8 value) ;
void    Din_SetDriveMode(uint8 mode) ;
uint8   Din_ReadDataReg(void) ;
uint8   Din_Read(void) ;
uint8   Din_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Din_DRIVE_MODE_BITS        (3)
#define Din_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Din_DRIVE_MODE_BITS))
#define Din_DRIVE_MODE_SHIFT       (0x00u)
#define Din_DRIVE_MODE_MASK        (0x07u << Din_DRIVE_MODE_SHIFT)

#define Din_DM_ALG_HIZ         (0x00u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_DIG_HIZ         (0x01u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_RES_UP          (0x02u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_RES_DWN         (0x03u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_OD_LO           (0x04u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_OD_HI           (0x05u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_STRONG          (0x06u << Din_DRIVE_MODE_SHIFT)
#define Din_DM_RES_UPDWN       (0x07u << Din_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Din_MASK               Din__MASK
#define Din_SHIFT              Din__SHIFT
#define Din_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Din_PS                     (* (reg32 *) Din__PS)
/* Port Configuration */
#define Din_PC                     (* (reg32 *) Din__PC)
/* Data Register */
#define Din_DR                     (* (reg32 *) Din__DR)
/* Input Buffer Disable Override */
#define Din_INP_DIS                (* (reg32 *) Din__PC2)


#if defined(Din__INTSTAT)  /* Interrupt Registers */

    #define Din_INTSTAT                (* (reg32 *) Din__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Din_H */


/* [] END OF FILE */
