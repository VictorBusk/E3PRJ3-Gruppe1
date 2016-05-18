/*******************************************************************************
* File Name: SPIM_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_SPIM_H)
#define CY_SCB_SPI_UART_SPIM_H

#include "SPIM.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define SPIM_SPI_MODE                   (1u)
#define SPIM_SPI_SUB_MODE               (0u)
#define SPIM_SPI_CLOCK_MODE             (3u)
#define SPIM_SPI_OVS_FACTOR             (16u)
#define SPIM_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define SPIM_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define SPIM_SPI_RX_DATA_BITS_NUM       (16u)
#define SPIM_SPI_TX_DATA_BITS_NUM       (16u)
#define SPIM_SPI_WAKE_ENABLE            (0u)
#define SPIM_SPI_BITS_ORDER             (1u)
#define SPIM_SPI_TRANSFER_SEPARATION    (1u)
#define SPIM_SPI_NUMBER_OF_SS_LINES     (3u)
#define SPIM_SPI_RX_BUFFER_SIZE         (8u)
#define SPIM_SPI_TX_BUFFER_SIZE         (8u)

#define SPIM_SPI_INTERRUPT_MODE         (0u)

#define SPIM_SPI_INTR_RX_MASK           (0u)
#define SPIM_SPI_INTR_TX_MASK           (0u)

#define SPIM_SPI_RX_TRIGGER_LEVEL       (7u)
#define SPIM_SPI_TX_TRIGGER_LEVEL       (0u)

#define SPIM_SPI_BYTE_MODE_ENABLE       (0u)
#define SPIM_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define SPIM_SPI_SS0_POLARITY           (0u)
#define SPIM_SPI_SS1_POLARITY           (0u)
#define SPIM_SPI_SS2_POLARITY           (0u)
#define SPIM_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define SPIM_UART_SUB_MODE              (0u)
#define SPIM_UART_DIRECTION             (3u)
#define SPIM_UART_DATA_BITS_NUM         (8u)
#define SPIM_UART_PARITY_TYPE           (2u)
#define SPIM_UART_STOP_BITS_NUM         (2u)
#define SPIM_UART_OVS_FACTOR            (12u)
#define SPIM_UART_IRDA_LOW_POWER        (0u)
#define SPIM_UART_MEDIAN_FILTER_ENABLE  (0u)
#define SPIM_UART_RETRY_ON_NACK         (0u)
#define SPIM_UART_IRDA_POLARITY         (0u)
#define SPIM_UART_DROP_ON_FRAME_ERR     (0u)
#define SPIM_UART_DROP_ON_PARITY_ERR    (0u)
#define SPIM_UART_WAKE_ENABLE           (0u)
#define SPIM_UART_RX_BUFFER_SIZE        (8u)
#define SPIM_UART_TX_BUFFER_SIZE        (8u)
#define SPIM_UART_MP_MODE_ENABLE        (0u)
#define SPIM_UART_MP_ACCEPT_ADDRESS     (0u)
#define SPIM_UART_MP_RX_ADDRESS         (2u)
#define SPIM_UART_MP_RX_ADDRESS_MASK    (255u)

#define SPIM_UART_INTERRUPT_MODE        (0u)

#define SPIM_UART_INTR_RX_MASK          (0u)
#define SPIM_UART_INTR_TX_MASK          (0u)

#define SPIM_UART_RX_TRIGGER_LEVEL      (7u)
#define SPIM_UART_TX_TRIGGER_LEVEL      (0u)

#define SPIM_UART_BYTE_MODE_ENABLE      (0u)
#define SPIM_UART_CTS_ENABLE            (0u)
#define SPIM_UART_CTS_POLARITY          (0u)
#define SPIM_UART_RTS_ENABLE            (0u)
#define SPIM_UART_RTS_POLARITY          (0u)
#define SPIM_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define SPIM_SPI_SLAVE  (0u)
#define SPIM_SPI_MASTER (1u)

/* UART direction enum */
#define SPIM_UART_RX    (1u)
#define SPIM_UART_TX    (2u)
#define SPIM_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define SPIM_SPI_SLAVE_CONST        (1u)
    #define SPIM_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define SPIM_RX_DIRECTION           (1u)
    #define SPIM_TX_DIRECTION           (1u)
    #define SPIM_UART_RX_DIRECTION      (1u)
    #define SPIM_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define SPIM_INTERNAL_RX_SW_BUFFER   (0u)
    #define SPIM_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define SPIM_INTERNAL_RX_BUFFER_SIZE    (SPIM_rxBufferSize + 1u)
    #define SPIM_RX_BUFFER_SIZE             (SPIM_rxBufferSize)
    #define SPIM_TX_BUFFER_SIZE             (SPIM_txBufferSize)

    /* Return true if buffer is provided */
    #define SPIM_CHECK_RX_SW_BUFFER (NULL != SPIM_rxBuffer)
    #define SPIM_CHECK_TX_SW_BUFFER (NULL != SPIM_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define SPIM_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define SPIM_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define SPIM_SPI_WAKE_ENABLE_CONST  (1u)
    #define SPIM_CHECK_SPI_WAKE_ENABLE  (0u != SPIM_scbEnableWake)
    #define SPIM_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
        #define SPIM_SPI_UART_FIFO_SIZE             (SPIM_FIFO_SIZE)
        #define SPIM_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define SPIM_SPI_UART_FIFO_SIZE (SPIM_GET_FIFO_SIZE(SPIM_CTRL_REG & \
                                                                                    SPIM_CTRL_BYTE_MODE))

        #define SPIM_CHECK_UART_RTS_CONTROL_FLOW \
                    ((SPIM_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != SPIM_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SPIM_UART_FLOW_CTRL_REG)))
    #endif /* (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (SPIM_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define SPIM_SPI_RX_DIRECTION (1u)
        #define SPIM_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
            #define SPIM_SPI_UART_FIFO_SIZE    (SPIM_FIFO_SIZE)
        #else
            #define SPIM_SPI_UART_FIFO_SIZE \
                                           SPIM_GET_FIFO_SIZE(SPIM_SPI_BYTE_MODE_ENABLE)

        #endif /* (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define SPIM_INTERNAL_SPI_RX_SW_BUFFER  (SPIM_SPI_RX_BUFFER_SIZE > \
                                                                SPIM_SPI_UART_FIFO_SIZE)
        #define SPIM_INTERNAL_SPI_TX_SW_BUFFER  (SPIM_SPI_TX_BUFFER_SIZE > \
                                                                SPIM_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define SPIM_INTERNAL_RX_SW_BUFFER  (SPIM_INTERNAL_SPI_RX_SW_BUFFER)
        #define SPIM_INTERNAL_TX_SW_BUFFER  (SPIM_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define SPIM_INTERNAL_RX_BUFFER_SIZE    (SPIM_SPI_RX_BUFFER_SIZE + 1u)
        #define SPIM_RX_BUFFER_SIZE             (SPIM_SPI_RX_BUFFER_SIZE)
        #define SPIM_TX_BUFFER_SIZE             (SPIM_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SPIM_SPI_WAKE_ENABLE_CONST  (0u != SPIM_SPI_WAKE_ENABLE)
        #define SPIM_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define SPIM_UART_RX_DIRECTION (0u != (SPIM_UART_DIRECTION & SPIM_UART_RX))
        #define SPIM_UART_TX_DIRECTION (0u != (SPIM_UART_DIRECTION & SPIM_UART_TX))

        /* Get FIFO size */
        #if (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
            #define SPIM_SPI_UART_FIFO_SIZE    (SPIM_FIFO_SIZE)
        #else
            #define SPIM_SPI_UART_FIFO_SIZE \
                                           SPIM_GET_FIFO_SIZE(SPIM_UART_BYTE_MODE_ENABLE)
        #endif /* (SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define SPIM_INTERNAL_UART_RX_SW_BUFFER  (SPIM_UART_RX_BUFFER_SIZE > \
                                                                SPIM_SPI_UART_FIFO_SIZE)
        #define SPIM_INTERNAL_UART_TX_SW_BUFFER  (SPIM_UART_TX_BUFFER_SIZE > \
                                                                    SPIM_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define SPIM_INTERNAL_RX_SW_BUFFER  (SPIM_INTERNAL_UART_RX_SW_BUFFER)
        #define SPIM_INTERNAL_TX_SW_BUFFER  (SPIM_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define SPIM_INTERNAL_RX_BUFFER_SIZE    (SPIM_UART_RX_BUFFER_SIZE + 1u)
        #define SPIM_RX_BUFFER_SIZE             (SPIM_UART_RX_BUFFER_SIZE)
        #define SPIM_TX_BUFFER_SIZE             (SPIM_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define SPIM_SPI_WAKE_ENABLE_CONST  (0u)
        #define SPIM_UART_WAKE_ENABLE_CONST (0u != SPIM_UART_WAKE_ENABLE)

    #endif /* (SPIM_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define SPIM_SPI_SLAVE_CONST    (SPIM_SPI_MODE == SPIM_SPI_SLAVE)
    #define SPIM_SPI_MASTER_CONST   (SPIM_SPI_MODE == SPIM_SPI_MASTER)

    /* Direction */
    #define SPIM_RX_DIRECTION ((SPIM_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPIM_SPI_RX_DIRECTION) : (SPIM_UART_RX_DIRECTION))

    #define SPIM_TX_DIRECTION ((SPIM_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPIM_SPI_TX_DIRECTION) : (SPIM_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define SPIM_CHECK_RX_SW_BUFFER (SPIM_INTERNAL_RX_SW_BUFFER)
    #define SPIM_CHECK_TX_SW_BUFFER (SPIM_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define SPIM_INTERNAL_RX_SW_BUFFER_CONST    (SPIM_INTERNAL_RX_SW_BUFFER)
    #define SPIM_INTERNAL_TX_SW_BUFFER_CONST    (SPIM_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define SPIM_CHECK_SPI_WAKE_ENABLE  (SPIM_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define SPIM_CHECK_UART_RTS_CONTROL_FLOW    (SPIM_SCB_MODE_UART_CONST_CFG && \
                                                             SPIM_UART_RTS_ENABLE)

