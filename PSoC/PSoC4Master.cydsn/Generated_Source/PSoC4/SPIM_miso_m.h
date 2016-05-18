/*******************************************************************************
* File Name: SPIM_miso_m.h  
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

#if !defined(CY_PINS_SPIM_miso_m_H) /* Pins SPIM_miso_m_H */
#define CY_PINS_SPIM_miso_m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SPIM_miso_m_aliases.h"


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
} SPIM_miso_m_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SPIM_miso_m_Read(void);
void    SPIM_miso_m_Write(uint8 value);
uint8   SPIM_miso_m_ReadDataReg(void);
#if defined(SPIM_miso_m__PC) || (CY_PSOC4_4200L) 
    void    SPIM_miso_m_SetDriveMode(uint8 mode);
#endif
void    SPIM_miso_m_SetInterruptMode(uint16 position, uint16 mode);
uint8   SPIM_miso_m_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SPIM_miso_m_Sleep(void); 
void SPIM_miso_m_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SPIM_miso_m__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SPIM_miso_m_DRIVE_MODE_BITS        (3)
    #define SPIM_miso_m_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SPIM_miso_m_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SPIM_miso_m_SetDriveMode() function.
         *  @{
         */
        #define SPIM_miso_m_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SPIM_miso_m_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SPIM_miso_m_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SPIM_miso_m_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SPIM_miso_m_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SPIM_miso_m_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SPIM_miso_m_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SPIM_miso_m_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SPIM_miso_m_MASK               SPIM_miso_m__MASK
#define SPIM_miso_m_SHIFT              SPIM_miso_m__SHIFT
#define SPIM_miso_m_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SPIM_miso_m_SetInterruptMode() function.
     *  @{
     */
        #define SPIM_miso_m_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SPIM_miso_m_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SPIM_miso_m_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SPIM_miso_m_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SPIM_miso_m__SIO)
    #define SPIM_miso_m_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SPIM_miso_m__PC) && (CY_PSOC4_4200L)
    #define SPIM_miso_m_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SPIM_miso_m_USBIO_DISABLE              ((uint32)(~SPIM_miso_m_USBIO_ENABLE))
    #define SPIM_miso_m_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SPIM_miso_m_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SPIM_miso_m_USBIO_ENTER_SLEEP          ((uint32)((1u << SPIM_miso_m_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SPIM_miso_m_USBIO_SUSPEND_DEL_SHIFT)))
    #define SPIM_miso_m_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SPIM_miso_m_USBIO_SUSPEND_SHIFT)))
    #define SPIM_miso_m_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SPIM_miso_m_USBIO_SUSPEND_DEL_SHIFT)))
    #define SPIM_miso_m_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SPIM_miso_m__PC)
    /* Port Configuration */
    #define SPIM_miso_m_PC                 (* (reg32 *) SPIM_miso_m__PC)
#endif
/* Pin State */
#define SPIM_miso_m_PS                     (* (reg32 *) SPIM_miso_m__PS)
/* Data Register */
#define SPIM_miso_m_DR                     (* (reg32 *) SPIM_miso_m__DR)
/* Input Buffer Disable Override */
#define SPIM_miso_m_INP_DIS                (* (reg32 *) SPIM_miso_m__PC2)

/* Interrupt configuration Registers */
#define SPIM_miso_m_INTCFG                 (* (reg32 *) SPIM_miso_m__INTCFG)
#define SPIM_miso_m_INTSTAT                (* (reg32 *) SPIM_miso_m__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SPIM_miso_m_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SPIM_miso_m__SIO)
    #define SPIM_miso_m_SIO_REG            (* (reg32 *) SPIM_miso_m__SIO)
#endif /* (SPIM_miso_m__SIO_CFG) */

/* USBIO registers */
#if !defined(SPIM_miso_m__PC) && (CY_PSOC4_4200L)
    #define SPIM_miso_m_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SPIM_miso_m_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SPIM_miso_m_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SPIM_miso_m_DRIVE_MODE_SHIFT       (0x00u)
#define SPIM_miso_m_DRIVE_MODE_MASK        (0x07u << SPIM_miso_m_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SPIM_miso_m_H */


/* [] END OF FILE */
