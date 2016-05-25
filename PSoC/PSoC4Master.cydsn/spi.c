/*!
 *  @file       spi.c
 *  @brief      SPI modul
 *  @details    Håndter kommunikation via SPI-busset
 *  @ingroup    master
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "data.h"
#include "handler.h"
#include "spi.h"
#include "queue.h"
#include "lcd.h"
#include <stdio.h>

/***************************************
 *       Public methods
 ***************************************/

/*!
 *  @brief      Initialiser SPI modulet.
 *  @details    Initailiser SPI komponent på PSoC'en og sætter "Custom Interrupt Handler".
 *  @ingroup    master
 *  @public
 *  @memberof   SPIMaster
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
 *  @brief      Modtager kald fra SPI-busset
 *  @details    En "Interrupt Service Routine(ISR)" der aktiveres ved modtagelse af kald via SPI-busset, det modtaget data behandles og håndteres.
 *  @ingroup    master
 *  @public
 *  @memberof   SPIMaster
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
CY_ISR(isr_spi_rx)
{
  SPIS_DisableInt();
  char lcd[12];
  uint16 spiRxBuffer[SPI_PACKET_SIZE];
  uint16 spiTxBuffer[SPI_PACKET_SIZE];
  struct Action spiRxAction;
  
  while(SPIS_SpiUartGetRxBufferSize() > 0)
  {
    spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
    spiRxAction.val = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
    spiRxAction.cmd = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
    
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
      sprintf(lcd, ">S %4x %2x", (int)spiRxAction.cmd_, (int)spiRxAction.val_);
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
  
  SPIS_SpiUartClearRxBuffer();
  SPIS_ClearRxInterruptSource(SPIS_GetRxInterruptSource());
  SPIS_EnableInt();
}

/* [] END OF FILE */