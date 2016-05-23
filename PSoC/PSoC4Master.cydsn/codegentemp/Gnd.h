/*******************************************************************************
* File Name: Gnd.h  
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

#if !defined(CY_PINS_Gnd_H) /* Pins Gnd_H */
#define CY_PINS_Gnd_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Gnd_aliases.h"


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
} Gnd_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Gnd_Read(void);
void    Gnd_Write(uint8 value);
uint8   Gnd_ReadDataReg(void);
#if defined(Gnd__PC) || (CY_PSOC4_4200L) 
    void    Gnd_SetDriveMode(uint8 mode);
#endif
void    Gnd_SetInterruptMode(uint16 position, uint16 mode);
uint8   Gnd_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Gnd_Sleep(void); 
void Gnd_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Gnd__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Gnd_DRIVE_MODE_BITS        (3)
    #define Gnd_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Gnd_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Gnd_SetDriveMode() function.
         *  @{
         */
        #define Gnd_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Gnd_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Gnd_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Gnd_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Gnd_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Gnd_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Gnd_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Gnd_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Gnd_MASK               Gnd__MASK
#define Gnd_SHIFT              Gnd__SHIFT
#define Gnd_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Gnd_SetInterruptMode() function.
     *  @{
     */
        #define Gnd_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Gnd_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Gnd_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Gnd_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Gnd__SIO)
    #define Gnd_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Gnd__PC) && (CY_PSOC4_4200L)
    #define Gnd_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Gnd_USBIO_DISABLE              ((uint32)(~Gnd_USBIO_ENABLE))
    #define Gnd_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Gnd_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Gnd_USBIO_ENTER_SLEEP          ((uint32)((1u << Gnd_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Gnd_USBIO_SUSPEND_DEL_SHIFT)))
    #define Gnd_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Gnd_USBIO_SUSPEND_SHIFT)))
    #define Gnd_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Gnd_USBIO_SUSPEND_DEL_SHIFT)))
    #define Gnd_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Gnd__PC)
    /* Port Configuration */
    #define Gnd_PC                 (* (reg32 *) Gnd__PC)
#endif
/* Pin State */
#define Gnd_PS                     (* (reg32 *) Gnd__PS)
/* Data Register */
#define Gnd_DR                     (* (reg32 *) Gnd__DR)
/* Input Buffer Disable Override */
#define Gnd_INP_DIS                (* (reg32 *) Gnd__PC2)

/* Interrupt configuration Registers */
#define Gnd_INTCFG                 (* (reg32 *) Gnd__INTCFG)
#define Gnd_INTSTAT                (* (reg32 *) Gnd__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Gnd_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Gnd__SIO)
    #define Gnd_SIO_REG            (* (reg32 *) Gnd__SIO)
#endif /* (Gnd__SIO_CFG) */

/* USBIO registers */
#if !defined(Gnd__PC) && (CY_PSOC4_4200L)
    #define Gnd_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Gnd_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Gnd_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Gnd_DRIVE_MODE_SHIFT       (0x00u)
#define Gnd_DRIVE_MODE_MASK        (0x07u << Gnd_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Gnd_H */


/* [] END OF FILE */
