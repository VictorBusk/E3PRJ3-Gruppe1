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
        case cmdSetXPos : 
            setXPos(val);
            break;
        case cmdSetYPos :
            setYPos(val);
            break;
        case cmdGetXPos :
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = 0xBA;
            i2c_tx();
            break;
        case cmdGetYPos : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = 0xAF;
            i2c_tx();
            break;
        case cmdGetXMax : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = getXMax();
            i2c_tx();
            break;
        case cmdGetYMax : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = getYMax();
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