#endif /* End (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* SPIM_SPI_INIT_STRUCT */
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
} SPIM_SPI_INIT_STRUCT;

/* SPIM_UART_INIT_STRUCT */
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
} SPIM_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPIM_SpiInit(const SPIM_SPI_INIT_STRUCT *config);
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPIM_SCB_MODE_SPI_INC)
    #define SPIM_SpiIsBusBusy() ((uint32) (0u != (SPIM_SPI_STATUS_REG & \
                                                              SPIM_SPI_STATUS_BUS_BUSY)))

    #if (SPIM_SPI_MASTER_CONST)
        void SPIM_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(SPIM_SPI_MASTER_CONST) */

    #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
        void SPIM_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
#endif /* (SPIM_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPIM_UartInit(const SPIM_UART_INIT_STRUCT *config);
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPIM_SCB_MODE_UART_INC)
    void SPIM_UartSetRxAddress(uint32 address);
    void SPIM_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(SPIM_UART_RX_DIRECTION)
        uint32 SPIM_UartGetChar(void);
        uint32 SPIM_UartGetByte(void);

        #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SPIM_UartSetRtsPolarity(uint32 polarity);
            void SPIM_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
    #endif /* (SPIM_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(SPIM_UART_TX_DIRECTION)
        #define SPIM_UartPutChar(ch)    SPIM_SpiUartWriteTxData((uint32)(ch))
        void SPIM_UartPutString(const char8 string[]);
        void SPIM_UartPutCRLF(uint32 txDataByte);

        #if !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void SPIM_UartEnableCts(void);
            void SPIM_UartDisableCts(void);
            void SPIM_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(SPIM_CY_SCBIP_V0 || SPIM_CY_SCBIP_V1) */
    #endif /* (SPIM_UART_TX_DIRECTION) */
