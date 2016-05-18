/*******************************************************************************
* File Name: Z_interrupt.h  
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

#if !defined(CY_PINS_Z_interrupt_H) /* Pins Z_interrupt_H */
#define CY_PINS_Z_interrupt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Z_interrupt_aliases.h"


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
} Z_interrupt_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Z_interrupt_Read(void);
void    Z_interrupt_Write(uint8 value);
uint8   Z_interrupt_ReadDataReg(void);
#if defined(Z_interrupt__PC) || (CY_PSOC4_4200L) 
    void    Z_interrupt_SetDriveMode(uint8 mode);
#endif
void    Z_interrupt_SetInterruptMode(uint16 position, uint16 mode);
uint8   Z_interrupt_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Z_interrupt_Sleep(void); 
void Z_interrupt_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Z_interrupt__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Z_interrupt_DRIVE_MODE_BITS        (3)
    #define Z_interrupt_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Z_interrupt_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Z_interrupt_SetDriveMode() function.
         *  @{
         */
        #define Z_interrupt_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Z_interrupt_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Z_interrupt_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Z_interrupt_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Z_interrupt_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Z_interrupt_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Z_interrupt_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Z_interrupt_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Z_interrupt_MASK               Z_interrupt__MASK
#define Z_interrupt_SHIFT              Z_interrupt__SHIFT
#define Z_interrupt_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Z_interrupt_SetInterruptMode() function.
     *  @{
     */
        #define Z_interrupt_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Z_interrupt_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Z_interrupt_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Z_interrupt_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Z_interrupt__SIO)
    #define Z_interrupt_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Z_interrupt__PC) && (CY_PSOC4_4200L)
    #define Z_interrupt_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Z_interrupt_USBIO_DISABLE              ((uint32)(~Z_interrupt_USBIO_ENABLE))
    #define Z_interrupt_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Z_interrupt_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Z_interrupt_USBIO_ENTER_SLEEP          ((uint32)((1u << Z_interrupt_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Z_interrupt_USBIO_SUSPEND_DEL_SHIFT)))
    #define Z_interrupt_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Z_interrupt_USBIO_SUSPEND_SHIFT)))
    #define Z_interrupt_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Z_interrupt_USBIO_SUSPEND_DEL_SHIFT)))
    #define Z_interrupt_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Z_interrupt__PC)
    /* Port Configuration */
    #define Z_interrupt_PC                 (* (reg32 *) Z_interrupt__PC)
#endif
/* Pin State */
#define Z_interrupt_PS                     (* (reg32 *) Z_interrupt__PS)
/* Data Register */
#define Z_interrupt_DR                     (* (reg32 *) Z_interrupt__DR)
/* Input Buffer Disable Override */
#define Z_interrupt_INP_DIS                (* (reg32 *) Z_interrupt__PC2)

/* Interrupt configuration Registers */
#define Z_interrupt_INTCFG                 (* (reg32 *) Z_interrupt__INTCFG)
#define Z_interrupt_INTSTAT                (* (reg32 *) Z_interrupt__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Z_interrupt_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Z_interrupt__SIO)
    #define Z_interrupt_SIO_REG            (* (reg32 *) Z_interrupt__SIO)
#endif /* (Z_interrupt__SIO_CFG) */

/* USBIO registers */
#if !defined(Z_interrupt__PC) && (CY_PSOC4_4200L)
    #define Z_interrupt_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Z_interrupt_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Z_interrupt_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Z_interrupt_DRIVE_MODE_SHIFT       (0x00u)
#define Z_interrupt_DRIVE_MODE_MASK        (0x07u << Z_interrupt_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Z_interrupt_H */


/* [] END OF FILE */
