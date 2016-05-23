/*!
 *  @file        spi.c
 *  @brief       SPI comunication
 *  @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "data.h"
#include "handler.h"
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

void spi_rx()
{
    char lcd[12];
    uint16 spiRxBuffer[SPI_PACKET_SIZE];
    struct Data spiRxAction;
    
    spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
    if(spiRxBuffer[SPI_PACKET_DATA_POS] > 0)
    {
        spiRxAction.val_ = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
        spiRxAction.cmd_ = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
        pushQueue(spiRxAction);
        
        sprintf(lcd, ">S %4x %2x %1d", (int)spiRxAction.cmd_, (int)spiRxAction.cmd_, queueCount_);
        lcd_newline(lcd);
        
        DEBUG_PutString(">S: cmd: ");
        DEBUG_PutHexByte(spiRxAction.cmd_);
        DEBUG_PutString(" val: ");
        DEBUG_PutHexByte(spiRxAction.val_);
        DEBUG_PutCRLF();
    }
    SPIS_SpiUartClearRxBuffer();
}

/*!
 *  @brief      ISR for SPI slave rx
 *  @public
 *  @memberof   Spi
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
CY_ISR(isr_spi_rx)
{
    SPIS_DisableInt();
    char lcd[12];
    uint16 spiRxBuffer[SPI_PACKET_SIZE];
    uint16 spiTxBuffer[SPI_PACKET_SIZE];
    struct Data spiRxAction;
    
    while(SPIS_SpiUartGetRxBufferSize() > 0)
    {
        spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
        spiRxAction.val_ = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
        spiRxAction.cmd_ = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
        
        if(spiRxBuffer[SPI_PACKET_DATA_POS] == 0xBADA)
        {
            sprintf(lcd, "S> %x",spiTxBuffer[SPI_PACKET_DATA_POS]);
            lcd_newline(lcd);
            
            DEBUG_PutString("S>: val: ");
            DEBUG_PutHexByte(spiTxBuffer[SPI_PACKET_DATA_POS]);
            DEBUG_PutCRLF();
        }
        else
        {
            sprintf(lcd, ">S %4x %2x %1d", (int)spiRxAction.cmd_, (int)spiRxAction.val_, queueCount_);
            lcd_newline(lcd);
            
            DEBUG_PutString(">S: cmd: ");
            DEBUG_PutHexByte(spiRxAction.cmd_);
            DEBUG_PutString(" val: ");
            DEBUG_PutHexByte(spiRxAction.val_);
            DEBUG_PutCRLF();
            DEBUG_PutCRLF();
            
            switch(spiRxAction.cmd_) {
                case CMD_GET_X_POS :
                    SPIS_SpiUartClearTxBuffer();
                    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16)dataMaster.xVal;
                    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
                    break;
                case CMD_GET_Y_POS :
                    SPIS_SpiUartClearTxBuffer();
                    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16)dataMaster.yVal;
                    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
                    break;
                case CMD_GET_Z_POS :
                    SPIS_SpiUartClearTxBuffer();
                    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16)dataMaster.zVal;
                    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
                    break;
                case CMD_GET_RED_VAL :
                    SPIS_SpiUartClearTxBuffer();
                    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16)dataMaster.rVal;
                    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
                    break;
                case CMD_GET_GREEN_VAL :
                    SPIS_SpiUartClearTxBuffer();
                    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16)dataMaster.gVal;
                    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
                    break;
                case CMD_GET_BLUE_VAL :
                    SPIS_SpiUartClearTxBuffer();
                    spiTxBuffer[SPI_PACKET_DATA_POS] = (uint16)dataMaster.bVal;
                    SPIS_SpiUartPutArray(spiTxBuffer, SPI_PACKET_SIZE);
                    break;
                default :
                    pushQueue(spiRxAction);
                break;
            }
        }
    }

    SPIS_ClearRxInterruptSource(SPIS_GetRxInterruptSource());
    SPIS_EnableInt();
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