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
    SPIS_SpiUartClearTxBuffer();
    SPIS_SpiUartClearRxBuffer();
    SPIS_Start();
}

void spi_rx()
{
    uint16 spiRxBuffer[SPI_PACKET_SIZE];
    struct Data spiRxAction;

//    while (SPI_PACKET_SIZE != SPIS_SpiUartGetRxBufferSize())
//    {
//    }
    
    if (0u != SPIS_SpiUartGetRxBufferSize())
    {
        spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
        spiRxAction.val_ = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
        spiRxAction.cmd_ = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
        pushQueue(spiRxAction);
    }
//    if ((spiBuffer[SPI_PACKET_SOP_POS] == SPI_PACKET_SOP) && (spiBuffer[SPI_PACKET_EOP_POS] == SPI_PACKET_EOP))
//    {

//    }
//    else
//    {
//        
//    }
}

//void spi_wait()
//{
//    uint32 i;
//    struct Data spiRxData;
//    uint16 spiBuffer[SPI_PACKET_SIZE];
//
//    while (SPI_PACKET_SIZE != SPIS_SpiUartGetRxBufferSize())
//    {
//    }
//    
//    i = 0u;
//    while (0u != SPIS_SpiUartGetRxBufferSize())
//    {
//        spiBuffer[i] = SPIS_SpiUartReadRxData();
//        i++;
//    }
//    if ((spiBuffer[SPI_PACKET_SOP_POS] == SPI_PACKET_SOP) && (spiBuffer[SPI_PACKET_EOP_POS] == SPI_PACKET_EOP))
//    {
//        spiRxData.val_ = spiBuffer[SPI_PACKET_DATA_POS] & 0xff;
//        spiRxData.cmd_ = (spiBuffer[SPI_PACKET_DATA_POS] >> 8);
//        pushQueue(spiRxData);
//    }
//    else
//    {
//        
//    }
//}

void spi_cleanup()
{
    uint16 dummyBuffer[1] = {SPI_STS_CMD_FAIL};
    if (SPI_PACKET_SIZE = SPIS_SpiUartGetRxBufferSize())
    {
        SPIS_SpiUartClearRxBuffer();

        SPIS_SpiUartPutArray(dummyBuffer, SPI_PACKET_SIZE);
    }
}

void spi_tx(uint8 data)
{
    uint16 spiTxBuffer[SPI_PACKET_SIZE] = {SPI_STS_CMD_FAIL};

    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16) data;

    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
}

//static void spi_update(uint16 data)
//{
//    static uint16 sTxBuffer[SPI_PACKET_SIZE] = {SPI_PACKET_SOP, SPI_STS_CMD_FAIL, SPI_PACKET_EOP};
//
//    sTxBuffer[SPI_PACKET_DATA_POS] = data;
//
//    SPIS_SpiUartPutArray(sTxBuffer, SPI_PACKET_SIZE);
//}

//void spi_rx()
//{
//    while(SPIS_SpiUartGetRxBufferSize() > 0)
//    {
//        
//        
//        spiRxBuffer = SPIS_SpiUartReadRxData();
//        
//        spiRxData.val_ = spiRxBuffer & 0xff;
//        spiRxData.cmd_ = (spiRxBuffer >> 8);
//        
//        pushQueue(spiRxData);
//        
//    }
//    SPIS_SpiUartClearRxBuffer();
//}
//
//void spi_tx(uint8 txVal)
//{
//
//}

/* [] END OF FILE */