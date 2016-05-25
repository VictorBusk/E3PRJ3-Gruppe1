/* ========================================
 *
 * File: handler.c
 * Description:
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 *
 * Author:
 * Matriculation number:
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
 */

#include "handler.h"
#include "data.h"
#include "i2c.h"
#include "z.h"

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
