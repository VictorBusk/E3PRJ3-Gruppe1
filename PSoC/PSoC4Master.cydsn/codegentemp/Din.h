/*******************************************************************************
* File Name: Din.h  
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

#if !defined(CY_PINS_Din_H) /* Pins Din_H */
#define CY_PINS_Din_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Din_aliases.h"


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
} Din_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Din_Read(void);
void    Din_Write(uint8 value);
uint8   Din_ReadDataReg(void);
#if defined(Din__PC) || (CY_PSOC4_4200L) 
    void    Din_SetDriveMode(uint8 mode);
#endif
void    Din_SetInterruptMode(uint16 position, uint16 mode);
uint8   Din_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Din_Sleep(void); 
void Din_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Din__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Din_DRIVE_MODE_BITS        (3)
    #define Din_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Din_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Din_SetDriveMode() function.
         *  @{
         */
        #define Din_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Din_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Din_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Din_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Din_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Din_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Din_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Din_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Din_MASK               Din__MASK
#define Din_SHIFT              Din__SHIFT
#define Din_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Din_SetInterruptMode() function.
     *  @{
     */
        #define Din_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Din_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Din_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Din_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Din__SIO)
    #define Din_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Din__PC) && (CY_PSOC4_4200L)
    #define Din_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Din_USBIO_DISABLE              ((uint32)(~Din_USBIO_ENABLE))
    #define Din_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Din_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Din_USBIO_ENTER_SLEEP          ((uint32)((1u << Din_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Din_USBIO_SUSPEND_DEL_SHIFT)))
    #define Din_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Din_USBIO_SUSPEND_SHIFT)))
    #define Din_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Din_USBIO_SUSPEND_DEL_SHIFT)))
    #define Din_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Din__PC)
    /* Port Configuration */
    #define Din_PC                 (* (reg32 *) Din__PC)
#endif
/* Pin State */
#define Din_PS                     (* (reg32 *) Din__PS)
/* Data Register */
#define Din_DR                     (* (reg32 *) Din__DR)
/* Input Buffer Disable Override */
#define Din_INP_DIS                (* (reg32 *) Din__PC2)

/* Interrupt configuration Registers */
#define Din_INTCFG                 (* (reg32 *) Din__INTCFG)
#define Din_INTSTAT                (* (reg32 *) Din__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Din_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Din__SIO)
    #define Din_SIO_REG            (* (reg32 *) Din__SIO)
#endif /* (Din__SIO_CFG) */

/* USBIO registers */
#if !defined(Din__PC) && (CY_PSOC4_4200L)
    #define Din_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Din_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Din_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Din_DRIVE_MODE_SHIFT       (0x00u)
#define Din_DRIVE_MODE_MASK        (0x07u << Din_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Din_H */


/* [] END OF FILE */
