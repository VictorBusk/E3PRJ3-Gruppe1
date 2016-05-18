/*******************************************************************************
* File Name: commons.h  
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

#if !defined(CY_PINS_commons_H) /* Pins commons_H */
#define CY_PINS_commons_H

#include "cytypes.h"
#include "cyfitter.h"
#include "commons_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    commons_Write(uint8 value) ;
void    commons_SetDriveMode(uint8 mode) ;
uint8   commons_ReadDataReg(void) ;
uint8   commons_Read(void) ;
uint8   commons_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define commons_DRIVE_MODE_BITS        (3)
#define commons_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - commons_DRIVE_MODE_BITS))

#define commons_DM_ALG_HIZ         (0x00u)
#define commons_DM_DIG_HIZ         (0x01u)
#define commons_DM_RES_UP          (0x02u)
#define commons_DM_RES_DWN         (0x03u)
#define commons_DM_OD_LO           (0x04u)
#define commons_DM_OD_HI           (0x05u)
#define commons_DM_STRONG          (0x06u)
#define commons_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define commons_MASK               commons__MASK
#define commons_SHIFT              commons__SHIFT
#define commons_WIDTH              4u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define commons_PS                     (* (reg32 *) commons__PS)
/* Port Configuration */
#define commons_PC                     (* (reg32 *) commons__PC)
/* Data Register */
#define commons_DR                     (* (reg32 *) commons__DR)
/* Input Buffer Disable Override */
#define commons_INP_DIS                (* (reg32 *) commons__PC2)


#if defined(commons__INTSTAT)  /* Interrupt Registers */

    #define commons_INTSTAT                (* (reg32 *) commons__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define commons_DRIVE_MODE_SHIFT       (0x00u)
#define commons_DRIVE_MODE_MASK        (0x07u << commons_DRIVE_MODE_SHIFT)


#endif /* End Pins commons_H */


/* [] END OF FILE */