#endif /* (SPIM_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(SPIM_RX_DIRECTION)
    uint32 SPIM_SpiUartReadRxData(void);
    uint32 SPIM_SpiUartGetRxBufferSize(void);
    void   SPIM_SpiUartClearRxBuffer(void);
#endif /* (SPIM_RX_DIRECTION) */

/* Common APIs TX direction */
#if(SPIM_TX_DIRECTION)
    void   SPIM_SpiUartWriteTxData(uint32 txData);
    void   SPIM_SpiUartPutArray(const uint16 wrBuf[], uint32 count);
    uint32 SPIM_SpiUartGetTxBufferSize(void);
    void   SPIM_SpiUartClearTxBuffer(void);
#endif /* (SPIM_TX_DIRECTION) */

CY_ISR_PROTO(SPIM_SPI_UART_ISR);

#if(SPIM_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(SPIM_UART_WAKEUP_ISR);
#endif /* (SPIM_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   SPIM_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 SPIM_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   SPIM_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 SPIM_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(SPIM_INTERNAL_RX_SW_BUFFER_CONST)
        #define SPIM_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    SPIM_rxBufferInternal[(idx)] = ((uint16) (rxDataByte)); \
                }while(0)

        #define SPIM_GetWordFromRxBuffer(idx) SPIM_rxBufferInternal[(idx)]

    #endif /* (SPIM_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(SPIM_INTERNAL_TX_SW_BUFFER_CONST)
        #define SPIM_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        SPIM_txBufferInternal[(idx)] = ((uint16) (txDataByte)); \
                    }while(0)

        #define SPIM_GetWordFromTxBuffer(idx) SPIM_txBufferInternal[(idx)]

    #endif /* (SPIM_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (SPIM_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define SPIM_SPI_MODE_MOTOROLA      (0x00u)
