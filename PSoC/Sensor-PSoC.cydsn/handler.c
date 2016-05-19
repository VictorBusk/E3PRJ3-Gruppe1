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
#include "SensorData.h"

void handler(uint8 cmd, uint8 val)
{
    int tmp;
    switch (cmd) {
        case cmdGetRed : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = sensorData.redPWMPct;
            i2c_tx();
            break;
        case cmdSetRed : 
            sensorData.redPWMPct = val;
            RedPWM_WriteCompare(sensorData.redPWMPct);            
            break;
        case cmdGetGreen : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = sensorData.greenPWMPct;
            i2c_tx();
            break;
        case cmdSetGreen : 
            sensorData.greenPWMPct = val;
            GreenPWM_WriteCompare(sensorData.greenPWMPct);            
            break;
        case cmdGetBlue : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = sensorData.bluePWMPct;
            i2c_tx();
            break;
        case cmdSetBlue : 
            sensorData.bluePWMPct = val;
            BluePWM_WriteCompare(sensorData.bluePWMPct);            
            break;

        case cmdGetPower : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = sensorData.ledPower;
            i2c_tx();
            break;
        case cmdSetPower : 
            sensorData.ledPower = val;
            if (val) {
                RedPWM_Start();
                GreenPWM_Start();
                BluePWM_Start();
            } else {
                RedPWM_Stop();
                GreenPWM_Stop();
                BluePWM_Stop();
            }
            break;

        case cmdGetLumen : 
            // Scale Lux to 1530 max, range 0-255
            //  1530 chosen because 1530/255 = 6
            tmp = (255 * sensorData.lux) / 1530;
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = (uint8)((tmp < 255) ? tmp : 255);
            i2c_tx();
            break;
        case cmdSetLumen : 
            // Scale Lux to 1530 max, range 0-255
            sensorData.desiredLux = (val * 1530) / 255;
            break;

        case cmdGetDistance : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = (uint8)((sensorData.distance < 255) ? sensorData.distance : 255);
            i2c_tx();
            break;
        case cmdSetDistance : 
            sensorData.desiredTimeDistance = val * 58;
            break;
        case cmdDistanceAlert : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = val;
            i2c_tx();
            break;

        case cmdGetMovement : 
            // Return 0xff if there is movement, 0x00 if there is not
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = (sensorData.movement) ? 0xff : 0x00;
            i2c_tx();
            break;
        case cmdSetMovement : 
            sensorData.movementAlertOn = val;
            break;
        case cmdMovementAlert : 
            i2c_txBuffer[1] = cmd;
            i2c_txBuffer[2] = val;
            i2c_tx();
            break;

        default :
            break;
    }
}
/* [] END OF FILE */
