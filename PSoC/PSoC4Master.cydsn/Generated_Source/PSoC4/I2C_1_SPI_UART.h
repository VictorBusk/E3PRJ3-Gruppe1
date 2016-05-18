/*******************************************************************************
* File Name: I2C_1_SPI_UART.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_I2C_1_H)
#define CY_SCB_SPI_UART_I2C_1_H

#include "I2C_1.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define I2C_1_SPI_MODE                   (1u)
#define I2C_1_SPI_SUB_MODE               (0u)
#define I2C_1_SPI_CLOCK_MODE             (3u)
#define I2C_1_SPI_OVS_FACTOR             (16u)
#define I2C_1_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define I2C_1_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define I2C_1_SPI_RX_DATA_BITS_NUM       (8u)
#define I2C_1_SPI_TX_DATA_BITS_NUM       (8u)
#define I2C_1_SPI_WAKE_ENABLE            (0u)
#define I2C_1_SPI_BITS_ORDER             (1u)
#define I2C_1_SPI_TRANSFER_SEPARATION    (1u)
#define I2C_1_SPI_NUMBER_OF_SS_LINES     (1u)
#define I2C_1_SPI_RX_BUFFER_SIZE         (8u)
#define I2C_1_SPI_TX_BUFFER_SIZE         (8u)

#define I2C_1_SPI_INTERRUPT_MODE         (0u)

#define I2C_1_SPI_INTR_RX_MASK           (0u)
#define I2C_1_SPI_INTR_TX_MASK           (0u)

#define I2C_1_SPI_RX_TRIGGER_LEVEL       (7u)
#define I2C_1_SPI_TX_TRIGGER_LEVEL       (0u)

#define I2C_1_SPI_BYTE_MODE_ENABLE       (0u)
#define I2C_1_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define I2C_1_SPI_SS0_POLARITY           (0u)
#define I2C_1_SPI_SS1_POLARITY           (0u)
#define I2C_1_SPI_SS2_POLARITY           (0u)
#define I2C_1_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define I2C_1_UART_SUB_MODE              (0u)
#define I2C_1_UART_DIRECTION             (3u)
#define I2C_1_UART_DATA_BITS_NUM         (8u)
#define I2C_1_UART_PARITY_TYPE           (2u)
#define I2C_1_UART_STOP_BITS_NUM         (2u)
#define I2C_1_UART_OVS_FACTOR            (12u)
#define I2C_1_UART_IRDA_LOW_POWER        (0u)
#define I2C_1_UART_MEDIAN_FILTER_ENABLE  (0u)
#define I2C_1_UART_RETRY_ON_NACK         (0u)
#define I2C_1_UART_IRDA_POLARITY         (0u)
#define I2C_1_UART_DROP_ON_FRAME_ERR     (0u)
#define I2C_1_UART_DROP_ON_PARITY_ERR    (0u)
#define I2C_1_UART_WAKE_ENABLE           (0u)
#define I2C_1_UART_RX_BUFFER_SIZE        (8u)
#define I2C_1_UART_TX_BUFFER_SIZE        (8u)
#define I2C_1_UART_MP_MODE_ENABLE        (0u)
#define I2C_1_UART_MP_ACCEPT_ADDRESS     (0u)
#define I2C_1_UART_MP_RX_ADDRESS         (2u)
#define I2C_1_UART_MP_RX_ADDRESS_MASK    (255u)

#define I2C_1_UART_INTERRUPT_MODE        (0u)

#define I2C_1_UART_INTR_RX_MASK          (0u)
#define I2C_1_UART_INTR_TX_MASK          (0u)

#define I2C_1_UART_RX_TRIGGER_LEVEL      (7u)
#define I2C_1_UART_TX_TRIGGER_LEVEL      (0u)

#define I2C_1_UART_BYTE_MODE_ENABLE      (0u)
#define I2C_1_UART_CTS_ENABLE            (0u)
#define I2C_1_UART_CTS_POLARITY          (0u)
#define I2C_1_UART_RTS_ENABLE            (0u)
#define I2C_1_UART_RTS_POLARITY          (0u)
#define I2C_1_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define I2C_1_SPI_SLAVE  (0u)
#define I2C_1_SPI_MASTER (1u)

/* UART direction enum */
#define I2C_1_UART_RX    (1u)
#define I2C_1_UART_TX    (2u)
#define I2C_1_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define I2C_1_SPI_SLAVE_CONST        (1u)
    #define I2C_1_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define I2C_1_RX_DIRECTION           (1u)
    #define I2C_1_TX_DIRECTION           (1u)
    #define I2C_1_UART_RX_DIRECTION      (1u)
    #define I2C_1_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define I2C_1_INTERNAL_RX_SW_BUFFER   (0u)
    #define I2C_1_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define I2C_1_INTERNAL_RX_BUFFER_SIZE    (I2C_1_rxBufferSize + 1u)
    #define I2C_1_RX_BUFFER_SIZE             (I2C_1_rxBufferSize)
    #define I2C_1_TX_BUFFER_SIZE             (I2C_1_txBufferSize)

    /* Return true if buffer is provided */
    #define I2C_1_CHECK_RX_SW_BUFFER (NULL != I2C_1_rxBuffer)
    #define I2C_1_CHECK_TX_SW_BUFFER (NULL != I2C_1_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define I2C_1_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define I2C_1_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define I2C_1_SPI_WAKE_ENABLE_CONST  (1u)
    #define I2C_1_CHECK_SPI_WAKE_ENABLE  (0u != I2C_1_scbEnableWake)
    #define I2C_1_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        #define I2C_1_SPI_UART_FIFO_SIZE             (I2C_1_FIFO_SIZE)
        #define I2C_1_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define I2C_1_SPI_UART_FIFO_SIZE (I2C_1_GET_FIFO_SIZE(I2C_1_CTRL_REG & \
                                                                                    I2C_1_CTRL_BYTE_MODE))

        #define I2C_1_CHECK_UART_RTS_CONTROL_FLOW \
                    ((I2C_1_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != I2C_1_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(I2C_1_UART_FLOW_CTRL_REG)))
    #endif /* (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (I2C_1_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define I2C_1_SPI_RX_DIRECTION (1u)
        #define I2C_1_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
            #define I2C_1_SPI_UART_FIFO_SIZE    (I2C_1_FIFO_SIZE)
        #else
            #define I2C_1_SPI_UART_FIFO_SIZE \
                                           I2C_1_GET_FIFO_SIZE(I2C_1_SPI_BYTE_MODE_ENABLE)

        #endif /* (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define I2C_1_INTERNAL_SPI_RX_SW_BUFFER  (I2C_1_SPI_RX_BUFFER_SIZE > \
                                                                I2C_1_SPI_UART_FIFO_SIZE)
        #define I2C_1_INTERNAL_SPI_TX_SW_BUFFER  (I2C_1_SPI_TX_BUFFER_SIZE > \
                                                                I2C_1_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define I2C_1_INTERNAL_RX_SW_BUFFER  (I2C_1_INTERNAL_SPI_RX_SW_BUFFER)
        #define I2C_1_INTERNAL_TX_SW_BUFFER  (I2C_1_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define I2C_1_INTERNAL_RX_BUFFER_SIZE    (I2C_1_SPI_RX_BUFFER_SIZE + 1u)
        #define I2C_1_RX_BUFFER_SIZE             (I2C_1_SPI_RX_BUFFER_SIZE)
        #define I2C_1_TX_BUFFER_SIZE             (I2C_1_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define I2C_1_SPI_WAKE_ENABLE_CONST  (0u != I2C_1_SPI_WAKE_ENABLE)
        #define I2C_1_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define I2C_1_UART_RX_DIRECTION (0u != (I2C_1_UART_DIRECTION & I2C_1_UART_RX))
        #define I2C_1_UART_TX_DIRECTION (0u != (I2C_1_UART_DIRECTION & I2C_1_UART_TX))

        /* Get FIFO size */
        #if (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
            #define I2C_1_SPI_UART_FIFO_SIZE    (I2C_1_FIFO_SIZE)
        #else
            #define I2C_1_SPI_UART_FIFO_SIZE \
                                           I2C_1_GET_FIFO_SIZE(I2C_1_UART_BYTE_MODE_ENABLE)
        #endif /* (I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define I2C_1_INTERNAL_UART_RX_SW_BUFFER  (I2C_1_UART_RX_BUFFER_SIZE > \
                                                                I2C_1_SPI_UART_FIFO_SIZE)
        #define I2C_1_INTERNAL_UART_TX_SW_BUFFER  (I2C_1_UART_TX_BUFFER_SIZE > \
                                                                    I2C_1_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define I2C_1_INTERNAL_RX_SW_BUFFER  (I2C_1_INTERNAL_UART_RX_SW_BUFFER)
        #define I2C_1_INTERNAL_TX_SW_BUFFER  (I2C_1_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define I2C_1_INTERNAL_RX_BUFFER_SIZE    (I2C_1_UART_RX_BUFFER_SIZE + 1u)
        #define I2C_1_RX_BUFFER_SIZE             (I2C_1_UART_RX_BUFFER_SIZE)
        #define I2C_1_TX_BUFFER_SIZE             (I2C_1_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define I2C_1_SPI_WAKE_ENABLE_CONST  (0u)
        #define I2C_1_UART_WAKE_ENABLE_CONST (0u != I2C_1_UART_WAKE_ENABLE)

    #endif /* (I2C_1_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define I2C_1_SPI_SLAVE_CONST    (I2C_1_SPI_MODE == I2C_1_SPI_SLAVE)
    #define I2C_1_SPI_MASTER_CONST   (I2C_1_SPI_MODE == I2C_1_SPI_MASTER)

    /* Direction */
    #define I2C_1_RX_DIRECTION ((I2C_1_SCB_MODE_SPI_CONST_CFG) ? \
                                            (I2C_1_SPI_RX_DIRECTION) : (I2C_1_UART_RX_DIRECTION))

    #define I2C_1_TX_DIRECTION ((I2C_1_SCB_MODE_SPI_CONST_CFG) ? \
                                            (I2C_1_SPI_TX_DIRECTION) : (I2C_1_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define I2C_1_CHECK_RX_SW_BUFFER (I2C_1_INTERNAL_RX_SW_BUFFER)
    #define I2C_1_CHECK_TX_SW_BUFFER (I2C_1_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define I2C_1_INTERNAL_RX_SW_BUFFER_CONST    (I2C_1_INTERNAL_RX_SW_BUFFER)
    #define I2C_1_INTERNAL_TX_SW_BUFFER_CONST    (I2C_1_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define I2C_1_CHECK_SPI_WAKE_ENABLE  (I2C_1_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define I2C_1_CHECK_UART_RTS_CONTROL_FLOW    (I2C_1_SCB_MODE_UART_CONST_CFG && \
                                                             I2C_1_UART_RTS_ENABLE)

