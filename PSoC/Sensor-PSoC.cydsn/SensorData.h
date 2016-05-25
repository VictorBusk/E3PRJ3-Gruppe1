/*!
 * @file        SensorData.c
 * @class       SensorData
 * @brief       Container for sensor data
 * @author      Simon Nejmann (19981127@uni.au.dk)
 */
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <project.h>
#include "CircularMean.h"

/*!
 * @brief       Container for sensor data
 */
struct sensorDataT {
    // Lumen sensor
    unsigned int lux;   /*!< The average value of lux measured */
    unsigned int desiredLux;   /*!< The lux value the system should try to maintain */
    struct CircularMean LumenMean;   /*!< Circular structure. Can add values and get their average. Used for lux measurements */

    // PIR sensor
    uint8 movement;   /*!< The latest reading from the PIR movement sensor */
    uint8 movementAlertOn;  /*!< Should the system react to movement or ignore it */

    // Distance sensor
    int distance;   /*!< The latest reading from the ultrasonic distance sensor */
    int desiredTimeDistance;   /*!< The distance the lamp should not be lowered below. Stored in micro-seconds for greater resolution */

    // LED PWM
    uint8 greenPWMPct;   /*!< Power level of the green LED: Scale 0-255. */
    uint8 redPWMPct;   /*!< Power level of the red LED: Scale 0-255. */
    uint8 bluePWMPct;   /*!< Power level of the blue LED: Scale 0-255. */
    uint8 ledPower;   /*!< Are the LEDs currently on or off */
} sensorData;

/*!
 *  @brief      Initializes the SensorData struct parts that need initial values
 *  @public
 *  @memberof   SensorData
 * @author      Simon Nejmann (19981127@uni.au.dk)
 */
void initSensorData();

#endif  // ifndef SENSOR_DATA_H
/* [] END OF FILE */
