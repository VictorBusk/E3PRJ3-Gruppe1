/*******************************************************************************
* File Name: Debug_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_Debug_H)
#define CY_SCB_SPI_UART_Debug_H

#include "Debug.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define Debug_SPI_MODE                   (0u)
#define Debug_SPI_SUB_MODE               (0u)
#define Debug_SPI_CLOCK_MODE             (0u)
#define Debug_SPI_OVS_FACTOR             (16u)
#define Debug_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define Debug_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define Debug_SPI_RX_DATA_BITS_NUM       (8u)
#define Debug_SPI_TX_DATA_BITS_NUM       (8u)
#define Debug_SPI_WAKE_ENABLE            (0u)
#define Debug_SPI_BITS_ORDER             (1u)
#define Debug_SPI_TRANSFER_SEPARATION    (1u)
#define Debug_SPI_NUMBER_OF_SS_LINES     (1u)
#define Debug_SPI_RX_BUFFER_SIZE         (8u)
#define Debug_SPI_TX_BUFFER_SIZE         (8u)

#define Debug_SPI_INTERRUPT_MODE         (0u)

#define Debug_SPI_INTR_RX_MASK           (0u)
#define Debug_SPI_INTR_TX_MASK           (0u)

#define Debug_SPI_RX_TRIGGER_LEVEL       (7u)
#define Debug_SPI_TX_TRIGGER_LEVEL       (0u)

#define Debug_SPI_BYTE_MODE_ENABLE       (0u)
#define Debug_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define Debug_SPI_SS0_POLARITY           (0u)
#define Debug_SPI_SS1_POLARITY           (0u)
#define Debug_SPI_SS2_POLARITY           (0u)
#define Debug_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define Debug_UART_SUB_MODE              (0u)
#define Debug_UART_DIRECTION             (3u)
#define Debug_UART_DATA_BITS_NUM         (8u)
#define Debug_UART_PARITY_TYPE           (2u)
#define Debug_UART_STOP_BITS_NUM         (2u)
#define Debug_UART_OVS_FACTOR            (12u)
#define Debug_UART_IRDA_LOW_POWER        (0u)
#define Debug_UART_MEDIAN_FILTER_ENABLE  (0u)
#define Debug_UART_RETRY_ON_NACK         (0u)
#define Debug_UART_IRDA_POLARITY         (0u)
#define Debug_UART_DROP_ON_FRAME_ERR     (0u)
#define Debug_UART_DROP_ON_PARITY_ERR    (0u)
#define Debug_UART_WAKE_ENABLE           (0u)
#define Debug_UART_RX_BUFFER_SIZE        (8u)
#define Debug_UART_TX_BUFFER_SIZE        (8u)
#define Debug_UART_MP_MODE_ENABLE        (0u)
#define Debug_UART_MP_ACCEPT_ADDRESS     (0u)
#define Debug_UART_MP_RX_ADDRESS         (2u)
#define Debug_UART_MP_RX_ADDRESS_MASK    (255u)

#define Debug_UART_INTERRUPT_MODE        (0u)

#define Debug_UART_INTR_RX_MASK          (0u)
#define Debug_UART_INTR_TX_MASK          (0u)

#define Debug_UART_RX_TRIGGER_LEVEL      (7u)
#define Debug_UART_TX_TRIGGER_LEVEL      (0u)

#define Debug_UART_BYTE_MODE_ENABLE      (0u)
#define Debug_UART_CTS_ENABLE            (0u)
#define Debug_UART_CTS_POLARITY          (0u)
#define Debug_UART_RTS_ENABLE            (0u)
#define Debug_UART_RTS_POLARITY          (0u)
#define Debug_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define Debug_SPI_SLAVE  (0u)
#define Debug_SPI_MASTER (1u)

/* UART direction enum */
#define Debug_UART_RX    (1u)
#define Debug_UART_TX    (2u)
#define Debug_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define Debug_SPI_SLAVE_CONST        (1u)
    #define Debug_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define Debug_RX_DIRECTION           (1u)
    #define Debug_TX_DIRECTION           (1u)
    #define Debug_UART_RX_DIRECTION      (1u)
    #define Debug_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define Debug_INTERNAL_RX_SW_BUFFER   (0u)
    #define Debug_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define Debug_INTERNAL_RX_BUFFER_SIZE    (Debug_rxBufferSize + 1u)
    #define Debug_RX_BUFFER_SIZE             (Debug_rxBufferSize)
    #define Debug_TX_BUFFER_SIZE             (Debug_txBufferSize)

    /* Return true if buffer is provided */
    #define Debug_CHECK_RX_SW_BUFFER (NULL != Debug_rxBuffer)
    #define Debug_CHECK_TX_SW_BUFFER (NULL != Debug_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define Debug_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define Debug_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define Debug_SPI_WAKE_ENABLE_CONST  (1u)
    #define Debug_CHECK_SPI_WAKE_ENABLE  (0u != Debug_scbEnableWake)
    #define Debug_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
        #define Debug_SPI_UART_FIFO_SIZE             (Debug_FIFO_SIZE)
        #define Debug_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define Debug_SPI_UART_FIFO_SIZE (Debug_GET_FIFO_SIZE(Debug_CTRL_REG & \
                                                                                    Debug_CTRL_BYTE_MODE))

        #define Debug_CHECK_UART_RTS_CONTROL_FLOW \
                    ((Debug_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != Debug_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(Debug_UART_FLOW_CTRL_REG)))
    #endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (Debug_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define Debug_SPI_RX_DIRECTION (1u)
        #define Debug_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
            #define Debug_SPI_UART_FIFO_SIZE    (Debug_FIFO_SIZE)
        #else
            #define Debug_SPI_UART_FIFO_SIZE \
                                           Debug_GET_FIFO_SIZE(Debug_SPI_BYTE_MODE_ENABLE)

        #endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define Debug_INTERNAL_SPI_RX_SW_BUFFER  (Debug_SPI_RX_BUFFER_SIZE > \
                                                                Debug_SPI_UART_FIFO_SIZE)
        #define Debug_INTERNAL_SPI_TX_SW_BUFFER  (Debug_SPI_TX_BUFFER_SIZE > \
                                                                Debug_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define Debug_INTERNAL_RX_SW_BUFFER  (Debug_INTERNAL_SPI_RX_SW_BUFFER)
        #define Debug_INTERNAL_TX_SW_BUFFER  (Debug_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define Debug_INTERNAL_RX_BUFFER_SIZE    (Debug_SPI_RX_BUFFER_SIZE + 1u)
        #define Debug_RX_BUFFER_SIZE             (Debug_SPI_RX_BUFFER_SIZE)
        #define Debug_TX_BUFFER_SIZE             (Debug_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define Debug_SPI_WAKE_ENABLE_CONST  (0u != Debug_SPI_WAKE_ENABLE)
        #define Debug_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define Debug_UART_RX_DIRECTION (0u != (Debug_UART_DIRECTION & Debug_UART_RX))
        #define Debug_UART_TX_DIRECTION (0u != (Debug_UART_DIRECTION & Debug_UART_TX))

        /* Get FIFO size */
        #if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
            #define Debug_SPI_UART_FIFO_SIZE    (Debug_FIFO_SIZE)
        #else
            #define Debug_SPI_UART_FIFO_SIZE \
                                           Debug_GET_FIFO_SIZE(Debug_UART_BYTE_MODE_ENABLE)
        #endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define Debug_INTERNAL_UART_RX_SW_BUFFER  (Debug_UART_RX_BUFFER_SIZE > \
                                                                Debug_SPI_UART_FIFO_SIZE)
        #define Debug_INTERNAL_UART_TX_SW_BUFFER  (Debug_UART_TX_BUFFER_SIZE > \
                                                                    Debug_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define Debug_INTERNAL_RX_SW_BUFFER  (Debug_INTERNAL_UART_RX_SW_BUFFER)
        #define Debug_INTERNAL_TX_SW_BUFFER  (Debug_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define Debug_INTERNAL_RX_BUFFER_SIZE    (Debug_UART_RX_BUFFER_SIZE + 1u)
        #define Debug_RX_BUFFER_SIZE             (Debug_UART_RX_BUFFER_SIZE)
        #define Debug_TX_BUFFER_SIZE             (Debug_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define Debug_SPI_WAKE_ENABLE_CONST  (0u)
        #define Debug_UART_WAKE_ENABLE_CONST (0u != Debug_UART_WAKE_ENABLE)

    #endif /* (Debug_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define Debug_SPI_SLAVE_CONST    (Debug_SPI_MODE == Debug_SPI_SLAVE)
    #define Debug_SPI_MASTER_CONST   (Debug_SPI_MODE == Debug_SPI_MASTER)

    /* Direction */
    #define Debug_RX_DIRECTION ((Debug_SCB_MODE_SPI_CONST_CFG) ? \
                                            (Debug_SPI_RX_DIRECTION) : (Debug_UART_RX_DIRECTION))

    #define Debug_TX_DIRECTION ((Debug_SCB_MODE_SPI_CONST_CFG) ? \
                                            (Debug_SPI_TX_DIRECTION) : (Debug_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define Debug_CHECK_RX_SW_BUFFER (Debug_INTERNAL_RX_SW_BUFFER)
    #define Debug_CHECK_TX_SW_BUFFER (Debug_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define Debug_INTERNAL_RX_SW_BUFFER_CONST    (Debug_INTERNAL_RX_SW_BUFFER)
    #define Debug_INTERNAL_TX_SW_BUFFER_CONST    (Debug_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define Debug_CHECK_SPI_WAKE_ENABLE  (Debug_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define Debug_CHECK_UART_RTS_CONTROL_FLOW    (Debug_SCB_MODE_UART_CONST_CFG && \
                                                             Debug_UART_RTS_ENABLE)