#endif /* End (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* I2C_1_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} I2C_1_SPI_INIT_STRUCT;

/* I2C_1_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} I2C_1_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    void I2C_1_SpiInit(const I2C_1_SPI_INIT_STRUCT *config);
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(I2C_1_SCB_MODE_SPI_INC)
    #define I2C_1_SpiIsBusBusy() ((uint32) (0u != (I2C_1_SPI_STATUS_REG & \
                                                              I2C_1_SPI_STATUS_BUS_BUSY)))

    #if (I2C_1_SPI_MASTER_CONST)
        void I2C_1_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(I2C_1_SPI_MASTER_CONST) */

    #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
        void I2C_1_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */
#endif /* (I2C_1_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    void I2C_1_UartInit(const I2C_1_UART_INIT_STRUCT *config);
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(I2C_1_SCB_MODE_UART_INC)
    void I2C_1_UartSetRxAddress(uint32 address);
    void I2C_1_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(I2C_1_UART_RX_DIRECTION)
        uint32 I2C_1_UartGetChar(void);
        uint32 I2C_1_UartGetByte(void);

        #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void I2C_1_UartSetRtsPolarity(uint32 polarity);
            void I2C_1_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */
    #endif /* (I2C_1_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(I2C_1_UART_TX_DIRECTION)
        #define I2C_1_UartPutChar(ch)    I2C_1_SpiUartWriteTxData((uint32)(ch))
        void I2C_1_UartPutString(const char8 string[]);
        void I2C_1_UartPutCRLF(uint32 txDataByte);

        #if !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void I2C_1_UartEnableCts(void);
            void I2C_1_UartDisableCts(void);
            void I2C_1_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(I2C_1_CY_SCBIP_V0 || I2C_1_CY_SCBIP_V1) */
    #endif /* (I2C_1_UART_TX_DIRECTION) */
