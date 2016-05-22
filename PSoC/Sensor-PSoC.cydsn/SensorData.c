/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "SensorData.h"

//#define DEBUG_ON

void initSensorData()
{
    sensorData.desiredLux = 0;
    sensorData.desiredTimeDistance = 0;
    sensorData.ledPower = 1;
    sensorData.movementAlertOn = 0;

    
    // debug
#ifdef DEBUG_ON
    sensorData.desiredTimeDistance = 580;
    sensorData.movementAlertOn = 1;
    sensorData.ledPower = 1;
    sensorData.redPWMPct = 255;
    sensorData.greenPWMPct = 255;
    sensorData.bluePWMPct = 255;
#endif
    
    initCircularMean(&sensorData.LumenMean);
}

/* [] END OF FILE */
