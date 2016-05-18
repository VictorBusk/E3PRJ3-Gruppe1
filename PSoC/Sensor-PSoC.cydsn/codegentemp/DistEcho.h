/*******************************************************************************
* File Name: DistEcho.h  
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

#if !defined(CY_PINS_DistEcho_H) /* Pins DistEcho_H */
#define CY_PINS_DistEcho_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DistEcho_aliases.h"


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
} DistEcho_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DistEcho_Read(void);
void    DistEcho_Write(uint8 value);
uint8   DistEcho_ReadDataReg(void);
#if defined(DistEcho__PC) || (CY_PSOC4_4200L) 
    void    DistEcho_SetDriveMode(uint8 mode);
#endif
void    DistEcho_SetInterruptMode(uint16 position, uint16 mode);
uint8   DistEcho_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DistEcho_Sleep(void); 
void DistEcho_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DistEcho__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DistEcho_DRIVE_MODE_BITS        (3)
    #define DistEcho_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DistEcho_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DistEcho_SetDriveMode() function.
         *  @{
         */
        #define DistEcho_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DistEcho_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DistEcho_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DistEcho_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DistEcho_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DistEcho_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DistEcho_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DistEcho_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DistEcho_MASK               DistEcho__MASK
#define DistEcho_SHIFT              DistEcho__SHIFT
#define DistEcho_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DistEcho_SetInterruptMode() function.
     *  @{
     */
        #define DistEcho_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DistEcho_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DistEcho_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DistEcho_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DistEcho__SIO)
    #define DistEcho_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DistEcho__PC) && (CY_PSOC4_4200L)
    #define DistEcho_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DistEcho_USBIO_DISABLE              ((uint32)(~DistEcho_USBIO_ENABLE))
    #define DistEcho_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DistEcho_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DistEcho_USBIO_ENTER_SLEEP          ((uint32)((1u << DistEcho_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DistEcho_USBIO_SUSPEND_DEL_SHIFT)))
    #define DistEcho_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DistEcho_USBIO_SUSPEND_SHIFT)))
    #define DistEcho_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DistEcho_USBIO_SUSPEND_DEL_SHIFT)))
    #define DistEcho_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DistEcho__PC)
    /* Port Configuration */
    #define DistEcho_PC                 (* (reg32 *) DistEcho__PC)
#endif
/* Pin State */
#define DistEcho_PS                     (* (reg32 *) DistEcho__PS)
/* Data Register */
#define DistEcho_DR                     (* (reg32 *) DistEcho__DR)
/* Input Buffer Disable Override */
#define DistEcho_INP_DIS                (* (reg32 *) DistEcho__PC2)

/* Interrupt configuration Registers */
#define DistEcho_INTCFG                 (* (reg32 *) DistEcho__INTCFG)
#define DistEcho_INTSTAT                (* (reg32 *) DistEcho__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DistEcho_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DistEcho__SIO)
    #define DistEcho_SIO_REG            (* (reg32 *) DistEcho__SIO)
#endif /* (DistEcho__SIO_CFG) */

/* USBIO registers */
#if !defined(DistEcho__PC) && (CY_PSOC4_4200L)
    #define DistEcho_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DistEcho_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DistEcho_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DistEcho_DRIVE_MODE_SHIFT       (0x00u)
#define DistEcho_DRIVE_MODE_MASK        (0x07u << DistEcho_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DistEcho_H */


/* [] END OF FILE */
