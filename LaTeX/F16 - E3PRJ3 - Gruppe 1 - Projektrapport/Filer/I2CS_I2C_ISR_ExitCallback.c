void I2CS_I2C_ISR_ExitCallback()
{
	if(I2CS_I2CSlaveGetWriteBufSize() == I2C_BUFFER_SIZE)
	{
		struct Data action;
		action.cmd_ = i2cRxBuffer[I2C_PACKET_CMD_POS];
		action.val_ = i2cRxBuffer[I2C_PACKET_VAL_POS];
		
		switch(i2cRxBuffer[I2C_PACKET_CMD_POS]) {
			case CMD_SET_X_POS :
			dataXY.isrStopX = 1;
			pushQueue(action);
			break;
			case CMD_SET_Y_POS :
			dataXY.isrStopY = 1;
			pushQueue(action);
			break;
			default :
			pushQueue(action);
			break;
		}
		I2CS_I2CSlaveClearWriteBuf();
		(void) I2CS_I2CSlaveClearWriteStatus();
	}
}
