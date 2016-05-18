/*******************************************************************************
* File Name: Debug_SPI_UART.c
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

#include "Debug_PVT.h"
#include "Debug_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(Debug_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 Debug_rxBufferHead;
    volatile uint32 Debug_rxBufferTail;
    volatile uint8  Debug_rxBufferOverflow;
#endif /* (Debug_INTERNAL_RX_SW_BUFFER_CONST) */

#if(Debug_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 Debug_txBufferHead;
    volatile uint32 Debug_txBufferTail;
#endif /* (Debug_INTERNAL_TX_SW_BUFFER_CONST) */

#if(Debug_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 Debug_rxBufferInternal[Debug_INTERNAL_RX_BUFFER_SIZE];
#endif /* (Debug_INTERNAL_RX_SW_BUFFER) */

#if(Debug_INTERNAL_TX_SW_BUFFER)
    volatile uint8 Debug_txBufferInternal[Debug_TX_BUFFER_SIZE];
#endif /* (Debug_INTERNAL_TX_SW_BUFFER) */


#if(Debug_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: Debug_SpiUartReadRxData
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
    *  Look into Debug_SpiInit for description.
    *
    *******************************************************************************/
    uint32 Debug_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (Debug_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (Debug_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (Debug_CHECK_RX_SW_BUFFER)
        {
            if (Debug_rxBufferHead != Debug_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (Debug_rxBufferTail + 1u);

                if (Debug_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = Debug_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                Debug_rxBufferTail = locTail;

                #if (Debug_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (Debug_INTR_RX_MASK_REG & Debug_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        Debug_INTR_RX_MASK_REG |= Debug_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = Debug_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: Debug_SpiUartGetRxBufferSize
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
    uint32 Debug_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (Debug_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (Debug_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (Debug_CHECK_RX_SW_BUFFER)
        {
            locHead = Debug_rxBufferHead;

            if(locHead >= Debug_rxBufferTail)
            {
                size = (locHead - Debug_rxBufferTail);
            }
            else
            {
                size = (locHead + (Debug_INTERNAL_RX_BUFFER_SIZE - Debug_rxBufferTail));
            }
        }
        #else
        {
            size = Debug_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: Debug_SpiUartClearRxBuffer
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
    void Debug_SpiUartClearRxBuffer(void)
    {
        #if (Debug_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            Debug_DisableInt();

            /* Flush RX software buffer */
            Debug_rxBufferHead = Debug_rxBufferTail;
            Debug_rxBufferOverflow = 0u;

            Debug_CLEAR_RX_FIFO;
            Debug_ClearRxInterruptSource(Debug_INTR_RX_ALL);

            #if (Debug_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                Debug_INTR_RX_MASK_REG |= Debug_INTR_RX_NOT_EMPTY;
            }
            #endif

            /* Release lock */
            Debug_EnableInt();
        }
        #else
        {
            Debug_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (Debug_RX_DIRECTION) */


#if(Debug_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: Debug_SpiUartWriteTxData
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
    void Debug_SpiUartWriteTxData(uint32 txData)
    {
    #if (Debug_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (Debug_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (Debug_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((Debug_txBufferHead == Debug_txBufferTail) &&
                (Debug_SPI_UART_FIFO_SIZE != Debug_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                Debug_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (Debug_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (Debug_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == Debug_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                Debug_ClearTxInterruptSource(Debug_INTR_TX_NOT_FULL);

                Debug_PutWordInTxBuffer(locHead, txData);

                Debug_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (Debug_INTR_TX_MASK_REG & Debug_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    Debug_INTR_TX_MASK_REG |= (uint32) Debug_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (Debug_SPI_UART_FIFO_SIZE == Debug_GET_TX_FIFO_ENTRIES)
            {
            }

            Debug_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: Debug_SpiUartPutArray
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
    void Debug_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            Debug_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: Debug_SpiUartGetTxBufferSize
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
    uint32 Debug_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (Debug_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (Debug_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (Debug_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = Debug_txBufferTail;

            if (Debug_txBufferHead >= locTail)
            {
                size = (Debug_txBufferHead - locTail);
            }
            else
            {
                size = (Debug_txBufferHead + (Debug_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = Debug_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: Debug_SpiUartClearTxBuffer
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
    void Debug_SpiUartClearTxBuffer(void)
    {
        #if (Debug_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            Debug_DisableInt();

            /* Flush TX software buffer */
            Debug_txBufferHead = Debug_txBufferTail;

            Debug_INTR_TX_MASK_REG &= (uint32) ~Debug_INTR_TX_NOT_FULL;
            Debug_CLEAR_TX_FIFO;
            Debug_ClearTxInterruptSource(Debug_INTR_TX_ALL);

            /* Release lock */
            Debug_EnableInt();
        }
        #else
        {
            Debug_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (Debug_TX_DIRECTION) */


/*******************************************************************************
* Function Name: Debug_SpiUartDisableIntRx
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
uint32 Debug_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = Debug_GetRxInterruptMode();

    Debug_SetRxInterruptMode(Debug_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: Debug_SpiUartDisableIntTx
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
uint32 Debug_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = Debug_GetTxInterruptMode();

    Debug_SetTxInterruptMode(Debug_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Debug_PutWordInRxBuffer
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
    void Debug_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (Debug_ONE_BYTE_WIDTH == Debug_rxDataBits)
        {
            Debug_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            Debug_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            Debug_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: Debug_GetWordFromRxBuffer
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
    uint32 Debug_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (Debug_ONE_BYTE_WIDTH == Debug_rxDataBits)
        {
            value = Debug_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) Debug_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)Debug_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: Debug_PutWordInTxBuffer
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
    void Debug_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (Debug_ONE_BYTE_WIDTH == Debug_txDataBits)
        {
            Debug_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            Debug_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            Debug_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: Debug_GetWordFromTxBuffer
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
    uint32 Debug_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (Debug_ONE_BYTE_WIDTH == Debug_txDataBits)
        {
            value = (uint32) Debug_txBuffer[idx];
        }
        else
        {
            value  = (uint32) Debug_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) Debug_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
