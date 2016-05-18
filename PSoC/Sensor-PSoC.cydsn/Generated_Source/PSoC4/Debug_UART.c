/*******************************************************************************
* File Name: Debug_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Debug_PVT.h"
#include "Debug_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const Debug_UART_INIT_STRUCT Debug_configUart =
    {
        Debug_UART_SUB_MODE,
        Debug_UART_DIRECTION,
        Debug_UART_DATA_BITS_NUM,
        Debug_UART_PARITY_TYPE,
        Debug_UART_STOP_BITS_NUM,
        Debug_UART_OVS_FACTOR,
        Debug_UART_IRDA_LOW_POWER,
        Debug_UART_MEDIAN_FILTER_ENABLE,
        Debug_UART_RETRY_ON_NACK,
        Debug_UART_IRDA_POLARITY,
        Debug_UART_DROP_ON_PARITY_ERR,
        Debug_UART_DROP_ON_FRAME_ERR,
        Debug_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        Debug_UART_MP_MODE_ENABLE,
        Debug_UART_MP_ACCEPT_ADDRESS,
        Debug_UART_MP_RX_ADDRESS,
        Debug_UART_MP_RX_ADDRESS_MASK,
        (uint32) Debug_SCB_IRQ_INTERNAL,
        Debug_UART_INTR_RX_MASK,
        Debug_UART_RX_TRIGGER_LEVEL,
        Debug_UART_INTR_TX_MASK,
        Debug_UART_TX_TRIGGER_LEVEL,
        (uint8) Debug_UART_BYTE_MODE_ENABLE,
        (uint8) Debug_UART_CTS_ENABLE,
        (uint8) Debug_UART_CTS_POLARITY,
        (uint8) Debug_UART_RTS_POLARITY,
        (uint8) Debug_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: Debug_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Debug_UartInit(const Debug_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (Debug_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (Debug_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

            /* Configure pins */
            Debug_SetPins(Debug_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            Debug_scbMode       = (uint8) Debug_SCB_MODE_UART;
            Debug_scbEnableWake = (uint8) config->enableWake;
            Debug_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            Debug_rxBuffer      =         config->rxBuffer;
            Debug_rxDataBits    = (uint8) config->dataBits;
            Debug_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            Debug_txBuffer      =         config->txBuffer;
            Debug_txDataBits    = (uint8) config->dataBits;
            Debug_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(Debug_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                Debug_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (Debug_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (Debug_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                Debug_CTRL_REG  = Debug_GET_CTRL_OVS(config->oversample);
            }

            Debug_CTRL_REG     |= Debug_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             Debug_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             Debug_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            Debug_UART_CTRL_REG = Debug_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            Debug_UART_RX_CTRL_REG = Debug_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        Debug_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        Debug_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        Debug_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        Debug_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(Debug_UART_PARITY_NONE != config->parity)
            {
               Debug_UART_RX_CTRL_REG |= Debug_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    Debug_UART_RX_CTRL_PARITY_ENABLED;
            }

            Debug_RX_CTRL_REG      = Debug_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                Debug_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                Debug_GET_UART_RX_CTRL_ENABLED(config->direction);

            Debug_RX_FIFO_CTRL_REG = Debug_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            Debug_RX_MATCH_REG     = Debug_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                Debug_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            Debug_UART_TX_CTRL_REG = Debug_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                Debug_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(Debug_UART_PARITY_NONE != config->parity)
            {
               Debug_UART_TX_CTRL_REG |= Debug_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    Debug_UART_TX_CTRL_PARITY_ENABLED;
            }

            Debug_TX_CTRL_REG      = Debug_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                Debug_GET_UART_TX_CTRL_ENABLED(config->direction);

            Debug_TX_FIFO_CTRL_REG = Debug_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
            Debug_UART_FLOW_CTRL_REG = Debug_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            Debug_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            Debug_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            Debug_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (Debug_ISR_NUMBER);
            CyIntSetPriority(Debug_ISR_NUMBER, Debug_ISR_PRIORITY);
            (void) CyIntSetVector(Debug_ISR_NUMBER, &Debug_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(Debug_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (Debug_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(Debug_RX_WAKE_ISR_NUMBER, Debug_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(Debug_RX_WAKE_ISR_NUMBER, &Debug_UART_WAKEUP_ISR);
        #endif /* (Debug_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            Debug_INTR_I2C_EC_MASK_REG = Debug_NO_INTR_SOURCES;
            Debug_INTR_SPI_EC_MASK_REG = Debug_NO_INTR_SOURCES;
            Debug_INTR_SLAVE_MASK_REG  = Debug_NO_INTR_SOURCES;
            Debug_INTR_MASTER_MASK_REG = Debug_NO_INTR_SOURCES;
            Debug_INTR_RX_MASK_REG     = config->rxInterruptMask;
            Debug_INTR_TX_MASK_REG     = config->txInterruptMask;

            /* Clear RX buffer indexes */
            Debug_rxBufferHead     = 0u;
            Debug_rxBufferTail     = 0u;
            Debug_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            Debug_txBufferHead = 0u;
            Debug_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: Debug_UartInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the UART operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Debug_UartInit(void)
    {
        /* Configure UART interface */
        Debug_CTRL_REG = Debug_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        Debug_UART_CTRL_REG = Debug_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        Debug_UART_RX_CTRL_REG = Debug_UART_DEFAULT_UART_RX_CTRL;
        Debug_RX_CTRL_REG      = Debug_UART_DEFAULT_RX_CTRL;
        Debug_RX_FIFO_CTRL_REG = Debug_UART_DEFAULT_RX_FIFO_CTRL;
        Debug_RX_MATCH_REG     = Debug_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        Debug_UART_TX_CTRL_REG = Debug_UART_DEFAULT_UART_TX_CTRL;
        Debug_TX_CTRL_REG      = Debug_UART_DEFAULT_TX_CTRL;
        Debug_TX_FIFO_CTRL_REG = Debug_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
        Debug_UART_FLOW_CTRL_REG = Debug_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(Debug_SCB_IRQ_INTERNAL)
        CyIntDisable    (Debug_ISR_NUMBER);
        CyIntSetPriority(Debug_ISR_NUMBER, Debug_ISR_PRIORITY);
        (void) CyIntSetVector(Debug_ISR_NUMBER, &Debug_SPI_UART_ISR);
    #endif /* (Debug_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(Debug_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (Debug_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(Debug_RX_WAKE_ISR_NUMBER, Debug_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(Debug_RX_WAKE_ISR_NUMBER, &Debug_UART_WAKEUP_ISR);
    #endif /* (Debug_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        Debug_INTR_I2C_EC_MASK_REG = Debug_UART_DEFAULT_INTR_I2C_EC_MASK;
        Debug_INTR_SPI_EC_MASK_REG = Debug_UART_DEFAULT_INTR_SPI_EC_MASK;
        Debug_INTR_SLAVE_MASK_REG  = Debug_UART_DEFAULT_INTR_SLAVE_MASK;
        Debug_INTR_MASTER_MASK_REG = Debug_UART_DEFAULT_INTR_MASTER_MASK;
        Debug_INTR_RX_MASK_REG     = Debug_UART_DEFAULT_INTR_RX_MASK;
        Debug_INTR_TX_MASK_REG     = Debug_UART_DEFAULT_INTR_TX_MASK;

    #if(Debug_INTERNAL_RX_SW_BUFFER_CONST)
        Debug_rxBufferHead     = 0u;
        Debug_rxBufferTail     = 0u;
        Debug_rxBufferOverflow = 0u;
    #endif /* (Debug_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(Debug_INTERNAL_TX_SW_BUFFER_CONST)
        Debug_txBufferHead = 0u;
        Debug_txBufferTail = 0u;
    #endif /* (Debug_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: Debug_UartPostEnable
********************************************************************************
*
* Summary:
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be 
*  controlled by the SCB UART.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Debug_UartPostEnable(void)
{
#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)

#if (Debug_TX_SDA_MISO_PIN)
    if (Debug_CHECK_TX_SDA_MISO_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        Debug_SET_HSIOM_SEL(Debug_TX_SDA_MISO_HSIOM_REG, Debug_TX_SDA_MISO_HSIOM_MASK,
                                       Debug_TX_SDA_MISO_HSIOM_POS, Debug_HSIOM_UART_SEL);
    }
#endif /* (Debug_TX_SDA_MISO_PIN_PIN) */

#if (Debug_SS0_PIN)
    if (Debug_CHECK_SS0_PIN_USED)
    {
        /* Set SCB UART to drive the output pin */
        Debug_SET_HSIOM_SEL(Debug_SS0_HSIOM_REG, Debug_SS0_HSIOM_MASK,
                                       Debug_SS0_HSIOM_POS, Debug_HSIOM_UART_SEL);
    }
#endif /* (Debug_SS0_PIN) */

#else
#if (Debug_UART_TX_PIN)
     /* Set SCB UART to drive the output pin */
    Debug_SET_HSIOM_SEL(Debug_TX_HSIOM_REG, Debug_TX_HSIOM_MASK,
                                   Debug_TX_HSIOM_POS, Debug_HSIOM_UART_SEL);
#endif /* (Debug_UART_TX_PIN) */

#if (Debug_UART_RTS_PIN)
    /* Set SCB UART to drive the output pin */
    Debug_SET_HSIOM_SEL(Debug_RTS_HSIOM_REG, Debug_RTS_HSIOM_MASK,
                                   Debug_RTS_HSIOM_POS, Debug_HSIOM_UART_SEL);
#endif /* (Debug_UART_RTS_PIN) */

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Debug_UartStop
********************************************************************************
*
* Summary:
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature to
*  not cause it to trigger after the component is enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Debug_UartStop(void)
{
#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (Debug_TX_SDA_MISO_PIN)
        if (Debug_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            Debug_SET_HSIOM_SEL(Debug_TX_SDA_MISO_HSIOM_REG, Debug_TX_SDA_MISO_HSIOM_MASK,
                                           Debug_TX_SDA_MISO_HSIOM_POS, Debug_HSIOM_GPIO_SEL);
        }
    #endif /* (Debug_TX_SDA_MISO_PIN_PIN) */

    #if (Debug_SS0_PIN)
        if (Debug_CHECK_SS0_PIN_USED)
        {
            /* Set output pin state after block is disabled */
            Debug_spi_ss0_Write(Debug_GET_UART_RTS_INACTIVE);

            /* Set GPIO to drive output pin */
            Debug_SET_HSIOM_SEL(Debug_SS0_HSIOM_REG, Debug_SS0_HSIOM_MASK,
                                           Debug_SS0_HSIOM_POS, Debug_HSIOM_GPIO_SEL);
        }
    #endif /* (Debug_SS0_PIN) */

#else
    #if (Debug_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        Debug_SET_HSIOM_SEL(Debug_TX_HSIOM_REG, Debug_TX_HSIOM_MASK,
                                       Debug_TX_HSIOM_POS, Debug_HSIOM_GPIO_SEL);
    #endif /* (Debug_UART_TX_PIN) */

    #if (Debug_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        Debug_rts_Write(Debug_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        Debug_SET_HSIOM_SEL(Debug_RTS_HSIOM_REG, Debug_RTS_HSIOM_MASK,
                                       Debug_RTS_HSIOM_POS, Debug_HSIOM_GPIO_SEL);
    #endif /* (Debug_UART_RTS_PIN) */

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (Debug_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    Debug_UART_RX_CTRL_REG &= (uint32) ~Debug_UART_RX_CTRL_SKIP_START;
#endif /* (Debug_UART_WAKE_ENABLE_CONST) */
}


/*******************************************************************************
* Function Name: Debug_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
* Parameters:
*  address: Address for hardware address detection.
*
* Return:
*  None
*
*******************************************************************************/
void Debug_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = Debug_RX_MATCH_REG;

    matchReg &= ((uint32) ~Debug_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & Debug_RX_MATCH_ADDR_MASK)); /* Set address  */

    Debug_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: Debug_UartSetRxAddressMask
********************************************************************************
*
* Summary:
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
* Parameters:
*  addressMask: Address mask.
*   0 - address bit does not care while comparison.
*   1 - address bit is significant while comparison.
*
* Return:
*  None
*
*******************************************************************************/
void Debug_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = Debug_RX_MATCH_REG;

    matchReg &= ((uint32) ~Debug_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << Debug_RX_MATCH_MASK_POS));

    Debug_RX_MATCH_REG = matchReg;
}


#if(Debug_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: Debug_UartGetChar
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *  This function is designed for ASCII characters and returns a char
    *  where 1 to 255 are valid characters and 0 indicates an error occurred or
    *  no data present.
    *  - The RX software buffer is disabled: returns the data element
    *    retrieved from the RX FIFO.
    *    Undefined data will be returned if the RX FIFO is empty.
    *  - The RX software buffer is enabled: returns the data element from
    *    the software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The next data element from the receive buffer.
    *  ASCII character values from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is enabled: The internal software buffer overflow
    *  does not treat as an error condition.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 Debug_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != Debug_SpiUartGetRxBufferSize())
        {
            rxData = Debug_SpiUartReadRxData();
        }

        if (Debug_CHECK_INTR_RX(Debug_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            Debug_ClearRxInterruptSource(Debug_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: Debug_UartGetByte
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Bits 7-0 contain the next data element from the receive buffer and
    *  other bits contain the error condition.
    *
    * Side Effects:
    *  The errors bits may not correspond with reading characters due to RX FIFO
    *  and software buffer usage.
    *  RX software buffer is disabled: The internal software buffer overflow
    *  is not returned as status by this function.
    *  Check SCB_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 Debug_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (Debug_CHECK_RX_SW_BUFFER)
        {
            Debug_DisableInt();
        }
        #endif

        if (0u != Debug_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (Debug_CHECK_RX_SW_BUFFER)
            {            
                Debug_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = Debug_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the case
            * of empty. Otherwise the first received byte will be read.
            */
            rxData = Debug_RX_FIFO_RD_REG;

            /* Enables interrupt to receive more bytes.
            * The RX_NOT_EMPTY interrupt is cleared by the interrupt routine
            * in case the byte was received and read by code above.
            */
            #if (Debug_CHECK_RX_SW_BUFFER)
            {
                Debug_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (Debug_GetRxInterruptSource() & Debug_INTR_RX_ERR);
        Debug_ClearRxInterruptSource(Debug_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: Debug_UartSetRtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of RTS output signal.
        *
        * Parameters:
        *  polarity: Active polarity of RTS output signal.
        *   Debug_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   Debug_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Debug_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                Debug_UART_FLOW_CTRL_REG |= (uint32)  Debug_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                Debug_UART_FLOW_CTRL_REG &= (uint32) ~Debug_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: Debug_UartSetRtsFifoLevel
        ********************************************************************************
        *
        * Summary:
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *
        * Parameters:
        *  level: Level in the RX FIFO for RTS signal activation.
        *         The range of valid level values is between 0 and RX FIFO depth - 1.
        *         Setting level value to 0 disables RTS signal activation.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Debug_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = Debug_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~Debug_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (Debug_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            Debug_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#endif /* (Debug_UART_RX_DIRECTION) */


#if(Debug_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: Debug_UartPutString
    ********************************************************************************
    *
    * Summary:
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  string: pointer to the null terminated string array to be placed in the
    *          transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Debug_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            Debug_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: Debug_UartPutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data followed by a carriage return (0x0D) and
    *  line feed (0x0A) into the transmit buffer.
    *  This function is blocking and waits until there is space available to put
    *  all the requested data into the  transmit buffer.
    *
    * Parameters:
    *  txDataByte : the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Debug_UartPutCRLF(uint32 txDataByte)
    {
        Debug_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        Debug_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        Debug_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: DebugSCB_UartEnableCts
        ********************************************************************************
        *
        * Summary:
        *  Enables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Debug_UartEnableCts(void)
        {
            Debug_UART_FLOW_CTRL_REG |= (uint32)  Debug_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Debug_UartDisableCts
        ********************************************************************************
        *
        * Summary:
        *  Disables usage of CTS input signal by the UART transmitter.
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Debug_UartDisableCts(void)
        {
            Debug_UART_FLOW_CTRL_REG &= (uint32) ~Debug_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: Debug_UartSetCtsPolarity
        ********************************************************************************
        *
        * Summary:
        *  Sets active polarity of CTS input signal.
        *
        * Parameters:
        *  polarity: Active polarity of CTS output signal.
        *   Debug_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   Debug_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void Debug_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                Debug_UART_FLOW_CTRL_REG |= (uint32)  Debug_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                Debug_UART_FLOW_CTRL_REG &= (uint32) ~Debug_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#endif /* (Debug_UART_TX_DIRECTION) */


#if(Debug_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: Debug_UartSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Clears and enables interrupt on a falling edge of the Rx input. The GPIO
    *  event wakes up the device and SKIP_START feature allows the UART continue
    *  receiving data bytes properly. The GPIO interrupt does not track in the
    *  active mode therefore requires to be cleared by this API.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Debug_UartSaveConfig(void)
    {
        /* Clear interrupt activity:
        *  - set skip start and disable RX. At GPIO wakeup RX will be enabled.
        *  - clear rx_wake interrupt source as it triggers during normal operation.
        *  - clear wake interrupt pending state as it becomes pending in active mode.
        */

        Debug_UART_RX_CTRL_REG |= Debug_UART_RX_CTRL_SKIP_START;

    #if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Debug_MOSI_SCL_RX_WAKE_PIN)
            (void) Debug_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (Debug_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Debug_UART_RX_WAKE_PIN)
            (void) Debug_rx_wake_ClearInterrupt();
        #endif /* (Debug_UART_RX_WAKE_PIN) */
    #endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

    #if(Debug_UART_RX_WAKEUP_IRQ)
        Debug_RxWakeClearPendingInt();
        Debug_RxWakeEnableInt();
    #endif /* (Debug_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: Debug_UartRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void Debug_UartRestoreConfig(void)
    {
    /* Disable RX GPIO interrupt: no more triggers in active mode */
    #if(Debug_UART_RX_WAKEUP_IRQ)
        Debug_RxWakeDisableInt();
    #endif /* (Debug_UART_RX_WAKEUP_IRQ) */
    }
#endif /* (Debug_UART_WAKE_ENABLE_CONST) */


#if(Debug_UART_RX_WAKEUP_IRQ)
    /*******************************************************************************
    * Function Name: Debug_UART_WAKEUP_ISR
    ********************************************************************************
    *
    * Summary:
    *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
    *  event. This event is configured to trigger on a falling edge of the RX line.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    CY_ISR(Debug_UART_WAKEUP_ISR)
    {
    #ifdef Debug_UART_WAKEUP_ISR_ENTRY_CALLBACK
        Debug_UART_WAKEUP_ISR_EntryCallback();
    #endif /* Debug_UART_WAKEUP_ISR_ENTRY_CALLBACK */

        /* Clear interrupt source: the event becomes multi triggered and is
        * only disabled by Debug_UartRestoreConfig() call.
        */
    #if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
        #if(Debug_MOSI_SCL_RX_WAKE_PIN)
            (void) Debug_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt();
        #endif /* (Debug_MOSI_SCL_RX_WAKE_PIN) */
    #else
        #if(Debug_UART_RX_WAKE_PIN)
            (void) Debug_rx_wake_ClearInterrupt();
        #endif /* (Debug_UART_RX_WAKE_PIN) */
    #endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */

    #ifdef Debug_UART_WAKEUP_ISR_EXIT_CALLBACK
        Debug_UART_WAKEUP_ISR_ExitCallback();
    #endif /* Debug_UART_WAKEUP_ISR_EXIT_CALLBACK */
    }
#endif /* (Debug_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
