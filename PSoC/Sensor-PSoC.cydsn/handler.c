/*!
 *  @file        Handler.c
 *  @brief       Communication handler for the Sensor-PSoC (to PSoC4Master)
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */

#include "handler.h"
#include "SensorData.h"
#include "LumenSensor.h"

/*! Debug define. Comment out to suppress debug prints */
//#define DEBUG_ON

/*!
 *  @brief      Communication handler for the Sensor-PSoC
 *  @param[in]  cmd The command to be executed
 *  @param[in]  val Optional command argument
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
void handler(uint8 cmd, uint8 val)
{
    switch (cmd) {
        case cmdGetRed : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = sensorData.redPWMPct;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetRed ");
    DEBUG_PutHexByte(sensorData.redPWMPct);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdSetRed : 
            sensorData.redPWMPct = val;
            RedPWM_WriteCompare(sensorData.redPWMPct);
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetRed ");
    DEBUG_PutHexByte(sensorData.redPWMPct);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdGetGreen : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = sensorData.greenPWMPct;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetGreen ");
    DEBUG_PutHexByte(sensorData.greenPWMPct);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdSetGreen : 
            sensorData.greenPWMPct = val;
            GreenPWM_WriteCompare(sensorData.greenPWMPct);
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetGreen ");
    DEBUG_PutHexByte(sensorData.greenPWMPct);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdGetBlue : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = sensorData.bluePWMPct;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetBlue ");
    DEBUG_PutHexByte(sensorData.bluePWMPct);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdSetBlue : 
            sensorData.bluePWMPct = val;
            BluePWM_WriteCompare(sensorData.bluePWMPct);
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetBlue ");
    DEBUG_PutHexByte(sensorData.bluePWMPct);
    DEBUG_PutCRLF();
#endif
            break;

        case cmdGetPower : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = sensorData.ledPower;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetPower ");
    DEBUG_PutHexByte(sensorData.ledPower);
    DEBUG_PutCRLF();
#endif
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
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetPower ");
    DEBUG_PutHexByte(sensorData.ledPower);
    DEBUG_PutCRLF();
#endif
            break;

        case cmdGetLumen : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = scaleLuxToFF(sensorData.lux);
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetLumen ");
    DEBUG_PutHexByte(i2cTxBuffer[2]);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdSetLumen : 
            sensorData.desiredLux = scaleFFtoLux(val);
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetLumen ");
    DEBUG_PutHexByte(sensorData.desiredLux);
    DEBUG_PutCRLF();
#endif
            break;

        case cmdGetDistance : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = (uint8)((sensorData.distance < 255) ? sensorData.distance : 255);
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetDistance ");
    DEBUG_PutHexByte(i2cTxBuffer[2]);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdSetDistance : 
            sensorData.desiredTimeDistance = val * 58;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetDistance ");
    DEBUG_PutHexByte(sensorData.desiredTimeDistance);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdDistanceAlert : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = val;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdDistanceAlert ");
    DEBUG_PutHexByte(val);
    DEBUG_PutCRLF();
#endif
            break;

        case cmdGetMovement : 
            // Return 0xff if there is movement, 0x00 if there is not
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = (sensorData.movement) ? 0xff : 0x00;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdGetMovement ");
    DEBUG_PutHexByte(sensorData.movement);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdSetMovement : 
            sensorData.movementAlertOn = val;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdSetMovement ");
    DEBUG_PutHexByte(sensorData.movementAlertOn);
    DEBUG_PutCRLF();
#endif
            break;
        case cmdMovementAlert : 
            i2cTxBuffer[1] = cmd;
            i2cTxBuffer[2] = val;
#ifdef DEBUG_ON
    DEBUG_PutString("cmdMovementAlert ");
    DEBUG_PutHexByte(val);
    DEBUG_PutCRLF();
#endif
            break;

        default :
            break;
    }
}