#endif /* End (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* Debug_SPI_INIT_STRUCT */
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
} Debug_SPI_INIT_STRUCT;

/* Debug_UART_INIT_STRUCT */
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
} Debug_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    void Debug_SpiInit(const Debug_SPI_INIT_STRUCT *config);
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(Debug_SCB_MODE_SPI_INC)
    #define Debug_SpiIsBusBusy() ((uint32) (0u != (Debug_SPI_STATUS_REG & \
                                                              Debug_SPI_STATUS_BUS_BUSY)))

    #if (Debug_SPI_MASTER_CONST)
        void Debug_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(Debug_SPI_MASTER_CONST) */

    #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
        void Debug_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
#endif /* (Debug_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    void Debug_UartInit(const Debug_UART_INIT_STRUCT *config);
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(Debug_SCB_MODE_UART_INC)
    void Debug_UartSetRxAddress(uint32 address);
    void Debug_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(Debug_UART_RX_DIRECTION)
        uint32 Debug_UartGetChar(void);
        uint32 Debug_UartGetByte(void);

        #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void Debug_UartSetRtsPolarity(uint32 polarity);
            void Debug_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
    #endif /* (Debug_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(Debug_UART_TX_DIRECTION)
        #define Debug_UartPutChar(ch)    Debug_SpiUartWriteTxData((uint32)(ch))
        void Debug_UartPutString(const char8 string[]);
        void Debug_UartPutCRLF(uint32 txDataByte);

        #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void Debug_UartEnableCts(void);
            void Debug_UartDisableCts(void);
            void Debug_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
    #endif /* (Debug_UART_TX_DIRECTION) */
