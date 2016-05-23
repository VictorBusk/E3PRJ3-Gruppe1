/*******************************************************************************
* File Name: SPIS_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_SPIS_H)
#define CY_SCB_SPI_UART_SPIS_H

#include "SPIS.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define SPIS_SPI_MODE                   (0u)
#define SPIS_SPI_SUB_MODE               (0u)
#define SPIS_SPI_CLOCK_MODE             (3u)
#define SPIS_SPI_OVS_FACTOR             (12u)
#define SPIS_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define SPIS_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define SPIS_SPI_RX_DATA_BITS_NUM       (16u)
#define SPIS_SPI_TX_DATA_BITS_NUM       (16u)
#define SPIS_SPI_WAKE_ENABLE            (0u)
#define SPIS_SPI_BITS_ORDER             (1u)
#define SPIS_SPI_TRANSFER_SEPARATION    (1u)
#define SPIS_SPI_NUMBER_OF_SS_LINES     (1u)
#define SPIS_SPI_RX_BUFFER_SIZE         (30u)
#define SPIS_SPI_TX_BUFFER_SIZE         (30u)

#define SPIS_SPI_INTERRUPT_MODE         (1u)

#define SPIS_SPI_INTR_RX_MASK           (12u)
#define SPIS_SPI_INTR_TX_MASK           (0u)

#define SPIS_SPI_RX_TRIGGER_LEVEL       (7u)
#define SPIS_SPI_TX_TRIGGER_LEVEL       (0u)

#define SPIS_SPI_BYTE_MODE_ENABLE       (0u)
#define SPIS_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define SPIS_SPI_SS0_POLARITY           (0u)
#define SPIS_SPI_SS1_POLARITY           (0u)
#define SPIS_SPI_SS2_POLARITY           (0u)
#define SPIS_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define SPIS_UART_SUB_MODE              (0u)
#define SPIS_UART_DIRECTION             (3u)
#define SPIS_UART_DATA_BITS_NUM         (8u)
#define SPIS_UART_PARITY_TYPE           (2u)
#define SPIS_UART_STOP_BITS_NUM         (2u)
#define SPIS_UART_OVS_FACTOR            (12u)
#define SPIS_UART_IRDA_LOW_POWER        (0u)
#define SPIS_UART_MEDIAN_FILTER_ENABLE  (0u)
#define SPIS_UART_RETRY_ON_NACK         (0u)
#define SPIS_UART_IRDA_POLARITY         (0u)
#define SPIS_UART_DROP_ON_FRAME_ERR     (0u)
#define SPIS_UART_DROP_ON_PARITY_ERR    (0u)
#define SPIS_UART_WAKE_ENABLE           (0u)
#define SPIS_UART_RX_BUFFER_SIZE        (8u)
#define SPIS_UART_TX_BUFFER_SIZE        (8u)
#define SPIS_UART_MP_MODE_ENABLE        (0u)
#define SPIS_UART_MP_ACCEPT_ADDRESS     (0u)
#define SPIS_UART_MP_RX_ADDRESS         (2u)
#define SPIS_UART_MP_RX_ADDRESS_MASK    (255u)

#define SPIS_UART_INTERRUPT_MODE        (0u)

#define SPIS_UART_INTR_RX_MASK          (0u)
#define SPIS_UART_INTR_TX_MASK          (0u)

#define SPIS_UART_RX_TRIGGER_LEVEL      (7u)
#define SPIS_UART_TX_TRIGGER_LEVEL      (0u)

#define SPIS_UART_BYTE_MODE_ENABLE      (0u)
#define SPIS_UART_CTS_ENABLE            (0u)
#define SPIS_UART_CTS_POLARITY          (0u)
#define SPIS_UART_RTS_ENABLE            (0u)
#define SPIS_UART_RTS_POLARITY          (0u)
#define SPIS_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define SPIS_SPI_SLAVE  (0u)
#define SPIS_SPI_MASTER (1u)

/* UART direction enum */
#define SPIS_UART_RX    (1u)
#define SPIS_UART_TX    (2u)
#define SPIS_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define SPIS_SPI_SLAVE_CONST        (1u)
    #define SPIS_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define SPIS_RX_DIRECTION           (1u)
    #define SPIS_TX_DIRECTION           (1u)
    #define SPIS_UART_RX_DIRECTION      (1u)
    #define SPIS_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define SPIS_INTERNAL_RX_SW_BUFFER   (0u)
    #define SPIS_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define SPIS_INTERNAL_RX_BUFFER_SIZE    (SPIS_rxBufferSize + 1u)
    #define SPIS_RX_BUFFER_SIZE             (SPIS_rxBufferSize)
    #define SPIS_TX_BUFFER_SIZE             (SPIS_txBufferSize)

    /* Return true if buffer is provided */
    #define SPIS_CHECK_RX_SW_BUFFER (NULL != SPIS_rxBuffer)
    #define SPIS_CHECK_TX_SW_BUFFER (NULL != SPIS_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define SPIS_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define SPIS_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define SPIS_SPI_WAKE_ENABLE_CONST  (1u)
    #define SPIS_CHECK_SPI_WAKE_ENABLE  (0u != SPIS_scbEnableWake)
    #define SPIS_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
        #define SPIS_SPI_UART_FIFO_SIZE             (SPIS_FIFO_SIZE)
        #define SPIS_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define SPIS_SPI_UART_FIFO_SIZE (SPIS_GET_FIFO_SIZE(SPIS_CTRL_REG & \
                                                                                    SPIS_CTRL_BYTE_MODE))

        #define SPIS_CHECK_UART_RTS_CONTROL_FLOW \
                    ((SPIS_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != SPIS_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SPIS_UART_FLOW_CTRL_REG)))
    #endif /* (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (SPIS_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define SPIS_SPI_RX_DIRECTION (1u)
        #define SPIS_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
            #define SPIS_SPI_UART_FIFO_SIZE    (SPIS_FIFO_SIZE)
        #else
            #define SPIS_SPI_UART_FIFO_SIZE \
                                           SPIS_GET_FIFO_SIZE(SPIS_SPI_BYTE_MODE_ENABLE)

        #endif /* (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define SPIS_INTERNAL_SPI_RX_SW_BUFFER  (SPIS_SPI_RX_BUFFER_SIZE > \
                                                                SPIS_SPI_UART_FIFO_SIZE)
        #define SPIS_INTERNAL_SPI_TX_SW_BUFFER  (SPIS_SPI_TX_BUFFER_SIZE > \
                                                                SPIS_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define SPIS_INTERNAL_RX_SW_BUFFER  (SPIS_INTERNAL_SPI_RX_SW_BUFFER)
        #define SPIS_INTERNAL_TX_SW_BUFFER  (SPIS_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define SPIS_INTERNAL_RX_BUFFER_SIZE    (SPIS_SPI_RX_BUFFER_SIZE + 1u)
        #define SPIS_RX_BUFFER_SIZE             (SPIS_SPI_RX_BUFFER_SIZE)
        #define SPIS_TX_BUFFER_SIZE             (SPIS_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SPIS_SPI_WAKE_ENABLE_CONST  (0u != SPIS_SPI_WAKE_ENABLE)
        #define SPIS_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define SPIS_UART_RX_DIRECTION (0u != (SPIS_UART_DIRECTION & SPIS_UART_RX))
        #define SPIS_UART_TX_DIRECTION (0u != (SPIS_UART_DIRECTION & SPIS_UART_TX))

        /* Get FIFO size */
        #if (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
            #define SPIS_SPI_UART_FIFO_SIZE    (SPIS_FIFO_SIZE)
        #else
            #define SPIS_SPI_UART_FIFO_SIZE \
                                           SPIS_GET_FIFO_SIZE(SPIS_UART_BYTE_MODE_ENABLE)
        #endif /* (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define SPIS_INTERNAL_UART_RX_SW_BUFFER  (SPIS_UART_RX_BUFFER_SIZE > \
                                                                SPIS_SPI_UART_FIFO_SIZE)
        #define SPIS_INTERNAL_UART_TX_SW_BUFFER  (SPIS_UART_TX_BUFFER_SIZE > \
                                                                    SPIS_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define SPIS_INTERNAL_RX_SW_BUFFER  (SPIS_INTERNAL_UART_RX_SW_BUFFER)
        #define SPIS_INTERNAL_TX_SW_BUFFER  (SPIS_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define SPIS_INTERNAL_RX_BUFFER_SIZE    (SPIS_UART_RX_BUFFER_SIZE + 1u)
        #define SPIS_RX_BUFFER_SIZE             (SPIS_UART_RX_BUFFER_SIZE)
        #define SPIS_TX_BUFFER_SIZE             (SPIS_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SPIS_SPI_WAKE_ENABLE_CONST  (0u)
        #define SPIS_UART_WAKE_ENABLE_CONST (0u != SPIS_UART_WAKE_ENABLE)

    #endif /* (SPIS_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define SPIS_SPI_SLAVE_CONST    (SPIS_SPI_MODE == SPIS_SPI_SLAVE)
    #define SPIS_SPI_MASTER_CONST   (SPIS_SPI_MODE == SPIS_SPI_MASTER)

    /* Direction */
    #define SPIS_RX_DIRECTION ((SPIS_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPIS_SPI_RX_DIRECTION) : (SPIS_UART_RX_DIRECTION))

    #define SPIS_TX_DIRECTION ((SPIS_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPIS_SPI_TX_DIRECTION) : (SPIS_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define SPIS_CHECK_RX_SW_BUFFER (SPIS_INTERNAL_RX_SW_BUFFER)
    #define SPIS_CHECK_TX_SW_BUFFER (SPIS_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define SPIS_INTERNAL_RX_SW_BUFFER_CONST    (SPIS_INTERNAL_RX_SW_BUFFER)
    #define SPIS_INTERNAL_TX_SW_BUFFER_CONST    (SPIS_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define SPIS_CHECK_SPI_WAKE_ENABLE  (SPIS_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define SPIS_CHECK_UART_RTS_CONTROL_FLOW    (SPIS_SCB_MODE_UART_CONST_CFG && \
                                                             SPIS_UART_RTS_ENABLE)

