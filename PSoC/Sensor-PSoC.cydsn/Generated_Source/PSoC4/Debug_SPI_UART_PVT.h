/*******************************************************************************
* File Name: Debug_SPI_UART_PVT.h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_Debug_H)
#define CY_SCB_SPI_UART_PVT_Debug_H

#include "Debug_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (Debug_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  Debug_rxBufferHead;
    extern volatile uint32  Debug_rxBufferTail;
    extern volatile uint8   Debug_rxBufferOverflow;
#endif /* (Debug_INTERNAL_RX_SW_BUFFER_CONST) */

#if (Debug_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  Debug_txBufferHead;
    extern volatile uint32  Debug_txBufferTail;
#endif /* (Debug_INTERNAL_TX_SW_BUFFER_CONST) */

#if (Debug_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 Debug_rxBufferInternal[Debug_INTERNAL_RX_BUFFER_SIZE];
#endif /* (Debug_INTERNAL_RX_SW_BUFFER) */

#if (Debug_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 Debug_txBufferInternal[Debug_TX_BUFFER_SIZE];
#endif /* (Debug_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void Debug_SpiPostEnable(void);
void Debug_SpiStop(void);

#if (Debug_SCB_MODE_SPI_CONST_CFG)
    void Debug_SpiInit(void);
#endif /* (Debug_SCB_MODE_SPI_CONST_CFG) */

#if (Debug_SPI_WAKE_ENABLE_CONST)
    void Debug_SpiSaveConfig(void);
    void Debug_SpiRestoreConfig(void);
#endif /* (Debug_SPI_WAKE_ENABLE_CONST) */

void Debug_UartPostEnable(void);
void Debug_UartStop(void);

#if (Debug_SCB_MODE_UART_CONST_CFG)
    void Debug_UartInit(void);
#endif /* (Debug_SCB_MODE_UART_CONST_CFG) */

#if (Debug_UART_WAKE_ENABLE_CONST)
    void Debug_UartSaveConfig(void);
    void Debug_UartRestoreConfig(void);
#endif /* (Debug_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in Debug_SetPins() */
#define Debug_UART_RX_PIN_ENABLE    (Debug_UART_RX)
#define Debug_UART_TX_PIN_ENABLE    (Debug_UART_TX)

/* UART RTS and CTS position to be used in  Debug_SetPins() */
#define Debug_UART_RTS_PIN_ENABLE    (0x10u)
#define Debug_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define Debug_SpiUartEnableIntRx(intSourceMask)  Debug_SetRxInterruptMode(intSourceMask)
#define Debug_SpiUartEnableIntTx(intSourceMask)  Debug_SetTxInterruptMode(intSourceMask)
uint32  Debug_SpiUartDisableIntRx(void);
uint32  Debug_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_Debug_H) */


/* [] END OF FILE */
