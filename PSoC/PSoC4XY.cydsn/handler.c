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
    uint8 txVal;
    
    switch (cmd) {
        case cmdSetXPos : 
            setXPos(val);
            break;
        case cmdSetYPos :
            setYPos(val);
            break;
        case cmdGetXPos :
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = txVal = getXPos();
            i2c_tx();
            break;
        case cmdGetYPos : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = (uint8)(resolution / yMax * yPos);
            i2c_tx();
            break;
        case cmdGetXMax : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = (xMax > 0) ? (255u) : 0xee;
            i2c_tx();
            break;
        case cmdGetYMax : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = (yMax > 0) ? (255u) : 0xee;
            i2c_tx();
            break;
        case cmdStopX : 
            stopX();
            break;
        case cmdStopY : 
            stopY();
            break;
        case cmdCalibrateX : 
            calibrateX();
            break;
        case cmdCalibrateY : 
            calibrateY();
            break;
        case 0x90 :
            calibrateX();
            calibrateY();
            break;
        default :
            break;
    }
}
/* [] END OF FILE */