#endif /* End (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* SPIS_SPI_INIT_STRUCT */
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
} SPIS_SPI_INIT_STRUCT;

/* SPIS_UART_INIT_STRUCT */
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
} SPIS_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPIS_SpiInit(const SPIS_SPI_INIT_STRUCT *config);
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPIS_SCB_MODE_SPI_INC)
    #define SPIS_SpiIsBusBusy() ((uint32) (0u != (SPIS_SPI_STATUS_REG & \
                                                              SPIS_SPI_STATUS_BUS_BUSY)))

    #if (SPIS_SPI_MASTER_CONST)
        void SPIS_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(SPIS_SPI_MASTER_CONST) */

    #if !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
        void SPIS_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */
#endif /* (SPIS_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPIS_UartInit(const SPIS_UART_INIT_STRUCT *config);
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPIS_SCB_MODE_UART_INC)
    void SPIS_UartSetRxAddress(uint32 address);
    void SPIS_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(SPIS_UART_RX_DIRECTION)
        uint32 SPIS_UartGetChar(void);
        uint32 SPIS_UartGetByte(void);

        #if !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SPIS_UartSetRtsPolarity(uint32 polarity);
            void SPIS_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */
    #endif /* (SPIS_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(SPIS_UART_TX_DIRECTION)
        #define SPIS_UartPutChar(ch)    SPIS_SpiUartWriteTxData((uint32)(ch))
        void SPIS_UartPutString(const char8 string[]);
        void SPIS_UartPutCRLF(uint32 txDataByte);

        #if !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SPIS_UartEnableCts(void);
            void SPIS_UartDisableCts(void);
            void SPIS_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */
    #endif /* (SPIS_UART_TX_DIRECTION) */