#endif /* (Debug_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(Debug_RX_DIRECTION)
    uint32 Debug_SpiUartReadRxData(void);
    uint32 Debug_SpiUartGetRxBufferSize(void);
    void   Debug_SpiUartClearRxBuffer(void);
#endif /* (Debug_RX_DIRECTION) */

/* Common APIs TX direction */
#if(Debug_TX_DIRECTION)
    void   Debug_SpiUartWriteTxData(uint32 txData);
    void   Debug_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 Debug_SpiUartGetTxBufferSize(void);
    void   Debug_SpiUartClearTxBuffer(void);
#endif /* (Debug_TX_DIRECTION) */

CY_ISR_PROTO(Debug_SPI_UART_ISR);

#if(Debug_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(Debug_UART_WAKEUP_ISR);
#endif /* (Debug_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   Debug_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 Debug_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   Debug_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 Debug_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(Debug_INTERNAL_RX_SW_BUFFER_CONST)
        #define Debug_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    Debug_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define Debug_GetWordFromRxBuffer(idx) Debug_rxBufferInternal[(idx)]

    #endif /* (Debug_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(Debug_INTERNAL_TX_SW_BUFFER_CONST)
        #define Debug_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        Debug_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define Debug_GetWordFromTxBuffer(idx) Debug_txBufferInternal[(idx)]

    #endif /* (Debug_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (Debug_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define Debug_SPI_MODE_MOTOROLA      (0x00u)
