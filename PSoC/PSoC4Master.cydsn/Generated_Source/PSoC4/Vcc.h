/*******************************************************************************
* File Name: Vcc.h  
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

#if !defined(CY_PINS_Vcc_H) /* Pins Vcc_H */
#define CY_PINS_Vcc_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vcc_aliases.h"


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
} Vcc_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vcc_Read(void);
void    Vcc_Write(uint8 value);
uint8   Vcc_ReadDataReg(void);
#if defined(Vcc__PC) || (CY_PSOC4_4200L) 
    void    Vcc_SetDriveMode(uint8 mode);
#endif
void    Vcc_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vcc_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vcc_Sleep(void); 
void Vcc_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vcc__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vcc_DRIVE_MODE_BITS        (3)
    #define Vcc_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vcc_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vcc_SetDriveMode() function.
         *  @{
         */
        #define Vcc_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vcc_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vcc_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vcc_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vcc_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vcc_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vcc_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vcc_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vcc_MASK               Vcc__MASK
#define Vcc_SHIFT              Vcc__SHIFT
#define Vcc_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vcc_SetInterruptMode() function.
     *  @{
     */
        #define Vcc_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vcc_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vcc_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vcc_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vcc__SIO)
    #define Vcc_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vcc__PC) && (CY_PSOC4_4200L)
    #define Vcc_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vcc_USBIO_DISABLE              ((uint32)(~Vcc_USBIO_ENABLE))
    #define Vcc_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vcc_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vcc_USBIO_ENTER_SLEEP          ((uint32)((1u << Vcc_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vcc_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vcc_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vcc_USBIO_SUSPEND_SHIFT)))
    #define Vcc_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vcc_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vcc_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vcc__PC)
    /* Port Configuration */
    #define Vcc_PC                 (* (reg32 *) Vcc__PC)
#endif
/* Pin State */
#define Vcc_PS                     (* (reg32 *) Vcc__PS)
/* Data Register */
#define Vcc_DR                     (* (reg32 *) Vcc__DR)
/* Input Buffer Disable Override */
#define Vcc_INP_DIS                (* (reg32 *) Vcc__PC2)

/* Interrupt configuration Registers */
#define Vcc_INTCFG                 (* (reg32 *) Vcc__INTCFG)
#define Vcc_INTSTAT                (* (reg32 *) Vcc__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vcc_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vcc__SIO)
    #define Vcc_SIO_REG            (* (reg32 *) Vcc__SIO)
#endif /* (Vcc__SIO_CFG) */

/* USBIO registers */
#if !defined(Vcc__PC) && (CY_PSOC4_4200L)
    #define Vcc_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vcc_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vcc_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vcc_DRIVE_MODE_SHIFT       (0x00u)
#define Vcc_DRIVE_MODE_MASK        (0x07u << Vcc_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vcc_H */


/* [] END OF FILE */
