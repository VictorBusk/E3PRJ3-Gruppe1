/*******************************************************************************
* File Name: Vcc.h  
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

#if !defined(CY_PINS_Vcc_H) /* Pins Vcc_H */
#define CY_PINS_Vcc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vcc_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Vcc_Write(uint8 value) ;
void    Vcc_SetDriveMode(uint8 mode) ;
uint8   Vcc_ReadDataReg(void) ;
uint8   Vcc_Read(void) ;
uint8   Vcc_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Vcc_DRIVE_MODE_BITS        (3)
#define Vcc_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vcc_DRIVE_MODE_BITS))
#define Vcc_DRIVE_MODE_SHIFT       (0x00u)
#define Vcc_DRIVE_MODE_MASK        (0x07u << Vcc_DRIVE_MODE_SHIFT)

#define Vcc_DM_ALG_HIZ         (0x00u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_DIG_HIZ         (0x01u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_RES_UP          (0x02u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_RES_DWN         (0x03u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_OD_LO           (0x04u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_OD_HI           (0x05u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_STRONG          (0x06u << Vcc_DRIVE_MODE_SHIFT)
#define Vcc_DM_RES_UPDWN       (0x07u << Vcc_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Vcc_MASK               Vcc__MASK
#define Vcc_SHIFT              Vcc__SHIFT
#define Vcc_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Vcc_PS                     (* (reg32 *) Vcc__PS)
/* Port Configuration */
#define Vcc_PC                     (* (reg32 *) Vcc__PC)
/* Data Register */
#define Vcc_DR                     (* (reg32 *) Vcc__DR)
/* Input Buffer Disable Override */
#define Vcc_INP_DIS                (* (reg32 *) Vcc__PC2)


#if defined(Vcc__INTSTAT)  /* Interrupt Registers */

    #define Vcc_INTSTAT                (* (reg32 *) Vcc__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Vcc_H */


/* [] END OF FILE */
