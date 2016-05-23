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
#include "handler.h"
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
    
    I2CS_SetCustomInterruptHandler(isr_i2c_rx);
    I2CS_SetSlaveInterruptMode(I2CS_INTR_SLAVE_I2C_WRITE_STOP);
  
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

CY_ISR(isr_i2c_rx)
{  
    int i = 0;
    
    DEBUG_PutString(">I status: ");
    DEBUG_PutHexByte(I2CS_I2CSlaveStatus());
    DEBUG_PutString(" interrupt: ");
    DEBUG_PutHexByte(I2CS_GetSlaveInterruptSource());
    DEBUG_PutString(" buffer size: ");
    DEBUG_PutHexByte(I2CS_I2CSlaveGetWriteBufSize());
    DEBUG_PutCRLF();
    DEBUG_PutHexByte(i);
    DEBUG_PutString(") i2cRxBuffer[0]: ");
    DEBUG_PutHexByte(i2cRxBuffer[0]);
    DEBUG_PutString(" [1]: ");
    DEBUG_PutHexByte(i2cRxBuffer[1]);
    DEBUG_PutString(" [2]: ");
    DEBUG_PutHexByte(i2cRxBuffer[2]);
    DEBUG_PutString(" [3]: ");
    DEBUG_PutHexByte(i2cRxBuffer[3]);
    DEBUG_PutCRLF();
    
    I2CS_ClearSlaveInterruptSource(I2CS_GetSlaveInterruptSource());
    
    if(0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_WR_CMPLT))
    {
        while(I2CS_I2CSlaveGetWriteBufSize() > 0)
        {   
            DEBUG_PutHexByte(i);
            DEBUG_PutString(") i2cRxBuffer[0]: ");
            DEBUG_PutHexByte(i2cRxBuffer[0]);
            DEBUG_PutString(" [1]: ");
            DEBUG_PutHexByte(i2cRxBuffer[1]);
            DEBUG_PutString(" [2]: ");
            DEBUG_PutHexByte(i2cRxBuffer[2]);
            DEBUG_PutString(" [3]: ");
            DEBUG_PutHexByte(i2cRxBuffer[3]);
            DEBUG_PutString(" buffer size: ");
            DEBUG_PutHexByte(I2CS_I2CSlaveGetWriteBufSize());
            DEBUG_PutCRLF();
            setLed(0,0,1);
            if(I2C_BUFFER_SIZE == I2CS_I2CSlaveGetWriteBufSize())
            {
                if((i2cRxBuffer[I2C_PACKET_SOP_POS] == I2C_PACKET_SOP) && (i2cRxBuffer[I2C_PACKET_EOP_POS] == I2C_PACKET_EOP))
                {
                    struct Data action;
                    setLed(0,1,0);
                    DEBUG_PutHexByte(i);
                    DEBUG_PutString(") ok...");
                    DEBUG_PutCRLF();
                    
                    switch(i2cRxBuffer[I2C_PACKET_CMD_POS]) {
                        case CMD_SET_X_POS :                            
                            dataXY.isrStopX = 1;
                            DEBUG_PutHexByte(i);
                            DEBUG_PutString(") isrStopX = 1");
                            DEBUG_PutCRLF();
                            break;
                        case CMD_SET_Y_POS :
                            dataXY.isrStopY = 1;
                            DEBUG_PutHexByte(i);
                            DEBUG_PutString(") isrStopX = 1");
                            DEBUG_PutCRLF();
                            break;
                        default :                      
                            action.cmd_ = i2cRxBuffer[I2C_PACKET_CMD_POS];
                            action.val_ = i2cRxBuffer[I2C_PACKET_VAL_POS];
                            pushQueue(action);
                            DEBUG_PutHexByte(i);
                            DEBUG_PutString(") cmd: ");
                            DEBUG_PutHexByte(action.cmd_);
                            DEBUG_PutString(" val: ");
                            DEBUG_PutHexByte(action.val_);
                            DEBUG_PutCRLF();
                            break;                    
                    }
                }
                 else
                {
                    setLed(1,0,0);
                    DEBUG_PutHexByte(i);
                    DEBUG_PutString(") bad!");
                    DEBUG_PutCRLF();
                }
                DEBUG_PutHexByte(i);
                DEBUG_PutString(") done");
                DEBUG_PutCRLF();
            }
            setLed(0,0,0);
            i++;
            DEBUG_PutCRLF();
        }
        DEBUG_PutString(">I done");
        DEBUG_PutCRLF();
        I2CS_I2CSlaveClearWriteBuf();
        (void) I2CS_I2CSlaveClearWriteStatus();
    }
    DEBUG_PutCRLF();
}

/* [] END OF FILE */
