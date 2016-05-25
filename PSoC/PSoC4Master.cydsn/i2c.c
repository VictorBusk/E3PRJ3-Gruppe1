/*!
 *  @file       i2c.c
 *  @brief      I2C modul
 *  @details    Håndter kommunikation via I2C-busset
 *  @ingroup    PSoC-Master
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "i2c.h"
#include "led.h"
#include "lcd.h"
#include <stdio.h>

/***************************************
 *       Private methods
 ***************************************/

static uint8 i2c_tx(uint8 i2cAddr, uint8 i2cCmd, uint8 i2cVal);
static uint8 i2c_rx(uint8 i2cRxAddr, uint8* i2cRxCmd, uint8* i2cRxVal);


/***************************************
 *       Public methods
 ***************************************/

/*!
 *  @brief      Initialiser I2C modulet.
 *  @details    Initailiser I2C komponent på PSoC'en.
 *  @ingroup    PSoC-Master
 *  @public
 *  @memberof   I2C
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void i2c_init()
{
  I2CM_Start();
}

/*!
 *  @brief      Sender en I2C pakke
 *  @details    Metoden sender en I2C data pakke via I2C-busset til den defineret adresse med den modtaget kommande og tilhørende værdi.
 *  @param[in]  i2cAddr I2C adresse på modtager.
 *  @param[in]  i2cCmd Kommando til modtager.
 *  @param[in]  i2cVal Værdi til modtager.
 *  @ingroup    PSoC-Master
 *  @public
 *  @memberof   I2C
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void i2c_setPacket(uint8 i2cAddr, uint8 i2cCmd, uint8 i2cVal)
{
  uint8 status;
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
  
  DEBUG_PutString("I>: addr: ");
  DEBUG_PutHexByte(i2cAddr);
  DEBUG_PutString(" cmd: ");
  DEBUG_PutHexByte(i2cCmd);
  DEBUG_PutString(" val: ");
  DEBUG_PutHexByte(i2cVal);
  DEBUG_PutCRLF();
  setLed(0,0,0,50);
}

/*!
 *  @brief      Henter en I2C pakke
 *  @details    Metoden henter en I2C data pakke via I2C-busset fra den defineret adresse med den modtaget kommande og lager den på den modtaget værdi pointer.
 *  @param[in]  i2cAddr I2C adresse på modtager.
 *  @param[in]  i2cCmd Kommando til modtager.
 *  @param[out] i2cVal Pointer til variabel hvor den hentet værdi skal lagers.
 *  @return     Status på kommunikation.
 *  @ingroup    PSoC-Master
 *  @public
 *  @memberof   I2C
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void i2c_getPacket(uint8 i2cAddr, uint8 i2cCmd, uint8* i2cVal)
{
  uint8 status;
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
  sprintf(lcd, "I> %1.1x %2.2x %2.2x %1.1d", (int)i2cAddr, (int)i2cCmd, (int)*i2cVal, status);
  lcd_newline(lcd);
  
  DEBUG_PutString("I>: addr: ");
  DEBUG_PutHexByte(i2cAddr);
  DEBUG_PutString(" cmd: ");
  DEBUG_PutHexByte(i2cCmd);
  DEBUG_PutString(" val: ");
  DEBUG_PutHexByte(*i2cVal);
  DEBUG_PutCRLF();
  
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
  DEBUG_PutString(">I: addr: ");
  DEBUG_PutHexByte(i2cAddr);
  DEBUG_PutString(" cmd: ");
  DEBUG_PutHexByte(i2cCmd);
  DEBUG_PutString(" val: ");
  DEBUG_PutHexByte(*i2cVal);
  DEBUG_PutCRLF();
}


/***************************************
 *       Private methods
 ***************************************/

/*!
 *  @brief      Sender en I2C pakke
 *  @details    Metoden sender en I2C data pakke via I2C-busset til den defineret adresse med den modtaget kommande og tilhørende værdi.
 *  @param[in]  i2cTxAddr I2C adresse på modtager.
 *  @param[in]  i2cTxCmd Kommando til modtager.
 *  @param[in]  i2cTxVal Værdi til modtager.
 *  @return     Status på kommunikation.
 *  @ingroup    PSoC-Master
 *  @private
 *  @memberof   I2C
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
 *  @brief      Henter en I2C pakke
 *  @details    Metoden henter en I2C data pakke via I2C-busset fra den defineret adresse med den modtaget kommande og lager den på den modtaget værdi pointer.
 *  @param[in]  i2cRxAddr I2C adresse på modtager.
 *  @param[in]  i2cRxCmd Kommando til modtager.
 *  @param[out] i2cRxVal Pointer til variabel hvor den hentet værdi skal lagers.
 *  @return     Status på kommunikation.
 *  @ingroup    PSoC-Master
 *  @private
 *  @memberof   I2C
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