#endif /* (I2C_1_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(I2C_1_RX_DIRECTION)
    uint32 I2C_1_SpiUartReadRxData(void);
    uint32 I2C_1_SpiUartGetRxBufferSize(void);
    void   I2C_1_SpiUartClearRxBuffer(void);
#endif /* (I2C_1_RX_DIRECTION) */

/* Common APIs TX direction */
#if(I2C_1_TX_DIRECTION)
    void   I2C_1_SpiUartWriteTxData(uint32 txData);
    void   I2C_1_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 I2C_1_SpiUartGetTxBufferSize(void);
    void   I2C_1_SpiUartClearTxBuffer(void);
#endif /* (I2C_1_TX_DIRECTION) */

CY_ISR_PROTO(I2C_1_SPI_UART_ISR);

#if(I2C_1_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(I2C_1_UART_WAKEUP_ISR);
#endif /* (I2C_1_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   I2C_1_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 I2C_1_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   I2C_1_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 I2C_1_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(I2C_1_INTERNAL_RX_SW_BUFFER_CONST)
        #define I2C_1_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    I2C_1_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define I2C_1_GetWordFromRxBuffer(idx) I2C_1_rxBufferInternal[(idx)]

    #endif /* (I2C_1_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(I2C_1_INTERNAL_TX_SW_BUFFER_CONST)
        #define I2C_1_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        I2C_1_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define I2C_1_GetWordFromTxBuffer(idx) I2C_1_txBufferInternal[(idx)]

    #endif /* (I2C_1_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (I2C_1_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define I2C_1_SPI_MODE_MOTOROLA      (0x00u)
