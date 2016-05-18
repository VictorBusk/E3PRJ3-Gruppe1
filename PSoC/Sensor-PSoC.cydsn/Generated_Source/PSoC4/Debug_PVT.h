/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_Debug_H)
#define CY_SCB_PVT_Debug_H

#include "Debug.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define Debug_SetI2CExtClkInterruptMode(interruptMask) Debug_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define Debug_ClearI2CExtClkInterruptSource(interruptMask) Debug_CLEAR_INTR_I2C_EC(interruptMask)
#define Debug_GetI2CExtClkInterruptSource()                (Debug_INTR_I2C_EC_REG)
#define Debug_GetI2CExtClkInterruptMode()                  (Debug_INTR_I2C_EC_MASK_REG)
#define Debug_GetI2CExtClkInterruptSourceMasked()          (Debug_INTR_I2C_EC_MASKED_REG)

#if (!Debug_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define Debug_SetSpiExtClkInterruptMode(interruptMask) \
                                                                Debug_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define Debug_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                Debug_CLEAR_INTR_SPI_EC(interruptMask)
    #define Debug_GetExtSpiClkInterruptSource()                 (Debug_INTR_SPI_EC_REG)
    #define Debug_GetExtSpiClkInterruptMode()                   (Debug_INTR_SPI_EC_MASK_REG)
    #define Debug_GetExtSpiClkInterruptSourceMasked()           (Debug_INTR_SPI_EC_MASKED_REG)
#endif /* (!Debug_CY_SCBIP_V1) */

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void Debug_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (Debug_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_Debug_CUSTOM_INTR_HANDLER)
    extern cyisraddress Debug_customIntrHandler;
#endif /* !defined (CY_REMOVE_Debug_CUSTOM_INTR_HANDLER) */
#endif /* (Debug_SCB_IRQ_INTERNAL) */

extern Debug_BACKUP_STRUCT Debug_backup;

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 Debug_scbMode;
    extern uint8 Debug_scbEnableWake;
    extern uint8 Debug_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 Debug_mode;
    extern uint8 Debug_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * Debug_rxBuffer;
    extern uint8   Debug_rxDataBits;
    extern uint32  Debug_rxBufferSize;

    extern volatile uint8 * Debug_txBuffer;
    extern uint8   Debug_txDataBits;
    extern uint32  Debug_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 Debug_numberOfAddr;
    extern uint8 Debug_subAddrSize;
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define Debug_SCB_MODE_I2C_RUNTM_CFG     (Debug_SCB_MODE_I2C      == Debug_scbMode)
    #define Debug_SCB_MODE_SPI_RUNTM_CFG     (Debug_SCB_MODE_SPI      == Debug_scbMode)
    #define Debug_SCB_MODE_UART_RUNTM_CFG    (Debug_SCB_MODE_UART     == Debug_scbMode)
    #define Debug_SCB_MODE_EZI2C_RUNTM_CFG   (Debug_SCB_MODE_EZI2C    == Debug_scbMode)
    #define Debug_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (Debug_SCB_MODE_UNCONFIG == Debug_scbMode)

    /* Defines wakeup enable */
    #define Debug_SCB_WAKE_ENABLE_CHECK       (0u != Debug_scbEnableWake)
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!Debug_CY_SCBIP_V1)
    #define Debug_SCB_PINS_NUMBER    (7u)
#else
    #define Debug_SCB_PINS_NUMBER    (2u)
#endif /* (!Debug_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_Debug_H) */


/* [] END OF FILE */
