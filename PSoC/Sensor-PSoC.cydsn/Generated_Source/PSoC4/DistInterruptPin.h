/*******************************************************************************
* File Name: DistInterruptPin.h  
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

#if !defined(CY_PINS_DistInterruptPin_H) /* Pins DistInterruptPin_H */
#define CY_PINS_DistInterruptPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DistInterruptPin_aliases.h"


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
} DistInterruptPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DistInterruptPin_Read(void);
void    DistInterruptPin_Write(uint8 value);
uint8   DistInterruptPin_ReadDataReg(void);
#if defined(DistInterruptPin__PC) || (CY_PSOC4_4200L) 
    void    DistInterruptPin_SetDriveMode(uint8 mode);
#endif
void    DistInterruptPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   DistInterruptPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DistInterruptPin_Sleep(void); 
void DistInterruptPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DistInterruptPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DistInterruptPin_DRIVE_MODE_BITS        (3)
    #define DistInterruptPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DistInterruptPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DistInterruptPin_SetDriveMode() function.
         *  @{
         */
        #define DistInterruptPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DistInterruptPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DistInterruptPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DistInterruptPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DistInterruptPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DistInterruptPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DistInterruptPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DistInterruptPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DistInterruptPin_MASK               DistInterruptPin__MASK
#define DistInterruptPin_SHIFT              DistInterruptPin__SHIFT
#define DistInterruptPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DistInterruptPin_SetInterruptMode() function.
     *  @{
     */
        #define DistInterruptPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DistInterruptPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DistInterruptPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DistInterruptPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DistInterruptPin__SIO)
    #define DistInterruptPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DistInterruptPin__PC) && (CY_PSOC4_4200L)
    #define DistInterruptPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DistInterruptPin_USBIO_DISABLE              ((uint32)(~DistInterruptPin_USBIO_ENABLE))
    #define DistInterruptPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DistInterruptPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DistInterruptPin_USBIO_ENTER_SLEEP          ((uint32)((1u << DistInterruptPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DistInterruptPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define DistInterruptPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DistInterruptPin_USBIO_SUSPEND_SHIFT)))
    #define DistInterruptPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DistInterruptPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define DistInterruptPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DistInterruptPin__PC)
    /* Port Configuration */
    #define DistInterruptPin_PC                 (* (reg32 *) DistInterruptPin__PC)
#endif
/* Pin State */
#define DistInterruptPin_PS                     (* (reg32 *) DistInterruptPin__PS)
/* Data Register */
#define DistInterruptPin_DR                     (* (reg32 *) DistInterruptPin__DR)
/* Input Buffer Disable Override */
#define DistInterruptPin_INP_DIS                (* (reg32 *) DistInterruptPin__PC2)

/* Interrupt configuration Registers */
#define DistInterruptPin_INTCFG                 (* (reg32 *) DistInterruptPin__INTCFG)
#define DistInterruptPin_INTSTAT                (* (reg32 *) DistInterruptPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DistInterruptPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DistInterruptPin__SIO)
    #define DistInterruptPin_SIO_REG            (* (reg32 *) DistInterruptPin__SIO)
#endif /* (DistInterruptPin__SIO_CFG) */

/* USBIO registers */
#if !defined(DistInterruptPin__PC) && (CY_PSOC4_4200L)
    #define DistInterruptPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DistInterruptPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DistInterruptPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DistInterruptPin_DRIVE_MODE_SHIFT       (0x00u)
#define DistInterruptPin_DRIVE_MODE_MASK        (0x07u << DistInterruptPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DistInterruptPin_H */


/* [] END OF FILE */
