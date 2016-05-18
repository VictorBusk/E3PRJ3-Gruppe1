/*******************************************************************************
* File Name: Debug_BOOT.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_Debug_H)
#define CY_SCB_BOOT_Debug_H

#include "Debug_PVT.h"

#if (Debug_SCB_MODE_I2C_INC)
    #include "Debug_I2C.h"
#endif /* (Debug_SCB_MODE_I2C_INC) */

#if (Debug_SCB_MODE_EZI2C_INC)
    #include "Debug_EZI2C.h"
#endif /* (Debug_SCB_MODE_EZI2C_INC) */

#if (Debug_SCB_MODE_SPI_INC || Debug_SCB_MODE_UART_INC)
    #include "Debug_SPI_UART.h"
#endif /* (Debug_SCB_MODE_SPI_INC || Debug_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define Debug_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Debug) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (Debug_SCB_MODE_I2C_INC)
    #define Debug_I2C_BTLDR_COMM_ENABLED     (Debug_BTLDR_COMM_ENABLED && \
                                                            (Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Debug_I2C_SLAVE_CONST))
#else
     #define Debug_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (Debug_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (Debug_SCB_MODE_EZI2C_INC)
    #define Debug_EZI2C_BTLDR_COMM_ENABLED   (Debug_BTLDR_COMM_ENABLED && \
                                                         Debug_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define Debug_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (Debug_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (Debug_SCB_MODE_SPI_INC)
    #define Debug_SPI_BTLDR_COMM_ENABLED     (Debug_BTLDR_COMM_ENABLED && \
                                                            (Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             Debug_SPI_SLAVE_CONST))
#else
        #define Debug_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (Debug_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (Debug_SCB_MODE_UART_INC)
       #define Debug_UART_BTLDR_COMM_ENABLED    (Debug_BTLDR_COMM_ENABLED && \
                                                            (Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (Debug_UART_RX_DIRECTION && \
                                                              Debug_UART_TX_DIRECTION)))
#else
     #define Debug_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (Debug_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define Debug_BTLDR_COMM_MODE_ENABLED    (Debug_I2C_BTLDR_COMM_ENABLED   || \
                                                     Debug_SPI_BTLDR_COMM_ENABLED   || \
                                                     Debug_EZI2C_BTLDR_COMM_ENABLED || \
                                                     Debug_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void Debug_I2CCyBtldrCommStart(void);
    void Debug_I2CCyBtldrCommStop (void);
    void Debug_I2CCyBtldrCommReset(void);
    cystatus Debug_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Debug_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (Debug_SCB_MODE_I2C_CONST_CFG)
        #define Debug_CyBtldrCommStart   Debug_I2CCyBtldrCommStart
        #define Debug_CyBtldrCommStop    Debug_I2CCyBtldrCommStop
        #define Debug_CyBtldrCommReset   Debug_I2CCyBtldrCommReset
        #define Debug_CyBtldrCommRead    Debug_I2CCyBtldrCommRead
        #define Debug_CyBtldrCommWrite   Debug_I2CCyBtldrCommWrite
    #endif /* (Debug_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void Debug_EzI2CCyBtldrCommStart(void);
    void Debug_EzI2CCyBtldrCommStop (void);
    void Debug_EzI2CCyBtldrCommReset(void);
    cystatus Debug_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Debug_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (Debug_SCB_MODE_EZI2C_CONST_CFG)
        #define Debug_CyBtldrCommStart   Debug_EzI2CCyBtldrCommStart
        #define Debug_CyBtldrCommStop    Debug_EzI2CCyBtldrCommStop
        #define Debug_CyBtldrCommReset   Debug_EzI2CCyBtldrCommReset
        #define Debug_CyBtldrCommRead    Debug_EzI2CCyBtldrCommRead
        #define Debug_CyBtldrCommWrite   Debug_EzI2CCyBtldrCommWrite
    #endif /* (Debug_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void Debug_SpiCyBtldrCommStart(void);
    void Debug_SpiCyBtldrCommStop (void);
    void Debug_SpiCyBtldrCommReset(void);
    cystatus Debug_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Debug_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (Debug_SCB_MODE_SPI_CONST_CFG)
        #define Debug_CyBtldrCommStart   Debug_SpiCyBtldrCommStart
        #define Debug_CyBtldrCommStop    Debug_SpiCyBtldrCommStop
        #define Debug_CyBtldrCommReset   Debug_SpiCyBtldrCommReset
        #define Debug_CyBtldrCommRead    Debug_SpiCyBtldrCommRead
        #define Debug_CyBtldrCommWrite   Debug_SpiCyBtldrCommWrite
    #endif /* (Debug_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void Debug_UartCyBtldrCommStart(void);
    void Debug_UartCyBtldrCommStop (void);
    void Debug_UartCyBtldrCommReset(void);
    cystatus Debug_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus Debug_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (Debug_SCB_MODE_UART_CONST_CFG)
        #define Debug_CyBtldrCommStart   Debug_UartCyBtldrCommStart
        #define Debug_CyBtldrCommStop    Debug_UartCyBtldrCommStop
        #define Debug_CyBtldrCommReset   Debug_UartCyBtldrCommReset
        #define Debug_CyBtldrCommRead    Debug_UartCyBtldrCommRead
        #define Debug_CyBtldrCommWrite   Debug_UartCyBtldrCommWrite
    #endif /* (Debug_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_BTLDR_COMM_ENABLED)
    #if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void Debug_CyBtldrCommStart(void);
        void Debug_CyBtldrCommStop (void);
        void Debug_CyBtldrCommReset(void);
        cystatus Debug_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus Debug_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Debug)
        #define CyBtldrCommStart    Debug_CyBtldrCommStart
        #define CyBtldrCommStop     Debug_CyBtldrCommStop
        #define CyBtldrCommReset    Debug_CyBtldrCommReset
        #define CyBtldrCommWrite    Debug_CyBtldrCommWrite
        #define CyBtldrCommRead     Debug_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Debug) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Debug_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define Debug_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define Debug_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define Debug_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define Debug_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef Debug_SPI_BYTE_TO_BYTE
    #define Debug_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef Debug_UART_BYTE_TO_BYTE
    #define Debug_UART_BYTE_TO_BYTE  (2081u)
#endif /* Debug_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_Debug_H) */


/* [] END OF FILE */