#define I2C_1_SPI_MODE_TI_COINCIDES  (0x01u)
#define I2C_1_SPI_MODE_TI_PRECEDES   (0x11u)
#define I2C_1_SPI_MODE_NATIONAL      (0x02u)
#define I2C_1_SPI_MODE_MASK          (0x03u)
#define I2C_1_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define I2C_1_SPI_MODE_NS_MICROWIRE  (I2C_1_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define I2C_1_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define I2C_1_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define I2C_1_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define I2C_1_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define I2C_1_BITS_ORDER_LSB_FIRST   (0u)
#define I2C_1_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define I2C_1_SPI_TRANSFER_SEPARATED     (0u)
#define I2C_1_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define I2C_1_SPI_SLAVE_SELECT0    (I2C_1_SCB__SS0_POSISTION)
#define I2C_1_SPI_SLAVE_SELECT1    (I2C_1_SCB__SS1_POSISTION)
#define I2C_1_SPI_SLAVE_SELECT2    (I2C_1_SCB__SS2_POSISTION)
#define I2C_1_SPI_SLAVE_SELECT3    (I2C_1_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define I2C_1_SPI_SS_ACTIVE_LOW  (0u)
#define I2C_1_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define I2C_1_UART_MODE_STD          (0u)
#define I2C_1_UART_MODE_SMARTCARD    (1u)
#define I2C_1_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define I2C_1_UART_RX    (1u)
#define I2C_1_UART_TX    (2u)
#define I2C_1_UART_TX_RX (3u)

