/*!
 *  @file       handler.c
 *  @brief      Handler modul
 *  @details    Håndtere indkommende kommandoer med tilhørende værdier.
 *  @ingroup    PSoC-XY
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "handler.h"
#include "data.h"
#include "i2c.h"
#include "xy.h"

/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Håndter kommando med tilhørende værdi
 *  @details    Fortager en defineret handling ud fra den modtaget kommando med den tilhørende værdi.
 *  @param[in]  cmd Er den modtaget kommando.
 *  @param[in]  val Er den tilhørende værdi.
 *  @ingroup    PSoC-XY
 *  @public
 *  @memberof   Handler
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void handler(uint8 cmd, uint8 val)
{
  switch (cmd) {
    case CMD_SET_X_POS :
      setXPos(val);
      break;
    case CMD_SET_Y_POS:
      setYPos(val);
      break;
    case CMD_GET_X_POS :
      i2cTxBuffer[I2C_PACKET_CMD_POS] = cmd;
      i2cTxBuffer[I2C_PACKET_VAL_POS] = (uint8)((resolution * dataXY.xPos) / dataXY.xMax + 1);
      i2c_tx();
      break;
    case CMD_GET_Y_POS :
      i2cTxBuffer[I2C_PACKET_CMD_POS] = cmd;
      i2cTxBuffer[I2C_PACKET_VAL_POS] = (uint8)((resolution * dataXY.yPos) / dataXY.yMax + 1);
      i2c_tx();
      break;
    case CMD_X_STP:
      dataXY.isrStopX = 1;
      break;
    case CMD_Y_STP:
      dataXY.isrStopY = 1;
      break;
    case CMD_X_CAL:
      calibrateX();
      break;
    case CMD_Y_CAL:
      calibrateY();
      break;
    default :
      break;
  }
}
/* [] END OF FILE */
