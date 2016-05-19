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

void initSensorData()
{
    sensorData.desiredLux = 0;
    sensorData.desiredTimeDistance = 0;
    sensorData.ledPower = 1;
    sensorData.movementAlertOn = 0;

    initCircularMean(&sensorData.LumenMean);
}

/* [] END OF FILE */
