/*******************************************************************************
* File Name: BL.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
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
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} BL_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BL_Read(void);
void    BL_Write(uint8 value);
uint8   BL_ReadDataReg(void);
#if defined(BL__PC) || (CY_PSOC4_4200L) 
    void    BL_SetDriveMode(uint8 mode);
#endif
void    BL_SetInterruptMode(uint16 position, uint16 mode);
uint8   BL_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BL_Sleep(void); 
void BL_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BL__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BL_DRIVE_MODE_BITS        (3)
    #define BL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BL_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BL_SetDriveMode() function.
         *  @{
         */
        #define BL_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BL_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BL_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BL_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BL_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BL_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BL_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BL_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BL_MASK               BL__MASK
#define BL_SHIFT              BL__SHIFT
#define BL_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BL_SetInterruptMode() function.
     *  @{
     */
        #define BL_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BL_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BL_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BL_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BL__SIO)
    #define BL_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BL__PC) && (CY_PSOC4_4200L)
    #define BL_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BL_USBIO_DISABLE              ((uint32)(~BL_USBIO_ENABLE))
    #define BL_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BL_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BL_USBIO_ENTER_SLEEP          ((uint32)((1u << BL_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BL_USBIO_SUSPEND_DEL_SHIFT)))
    #define BL_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BL_USBIO_SUSPEND_SHIFT)))
    #define BL_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BL_USBIO_SUSPEND_DEL_SHIFT)))
    #define BL_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BL__PC)
    /* Port Configuration */
    #define BL_PC                 (* (reg32 *) BL__PC)
#endif
/* Pin State */
#define BL_PS                     (* (reg32 *) BL__PS)
/* Data Register */
#define BL_DR                     (* (reg32 *) BL__DR)
/* Input Buffer Disable Override */
#define BL_INP_DIS                (* (reg32 *) BL__PC2)

/* Interrupt configuration Registers */
#define BL_INTCFG                 (* (reg32 *) BL__INTCFG)
#define BL_INTSTAT                (* (reg32 *) BL__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BL_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BL__SIO)
    #define BL_SIO_REG            (* (reg32 *) BL__SIO)
#endif /* (BL__SIO_CFG) */

/* USBIO registers */
#if !defined(BL__PC) && (CY_PSOC4_4200L)
    #define BL_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BL_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BL_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BL_DRIVE_MODE_SHIFT       (0x00u)
#define BL_DRIVE_MODE_MASK        (0x07u << BL_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BL_H */


/* [] END OF FILE */
