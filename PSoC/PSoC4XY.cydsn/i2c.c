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

uint8 i2c_txBuffer[I2C_BUFFER_SIZE] = {I2C_PACKET_SOP, I2C_STS_CMD_FAIL, I2C_STS_CMD_FAIL, I2C_PACKET_EOP};
uint8 i2c_rxBuffer[I2C_BUFFER_SIZE];

void i2c_init()
{
    I2CS_I2CSlaveInitReadBuf(i2c_txBuffer, I2C_BUFFER_SIZE);
    I2CS_I2CSlaveClearReadBuf();
    I2CS_I2CSlaveClearReadStatus();
    
    I2CS_I2CSlaveInitWriteBuf(i2c_rxBuffer, I2C_BUFFER_SIZE);
    I2CS_I2CSlaveClearWriteBuf();
    I2CS_I2CSlaveClearWriteStatus();
    
    I2CS_Start();
}

void i2c_rx()
{
    if(0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_WR_CMPLT))
    {
        if(I2C_BUFFER_SIZE == I2CS_I2CSlaveGetWriteBufSize())
        {
            if((i2c_rxBuffer[0] == I2C_PACKET_SOP) && (i2c_rxBuffer[3] == I2C_PACKET_EOP))
            {
                struct Data action;
                action.cmd_ = i2c_rxBuffer[1];
                action.val_ = i2c_rxBuffer[2];
                
                pushQueue(action);
            }
        }
        
        I2CS_I2CSlaveClearWriteBuf();
        I2CS_I2CSlaveClearWriteStatus();
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
