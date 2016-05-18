/*******************************************************************************
* File Name: SPIS_SPI_UART.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIS_PVT.h"
#include "SPIS_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(SPIS_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 SPIS_rxBufferHead;
    volatile uint32 SPIS_rxBufferTail;
    volatile uint8  SPIS_rxBufferOverflow;
#endif /* (SPIS_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SPIS_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 SPIS_txBufferHead;
    volatile uint32 SPIS_txBufferTail;
#endif /* (SPIS_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SPIS_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint16 SPIS_rxBufferInternal[SPIS_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SPIS_INTERNAL_RX_SW_BUFFER) */

#if(SPIS_INTERNAL_TX_SW_BUFFER)
    volatile uint16 SPIS_txBufferInternal[SPIS_TX_BUFFER_SIZE];
#endif /* (SPIS_INTERNAL_TX_SW_BUFFER) */


#if(SPIS_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: SPIS_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into SPIS_SpiInit for description.
    *
    *******************************************************************************/
    uint32 SPIS_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (SPIS_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SPIS_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SPIS_CHECK_RX_SW_BUFFER)
        {
            if (SPIS_rxBufferHead != SPIS_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (SPIS_rxBufferTail + 1u);

                if (SPIS_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = SPIS_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                SPIS_rxBufferTail = locTail;

                #if (SPIS_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (SPIS_INTR_RX_MASK_REG & SPIS_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        SPIS_INTR_RX_MASK_REG |= SPIS_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = SPIS_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: SPIS_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 SPIS_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (SPIS_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SPIS_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SPIS_CHECK_RX_SW_BUFFER)
        {
            locHead = SPIS_rxBufferHead;

            if(locHead >= SPIS_rxBufferTail)
            {
                size = (locHead - SPIS_rxBufferTail);
            }
            else
            {
                size = (locHead + (SPIS_INTERNAL_RX_BUFFER_SIZE - SPIS_rxBufferTail));
            }
        }
        #else
        {
            size = SPIS_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SPIS_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_SpiUartClearRxBuffer(void)
    {
        #if (SPIS_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SPIS_DisableInt();

            /* Flush RX software buffer */
            SPIS_rxBufferHead = SPIS_rxBufferTail;
            SPIS_rxBufferOverflow = 0u;

            SPIS_CLEAR_RX_FIFO;
            SPIS_ClearRxInterruptSource(SPIS_INTR_RX_ALL);

            #if (SPIS_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                SPIS_INTR_RX_MASK_REG |= SPIS_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            SPIS_EnableInt();
        }
        #else
        {
            SPIS_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (SPIS_RX_DIRECTION) */


#if(SPIS_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: SPIS_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_SpiUartWriteTxData(uint32 txData)
    {
    #if (SPIS_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SPIS_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SPIS_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((SPIS_txBufferHead == SPIS_txBufferTail) &&
                (SPIS_SPI_UART_FIFO_SIZE != SPIS_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                SPIS_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (SPIS_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (SPIS_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == SPIS_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                SPIS_ClearTxInterruptSource(SPIS_INTR_TX_NOT_FULL);

                SPIS_PutWordInTxBuffer(locHead, txData);

                SPIS_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (SPIS_INTR_TX_MASK_REG & SPIS_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    SPIS_INTR_TX_MASK_REG |= (uint32) SPIS_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (SPIS_SPI_UART_FIFO_SIZE == SPIS_GET_TX_FIFO_ENTRIES)
            {
            }

            SPIS_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: SPIS_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_SpiUartPutArray(const uint16 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            SPIS_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: SPIS_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    * Returns the number of elements currently in the transmit buffer.
    *  - TX software buffer is disabled: returns the number of used entries in
    *    TX FIFO.
    *  - TX software buffer is enabled: returns the number of elements currently
    *    used in the transmit buffer. This number does not include used entries in
    *    the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *    not full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 SPIS_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (SPIS_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SPIS_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SPIS_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = SPIS_txBufferTail;

            if (SPIS_txBufferHead >= locTail)
            {
                size = (SPIS_txBufferHead - locTail);
            }
            else
            {
                size = (SPIS_txBufferHead + (SPIS_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = SPIS_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SPIS_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_SpiUartClearTxBuffer(void)
    {
        #if (SPIS_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SPIS_DisableInt();

            /* Flush TX software buffer */
            SPIS_txBufferHead = SPIS_txBufferTail;

            SPIS_INTR_TX_MASK_REG &= (uint32) ~SPIS_INTR_TX_NOT_FULL;
            SPIS_CLEAR_TX_FIFO;
            SPIS_ClearTxInterruptSource(SPIS_INTR_TX_ALL);

            /* Release lock */
            SPIS_EnableInt();
        }
        #else
        {
            SPIS_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (SPIS_TX_DIRECTION) */


/*******************************************************************************
* Function Name: SPIS_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables the RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 SPIS_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = SPIS_GetRxInterruptMode();

    SPIS_SetRxInterruptMode(SPIS_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: SPIS_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 SPIS_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = SPIS_GetTxInterruptMode();

    SPIS_SetTxInterruptMode(SPIS_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SPIS_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (SPIS_ONE_BYTE_WIDTH == SPIS_rxDataBits)
        {
            SPIS_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            SPIS_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            SPIS_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SPIS_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 SPIS_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (SPIS_ONE_BYTE_WIDTH == SPIS_rxDataBits)
        {
            value = SPIS_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) SPIS_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)SPIS_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: SPIS_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (SPIS_ONE_BYTE_WIDTH == SPIS_txDataBits)
        {
            SPIS_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            SPIS_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            SPIS_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SPIS_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 SPIS_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (SPIS_ONE_BYTE_WIDTH == SPIS_txDataBits)
        {
            value = (uint32) SPIS_txBuffer[idx];
        }
        else
        {
            value  = (uint32) SPIS_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) SPIS_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
