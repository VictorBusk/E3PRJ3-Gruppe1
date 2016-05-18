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

#if !defined(CY_SCB_PVT_LumenCom_H)
#define CY_SCB_PVT_LumenCom_H

#include "LumenCom.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define LumenCom_SetI2CExtClkInterruptMode(interruptMask) LumenCom_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define LumenCom_ClearI2CExtClkInterruptSource(interruptMask) LumenCom_CLEAR_INTR_I2C_EC(interruptMask)
#define LumenCom_GetI2CExtClkInterruptSource()                (LumenCom_INTR_I2C_EC_REG)
#define LumenCom_GetI2CExtClkInterruptMode()                  (LumenCom_INTR_I2C_EC_MASK_REG)
#define LumenCom_GetI2CExtClkInterruptSourceMasked()          (LumenCom_INTR_I2C_EC_MASKED_REG)

#if (!LumenCom_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define LumenCom_SetSpiExtClkInterruptMode(interruptMask) \
                                                                LumenCom_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define LumenCom_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                LumenCom_CLEAR_INTR_SPI_EC(interruptMask)
    #define LumenCom_GetExtSpiClkInterruptSource()                 (LumenCom_INTR_SPI_EC_REG)
    #define LumenCom_GetExtSpiClkInterruptMode()                   (LumenCom_INTR_SPI_EC_MASK_REG)
    #define LumenCom_GetExtSpiClkInterruptSourceMasked()           (LumenCom_INTR_SPI_EC_MASKED_REG)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void LumenCom_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (LumenCom_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LumenCom_CUSTOM_INTR_HANDLER)
    extern cyisraddress LumenCom_customIntrHandler;
#endif /* !defined (CY_REMOVE_LumenCom_CUSTOM_INTR_HANDLER) */
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */

extern LumenCom_BACKUP_STRUCT LumenCom_backup;

#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 LumenCom_scbMode;
    extern uint8 LumenCom_scbEnableWake;
    extern uint8 LumenCom_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 LumenCom_mode;
    extern uint8 LumenCom_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * LumenCom_rxBuffer;
    extern uint8   LumenCom_rxDataBits;
    extern uint32  LumenCom_rxBufferSize;

    extern volatile uint8 * LumenCom_txBuffer;
    extern uint8   LumenCom_txDataBits;
    extern uint32  LumenCom_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 LumenCom_numberOfAddr;
    extern uint8 LumenCom_subAddrSize;
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*        Conditional Macro
****************************************/

#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define LumenCom_SCB_MODE_I2C_RUNTM_CFG     (LumenCom_SCB_MODE_I2C      == LumenCom_scbMode)
    #define LumenCom_SCB_MODE_SPI_RUNTM_CFG     (LumenCom_SCB_MODE_SPI      == LumenCom_scbMode)
    #define LumenCom_SCB_MODE_UART_RUNTM_CFG    (LumenCom_SCB_MODE_UART     == LumenCom_scbMode)
    #define LumenCom_SCB_MODE_EZI2C_RUNTM_CFG   (LumenCom_SCB_MODE_EZI2C    == LumenCom_scbMode)
    #define LumenCom_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (LumenCom_SCB_MODE_UNCONFIG == LumenCom_scbMode)

    /* Defines wakeup enable */
    #define LumenCom_SCB_WAKE_ENABLE_CHECK       (0u != LumenCom_scbEnableWake)
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_SCB_PINS_NUMBER    (7u)
#else
    #define LumenCom_SCB_PINS_NUMBER    (2u)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_LumenCom_H) */


/* [] END OF FILE */
