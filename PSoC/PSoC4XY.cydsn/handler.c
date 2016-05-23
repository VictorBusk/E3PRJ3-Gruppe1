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
#include "xy.h"

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