#endif /* (SPIS_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(SPIS_RX_DIRECTION)
    uint32 SPIS_SpiUartReadRxData(void);
    uint32 SPIS_SpiUartGetRxBufferSize(void);
    void   SPIS_SpiUartClearRxBuffer(void);
#endif /* (SPIS_RX_DIRECTION) */

/* Common APIs TX direction */
#if(SPIS_TX_DIRECTION)
    void   SPIS_SpiUartWriteTxData(uint32 txData);
    void   SPIS_SpiUartPutArray(const uint16 wrBuf[], uint32 count);
    uint32 SPIS_SpiUartGetTxBufferSize(void);
    void   SPIS_SpiUartClearTxBuffer(void);
#endif /* (SPIS_TX_DIRECTION) */

CY_ISR_PROTO(SPIS_SPI_UART_ISR);

#if(SPIS_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(SPIS_UART_WAKEUP_ISR);
#endif /* (SPIS_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   SPIS_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 SPIS_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   SPIS_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 SPIS_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(SPIS_INTERNAL_RX_SW_BUFFER_CONST)
        #define SPIS_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    SPIS_rxBufferInternal[(idx)] = ((uint16) (rxDataByte)); \
                }while(0)

        #define SPIS_GetWordFromRxBuffer(idx) SPIS_rxBufferInternal[(idx)]

    #endif /* (SPIS_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(SPIS_INTERNAL_TX_SW_BUFFER_CONST)
        #define SPIS_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        SPIS_txBufferInternal[(idx)] = ((uint16) (txDataByte)); \
                    }while(0)

        #define SPIS_GetWordFromTxBuffer(idx) SPIS_txBufferInternal[(idx)]

    #endif /* (SPIS_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (SPIS_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define SPIS_SPI_MODE_MOTOROLA      (0x00u)
