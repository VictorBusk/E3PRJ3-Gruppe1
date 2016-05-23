/*!
 * @file        i2c.c
 * @brief       I2C comunication
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "lcd.h"
#include <stdio.h>

uint8 i2c_slaveBuffer[I2C_BUFFER_SIZE];

/*!
 *  @brief      Initialize I2C master.
 *  @public
 *  @memberof   I2c
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void i2c_init()
{
    I2CM_scl_SetDriveMode(I2CM_scl_DM_RES_UP);
    I2CM_sda_SetDriveMode(I2CM_sda_DM_RES_UP);
  
    I2CM_I2CSlaveInitWriteBuf(i2c_slaveBuffer, I2C_BUFFER_SIZE);
    I2CM_I2CSlaveClearWriteBuf();
    I2CM_I2CSlaveClearWriteStatus();
    
    I2CM_Start();
}

void i2c_setPacket(uint8 i2cAddr, uint8 i2cCmd, uint8 i2cVal)
{
    int status;
    char lcd[12];
  if(i2c_tx(i2cAddr, i2cCmd, i2cVal) == I2C_STS_CMD_DONE)
  {
    status = 1;
    setLed(0,0,1,50);
  }
  else
  {
    status = 0;
    setLed(1,0,0,50);
  }
  sprintf(lcd, "I>%2.1x %2.2x %2.2x %1.1d", (int)i2cAddr, (int)i2cCmd, (int)i2cVal, status);
  lcd_newline(lcd);
  setLed(0,0,0,50);
}

void i2c_getPacket(uint8 i2cAddr, uint8 i2cCmd, uint8* i2cVal)
{
  int status;
  uint8 i2cTxSTS;
  uint8 i2cRxCmd;
  char lcd[12];
  
  i2cTxSTS = i2c_tx(i2cAddr, i2cCmd, *i2cVal);
  if(i2cTxSTS == I2C_STS_CMD_DONE)
  {
    status = 1;
    setLed(0,0,1,50);
  }
  else
  {
    status = 0;
    setLed(1,0,0,50);
  }
  sprintf(lcd, "I> %1.1x %2.2x %2.2x %1.1d", (int)i2cAddr, (int)i2cCmd, (int)i2cVal, status);
  lcd_newline(lcd);

  i2c_rx(i2cAddr, &i2cRxCmd, i2cVal);
  if(i2cRxCmd == i2cCmd)
  {
    status = 1;
    setLed(0,1,0,50);
  }
  else
  {
    status = 0;
    setLed(1,0,0,50);
  }
  setLed(0,0,0,50);
  sprintf(lcd, ">I %1.1x %2.2x %2.2x %1.1d", (int)i2cAddr, (int)i2cCmd, (int)i2cVal, status);
  lcd_newline(lcd);
}

/*!
 *  @brief      Transmit I2C packet.
 *  @param[in]  i2cTxAddr I2C address on reciver.
 *  @param[in]  i2cTxCmd I2C command to reciver.
 *  @param[in]  i2cTxVal I2C value to reciver.
 *  @public
 *  @memberof   I2c
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
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

/*!
 *  @brief      Recive I2C packet.
 *  @param[in]  i2cRxAddr I2C address on sender.
 *  @param[in]  i2cRxCmd I2C command from sender.
 *  @param[out] i2cRxVal I2C value from sender.
 *  @public
 *  @memberof   I2c
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
uint8 i2c_rx(uint8 i2cRxAddr, uint8* i2cRxCmd, uint8* i2cRxVal)
{
    uint8 i2cRxStatus = I2C_STS_CMD_FAIL;
    uint8 i2cRxData[I2C_PACKET_SIZE];

    (void) I2CM_I2CMasterReadBuf(i2cRxAddr, i2cRxData, I2C_PACKET_SIZE, I2CM_I2C_MODE_COMPLETE_XFER);
     while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_RD_CMPLT))
    {
    }
    if (0u == (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))
    {
        if ((I2CM_I2CMasterGetReadBufSize() == I2C_BUFFER_SIZE))
        {
            if((i2cRxData[I2C_PACKET_SOP_POS] == I2C_PACKET_SOP) && (i2cRxData[I2C_PACKET_EOP_POS] == I2C_PACKET_EOP))
            {
                *i2cRxCmd = i2cRxData[I2C_PACKET_CMD_POS];
                *i2cRxVal = i2cRxData[I2C_PACKET_VAL_POS];
                i2cRxStatus = i2cRxData[I2C_PACKET_CMD_POS];
            }
        }
    }
    (void) I2CM_I2CMasterClearStatus();
  
    return i2cRxStatus;
}

/* [] END OF FILE */