#define SPIM_SPI_MODE_TI_COINCIDES  (0x01u)
#define SPIM_SPI_MODE_TI_PRECEDES   (0x11u)
#define SPIM_SPI_MODE_NATIONAL      (0x02u)
#define SPIM_SPI_MODE_MASK          (0x03u)
#define SPIM_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define SPIM_SPI_MODE_NS_MICROWIRE  (SPIM_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define SPIM_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define SPIM_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define SPIM_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define SPIM_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define SPIM_BITS_ORDER_LSB_FIRST   (0u)
#define SPIM_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define SPIM_SPI_TRANSFER_SEPARATED     (0u)
#define SPIM_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define SPIM_SPI_SLAVE_SELECT0    (SPIM_SCB__SS0_POSISTION)
#define SPIM_SPI_SLAVE_SELECT1    (SPIM_SCB__SS1_POSISTION)
#define SPIM_SPI_SLAVE_SELECT2    (SPIM_SCB__SS2_POSISTION)
#define SPIM_SPI_SLAVE_SELECT3    (SPIM_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define SPIM_SPI_SS_ACTIVE_LOW  (0u)
#define SPIM_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define SPIM_UART_MODE_STD          (0u)
#define SPIM_UART_MODE_SMARTCARD    (1u)
#define SPIM_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define SPIM_UART_RX    (1u)
#define SPIM_UART_TX    (2u)
#define SPIM_UART_TX_RX (3u)

/* UART parity enum */
#define SPIM_UART_PARITY_EVEN   (0u)
#define SPIM_UART_PARITY_ODD    (1u)
#define SPIM_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define SPIM_UART_STOP_BITS_1   (2u)
#define SPIM_UART_STOP_BITS_1_5 (3u)
#define SPIM_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define SPIM_UART_IRDA_LP_OVS16     (16u)
#define SPIM_UART_IRDA_LP_OVS32     (32u)
#define SPIM_UART_IRDA_LP_OVS48     (48u)
#define SPIM_UART_IRDA_LP_OVS96     (96u)
#define SPIM_UART_IRDA_LP_OVS192    (192u)
#define SPIM_UART_IRDA_LP_OVS768    (768u)
#define SPIM_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define SPIM_UART_MP_MARK       (0x100u)
#define SPIM_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define SPIM_UART_CTS_ACTIVE_LOW    (0u)
#define SPIM_UART_CTS_ACTIVE_HIGH   (1u)
#define SPIM_UART_RTS_ACTIVE_LOW    (0u)
#define SPIM_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define SPIM_INTR_RX_ERR        (SPIM_INTR_RX_OVERFLOW    | \
                                             SPIM_INTR_RX_UNDERFLOW   | \
                                             SPIM_INTR_RX_FRAME_ERROR | \
                                             SPIM_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for SPIM_UartGetByte() */
