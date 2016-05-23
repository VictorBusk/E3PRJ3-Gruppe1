/* ========================================
 *
 * File: i2c.c
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

#include "i2c.h"
#include "data.h"
#include "led.h"
#include "queue.h"

uint8 i2cTxBuffer[I2C_BUFFER_SIZE] = {I2C_PACKET_SOP, I2C_STS_CMD_FAIL, I2C_STS_CMD_FAIL, I2C_PACKET_EOP};
uint8 i2cRxBuffer[I2C_BUFFER_SIZE];

void i2c_init()
{
    I2CS_I2CSlaveInitReadBuf(i2cTxBuffer, I2C_BUFFER_SIZE);
    I2CS_I2CSlaveClearReadBuf();
    I2CS_I2CSlaveClearReadStatus();
    
    I2CS_I2CSlaveInitWriteBuf(i2cRxBuffer, I2C_BUFFER_SIZE);
    I2CS_I2CSlaveClearWriteBuf();
    I2CS_I2CSlaveClearWriteStatus();
    
    I2CS_Start();
}

void i2c_rx()
{
  if(0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_WR_CMPLT))
  {
    setLed(0,0,1);
    if(I2C_BUFFER_SIZE == I2CS_I2CSlaveGetWriteBufSize())
    {
      if((i2cRxBuffer[I2C_PACKET_SOP_POS] == I2C_PACKET_SOP) && (i2cRxBuffer[I2C_PACKET_EOP_POS] == I2C_PACKET_EOP))
      {
        setLed(0,1,0);
        struct Data action;
        
        action.cmd_ = i2cRxBuffer[I2C_PACKET_CMD_POS];
        action.val_ = i2cRxBuffer[I2C_PACKET_VAL_POS];
        
        pushQueue(action);
      }
      else
      {
        setLed(1,0,0);
      }
    }
    I2CS_I2CSlaveClearWriteBuf();
    (void) I2CS_I2CSlaveClearWriteStatus();
    setLed(0,0,0);
  }
}

void i2c_tx()
{
    if(0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_RD_CMPLT))
    {
        I2CS_I2CSlaveClearReadBuf();
        (void) I2CS_I2CSlaveClearReadStatus();   
    }   
}

/* [] END OF FILE */
