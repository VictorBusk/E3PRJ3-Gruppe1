/*!
 *  @file       i2c.c
 *  @brief      I2C modul
 *  @details    Håndter kommunikation via I2C-busset
 *  @ingroup    xy
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "i2c.h"
#include "cyapicallbacks.h"
#include "data.h"
#include "handler.h"
#include "led.h"
#include "queue.h"

/***************************************
 *       Public attributes
 ***************************************/

uint8 i2cTxBuffer[I2C_BUFFER_SIZE] = {I2C_PACKET_SOP, I2C_STS_CMD_FAIL, I2C_STS_CMD_FAIL, I2C_PACKET_EOP};
uint8 i2cRxBuffer[I2C_BUFFER_SIZE];


/***************************************
 *       Public methods
 ***************************************/

/*!
 *  @brief      Initialiser I2C modulet.
 *  @details    Initailiser I2C komponent på PSoC'en.
 *  @ingroup    xy
 *  @public
 *  @memberof   I2CXY
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
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

/*!
 * @todo  Dokumenter! I2CS_I2C_ISR_ExitCallback
 */
void I2CS_I2C_ISR_ExitCallback()
{
  if(I2CS_I2CSlaveGetWriteBufSize() == I2C_BUFFER_SIZE)
  {
    DEBUG_PutCRLF();
    DEBUG_PutString("** isr exit callback **");
    DEBUG_PutCRLF();
    DEBUG_PutString("I> i2cRxBuffer[0]: ");
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
    
    struct Data action;
    action.cmd_ = i2cRxBuffer[I2C_PACKET_CMD_POS];
    action.val_ = i2cRxBuffer[I2C_PACKET_VAL_POS];
    
    switch(i2cRxBuffer[I2C_PACKET_CMD_POS]) {
      case CMD_SET_X_POS :
        dataXY.isrStopX = 1;
        DEBUG_PutString(") isrStopX = 1");
        DEBUG_PutCRLF();
        pushQueue(action);
        break;
      case CMD_SET_Y_POS :
        dataXY.isrStopY = 1;
        DEBUG_PutString(") isrStopY = 1");
        DEBUG_PutCRLF();
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

/*!
 * @todo  Dokumenter! i2c_tx
 */
void i2c_tx()
{
  if(0u != (I2CS_I2CSlaveStatus() & I2CS_I2C_SSTAT_RD_CMPLT))
  {
    I2CS_I2CSlaveClearReadBuf();
    (void) I2CS_I2CSlaveClearReadStatus();
  }
}


/* [] END OF FILE */