#define Debug_SPI_MODE_TI_COINCIDES  (0x01u)
#define Debug_SPI_MODE_TI_PRECEDES   (0x11u)
#define Debug_SPI_MODE_NATIONAL      (0x02u)
#define Debug_SPI_MODE_MASK          (0x03u)
#define Debug_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define Debug_SPI_MODE_NS_MICROWIRE  (Debug_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define Debug_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define Debug_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define Debug_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define Debug_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define Debug_BITS_ORDER_LSB_FIRST   (0u)
#define Debug_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define Debug_SPI_TRANSFER_SEPARATED     (0u)
#define Debug_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define Debug_SPI_SLAVE_SELECT0    (Debug_SCB__SS0_POSISTION)
#define Debug_SPI_SLAVE_SELECT1    (Debug_SCB__SS1_POSISTION)
#define Debug_SPI_SLAVE_SELECT2    (Debug_SCB__SS2_POSISTION)
#define Debug_SPI_SLAVE_SELECT3    (Debug_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define Debug_SPI_SS_ACTIVE_LOW  (0u)
#define Debug_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define Debug_UART_MODE_STD          (0u)
#define Debug_UART_MODE_SMARTCARD    (1u)
#define Debug_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define Debug_UART_RX    (1u)
#define Debug_UART_TX    (2u)
#define Debug_UART_TX_RX (3u)

/* UART parity enum */
#define Debug_UART_PARITY_EVEN   (0u)
#define Debug_UART_PARITY_ODD    (1u)
#define Debug_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define Debug_UART_STOP_BITS_1   (2u)
#define Debug_UART_STOP_BITS_1_5 (3u)
#define Debug_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define Debug_UART_IRDA_LP_OVS16     (16u)
#define Debug_UART_IRDA_LP_OVS32     (32u)
#define Debug_UART_IRDA_LP_OVS48     (48u)
#define Debug_UART_IRDA_LP_OVS96     (96u)
#define Debug_UART_IRDA_LP_OVS192    (192u)
#define Debug_UART_IRDA_LP_OVS768    (768u)
#define Debug_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define Debug_UART_MP_MARK       (0x100u)
#define Debug_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define Debug_UART_CTS_ACTIVE_LOW    (0u)
#define Debug_UART_CTS_ACTIVE_HIGH   (1u)
#define Debug_UART_RTS_ACTIVE_LOW    (0u)
#define Debug_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define Debug_INTR_RX_ERR        (Debug_INTR_RX_OVERFLOW    | \
                                             Debug_INTR_RX_UNDERFLOW   | \
                                             Debug_INTR_RX_FRAME_ERROR | \
                                             Debug_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for Debug_UartGetByte() */
