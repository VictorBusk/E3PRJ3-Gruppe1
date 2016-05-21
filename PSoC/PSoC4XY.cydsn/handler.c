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
            i2cTxBuffer[I2C_PACKET_VAL_POS] = getXPos();
            break;
        case CMD_GET_Y_POS :
            i2cTxBuffer[I2C_PACKET_CMD_POS] = cmd;
            i2cTxBuffer[I2C_PACKET_VAL_POS] = getYPos();
            break;
        case CMD_GET_X_MAX:
            i2cTxBuffer[I2C_PACKET_CMD_POS] = cmd;
            i2cTxBuffer[I2C_PACKET_VAL_POS] = getXMax();
            break;
        case CMD_GET_Y_MAX :
            i2cTxBuffer[I2C_PACKET_CMD_POS] = cmd;
            i2cTxBuffer[I2C_PACKET_VAL_POS] = getYMax();
            break;
        case CMD_X_STP:
            stopX();
            break;
        case CMD_Y_STP:
            stopY();
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
