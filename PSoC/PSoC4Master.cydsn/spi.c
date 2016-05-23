/*!
 *  @file        spi.c
 *  @brief       SPI comunication
 *  @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "spi.h"
#include "queue.h"
#include "lcd.h"
#include <stdio.h>

/*!
 *  @brief      Initialize SPI slave
 *  @public
 *  @memberof   Spi
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void spi_init()
{
    SPIS_SpiUartClearTxBuffer();
    SPIS_SpiUartClearRxBuffer();
    SPIS_SetCustomInterruptHandler(isr_spi_rx);
  
    SPIS_Start();
}

/*!
 *  @brief      ISR for SPI slave rx
 *  @public
 *  @memberof   Spi
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
CY_ISR(isr_spi_rx)
{
    char lcd[12];
    uint16 spiRxBuffer[SPI_PACKET_SIZE];
    struct Data spiRxAction;
    
//    while (SPI_PACKET_SIZE != SPIS_SpiUartGetRxBufferSize())
//    {
//    }
    
//    if (SPI_PACKET_SIZE == SPIS_SpiUartGetRxBufferSize())
//    {
    
    spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
    if(spiRxBuffer[SPI_PACKET_DATA_POS] > 0)
    {
        spiRxAction.val_ = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
        spiRxAction.cmd_ = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
        pushQueue(spiRxAction);
        
        sprintf(lcd, ">S %4x %2x", (int)spiRxAction.cmd_, (int)spiRxAction.cmd_);
        lcd_newline(lcd);
    }    
//    }
//    
//    uint16 dummyBuffer[SPI_PACKET_SIZE] = {SPI_STS_CMD_FAIL};
//    if (SPI_PACKET_SIZE == SPIS_SpiUartGetRxBufferSize())
//    {
//        SPIS_SpiUartClearRxBuffer();
//
//        SPIS_SpiUartPutArray(dummyBuffer, SPI_PACKET_SIZE);
//    }
    SPIS_ClearRxInterruptSource(SPIS_GetRxInterruptSource());
}

/*!
 *  @brief      Update tx buffer for SPI slave.
 *  @param      data Data to bre sent.
 *  @public
 *  @memberof   Spi
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void spi_tx(uint8 data)
{
    SPIS_SpiUartClearTxBuffer();
    
    uint16 spiTxBuffer[SPI_PACKET_SIZE] = {SPI_STS_CMD_FAIL};

    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16) data;

    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
}

/* [] END OF FILE */