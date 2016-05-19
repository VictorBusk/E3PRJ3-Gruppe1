/* ========================================
 *
 * File: handler.c
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: Jeppe Stærk
 * Matriculation number: 201271201
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

#include "handler.h"

uint8 xPos = 0;
uint8 xMax = 0;
uint8 yPos = 0;
uint8 yMax = 0;
uint8 zPos = 0;
uint8 zMax = 0;


void handler(uint8 cmd, uint8 txVal)
{
    uint8 rxVal = 0;
    
    switch (cmd)
    {
        case 0x01 :
            i2c_rx(PSoC_XY, getXPos, &xPos);
            i2c_rx(PSoC_XY, getYPos, &yPos);
            i2c_rx(PSoC_Z, getZPos, &zPos);
            break;
        case 0x02 :
            i2c_rx(PSoC_XY, getXMax, &xMax);
            i2c_rx(PSoC_XY, getYMax, &yMax);
            i2c_rx(PSoC_Z, getZMax, &zMax);
            break;
        case setXPos : 
            i2c_tx(PSoC_XY, cmd, txVal);
            break;
        case setYPos : 
            i2c_tx(PSoC_XY, cmd, txVal);
            break;
        case getXPos : 
            spi_tx(xPos);
            break;
        case getYPos : 
            spi_tx(yPos);
            break;
        case getXMax : 
            spi_tx(xMax);
            break;
        case getYMax : 
            spi_tx(yMax);
            break;
        case cmdStopX : 
            i2c_tx(PSoC_XY, cmd, txVal);
            break;
        case cmdStopY : 
            i2c_tx(PSoC_XY, cmd, txVal);
            break;
        case cmdCalibrateX : 
            i2c_tx(PSoC_XY, cmd, txVal);
            break;
        case cmdCalibrateY : 
            i2c_tx(PSoC_XY, cmd, txVal);
            break;
        case setZPos : 
            i2c_tx(PSoC_Z, cmd, txVal);
            break;
        case getZPos : 
            spi_tx(zPos);
            break;
        case getZMax : 
            spi_tx(zMax);
            break;
        case cmdStopZ : 
            i2c_tx(PSoC_Z, cmd, txVal);
            break;
        case cmdCalibrateZ : 
            i2c_tx(PSoC_Z, cmd, txVal);
            break;
        case setRed : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case setGreen : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case setBlue : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case setLumen : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case setPower : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case getRed : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case getGreen : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case getBlue : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case getLumen : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case getPower : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case setDistance : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case setMovement : 
            i2c_tx(PSoC_Sensor, cmd, txVal);
            break;
        case getDistance : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case getMovement : 
            i2c_rx(PSoC_Sensor, cmd, &rxVal);
            break;
        case cmdDistanceAlert : 
            handler(cmdStopX, txVal);
            handler(cmdStopY, txVal);
            handler(cmdStopZ, txVal);
            break;
        case cmdMovementAlert : 
            handler(setPower, txVal);
            break;
        case setMasterLedOff :
            setLed(0,0,0,0);
            break;
        case setMasterLedRed :
            setLed(1,0,0,txVal);
            break;
        case setMasterLedGreen :
            setLed(0,1,0,txVal);
            break;
        case setMasterLedBlue :
            setLed(0,0,1,txVal);
            break;
        case 0x90 :
            i2c_tx(PSoC_XY, cmd, txVal);
        case 0x99 : 
            test(txVal);
            
    }
}

/* [] END OF FILE */
