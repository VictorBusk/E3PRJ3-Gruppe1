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
        case cmdSetZPos : 
            setZPos(val);
            break;
        case cmdGetZPos :
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = (zPos > 0) ? (zPos) : 0xee;
            i2c_tx();
            break;
        case cmdGetZMax : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = (zMax > 0) ? (zMax) : 0xee;
            i2c_tx();
            break;
        case cmdStopZ : 
            stopZ();
            break;
        case cmdCalibrateZ : 
            calibrateZ();
            break;
        default :
            break;
    }
}
/* [] END OF FILE */
