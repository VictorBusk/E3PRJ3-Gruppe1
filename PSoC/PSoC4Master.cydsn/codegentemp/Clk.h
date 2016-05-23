/*******************************************************************************
* File Name: Clk.h  
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

#if !defined(CY_PINS_Clk_H) /* Pins Clk_H */
#define CY_PINS_Clk_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Clk_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Clk_Write(uint8 value) ;
void    Clk_SetDriveMode(uint8 mode) ;
uint8   Clk_ReadDataReg(void) ;
uint8   Clk_Read(void) ;
uint8   Clk_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Clk_DRIVE_MODE_BITS        (3)
#define Clk_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Clk_DRIVE_MODE_BITS))
#define Clk_DRIVE_MODE_SHIFT       (0x00u)
#define Clk_DRIVE_MODE_MASK        (0x07u << Clk_DRIVE_MODE_SHIFT)

#define Clk_DM_ALG_HIZ         (0x00u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_DIG_HIZ         (0x01u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_RES_UP          (0x02u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_RES_DWN         (0x03u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_OD_LO           (0x04u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_OD_HI           (0x05u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_STRONG          (0x06u << Clk_DRIVE_MODE_SHIFT)
#define Clk_DM_RES_UPDWN       (0x07u << Clk_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Clk_MASK               Clk__MASK
#define Clk_SHIFT              Clk__SHIFT
#define Clk_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Clk_PS                     (* (reg32 *) Clk__PS)
/* Port Configuration */
#define Clk_PC                     (* (reg32 *) Clk__PC)
/* Data Register */
#define Clk_DR                     (* (reg32 *) Clk__DR)
/* Input Buffer Disable Override */
#define Clk_INP_DIS                (* (reg32 *) Clk__PC2)


#if defined(Clk__INTSTAT)  /* Interrupt Registers */

    #define Clk_INTSTAT                (* (reg32 *) Clk__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Clk_H */


/* [] END OF FILE */