#define Debug_UART_RX_OVERFLOW       (Debug_INTR_RX_OVERFLOW << 8u)
#define Debug_UART_RX_UNDERFLOW      (Debug_INTR_RX_UNDERFLOW << 8u)
#define Debug_UART_RX_FRAME_ERROR    (Debug_INTR_RX_FRAME_ERROR << 8u)
#define Debug_UART_RX_PARITY_ERROR   (Debug_INTR_RX_PARITY_ERROR << 8u)
#define Debug_UART_RX_ERROR_MASK     (Debug_UART_RX_OVERFLOW    | \
                                                 Debug_UART_RX_UNDERFLOW   | \
                                                 Debug_UART_RX_FRAME_ERROR | \
                                                 Debug_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const Debug_SPI_INIT_STRUCT  Debug_configSpi;
    extern const Debug_UART_INIT_STRUCT Debug_configUart;
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define Debug_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & Debug_INTR_SLAVE_SPI_BUS_ERROR)
#define Debug_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & Debug_INTR_MASTER_SPI_DONE)
#define Debug_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~Debug_INTR_SLAVE_SPI_BUS_ERROR)

#define Debug_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~Debug_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define Debug_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((Debug_UART_IRDA_LP_OVS16   == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS16 : \
         ((Debug_UART_IRDA_LP_OVS32   == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS32 : \
          ((Debug_UART_IRDA_LP_OVS48   == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS48 : \
           ((Debug_UART_IRDA_LP_OVS96   == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS96 : \
            ((Debug_UART_IRDA_LP_OVS192  == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS192 : \
             ((Debug_UART_IRDA_LP_OVS768  == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS768 : \
              ((Debug_UART_IRDA_LP_OVS1536 == (oversample)) ? Debug_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          Debug_CTRL_OVS_IRDA_LP_OVS16)))))))

#define Debug_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (Debug_UART_RX & (direction))) ? \
                                                                     (Debug_RX_CTRL_ENABLED) : (0u))

#define Debug_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (Debug_UART_TX & (direction))) ? \
                                                                     (Debug_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define Debug_CTRL_SPI      (Debug_CTRL_MODE_SPI)
#define Debug_SPI_RX_CTRL   (Debug_RX_CTRL_ENABLED)
#define Debug_SPI_TX_CTRL   (Debug_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define Debug_SPI_SS_POLARITY \
             (((uint32) Debug_SPI_SS0_POLARITY << Debug_SPI_SLAVE_SELECT0) | \
              ((uint32) Debug_SPI_SS1_POLARITY << Debug_SPI_SLAVE_SELECT1) | \
              ((uint32) Debug_SPI_SS2_POLARITY << Debug_SPI_SLAVE_SELECT2) | \
              ((uint32) Debug_SPI_SS3_POLARITY << Debug_SPI_SLAVE_SELECT3))

#if(Debug_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define Debug_SPI_DEFAULT_CTRL \
                    (Debug_GET_CTRL_OVS(Debug_SPI_OVS_FACTOR) | \
                     Debug_GET_CTRL_BYTE_MODE (Debug_SPI_BYTE_MODE_ENABLE) | \
                     Debug_GET_CTRL_EC_AM_MODE(Debug_SPI_WAKE_ENABLE)      | \
                     Debug_CTRL_SPI)

    #define Debug_SPI_DEFAULT_SPI_CTRL \
                    (Debug_GET_SPI_CTRL_CONTINUOUS    (Debug_SPI_TRANSFER_SEPARATION)       | \
                     Debug_GET_SPI_CTRL_SELECT_PRECEDE(Debug_SPI_SUB_MODE &                   \
                                                                  Debug_SPI_MODE_TI_PRECEDES_MASK)     | \
                     Debug_GET_SPI_CTRL_SCLK_MODE     (Debug_SPI_CLOCK_MODE)                | \
                     Debug_GET_SPI_CTRL_LATE_MISO_SAMPLE(Debug_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     Debug_GET_SPI_CTRL_SCLK_CONTINUOUS(Debug_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     Debug_GET_SPI_CTRL_SSEL_POLARITY (Debug_SPI_SS_POLARITY)               | \
                     Debug_GET_SPI_CTRL_SUB_MODE      (Debug_SPI_SUB_MODE)                  | \
                     Debug_GET_SPI_CTRL_MASTER_MODE   (Debug_SPI_MODE))

    /* RX direction */
    #define Debug_SPI_DEFAULT_RX_CTRL \
                    (Debug_GET_RX_CTRL_DATA_WIDTH(Debug_SPI_RX_DATA_BITS_NUM)     | \
                     Debug_GET_RX_CTRL_BIT_ORDER (Debug_SPI_BITS_ORDER)           | \
                     Debug_GET_RX_CTRL_MEDIAN    (Debug_SPI_MEDIAN_FILTER_ENABLE) | \
                     Debug_SPI_RX_CTRL)

    #define Debug_SPI_DEFAULT_RX_FIFO_CTRL \
                    Debug_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(Debug_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define Debug_SPI_DEFAULT_TX_CTRL \
                    (Debug_GET_TX_CTRL_DATA_WIDTH(Debug_SPI_TX_DATA_BITS_NUM) | \
                     Debug_GET_TX_CTRL_BIT_ORDER (Debug_SPI_BITS_ORDER)       | \
                     Debug_SPI_TX_CTRL)

    #define Debug_SPI_DEFAULT_TX_FIFO_CTRL \
                    Debug_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(Debug_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define Debug_SPI_DEFAULT_INTR_SPI_EC_MASK   (Debug_NO_INTR_SOURCES)

    #define Debug_SPI_DEFAULT_INTR_I2C_EC_MASK   (Debug_NO_INTR_SOURCES)
    #define Debug_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (Debug_SPI_INTR_RX_MASK & Debug_INTR_SLAVE_SPI_BUS_ERROR)

    #define Debug_SPI_DEFAULT_INTR_MASTER_MASK \
                    (Debug_SPI_INTR_TX_MASK & Debug_INTR_MASTER_SPI_DONE)

    #define Debug_SPI_DEFAULT_INTR_RX_MASK \
                    (Debug_SPI_INTR_RX_MASK & (uint32) ~Debug_INTR_SLAVE_SPI_BUS_ERROR)

    #define Debug_SPI_DEFAULT_INTR_TX_MASK \
                    (Debug_SPI_INTR_TX_MASK & (uint32) ~Debug_INTR_MASTER_SPI_DONE)

#endif /* (Debug_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define Debug_CTRL_UART      (Debug_CTRL_MODE_UART)
#define Debug_UART_RX_CTRL   (Debug_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define Debug_UART_TX_CTRL   (Debug_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(Debug_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(Debug_UART_MODE_IRDA == Debug_UART_SUB_MODE)

        #define Debug_DEFAULT_CTRL_OVS   ((0u != Debug_UART_IRDA_LOW_POWER) ?              \
                                (Debug_UART_GET_CTRL_OVS_IRDA_LP(Debug_UART_OVS_FACTOR)) : \
                                (Debug_CTRL_OVS_IRDA_OVS16))

    #else

        #define Debug_DEFAULT_CTRL_OVS   Debug_GET_CTRL_OVS(Debug_UART_OVS_FACTOR)

    #endif /* (Debug_UART_MODE_IRDA == Debug_UART_SUB_MODE) */

    #define Debug_UART_DEFAULT_CTRL \
                                (Debug_GET_CTRL_BYTE_MODE  (Debug_UART_BYTE_MODE_ENABLE)  | \
                                 Debug_GET_CTRL_ADDR_ACCEPT(Debug_UART_MP_ACCEPT_ADDRESS) | \
                                 Debug_DEFAULT_CTRL_OVS                                              | \
                                 Debug_CTRL_UART)

    #define Debug_UART_DEFAULT_UART_CTRL \
                                    (Debug_GET_UART_CTRL_MODE(Debug_UART_SUB_MODE))

    /* RX direction */
    #define Debug_UART_DEFAULT_RX_CTRL_PARITY \
                                ((Debug_UART_PARITY_NONE != Debug_UART_PARITY_TYPE) ?      \
                                  (Debug_GET_UART_RX_CTRL_PARITY(Debug_UART_PARITY_TYPE) | \
                                   Debug_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define Debug_UART_DEFAULT_UART_RX_CTRL \
                    (Debug_GET_UART_RX_CTRL_MODE(Debug_UART_STOP_BITS_NUM)                    | \
                     Debug_GET_UART_RX_CTRL_POLARITY(Debug_UART_IRDA_POLARITY)                | \
                     Debug_GET_UART_RX_CTRL_MP_MODE(Debug_UART_MP_MODE_ENABLE)                | \
                     Debug_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(Debug_UART_DROP_ON_PARITY_ERR) | \
                     Debug_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(Debug_UART_DROP_ON_FRAME_ERR)   | \
                     Debug_UART_DEFAULT_RX_CTRL_PARITY)

    #define Debug_UART_DEFAULT_RX_CTRL \
                                (Debug_GET_RX_CTRL_DATA_WIDTH(Debug_UART_DATA_BITS_NUM)        | \
                                 Debug_GET_RX_CTRL_MEDIAN    (Debug_UART_MEDIAN_FILTER_ENABLE) | \
                                 Debug_GET_UART_RX_CTRL_ENABLED(Debug_UART_DIRECTION))

    #define Debug_UART_DEFAULT_RX_FIFO_CTRL \
                                Debug_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(Debug_UART_RX_TRIGGER_LEVEL)

    #define Debug_UART_DEFAULT_RX_MATCH_REG  ((0u != Debug_UART_MP_MODE_ENABLE) ?          \
                                (Debug_GET_RX_MATCH_ADDR(Debug_UART_MP_RX_ADDRESS) | \
                                 Debug_GET_RX_MATCH_MASK(Debug_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define Debug_UART_DEFAULT_TX_CTRL_PARITY (Debug_UART_DEFAULT_RX_CTRL_PARITY)

    #define Debug_UART_DEFAULT_UART_TX_CTRL \
                                (Debug_GET_UART_TX_CTRL_MODE(Debug_UART_STOP_BITS_NUM)       | \
                                 Debug_GET_UART_TX_CTRL_RETRY_NACK(Debug_UART_RETRY_ON_NACK) | \
                                 Debug_UART_DEFAULT_TX_CTRL_PARITY)

    #define Debug_UART_DEFAULT_TX_CTRL \
                                (Debug_GET_TX_CTRL_DATA_WIDTH(Debug_UART_DATA_BITS_NUM) | \
                                 Debug_GET_UART_TX_CTRL_ENABLED(Debug_UART_DIRECTION))

    #define Debug_UART_DEFAULT_TX_FIFO_CTRL \
                                Debug_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(Debug_UART_TX_TRIGGER_LEVEL)

    #define Debug_UART_DEFAULT_FLOW_CTRL \
                        (Debug_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(Debug_UART_RTS_FIFO_LEVEL) | \
                         Debug_GET_UART_FLOW_CTRL_RTS_POLARITY (Debug_UART_RTS_POLARITY)   | \
                         Debug_GET_UART_FLOW_CTRL_CTS_POLARITY (Debug_UART_CTS_POLARITY)   | \
                         Debug_GET_UART_FLOW_CTRL_CTS_ENABLE   (Debug_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define Debug_UART_DEFAULT_INTR_I2C_EC_MASK  (Debug_NO_INTR_SOURCES)
    #define Debug_UART_DEFAULT_INTR_SPI_EC_MASK  (Debug_NO_INTR_SOURCES)
    #define Debug_UART_DEFAULT_INTR_SLAVE_MASK   (Debug_NO_INTR_SOURCES)
    #define Debug_UART_DEFAULT_INTR_MASTER_MASK  (Debug_NO_INTR_SOURCES)
    #define Debug_UART_DEFAULT_INTR_RX_MASK      (Debug_UART_INTR_RX_MASK)
    #define Debug_UART_DEFAULT_INTR_TX_MASK      (Debug_UART_INTR_TX_MASK)

#endif /* (Debug_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define Debug_SPIM_ACTIVE_SS0    (Debug_SPI_SLAVE_SELECT0)
#define Debug_SPIM_ACTIVE_SS1    (Debug_SPI_SLAVE_SELECT1)
#define Debug_SPIM_ACTIVE_SS2    (Debug_SPI_SLAVE_SELECT2)
#define Debug_SPIM_ACTIVE_SS3    (Debug_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_Debug_H */


/* [] END OF FILE */
