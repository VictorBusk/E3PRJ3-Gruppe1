/*******************************************************************************
* File Name: DistReset.h  
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

#if !defined(CY_PINS_DistReset_H) /* Pins DistReset_H */
#define CY_PINS_DistReset_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DistReset_aliases.h"


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
} DistReset_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DistReset_Read(void);
void    DistReset_Write(uint8 value);
uint8   DistReset_ReadDataReg(void);
#if defined(DistReset__PC) || (CY_PSOC4_4200L) 
    void    DistReset_SetDriveMode(uint8 mode);
#endif
void    DistReset_SetInterruptMode(uint16 position, uint16 mode);
uint8   DistReset_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DistReset_Sleep(void); 
void DistReset_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DistReset__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DistReset_DRIVE_MODE_BITS        (3)
    #define DistReset_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DistReset_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DistReset_SetDriveMode() function.
         *  @{
         */
        #define DistReset_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DistReset_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DistReset_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DistReset_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DistReset_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DistReset_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DistReset_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DistReset_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DistReset_MASK               DistReset__MASK
#define DistReset_SHIFT              DistReset__SHIFT
#define DistReset_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DistReset_SetInterruptMode() function.
     *  @{
     */
        #define DistReset_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DistReset_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DistReset_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DistReset_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DistReset__SIO)
    #define DistReset_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DistReset__PC) && (CY_PSOC4_4200L)
    #define DistReset_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DistReset_USBIO_DISABLE              ((uint32)(~DistReset_USBIO_ENABLE))
    #define DistReset_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DistReset_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DistReset_USBIO_ENTER_SLEEP          ((uint32)((1u << DistReset_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DistReset_USBIO_SUSPEND_DEL_SHIFT)))
    #define DistReset_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DistReset_USBIO_SUSPEND_SHIFT)))
    #define DistReset_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DistReset_USBIO_SUSPEND_DEL_SHIFT)))
    #define DistReset_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DistReset__PC)
    /* Port Configuration */
    #define DistReset_PC                 (* (reg32 *) DistReset__PC)
#endif
/* Pin State */
#define DistReset_PS                     (* (reg32 *) DistReset__PS)
/* Data Register */
#define DistReset_DR                     (* (reg32 *) DistReset__DR)
/* Input Buffer Disable Override */
#define DistReset_INP_DIS                (* (reg32 *) DistReset__PC2)

/* Interrupt configuration Registers */
#define DistReset_INTCFG                 (* (reg32 *) DistReset__INTCFG)
#define DistReset_INTSTAT                (* (reg32 *) DistReset__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DistReset_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DistReset__SIO)
    #define DistReset_SIO_REG            (* (reg32 *) DistReset__SIO)
#endif /* (DistReset__SIO_CFG) */

/* USBIO registers */
#if !defined(DistReset__PC) && (CY_PSOC4_4200L)
    #define DistReset_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DistReset_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DistReset_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DistReset_DRIVE_MODE_SHIFT       (0x00u)
#define DistReset_DRIVE_MODE_MASK        (0x07u << DistReset_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DistReset_H */


/* [] END OF FILE */
