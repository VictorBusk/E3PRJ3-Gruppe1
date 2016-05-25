CY_ISR(isr_spi_rx)
{
	SPIS_DisableInt();
	uint16 spiRxBuffer[SPI_PACKET_SIZE];
	uint16 spiTxBuffer[SPI_PACKET_SIZE];
	struct Data spiRxAction;
	
	while(SPIS_SpiUartGetRxBufferSize() > 0)
	{
		spiRxBuffer[SPI_PACKET_DATA_POS] = SPIS_SpiUartReadRxData();
		spiRxAction.val_ = spiRxBuffer[SPI_PACKET_DATA_POS] & 0xff;
		spiRxAction.cmd_ = (spiRxBuffer[SPI_PACKET_DATA_POS] >> 8);
		
		if(spiRxBuffer[SPI_PACKET_DATA_POS] != 0xBADA)
		{
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