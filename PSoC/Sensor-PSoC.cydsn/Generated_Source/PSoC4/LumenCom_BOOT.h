/*******************************************************************************
* File Name: LumenCom_BOOT.h
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

#if !defined(CY_SCB_BOOT_LumenCom_H)
#define CY_SCB_BOOT_LumenCom_H

#include "LumenCom_PVT.h"

#if (LumenCom_SCB_MODE_I2C_INC)
    #include "LumenCom_I2C.h"
#endif /* (LumenCom_SCB_MODE_I2C_INC) */

#if (LumenCom_SCB_MODE_EZI2C_INC)
    #include "LumenCom_EZI2C.h"
#endif /* (LumenCom_SCB_MODE_EZI2C_INC) */

#if (LumenCom_SCB_MODE_SPI_INC || LumenCom_SCB_MODE_UART_INC)
    #include "LumenCom_SPI_UART.h"
#endif /* (LumenCom_SCB_MODE_SPI_INC || LumenCom_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define LumenCom_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LumenCom) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (LumenCom_SCB_MODE_I2C_INC)
    #define LumenCom_I2C_BTLDR_COMM_ENABLED     (LumenCom_BTLDR_COMM_ENABLED && \
                                                            (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             LumenCom_I2C_SLAVE_CONST))
#else
     #define LumenCom_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (LumenCom_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (LumenCom_SCB_MODE_EZI2C_INC)
    #define LumenCom_EZI2C_BTLDR_COMM_ENABLED   (LumenCom_BTLDR_COMM_ENABLED && \
                                                         LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define LumenCom_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (LumenCom_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (LumenCom_SCB_MODE_SPI_INC)
    #define LumenCom_SPI_BTLDR_COMM_ENABLED     (LumenCom_BTLDR_COMM_ENABLED && \
                                                            (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             LumenCom_SPI_SLAVE_CONST))
#else
        #define LumenCom_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (LumenCom_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (LumenCom_SCB_MODE_UART_INC)
       #define LumenCom_UART_BTLDR_COMM_ENABLED    (LumenCom_BTLDR_COMM_ENABLED && \
                                                            (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (LumenCom_UART_RX_DIRECTION && \
                                                              LumenCom_UART_TX_DIRECTION)))
#else
     #define LumenCom_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (LumenCom_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define LumenCom_BTLDR_COMM_MODE_ENABLED    (LumenCom_I2C_BTLDR_COMM_ENABLED   || \
                                                     LumenCom_SPI_BTLDR_COMM_ENABLED   || \
                                                     LumenCom_EZI2C_BTLDR_COMM_ENABLED || \
                                                     LumenCom_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void LumenCom_I2CCyBtldrCommStart(void);
    void LumenCom_I2CCyBtldrCommStop (void);
    void LumenCom_I2CCyBtldrCommReset(void);
    cystatus LumenCom_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LumenCom_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (LumenCom_SCB_MODE_I2C_CONST_CFG)
        #define LumenCom_CyBtldrCommStart   LumenCom_I2CCyBtldrCommStart
        #define LumenCom_CyBtldrCommStop    LumenCom_I2CCyBtldrCommStop
        #define LumenCom_CyBtldrCommReset   LumenCom_I2CCyBtldrCommReset
        #define LumenCom_CyBtldrCommRead    LumenCom_I2CCyBtldrCommRead
        #define LumenCom_CyBtldrCommWrite   LumenCom_I2CCyBtldrCommWrite
    #endif /* (LumenCom_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void LumenCom_EzI2CCyBtldrCommStart(void);
    void LumenCom_EzI2CCyBtldrCommStop (void);
    void LumenCom_EzI2CCyBtldrCommReset(void);
    cystatus LumenCom_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LumenCom_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (LumenCom_SCB_MODE_EZI2C_CONST_CFG)
        #define LumenCom_CyBtldrCommStart   LumenCom_EzI2CCyBtldrCommStart
        #define LumenCom_CyBtldrCommStop    LumenCom_EzI2CCyBtldrCommStop
        #define LumenCom_CyBtldrCommReset   LumenCom_EzI2CCyBtldrCommReset
        #define LumenCom_CyBtldrCommRead    LumenCom_EzI2CCyBtldrCommRead
        #define LumenCom_CyBtldrCommWrite   LumenCom_EzI2CCyBtldrCommWrite
    #endif /* (LumenCom_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void LumenCom_SpiCyBtldrCommStart(void);
    void LumenCom_SpiCyBtldrCommStop (void);
    void LumenCom_SpiCyBtldrCommReset(void);
    cystatus LumenCom_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LumenCom_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (LumenCom_SCB_MODE_SPI_CONST_CFG)
        #define LumenCom_CyBtldrCommStart   LumenCom_SpiCyBtldrCommStart
        #define LumenCom_CyBtldrCommStop    LumenCom_SpiCyBtldrCommStop
        #define LumenCom_CyBtldrCommReset   LumenCom_SpiCyBtldrCommReset
        #define LumenCom_CyBtldrCommRead    LumenCom_SpiCyBtldrCommRead
        #define LumenCom_CyBtldrCommWrite   LumenCom_SpiCyBtldrCommWrite
    #endif /* (LumenCom_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void LumenCom_UartCyBtldrCommStart(void);
    void LumenCom_UartCyBtldrCommStop (void);
    void LumenCom_UartCyBtldrCommReset(void);
    cystatus LumenCom_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus LumenCom_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (LumenCom_SCB_MODE_UART_CONST_CFG)
        #define LumenCom_CyBtldrCommStart   LumenCom_UartCyBtldrCommStart
        #define LumenCom_CyBtldrCommStop    LumenCom_UartCyBtldrCommStop
        #define LumenCom_CyBtldrCommReset   LumenCom_UartCyBtldrCommReset
        #define LumenCom_CyBtldrCommRead    LumenCom_UartCyBtldrCommRead
        #define LumenCom_CyBtldrCommWrite   LumenCom_UartCyBtldrCommWrite
    #endif /* (LumenCom_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_BTLDR_COMM_ENABLED)
    #if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void LumenCom_CyBtldrCommStart(void);
        void LumenCom_CyBtldrCommStop (void);
        void LumenCom_CyBtldrCommReset(void);
        cystatus LumenCom_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus LumenCom_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LumenCom)
        #define CyBtldrCommStart    LumenCom_CyBtldrCommStart
        #define CyBtldrCommStop     LumenCom_CyBtldrCommStop
        #define CyBtldrCommReset    LumenCom_CyBtldrCommReset
        #define CyBtldrCommWrite    LumenCom_CyBtldrCommWrite
        #define CyBtldrCommRead     LumenCom_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LumenCom) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (LumenCom_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define LumenCom_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define LumenCom_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define LumenCom_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define LumenCom_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef LumenCom_SPI_BYTE_TO_BYTE
    #define LumenCom_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef LumenCom_UART_BYTE_TO_BYTE
    #define LumenCom_UART_BYTE_TO_BYTE  (2500u)
#endif /* LumenCom_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_LumenCom_H) */


/* [] END OF FILE */
