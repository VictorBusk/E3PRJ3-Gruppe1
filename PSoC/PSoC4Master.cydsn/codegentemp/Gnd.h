/*******************************************************************************
* File Name: Gnd.h  
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

#if !defined(CY_PINS_Gnd_H) /* Pins Gnd_H */
#define CY_PINS_Gnd_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Gnd_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Gnd_Write(uint8 value) ;
void    Gnd_SetDriveMode(uint8 mode) ;
uint8   Gnd_ReadDataReg(void) ;
uint8   Gnd_Read(void) ;
uint8   Gnd_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Gnd_DRIVE_MODE_BITS        (3)
#define Gnd_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Gnd_DRIVE_MODE_BITS))
#define Gnd_DRIVE_MODE_SHIFT       (0x00u)
#define Gnd_DRIVE_MODE_MASK        (0x07u << Gnd_DRIVE_MODE_SHIFT)

#define Gnd_DM_ALG_HIZ         (0x00u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_DIG_HIZ         (0x01u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_RES_UP          (0x02u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_RES_DWN         (0x03u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_OD_LO           (0x04u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_OD_HI           (0x05u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_STRONG          (0x06u << Gnd_DRIVE_MODE_SHIFT)
#define Gnd_DM_RES_UPDWN       (0x07u << Gnd_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Gnd_MASK               Gnd__MASK
#define Gnd_SHIFT              Gnd__SHIFT
#define Gnd_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Gnd_PS                     (* (reg32 *) Gnd__PS)
/* Port Configuration */
#define Gnd_PC                     (* (reg32 *) Gnd__PC)
/* Data Register */
#define Gnd_DR                     (* (reg32 *) Gnd__DR)
/* Input Buffer Disable Override */
#define Gnd_INP_DIS                (* (reg32 *) Gnd__PC2)


#if defined(Gnd__INTSTAT)  /* Interrupt Registers */

    #define Gnd_INTSTAT                (* (reg32 *) Gnd__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Gnd_H */


/* [] END OF FILE */
