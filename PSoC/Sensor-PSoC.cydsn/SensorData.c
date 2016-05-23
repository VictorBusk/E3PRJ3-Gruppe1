/*!
 * @file        SensorData.c
 * @brief       Container for sensor data
 * @author      Simon Nejmann (19981127@uni.au.dk)
 */
#include "SensorData.h"

/*! Debug define. Comment out to suppress debug prints */
//#define DEBUG_ON

/*!
 *  @brief      Initializes the SensorData struct parts that need initial values
 *  @public
 *  @memberof   SensorData
 * @author      Simon Nejmann (19981127@uni.au.dk)
 */
void initSensorData()
{
    sensorData.desiredLux = 0;
    sensorData.desiredTimeDistance = 0;

    sensorData.movementAlertOn = 0;
    
    sensorData.ledPower = 0;
    sensorData.redPWMPct = 0;
    sensorData.greenPWMPct = 0;
    sensorData.bluePWMPct = 0;

#ifdef DEBUG_ON
    sensorData.desiredTimeDistance = 580;
    sensorData.desiredLux = 0;
    sensorData.movementAlertOn = 1;
    sensorData.ledPower = 1;
    sensorData.redPWMPct = 255;
    sensorData.greenPWMPct = 255;
    sensorData.bluePWMPct = 255;
#endif
    
    initCircularMean(&sensorData.LumenMean);
}
