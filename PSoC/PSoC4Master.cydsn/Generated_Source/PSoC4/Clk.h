/*******************************************************************************
* File Name: Clk.h  
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

#if !defined(CY_PINS_Clk_H) /* Pins Clk_H */
#define CY_PINS_Clk_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Clk_aliases.h"


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
} Clk_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Clk_Read(void);
void    Clk_Write(uint8 value);
uint8   Clk_ReadDataReg(void);
#if defined(Clk__PC) || (CY_PSOC4_4200L) 
    void    Clk_SetDriveMode(uint8 mode);
#endif
void    Clk_SetInterruptMode(uint16 position, uint16 mode);
uint8   Clk_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Clk_Sleep(void); 
void Clk_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Clk__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Clk_DRIVE_MODE_BITS        (3)
    #define Clk_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Clk_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Clk_SetDriveMode() function.
         *  @{
         */
        #define Clk_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Clk_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Clk_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Clk_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Clk_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Clk_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Clk_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Clk_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Clk_MASK               Clk__MASK
#define Clk_SHIFT              Clk__SHIFT
#define Clk_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Clk_SetInterruptMode() function.
     *  @{
     */
        #define Clk_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Clk_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Clk_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Clk_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Clk__SIO)
    #define Clk_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Clk__PC) && (CY_PSOC4_4200L)
    #define Clk_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Clk_USBIO_DISABLE              ((uint32)(~Clk_USBIO_ENABLE))
    #define Clk_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Clk_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Clk_USBIO_ENTER_SLEEP          ((uint32)((1u << Clk_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Clk_USBIO_SUSPEND_DEL_SHIFT)))
    #define Clk_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Clk_USBIO_SUSPEND_SHIFT)))
    #define Clk_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Clk_USBIO_SUSPEND_DEL_SHIFT)))
    #define Clk_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Clk__PC)
    /* Port Configuration */
    #define Clk_PC                 (* (reg32 *) Clk__PC)
#endif
/* Pin State */
#define Clk_PS                     (* (reg32 *) Clk__PS)
/* Data Register */
#define Clk_DR                     (* (reg32 *) Clk__DR)
/* Input Buffer Disable Override */
#define Clk_INP_DIS                (* (reg32 *) Clk__PC2)

/* Interrupt configuration Registers */
#define Clk_INTCFG                 (* (reg32 *) Clk__INTCFG)
#define Clk_INTSTAT                (* (reg32 *) Clk__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Clk_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Clk__SIO)
    #define Clk_SIO_REG            (* (reg32 *) Clk__SIO)
#endif /* (Clk__SIO_CFG) */

/* USBIO registers */
#if !defined(Clk__PC) && (CY_PSOC4_4200L)
    #define Clk_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Clk_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Clk_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Clk_DRIVE_MODE_SHIFT       (0x00u)
#define Clk_DRIVE_MODE_MASK        (0x07u << Clk_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Clk_H */


/* [] END OF FILE */