#define SPIM_UART_RX_OVERFLOW       (SPIM_INTR_RX_OVERFLOW << 8u)
#define SPIM_UART_RX_UNDERFLOW      (SPIM_INTR_RX_UNDERFLOW << 8u)
#define SPIM_UART_RX_FRAME_ERROR    (SPIM_INTR_RX_FRAME_ERROR << 8u)
#define SPIM_UART_RX_PARITY_ERROR   (SPIM_INTR_RX_PARITY_ERROR << 8u)
#define SPIM_UART_RX_ERROR_MASK     (SPIM_UART_RX_OVERFLOW    | \
                                                 SPIM_UART_RX_UNDERFLOW   | \
                                                 SPIM_UART_RX_FRAME_ERROR | \
                                                 SPIM_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const SPIM_SPI_INIT_STRUCT  SPIM_configSpi;
    extern const SPIM_UART_INIT_STRUCT SPIM_configUart;
#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define SPIM_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & SPIM_INTR_SLAVE_SPI_BUS_ERROR)
#define SPIM_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & SPIM_INTR_MASTER_SPI_DONE)
#define SPIM_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPIM_INTR_SLAVE_SPI_BUS_ERROR)

#define SPIM_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPIM_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define SPIM_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((SPIM_UART_IRDA_LP_OVS16   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS16 : \
         ((SPIM_UART_IRDA_LP_OVS32   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS32 : \
          ((SPIM_UART_IRDA_LP_OVS48   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS48 : \
           ((SPIM_UART_IRDA_LP_OVS96   == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS96 : \
            ((SPIM_UART_IRDA_LP_OVS192  == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS192 : \
             ((SPIM_UART_IRDA_LP_OVS768  == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS768 : \
              ((SPIM_UART_IRDA_LP_OVS1536 == (oversample)) ? SPIM_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          SPIM_CTRL_OVS_IRDA_LP_OVS16)))))))

#define SPIM_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (SPIM_UART_RX & (direction))) ? \
                                                                     (SPIM_RX_CTRL_ENABLED) : (0u))

#define SPIM_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (SPIM_UART_TX & (direction))) ? \
                                                                     (SPIM_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define SPIM_CTRL_SPI      (SPIM_CTRL_MODE_SPI)
#define SPIM_SPI_RX_CTRL   (SPIM_RX_CTRL_ENABLED)
#define SPIM_SPI_TX_CTRL   (SPIM_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define SPIM_SPI_SS_POLARITY \
             (((uint32) SPIM_SPI_SS0_POLARITY << SPIM_SPI_SLAVE_SELECT0) | \
              ((uint32) SPIM_SPI_SS1_POLARITY << SPIM_SPI_SLAVE_SELECT1) | \
              ((uint32) SPIM_SPI_SS2_POLARITY << SPIM_SPI_SLAVE_SELECT2) | \
              ((uint32) SPIM_SPI_SS3_POLARITY << SPIM_SPI_SLAVE_SELECT3))

#if(SPIM_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define SPIM_SPI_DEFAULT_CTRL \
                    (SPIM_GET_CTRL_OVS(SPIM_SPI_OVS_FACTOR) | \
                     SPIM_GET_CTRL_BYTE_MODE (SPIM_SPI_BYTE_MODE_ENABLE) | \
                     SPIM_GET_CTRL_EC_AM_MODE(SPIM_SPI_WAKE_ENABLE)      | \
                     SPIM_CTRL_SPI)

    #define SPIM_SPI_DEFAULT_SPI_CTRL \
                    (SPIM_GET_SPI_CTRL_CONTINUOUS    (SPIM_SPI_TRANSFER_SEPARATION)       | \
                     SPIM_GET_SPI_CTRL_SELECT_PRECEDE(SPIM_SPI_SUB_MODE &                   \
                                                                  SPIM_SPI_MODE_TI_PRECEDES_MASK)     | \
                     SPIM_GET_SPI_CTRL_SCLK_MODE     (SPIM_SPI_CLOCK_MODE)                | \
                     SPIM_GET_SPI_CTRL_LATE_MISO_SAMPLE(SPIM_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     SPIM_GET_SPI_CTRL_SCLK_CONTINUOUS(SPIM_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     SPIM_GET_SPI_CTRL_SSEL_POLARITY (SPIM_SPI_SS_POLARITY)               | \
                     SPIM_GET_SPI_CTRL_SUB_MODE      (SPIM_SPI_SUB_MODE)                  | \
                     SPIM_GET_SPI_CTRL_MASTER_MODE   (SPIM_SPI_MODE))

    /* RX direction */
    #define SPIM_SPI_DEFAULT_RX_CTRL \
                    (SPIM_GET_RX_CTRL_DATA_WIDTH(SPIM_SPI_RX_DATA_BITS_NUM)     | \
                     SPIM_GET_RX_CTRL_BIT_ORDER (SPIM_SPI_BITS_ORDER)           | \
                     SPIM_GET_RX_CTRL_MEDIAN    (SPIM_SPI_MEDIAN_FILTER_ENABLE) | \
                     SPIM_SPI_RX_CTRL)

    #define SPIM_SPI_DEFAULT_RX_FIFO_CTRL \
                    SPIM_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define SPIM_SPI_DEFAULT_TX_CTRL \
                    (SPIM_GET_TX_CTRL_DATA_WIDTH(SPIM_SPI_TX_DATA_BITS_NUM) | \
                     SPIM_GET_TX_CTRL_BIT_ORDER (SPIM_SPI_BITS_ORDER)       | \
                     SPIM_SPI_TX_CTRL)

    #define SPIM_SPI_DEFAULT_TX_FIFO_CTRL \
                    SPIM_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SPIM_SPI_DEFAULT_INTR_SPI_EC_MASK   (SPIM_NO_INTR_SOURCES)

    #define SPIM_SPI_DEFAULT_INTR_I2C_EC_MASK   (SPIM_NO_INTR_SOURCES)
    #define SPIM_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (SPIM_SPI_INTR_RX_MASK & SPIM_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPIM_SPI_DEFAULT_INTR_MASTER_MASK \
                    (SPIM_SPI_INTR_TX_MASK & SPIM_INTR_MASTER_SPI_DONE)

    #define SPIM_SPI_DEFAULT_INTR_RX_MASK \
                    (SPIM_SPI_INTR_RX_MASK & (uint32) ~SPIM_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPIM_SPI_DEFAULT_INTR_TX_MASK \
                    (SPIM_SPI_INTR_TX_MASK & (uint32) ~SPIM_INTR_MASTER_SPI_DONE)

#endif /* (SPIM_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define SPIM_CTRL_UART      (SPIM_CTRL_MODE_UART)
#define SPIM_UART_RX_CTRL   (SPIM_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define SPIM_UART_TX_CTRL   (SPIM_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(SPIM_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(SPIM_UART_MODE_IRDA == SPIM_UART_SUB_MODE)

        #define SPIM_DEFAULT_CTRL_OVS   ((0u != SPIM_UART_IRDA_LOW_POWER) ?              \
                                (SPIM_UART_GET_CTRL_OVS_IRDA_LP(SPIM_UART_OVS_FACTOR)) : \
                                (SPIM_CTRL_OVS_IRDA_OVS16))

    #else

        #define SPIM_DEFAULT_CTRL_OVS   SPIM_GET_CTRL_OVS(SPIM_UART_OVS_FACTOR)

    #endif /* (SPIM_UART_MODE_IRDA == SPIM_UART_SUB_MODE) */

    #define SPIM_UART_DEFAULT_CTRL \
                                (SPIM_GET_CTRL_BYTE_MODE  (SPIM_UART_BYTE_MODE_ENABLE)  | \
                                 SPIM_GET_CTRL_ADDR_ACCEPT(SPIM_UART_MP_ACCEPT_ADDRESS) | \
                                 SPIM_DEFAULT_CTRL_OVS                                              | \
                                 SPIM_CTRL_UART)

    #define SPIM_UART_DEFAULT_UART_CTRL \
                                    (SPIM_GET_UART_CTRL_MODE(SPIM_UART_SUB_MODE))

    /* RX direction */
    #define SPIM_UART_DEFAULT_RX_CTRL_PARITY \
                                ((SPIM_UART_PARITY_NONE != SPIM_UART_PARITY_TYPE) ?      \
                                  (SPIM_GET_UART_RX_CTRL_PARITY(SPIM_UART_PARITY_TYPE) | \
                                   SPIM_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define SPIM_UART_DEFAULT_UART_RX_CTRL \
                    (SPIM_GET_UART_RX_CTRL_MODE(SPIM_UART_STOP_BITS_NUM)                    | \
                     SPIM_GET_UART_RX_CTRL_POLARITY(SPIM_UART_IRDA_POLARITY)                | \
                     SPIM_GET_UART_RX_CTRL_MP_MODE(SPIM_UART_MP_MODE_ENABLE)                | \
                     SPIM_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(SPIM_UART_DROP_ON_PARITY_ERR) | \
                     SPIM_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(SPIM_UART_DROP_ON_FRAME_ERR)   | \
                     SPIM_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPIM_UART_DEFAULT_RX_CTRL \
                                (SPIM_GET_RX_CTRL_DATA_WIDTH(SPIM_UART_DATA_BITS_NUM)        | \
                                 SPIM_GET_RX_CTRL_MEDIAN    (SPIM_UART_MEDIAN_FILTER_ENABLE) | \
                                 SPIM_GET_UART_RX_CTRL_ENABLED(SPIM_UART_DIRECTION))

    #define SPIM_UART_DEFAULT_RX_FIFO_CTRL \
                                SPIM_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_UART_RX_TRIGGER_LEVEL)

    #define SPIM_UART_DEFAULT_RX_MATCH_REG  ((0u != SPIM_UART_MP_MODE_ENABLE) ?          \
                                (SPIM_GET_RX_MATCH_ADDR(SPIM_UART_MP_RX_ADDRESS) | \
                                 SPIM_GET_RX_MATCH_MASK(SPIM_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define SPIM_UART_DEFAULT_TX_CTRL_PARITY (SPIM_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPIM_UART_DEFAULT_UART_TX_CTRL \
                                (SPIM_GET_UART_TX_CTRL_MODE(SPIM_UART_STOP_BITS_NUM)       | \
                                 SPIM_GET_UART_TX_CTRL_RETRY_NACK(SPIM_UART_RETRY_ON_NACK) | \
                                 SPIM_UART_DEFAULT_TX_CTRL_PARITY)

    #define SPIM_UART_DEFAULT_TX_CTRL \
                                (SPIM_GET_TX_CTRL_DATA_WIDTH(SPIM_UART_DATA_BITS_NUM) | \
                                 SPIM_GET_UART_TX_CTRL_ENABLED(SPIM_UART_DIRECTION))

    #define SPIM_UART_DEFAULT_TX_FIFO_CTRL \
                                SPIM_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPIM_UART_TX_TRIGGER_LEVEL)

    #define SPIM_UART_DEFAULT_FLOW_CTRL \
                        (SPIM_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(SPIM_UART_RTS_FIFO_LEVEL) | \
                         SPIM_GET_UART_FLOW_CTRL_RTS_POLARITY (SPIM_UART_RTS_POLARITY)   | \
                         SPIM_GET_UART_FLOW_CTRL_CTS_POLARITY (SPIM_UART_CTS_POLARITY)   | \
                         SPIM_GET_UART_FLOW_CTRL_CTS_ENABLE   (SPIM_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define SPIM_UART_DEFAULT_INTR_I2C_EC_MASK  (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_SPI_EC_MASK  (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_SLAVE_MASK   (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_MASTER_MASK  (SPIM_NO_INTR_SOURCES)
    #define SPIM_UART_DEFAULT_INTR_RX_MASK      (SPIM_UART_INTR_RX_MASK)
    #define SPIM_UART_DEFAULT_INTR_TX_MASK      (SPIM_UART_INTR_TX_MASK)

#endif /* (SPIM_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define SPIM_SPIM_ACTIVE_SS0    (SPIM_SPI_SLAVE_SELECT0)
#define SPIM_SPIM_ACTIVE_SS1    (SPIM_SPI_SLAVE_SELECT1)
#define SPIM_SPIM_ACTIVE_SS2    (SPIM_SPI_SLAVE_SELECT2)
#define SPIM_SPIM_ACTIVE_SS3    (SPIM_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_SPIM_H */


/* [] END OF FILE */
