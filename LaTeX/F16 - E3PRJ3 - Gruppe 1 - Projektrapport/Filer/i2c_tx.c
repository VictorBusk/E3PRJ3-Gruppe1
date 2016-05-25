uint8 i2c_tx(uint8 i2cAddr, uint8 i2cCmd, uint8 i2cVal)
{
	uint8 i2cTxStatus = I2C_STS_CMD_FAIL;
	uint8 i2cTxData[I2C_PACKET_SIZE];
	
	i2cTxData[I2C_PACKET_SOP_POS] = I2C_PACKET_SOP;
	i2cTxData[I2C_PACKET_CMD_POS] = i2cCmd;
	i2cTxData[I2C_PACKET_VAL_POS] = i2cVal;
	i2cTxData[I2C_PACKET_EOP_POS] = I2C_PACKET_EOP;
	
	(void) I2CM_I2CMasterWriteBuf(i2cAddr, i2cTxData, I2C_PACKET_SIZE, I2CM_I2C_MODE_COMPLETE_XFER);
	while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_WR_CMPLT))
	{
	}
	if (0u == (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))
	{
		if (I2CM_I2CMasterGetWriteBufSize() == I2C_BUFFER_SIZE)
		{
			i2cTxStatus = I2C_STS_CMD_DONE;
		}
	}
	(void) I2CM_I2CMasterClearStatus();
	
	return i2cTxStatus;
}