#define SPIS_SPI_MODE_TI_COINCIDES  (0x01u)
#define SPIS_SPI_MODE_TI_PRECEDES   (0x11u)
#define SPIS_SPI_MODE_NATIONAL      (0x02u)
#define SPIS_SPI_MODE_MASK          (0x03u)
#define SPIS_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define SPIS_SPI_MODE_NS_MICROWIRE  (SPIS_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define SPIS_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define SPIS_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define SPIS_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define SPIS_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define SPIS_BITS_ORDER_LSB_FIRST   (0u)
#define SPIS_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define SPIS_SPI_TRANSFER_SEPARATED     (0u)
#define SPIS_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define SPIS_SPI_SLAVE_SELECT0    (SPIS_SCB__SS0_POSISTION)
#define SPIS_SPI_SLAVE_SELECT1    (SPIS_SCB__SS1_POSISTION)
#define SPIS_SPI_SLAVE_SELECT2    (SPIS_SCB__SS2_POSISTION)
#define SPIS_SPI_SLAVE_SELECT3    (SPIS_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define SPIS_SPI_SS_ACTIVE_LOW  (0u)
#define SPIS_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define SPIS_UART_MODE_STD          (0u)
#define SPIS_UART_MODE_SMARTCARD    (1u)
#define SPIS_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define SPIS_UART_RX    (1u)
#define SPIS_UART_TX    (2u)
#define SPIS_UART_TX_RX (3u)

/* UART parity enum */
#define SPIS_UART_PARITY_EVEN   (0u)
#define SPIS_UART_PARITY_ODD    (1u)
#define SPIS_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define SPIS_UART_STOP_BITS_1   (2u)
#define SPIS_UART_STOP_BITS_1_5 (3u)
#define SPIS_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define SPIS_UART_IRDA_LP_OVS16     (16u)
#define SPIS_UART_IRDA_LP_OVS32     (32u)
#define SPIS_UART_IRDA_LP_OVS48     (48u)
#define SPIS_UART_IRDA_LP_OVS96     (96u)
#define SPIS_UART_IRDA_LP_OVS192    (192u)
#define SPIS_UART_IRDA_LP_OVS768    (768u)
#define SPIS_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define SPIS_UART_MP_MARK       (0x100u)
#define SPIS_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define SPIS_UART_CTS_ACTIVE_LOW    (0u)
#define SPIS_UART_CTS_ACTIVE_HIGH   (1u)
#define SPIS_UART_RTS_ACTIVE_LOW    (0u)
#define SPIS_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define SPIS_INTR_RX_ERR        (SPIS_INTR_RX_OVERFLOW    | \
                                             SPIS_INTR_RX_UNDERFLOW   | \
                                             SPIS_INTR_RX_FRAME_ERROR | \
                                             SPIS_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for SPIS_UartGetByte() */
