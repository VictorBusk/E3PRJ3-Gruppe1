/* ========================================
 *
 * File: spi.c
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: Jeppe Stærk
 * Matriculation number: 201271201
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

#include "spi.h"

void spi_init()
{
    SPIS_Start();
    SPIS_SpiUartClearTxBuffer();
    SPIS_SpiUartClearRxBuffer();
    SPIS_SetCustomInterruptHandler(isr_spi_rx);
}

CY_ISR(isr_spi_rx)
{
    uint16 spiRxBuffer[SPI_PACKET_SIZE];
    struct Data spiRxAction;
    
    while (SPI_PACKET_SIZE != SPIS_SpiUartGetRxBufferSize())
    {
    }
    
    if (0u != SPIS_SpiUartGetRxBufferSize())
    {
        spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
        spiRxAction.val_ = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
        spiRxAction.cmd_ = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
        pushQueue(spiRxAction);
    }
    
    uint16 dummyBuffer[1] = {SPI_STS_CMD_FAIL};
    if (SPI_PACKET_SIZE == SPIS_SpiUartGetRxBufferSize())
    {
        SPIS_SpiUartClearRxBuffer();

        SPIS_SpiUartPutArray(dummyBuffer, SPI_PACKET_SIZE);
    }
    SPIS_ClearRxInterruptSource(SPIS_GetRxInterruptSource());
}

void spi_tx(uint8 data)
{
    SPIS_SpiUartClearTxBuffer();
    
    uint16 spiTxBuffer[SPI_PACKET_SIZE] = {SPI_STS_CMD_FAIL};

    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16) data;

    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
}

/* [] END OF FILE */