/* UART parity enum */
#define I2C_1_UART_PARITY_EVEN   (0u)
#define I2C_1_UART_PARITY_ODD    (1u)
#define I2C_1_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define I2C_1_UART_STOP_BITS_1   (2u)
#define I2C_1_UART_STOP_BITS_1_5 (3u)
#define I2C_1_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define I2C_1_UART_IRDA_LP_OVS16     (16u)
#define I2C_1_UART_IRDA_LP_OVS32     (32u)
#define I2C_1_UART_IRDA_LP_OVS48     (48u)
#define I2C_1_UART_IRDA_LP_OVS96     (96u)
#define I2C_1_UART_IRDA_LP_OVS192    (192u)
#define I2C_1_UART_IRDA_LP_OVS768    (768u)
#define I2C_1_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define I2C_1_UART_MP_MARK       (0x100u)
#define I2C_1_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define I2C_1_UART_CTS_ACTIVE_LOW    (0u)
#define I2C_1_UART_CTS_ACTIVE_HIGH   (1u)
#define I2C_1_UART_RTS_ACTIVE_LOW    (0u)
#define I2C_1_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define I2C_1_INTR_RX_ERR        (I2C_1_INTR_RX_OVERFLOW    | \
                                             I2C_1_INTR_RX_UNDERFLOW   | \
                                             I2C_1_INTR_RX_FRAME_ERROR | \
                                             I2C_1_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for I2C_1_UartGetByte() */