#define SPIS_UART_RX_OVERFLOW       (SPIS_INTR_RX_OVERFLOW << 8u)
#define SPIS_UART_RX_UNDERFLOW      (SPIS_INTR_RX_UNDERFLOW << 8u)
#define SPIS_UART_RX_FRAME_ERROR    (SPIS_INTR_RX_FRAME_ERROR << 8u)
#define SPIS_UART_RX_PARITY_ERROR   (SPIS_INTR_RX_PARITY_ERROR << 8u)
#define SPIS_UART_RX_ERROR_MASK     (SPIS_UART_RX_OVERFLOW    | \
                                                 SPIS_UART_RX_UNDERFLOW   | \
                                                 SPIS_UART_RX_FRAME_ERROR | \
                                                 SPIS_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const SPIS_SPI_INIT_STRUCT  SPIS_configSpi;
    extern const SPIS_UART_INIT_STRUCT SPIS_configUart;
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define SPIS_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & SPIS_INTR_SLAVE_SPI_BUS_ERROR)
#define SPIS_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & SPIS_INTR_MASTER_SPI_DONE)
#define SPIS_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPIS_INTR_SLAVE_SPI_BUS_ERROR)

#define SPIS_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPIS_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define SPIS_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((SPIS_UART_IRDA_LP_OVS16   == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS16 : \
         ((SPIS_UART_IRDA_LP_OVS32   == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS32 : \
          ((SPIS_UART_IRDA_LP_OVS48   == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS48 : \
           ((SPIS_UART_IRDA_LP_OVS96   == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS96 : \
            ((SPIS_UART_IRDA_LP_OVS192  == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS192 : \
             ((SPIS_UART_IRDA_LP_OVS768  == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS768 : \
              ((SPIS_UART_IRDA_LP_OVS1536 == (oversample)) ? SPIS_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          SPIS_CTRL_OVS_IRDA_LP_OVS16)))))))

#define SPIS_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (SPIS_UART_RX & (direction))) ? \
                                                                     (SPIS_RX_CTRL_ENABLED) : (0u))

#define SPIS_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (SPIS_UART_TX & (direction))) ? \
                                                                     (SPIS_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define SPIS_CTRL_SPI      (SPIS_CTRL_MODE_SPI)
#define SPIS_SPI_RX_CTRL   (SPIS_RX_CTRL_ENABLED)
#define SPIS_SPI_TX_CTRL   (SPIS_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define SPIS_SPI_SS_POLARITY \
             (((uint32) SPIS_SPI_SS0_POLARITY << SPIS_SPI_SLAVE_SELECT0) | \
              ((uint32) SPIS_SPI_SS1_POLARITY << SPIS_SPI_SLAVE_SELECT1) | \
              ((uint32) SPIS_SPI_SS2_POLARITY << SPIS_SPI_SLAVE_SELECT2) | \
              ((uint32) SPIS_SPI_SS3_POLARITY << SPIS_SPI_SLAVE_SELECT3))

#if(SPIS_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define SPIS_SPI_DEFAULT_CTRL \
                    (SPIS_GET_CTRL_OVS(SPIS_SPI_OVS_FACTOR) | \
                     SPIS_GET_CTRL_BYTE_MODE (SPIS_SPI_BYTE_MODE_ENABLE) | \
                     SPIS_GET_CTRL_EC_AM_MODE(SPIS_SPI_WAKE_ENABLE)      | \
                     SPIS_CTRL_SPI)

    #define SPIS_SPI_DEFAULT_SPI_CTRL \
                    (SPIS_GET_SPI_CTRL_CONTINUOUS    (SPIS_SPI_TRANSFER_SEPARATION)       | \
                     SPIS_GET_SPI_CTRL_SELECT_PRECEDE(SPIS_SPI_SUB_MODE &                   \
                                                                  SPIS_SPI_MODE_TI_PRECEDES_MASK)     | \
                     SPIS_GET_SPI_CTRL_SCLK_MODE     (SPIS_SPI_CLOCK_MODE)                | \
                     SPIS_GET_SPI_CTRL_LATE_MISO_SAMPLE(SPIS_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     SPIS_GET_SPI_CTRL_SCLK_CONTINUOUS(SPIS_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     SPIS_GET_SPI_CTRL_SSEL_POLARITY (SPIS_SPI_SS_POLARITY)               | \
                     SPIS_GET_SPI_CTRL_SUB_MODE      (SPIS_SPI_SUB_MODE)                  | \
                     SPIS_GET_SPI_CTRL_MASTER_MODE   (SPIS_SPI_MODE))

    /* RX direction */
    #define SPIS_SPI_DEFAULT_RX_CTRL \
                    (SPIS_GET_RX_CTRL_DATA_WIDTH(SPIS_SPI_RX_DATA_BITS_NUM)     | \
                     SPIS_GET_RX_CTRL_BIT_ORDER (SPIS_SPI_BITS_ORDER)           | \
                     SPIS_GET_RX_CTRL_MEDIAN    (SPIS_SPI_MEDIAN_FILTER_ENABLE) | \
                     SPIS_SPI_RX_CTRL)

    #define SPIS_SPI_DEFAULT_RX_FIFO_CTRL \
                    SPIS_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPIS_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define SPIS_SPI_DEFAULT_TX_CTRL \
                    (SPIS_GET_TX_CTRL_DATA_WIDTH(SPIS_SPI_TX_DATA_BITS_NUM) | \
                     SPIS_GET_TX_CTRL_BIT_ORDER (SPIS_SPI_BITS_ORDER)       | \
                     SPIS_SPI_TX_CTRL)

    #define SPIS_SPI_DEFAULT_TX_FIFO_CTRL \
                    SPIS_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPIS_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SPIS_SPI_DEFAULT_INTR_SPI_EC_MASK   (SPIS_NO_INTR_SOURCES)

    #define SPIS_SPI_DEFAULT_INTR_I2C_EC_MASK   (SPIS_NO_INTR_SOURCES)
    #define SPIS_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (SPIS_SPI_INTR_RX_MASK & SPIS_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPIS_SPI_DEFAULT_INTR_MASTER_MASK \
                    (SPIS_SPI_INTR_TX_MASK & SPIS_INTR_MASTER_SPI_DONE)

    #define SPIS_SPI_DEFAULT_INTR_RX_MASK \
                    (SPIS_SPI_INTR_RX_MASK & (uint32) ~SPIS_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPIS_SPI_DEFAULT_INTR_TX_MASK \
                    (SPIS_SPI_INTR_TX_MASK & (uint32) ~SPIS_INTR_MASTER_SPI_DONE)

#endif /* (SPIS_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define SPIS_CTRL_UART      (SPIS_CTRL_MODE_UART)
#define SPIS_UART_RX_CTRL   (SPIS_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define SPIS_UART_TX_CTRL   (SPIS_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(SPIS_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(SPIS_UART_MODE_IRDA == SPIS_UART_SUB_MODE)

        #define SPIS_DEFAULT_CTRL_OVS   ((0u != SPIS_UART_IRDA_LOW_POWER) ?              \
                                (SPIS_UART_GET_CTRL_OVS_IRDA_LP(SPIS_UART_OVS_FACTOR)) : \
                                (SPIS_CTRL_OVS_IRDA_OVS16))

    #else

        #define SPIS_DEFAULT_CTRL_OVS   SPIS_GET_CTRL_OVS(SPIS_UART_OVS_FACTOR)

    #endif /* (SPIS_UART_MODE_IRDA == SPIS_UART_SUB_MODE) */

    #define SPIS_UART_DEFAULT_CTRL \
                                (SPIS_GET_CTRL_BYTE_MODE  (SPIS_UART_BYTE_MODE_ENABLE)  | \
                                 SPIS_GET_CTRL_ADDR_ACCEPT(SPIS_UART_MP_ACCEPT_ADDRESS) | \
                                 SPIS_DEFAULT_CTRL_OVS                                              | \
                                 SPIS_CTRL_UART)

    #define SPIS_UART_DEFAULT_UART_CTRL \
                                    (SPIS_GET_UART_CTRL_MODE(SPIS_UART_SUB_MODE))

    /* RX direction */
    #define SPIS_UART_DEFAULT_RX_CTRL_PARITY \
                                ((SPIS_UART_PARITY_NONE != SPIS_UART_PARITY_TYPE) ?      \
                                  (SPIS_GET_UART_RX_CTRL_PARITY(SPIS_UART_PARITY_TYPE) | \
                                   SPIS_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define SPIS_UART_DEFAULT_UART_RX_CTRL \
                    (SPIS_GET_UART_RX_CTRL_MODE(SPIS_UART_STOP_BITS_NUM)                    | \
                     SPIS_GET_UART_RX_CTRL_POLARITY(SPIS_UART_IRDA_POLARITY)                | \
                     SPIS_GET_UART_RX_CTRL_MP_MODE(SPIS_UART_MP_MODE_ENABLE)                | \
                     SPIS_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(SPIS_UART_DROP_ON_PARITY_ERR) | \
                     SPIS_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(SPIS_UART_DROP_ON_FRAME_ERR)   | \
                     SPIS_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPIS_UART_DEFAULT_RX_CTRL \
                                (SPIS_GET_RX_CTRL_DATA_WIDTH(SPIS_UART_DATA_BITS_NUM)        | \
                                 SPIS_GET_RX_CTRL_MEDIAN    (SPIS_UART_MEDIAN_FILTER_ENABLE) | \
                                 SPIS_GET_UART_RX_CTRL_ENABLED(SPIS_UART_DIRECTION))

    #define SPIS_UART_DEFAULT_RX_FIFO_CTRL \
                                SPIS_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPIS_UART_RX_TRIGGER_LEVEL)

    #define SPIS_UART_DEFAULT_RX_MATCH_REG  ((0u != SPIS_UART_MP_MODE_ENABLE) ?          \
                                (SPIS_GET_RX_MATCH_ADDR(SPIS_UART_MP_RX_ADDRESS) | \
                                 SPIS_GET_RX_MATCH_MASK(SPIS_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define SPIS_UART_DEFAULT_TX_CTRL_PARITY (SPIS_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPIS_UART_DEFAULT_UART_TX_CTRL \
                                (SPIS_GET_UART_TX_CTRL_MODE(SPIS_UART_STOP_BITS_NUM)       | \
                                 SPIS_GET_UART_TX_CTRL_RETRY_NACK(SPIS_UART_RETRY_ON_NACK) | \
                                 SPIS_UART_DEFAULT_TX_CTRL_PARITY)

    #define SPIS_UART_DEFAULT_TX_CTRL \
                                (SPIS_GET_TX_CTRL_DATA_WIDTH(SPIS_UART_DATA_BITS_NUM) | \
                                 SPIS_GET_UART_TX_CTRL_ENABLED(SPIS_UART_DIRECTION))

    #define SPIS_UART_DEFAULT_TX_FIFO_CTRL \
                                SPIS_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPIS_UART_TX_TRIGGER_LEVEL)

    #define SPIS_UART_DEFAULT_FLOW_CTRL \
                        (SPIS_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SPIS_UART_RTS_FIFO_LEVEL) | \
                         SPIS_GET_UART_FLOW_CTRL_RTS_POLARITY (SPIS_UART_RTS_POLARITY)   | \
                         SPIS_GET_UART_FLOW_CTRL_CTS_POLARITY (SPIS_UART_CTS_POLARITY)   | \
                         SPIS_GET_UART_FLOW_CTRL_CTS_ENABLE   (SPIS_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define SPIS_UART_DEFAULT_INTR_I2C_EC_MASK  (SPIS_NO_INTR_SOURCES)
    #define SPIS_UART_DEFAULT_INTR_SPI_EC_MASK  (SPIS_NO_INTR_SOURCES)
    #define SPIS_UART_DEFAULT_INTR_SLAVE_MASK   (SPIS_NO_INTR_SOURCES)
    #define SPIS_UART_DEFAULT_INTR_MASTER_MASK  (SPIS_NO_INTR_SOURCES)
    #define SPIS_UART_DEFAULT_INTR_RX_MASK      (SPIS_UART_INTR_RX_MASK)
    #define SPIS_UART_DEFAULT_INTR_TX_MASK      (SPIS_UART_INTR_TX_MASK)

#endif /* (SPIS_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define SPIS_SPIM_ACTIVE_SS0    (SPIS_SPI_SLAVE_SELECT0)
#define SPIS_SPIM_ACTIVE_SS1    (SPIS_SPI_SLAVE_SELECT1)
#define SPIS_SPIM_ACTIVE_SS2    (SPIS_SPI_SLAVE_SELECT2)
#define SPIS_SPIM_ACTIVE_SS3    (SPIS_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_SPIS_H */


/* [] END OF FILE */
