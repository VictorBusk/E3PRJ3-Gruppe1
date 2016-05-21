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
#include "led.h"
#include "queue.h"

uint8 i2c_slaveBuffer[I2C_BUFFER_SIZE];

void i2c_init()
{
    I2CM_scl_SetDriveMode(I2CM_scl_DM_RES_UP);
    I2CM_sda_SetDriveMode(I2CM_sda_DM_RES_UP);
    
    I2CM_I2CSlaveInitWriteBuf(i2c_slaveBuffer, I2C_BUFFER_SIZE);
    I2CM_I2CSlaveClearWriteBuf();
    I2CM_I2CSlaveClearWriteStatus();
    
    I2CM_Start();
}

void i2c_tx(uint8 i2cTxAddr, uint8 i2cTxCmd, uint8 i2cTxVal)
{
    uint8 i2cTxData[I2C_PACKET_SIZE];

    i2cTxData[I2C_PACKET_SOP_POS] = I2C_PACKET_SOP;
    i2cTxData[I2C_PACKET_CMD_POS] = i2cTxCmd;
    i2cTxData[I2C_PACKET_VAL_POS] = i2cTxVal;
    i2cTxData[I2C_PACKET_EOP_POS] = I2C_PACKET_EOP;
    
    (void) I2CM_I2CMasterWriteBuf(i2cTxAddr, i2cTxData, I2C_PACKET_SIZE, I2CM_I2C_MODE_COMPLETE_XFER);
    while (0u == (I2CM_I2CMasterStatus() & I2CM_I2C_MSTAT_WR_CMPLT))
    {
    }
    if (0u == (I2CM_I2C_MSTAT_ERR_XFER & I2CM_I2CMasterStatus()))
    {
        if (I2CM_I2CMasterGetWriteBufSize() == I2C_BUFFER_SIZE)
        {
            setLed(0,1,0,25);
        }
    }
    else
    {
        setLed(1,0,0,255);
    }
    (void) I2CM_I2CMasterClearStatus();
    setLed(0,0,0,25);
}
void i2c_rx(uint8 i2cRxAddr, uint8 i2cRxCmd, uint8* i2cRxVal)
{
    uint8 i2cRxData[I2C_PACKET_SIZE];

    i2c_tx(i2cRxAddr, i2cRxCmd, 0xaau);
    
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
                i2cRxCmd = i2cRxData[I2C_PACKET_CMD_POS];
                *i2cRxVal = i2cRxData[I2C_PACKET_VAL_POS];
                setLed(0,1,0,25);
            }
        }
    }
    else
    {
        setLed(1,0,0,255);
    }
    (void) I2CM_I2CMasterClearStatus(); 
    setLed(0,0,0,25);
}

void i2c_slave()
{
    if (0u != (I2CM_I2CSlaveStatus() & I2CM_I2C_SSTAT_WR_CMPLT))
    {
        if (I2C_PACKET_SIZE == I2CM_I2CSlaveGetWriteBufSize())
        {
            if ((i2c_slaveBuffer[I2C_PACKET_SOP_POS] == I2C_PACKET_SOP) && (i2c_slaveBuffer[I2C_PACKET_EOP_POS] == I2C_PACKET_EOP))
            {
                struct Data i2cRxData;
                i2cRxData.val_ = i2c_slaveBuffer[2];
                i2cRxData.cmd_ = i2c_slaveBuffer[1];
    
                pushQueue(i2cRxData);
            }
        }

        I2CM_I2CSlaveClearWriteBuf();
        (void) I2CM_I2CSlaveClearWriteStatus();
    }
}
/* [] END OF FILE */
