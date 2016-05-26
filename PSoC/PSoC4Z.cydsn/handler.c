/*!
 *  @file       handler.c
 *  @brief      Handler modul
 *  @details    Håndtere indkommende kommandoer med tilhørende værdier.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "handler.h"
#include "data.h"
#include "i2c.h"
#include "z.h"


/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Håndter kommando med tilhørende værdi
 *  @details    Fortager en defineret handling ud fra den modtaget kommando med den tilhørende værdi.
 *  @param[in]  cmd Er den modtaget kommando.
 *  @param[in]  val Er den tilhørende værdi.
 *  @public
 *  @memberof   Handler
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void handler(uint8 cmd, uint8 val)
{
  switch (cmd) {
    case CMD_SET_Z_POS :
      setZPos(val);
      break;
    case CMD_GET_Z_POS :
      i2cTxBuffer[I2C_PACKET_CMD_POS] = cmd;
      i2cTxBuffer[I2C_PACKET_VAL_POS] = (uint8)((resolution * dataZ.zPos) / dataZ.zMax + 1);;
      break;
    case CMD_Z_STP :
      dataZ.isrStopZ = 1;
      break;
    case CMD_Z_CAL :
      calibrateZ();
      break;
    default :
      break;
  }
}


/* [] END OF FILE */