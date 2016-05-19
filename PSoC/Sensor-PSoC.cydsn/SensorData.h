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
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <project.h>
#include "CircularMean.h"

// Data collection:
struct sensorDataT {
    // Lumen sensor
    unsigned int lux;
    unsigned int desiredLux;
    struct CircularMean LumenMean;

    // PIR sensor
    uint8 movement;
    uint8 movementAlertOn;
    
    // Distance sensor
    int distance;
    int timeDistance;
    int desiredTimeDistance;

    // LED PWM
    uint8 greenPWMPct;
    uint8 redPWMPct;
    uint8 bluePWMPct;
    uint8 ledPower;
} sensorData;

void initSensorData();

#endif  // ifndef SENSOR_DATA_H
/* [] END OF FILE */
