/*******************************************************************************
* File Name: segments.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_segments_H) /* Pins segments_H */
#define CY_PINS_segments_H

#include "cytypes.h"
#include "cyfitter.h"
#include "segments_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    segments_Write(uint8 value) ;
void    segments_SetDriveMode(uint8 mode) ;
uint8   segments_ReadDataReg(void) ;
uint8   segments_Read(void) ;
uint8   segments_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define segments_DRIVE_MODE_BITS        (3)
#define segments_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - segments_DRIVE_MODE_BITS))

#define segments_DM_ALG_HIZ         (0x00u)
#define segments_DM_DIG_HIZ         (0x01u)
#define segments_DM_RES_UP          (0x02u)
#define segments_DM_RES_DWN         (0x03u)
#define segments_DM_OD_LO           (0x04u)
#define segments_DM_OD_HI           (0x05u)
#define segments_DM_STRONG          (0x06u)
#define segments_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define segments_MASK               segments__MASK
#define segments_SHIFT              segments__SHIFT
#define segments_WIDTH              8u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define segments_PS                     (* (reg32 *) segments__PS)
/* Port Configuration */
#define segments_PC                     (* (reg32 *) segments__PC)
/* Data Register */
#define segments_DR                     (* (reg32 *) segments__DR)
/* Input Buffer Disable Override */
#define segments_INP_DIS                (* (reg32 *) segments__PC2)


#if defined(segments__INTSTAT)  /* Interrupt Registers */

    #define segments_INTSTAT                (* (reg32 *) segments__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define segments_DRIVE_MODE_SHIFT       (0x00u)
#define segments_DRIVE_MODE_MASK        (0x07u << segments_DRIVE_MODE_SHIFT)


#endif /* End Pins segments_H */


/* [] END OF FILE */