#define I2C_1_UART_RX_OVERFLOW       (I2C_1_INTR_RX_OVERFLOW << 8u)
#define I2C_1_UART_RX_UNDERFLOW      (I2C_1_INTR_RX_UNDERFLOW << 8u)
#define I2C_1_UART_RX_FRAME_ERROR    (I2C_1_INTR_RX_FRAME_ERROR << 8u)
#define I2C_1_UART_RX_PARITY_ERROR   (I2C_1_INTR_RX_PARITY_ERROR << 8u)
#define I2C_1_UART_RX_ERROR_MASK     (I2C_1_UART_RX_OVERFLOW    | \
                                                 I2C_1_UART_RX_UNDERFLOW   | \
                                                 I2C_1_UART_RX_FRAME_ERROR | \
                                                 I2C_1_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(I2C_1_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const I2C_1_SPI_INIT_STRUCT  I2C_1_configSpi;
    extern const I2C_1_UART_INIT_STRUCT I2C_1_configUart;
#endif /* (I2C_1_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define I2C_1_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & I2C_1_INTR_SLAVE_SPI_BUS_ERROR)
#define I2C_1_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & I2C_1_INTR_MASTER_SPI_DONE)
#define I2C_1_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~I2C_1_INTR_SLAVE_SPI_BUS_ERROR)

#define I2C_1_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~I2C_1_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define I2C_1_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((I2C_1_UART_IRDA_LP_OVS16   == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS16 : \
         ((I2C_1_UART_IRDA_LP_OVS32   == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS32 : \
          ((I2C_1_UART_IRDA_LP_OVS48   == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS48 : \
           ((I2C_1_UART_IRDA_LP_OVS96   == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS96 : \
            ((I2C_1_UART_IRDA_LP_OVS192  == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS192 : \
             ((I2C_1_UART_IRDA_LP_OVS768  == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS768 : \
              ((I2C_1_UART_IRDA_LP_OVS1536 == (oversample)) ? I2C_1_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          I2C_1_CTRL_OVS_IRDA_LP_OVS16)))))))

#define I2C_1_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (I2C_1_UART_RX & (direction))) ? \
                                                                     (I2C_1_RX_CTRL_ENABLED) : (0u))

#define I2C_1_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (I2C_1_UART_TX & (direction))) ? \
                                                                     (I2C_1_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define I2C_1_CTRL_SPI      (I2C_1_CTRL_MODE_SPI)
#define I2C_1_SPI_RX_CTRL   (I2C_1_RX_CTRL_ENABLED)
#define I2C_1_SPI_TX_CTRL   (I2C_1_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define I2C_1_SPI_SS_POLARITY \
             (((uint32) I2C_1_SPI_SS0_POLARITY << I2C_1_SPI_SLAVE_SELECT0) | \
              ((uint32) I2C_1_SPI_SS1_POLARITY << I2C_1_SPI_SLAVE_SELECT1) | \
              ((uint32) I2C_1_SPI_SS2_POLARITY << I2C_1_SPI_SLAVE_SELECT2) | \
              ((uint32) I2C_1_SPI_SS3_POLARITY << I2C_1_SPI_SLAVE_SELECT3))

#if(I2C_1_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define I2C_1_SPI_DEFAULT_CTRL \
                    (I2C_1_GET_CTRL_OVS(I2C_1_SPI_OVS_FACTOR) | \
                     I2C_1_GET_CTRL_BYTE_MODE (I2C_1_SPI_BYTE_MODE_ENABLE) | \
                     I2C_1_GET_CTRL_EC_AM_MODE(I2C_1_SPI_WAKE_ENABLE)      | \
                     I2C_1_CTRL_SPI)

    #define I2C_1_SPI_DEFAULT_SPI_CTRL \
                    (I2C_1_GET_SPI_CTRL_CONTINUOUS    (I2C_1_SPI_TRANSFER_SEPARATION)       | \
                     I2C_1_GET_SPI_CTRL_SELECT_PRECEDE(I2C_1_SPI_SUB_MODE &                   \
                                                                  I2C_1_SPI_MODE_TI_PRECEDES_MASK)     | \
                     I2C_1_GET_SPI_CTRL_SCLK_MODE     (I2C_1_SPI_CLOCK_MODE)                | \
                     I2C_1_GET_SPI_CTRL_LATE_MISO_SAMPLE(I2C_1_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     I2C_1_GET_SPI_CTRL_SCLK_CONTINUOUS(I2C_1_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     I2C_1_GET_SPI_CTRL_SSEL_POLARITY (I2C_1_SPI_SS_POLARITY)               | \
                     I2C_1_GET_SPI_CTRL_SUB_MODE      (I2C_1_SPI_SUB_MODE)                  | \
                     I2C_1_GET_SPI_CTRL_MASTER_MODE   (I2C_1_SPI_MODE))

    /* RX direction */
    #define I2C_1_SPI_DEFAULT_RX_CTRL \
                    (I2C_1_GET_RX_CTRL_DATA_WIDTH(I2C_1_SPI_RX_DATA_BITS_NUM)     | \
                     I2C_1_GET_RX_CTRL_BIT_ORDER (I2C_1_SPI_BITS_ORDER)           | \
                     I2C_1_GET_RX_CTRL_MEDIAN    (I2C_1_SPI_MEDIAN_FILTER_ENABLE) | \
                     I2C_1_SPI_RX_CTRL)

    #define I2C_1_SPI_DEFAULT_RX_FIFO_CTRL \
                    I2C_1_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(I2C_1_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define I2C_1_SPI_DEFAULT_TX_CTRL \
                    (I2C_1_GET_TX_CTRL_DATA_WIDTH(I2C_1_SPI_TX_DATA_BITS_NUM) | \
                     I2C_1_GET_TX_CTRL_BIT_ORDER (I2C_1_SPI_BITS_ORDER)       | \
                     I2C_1_SPI_TX_CTRL)

    #define I2C_1_SPI_DEFAULT_TX_FIFO_CTRL \
                    I2C_1_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(I2C_1_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define I2C_1_SPI_DEFAULT_INTR_SPI_EC_MASK   (I2C_1_NO_INTR_SOURCES)

    #define I2C_1_SPI_DEFAULT_INTR_I2C_EC_MASK   (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (I2C_1_SPI_INTR_RX_MASK & I2C_1_INTR_SLAVE_SPI_BUS_ERROR)

    #define I2C_1_SPI_DEFAULT_INTR_MASTER_MASK \
                    (I2C_1_SPI_INTR_TX_MASK & I2C_1_INTR_MASTER_SPI_DONE)

    #define I2C_1_SPI_DEFAULT_INTR_RX_MASK \
                    (I2C_1_SPI_INTR_RX_MASK & (uint32) ~I2C_1_INTR_SLAVE_SPI_BUS_ERROR)

    #define I2C_1_SPI_DEFAULT_INTR_TX_MASK \
                    (I2C_1_SPI_INTR_TX_MASK & (uint32) ~I2C_1_INTR_MASTER_SPI_DONE)

#endif /* (I2C_1_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define I2C_1_CTRL_UART      (I2C_1_CTRL_MODE_UART)
#define I2C_1_UART_RX_CTRL   (I2C_1_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define I2C_1_UART_TX_CTRL   (I2C_1_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(I2C_1_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(I2C_1_UART_MODE_IRDA == I2C_1_UART_SUB_MODE)

        #define I2C_1_DEFAULT_CTRL_OVS   ((0u != I2C_1_UART_IRDA_LOW_POWER) ?              \
                                (I2C_1_UART_GET_CTRL_OVS_IRDA_LP(I2C_1_UART_OVS_FACTOR)) : \
                                (I2C_1_CTRL_OVS_IRDA_OVS16))

    #else

        #define I2C_1_DEFAULT_CTRL_OVS   I2C_1_GET_CTRL_OVS(I2C_1_UART_OVS_FACTOR)

    #endif /* (I2C_1_UART_MODE_IRDA == I2C_1_UART_SUB_MODE) */

    #define I2C_1_UART_DEFAULT_CTRL \
                                (I2C_1_GET_CTRL_BYTE_MODE  (I2C_1_UART_BYTE_MODE_ENABLE)  | \
                                 I2C_1_GET_CTRL_ADDR_ACCEPT(I2C_1_UART_MP_ACCEPT_ADDRESS) | \
                                 I2C_1_DEFAULT_CTRL_OVS                                              | \
                                 I2C_1_CTRL_UART)

    #define I2C_1_UART_DEFAULT_UART_CTRL \
                                    (I2C_1_GET_UART_CTRL_MODE(I2C_1_UART_SUB_MODE))

    /* RX direction */
    #define I2C_1_UART_DEFAULT_RX_CTRL_PARITY \
                                ((I2C_1_UART_PARITY_NONE != I2C_1_UART_PARITY_TYPE) ?      \
                                  (I2C_1_GET_UART_RX_CTRL_PARITY(I2C_1_UART_PARITY_TYPE) | \
                                   I2C_1_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define I2C_1_UART_DEFAULT_UART_RX_CTRL \
                    (I2C_1_GET_UART_RX_CTRL_MODE(I2C_1_UART_STOP_BITS_NUM)                    | \
                     I2C_1_GET_UART_RX_CTRL_POLARITY(I2C_1_UART_IRDA_POLARITY)                | \
                     I2C_1_GET_UART_RX_CTRL_MP_MODE(I2C_1_UART_MP_MODE_ENABLE)                | \
                     I2C_1_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(I2C_1_UART_DROP_ON_PARITY_ERR) | \
                     I2C_1_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(I2C_1_UART_DROP_ON_FRAME_ERR)   | \
                     I2C_1_UART_DEFAULT_RX_CTRL_PARITY)

    #define I2C_1_UART_DEFAULT_RX_CTRL \
                                (I2C_1_GET_RX_CTRL_DATA_WIDTH(I2C_1_UART_DATA_BITS_NUM)        | \
                                 I2C_1_GET_RX_CTRL_MEDIAN    (I2C_1_UART_MEDIAN_FILTER_ENABLE) | \
                                 I2C_1_GET_UART_RX_CTRL_ENABLED(I2C_1_UART_DIRECTION))

    #define I2C_1_UART_DEFAULT_RX_FIFO_CTRL \
                                I2C_1_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(I2C_1_UART_RX_TRIGGER_LEVEL)

    #define I2C_1_UART_DEFAULT_RX_MATCH_REG  ((0u != I2C_1_UART_MP_MODE_ENABLE) ?          \
                                (I2C_1_GET_RX_MATCH_ADDR(I2C_1_UART_MP_RX_ADDRESS) | \
                                 I2C_1_GET_RX_MATCH_MASK(I2C_1_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define I2C_1_UART_DEFAULT_TX_CTRL_PARITY (I2C_1_UART_DEFAULT_RX_CTRL_PARITY)

    #define I2C_1_UART_DEFAULT_UART_TX_CTRL \
                                (I2C_1_GET_UART_TX_CTRL_MODE(I2C_1_UART_STOP_BITS_NUM)       | \
                                 I2C_1_GET_UART_TX_CTRL_RETRY_NACK(I2C_1_UART_RETRY_ON_NACK) | \
                                 I2C_1_UART_DEFAULT_TX_CTRL_PARITY)

    #define I2C_1_UART_DEFAULT_TX_CTRL \
                                (I2C_1_GET_TX_CTRL_DATA_WIDTH(I2C_1_UART_DATA_BITS_NUM) | \
                                 I2C_1_GET_UART_TX_CTRL_ENABLED(I2C_1_UART_DIRECTION))

    #define I2C_1_UART_DEFAULT_TX_FIFO_CTRL \
                                I2C_1_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(I2C_1_UART_TX_TRIGGER_LEVEL)

    #define I2C_1_UART_DEFAULT_FLOW_CTRL \
                        (I2C_1_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(I2C_1_UART_RTS_FIFO_LEVEL) | \
                         I2C_1_GET_UART_FLOW_CTRL_RTS_POLARITY (I2C_1_UART_RTS_POLARITY)   | \
                         I2C_1_GET_UART_FLOW_CTRL_CTS_POLARITY (I2C_1_UART_CTS_POLARITY)   | \
                         I2C_1_GET_UART_FLOW_CTRL_CTS_ENABLE   (I2C_1_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define I2C_1_UART_DEFAULT_INTR_I2C_EC_MASK  (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_UART_DEFAULT_INTR_SPI_EC_MASK  (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_UART_DEFAULT_INTR_SLAVE_MASK   (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_UART_DEFAULT_INTR_MASTER_MASK  (I2C_1_NO_INTR_SOURCES)
    #define I2C_1_UART_DEFAULT_INTR_RX_MASK      (I2C_1_UART_INTR_RX_MASK)
    #define I2C_1_UART_DEFAULT_INTR_TX_MASK      (I2C_1_UART_INTR_TX_MASK)

#endif /* (I2C_1_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define I2C_1_SPIM_ACTIVE_SS0    (I2C_1_SPI_SLAVE_SELECT0)
#define I2C_1_SPIM_ACTIVE_SS1    (I2C_1_SPI_SLAVE_SELECT1)
#define I2C_1_SPIM_ACTIVE_SS2    (I2C_1_SPI_SLAVE_SELECT2)
#define I2C_1_SPIM_ACTIVE_SS3    (I2C_1_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_I2C_1_H */


/* [] END OF FILE */
