/*******************************************************************************
* File Name: Reset.h  
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

#if !defined(CY_PINS_Reset_H) /* Pins Reset_H */
#define CY_PINS_Reset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Reset_aliases.h"


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
} Reset_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Reset_Read(void);
void    Reset_Write(uint8 value);
uint8   Reset_ReadDataReg(void);
#if defined(Reset__PC) || (CY_PSOC4_4200L) 
    void    Reset_SetDriveMode(uint8 mode);
#endif
void    Reset_SetInterruptMode(uint16 position, uint16 mode);
uint8   Reset_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Reset_Sleep(void); 
void Reset_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Reset__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Reset_DRIVE_MODE_BITS        (3)
    #define Reset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Reset_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Reset_SetDriveMode() function.
         *  @{
         */
        #define Reset_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Reset_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Reset_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Reset_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Reset_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Reset_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Reset_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Reset_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Reset_MASK               Reset__MASK
#define Reset_SHIFT              Reset__SHIFT
#define Reset_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Reset_SetInterruptMode() function.
     *  @{
     */
        #define Reset_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Reset_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Reset_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Reset_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Reset__SIO)
    #define Reset_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Reset__PC) && (CY_PSOC4_4200L)
    #define Reset_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Reset_USBIO_DISABLE              ((uint32)(~Reset_USBIO_ENABLE))
    #define Reset_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Reset_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Reset_USBIO_ENTER_SLEEP          ((uint32)((1u << Reset_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Reset_USBIO_SUSPEND_DEL_SHIFT)))
    #define Reset_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Reset_USBIO_SUSPEND_SHIFT)))
    #define Reset_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Reset_USBIO_SUSPEND_DEL_SHIFT)))
    #define Reset_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Reset__PC)
    /* Port Configuration */
    #define Reset_PC                 (* (reg32 *) Reset__PC)
#endif
/* Pin State */
#define Reset_PS                     (* (reg32 *) Reset__PS)
/* Data Register */
#define Reset_DR                     (* (reg32 *) Reset__DR)
/* Input Buffer Disable Override */
#define Reset_INP_DIS                (* (reg32 *) Reset__PC2)

/* Interrupt configuration Registers */
#define Reset_INTCFG                 (* (reg32 *) Reset__INTCFG)
#define Reset_INTSTAT                (* (reg32 *) Reset__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Reset_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Reset__SIO)
    #define Reset_SIO_REG            (* (reg32 *) Reset__SIO)
#endif /* (Reset__SIO_CFG) */

/* USBIO registers */
#if !defined(Reset__PC) && (CY_PSOC4_4200L)
    #define Reset_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Reset_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Reset_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Reset_DRIVE_MODE_SHIFT       (0x00u)
#define Reset_DRIVE_MODE_MASK        (0x07u << Reset_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Reset_H */


/* [] END OF FILE */
