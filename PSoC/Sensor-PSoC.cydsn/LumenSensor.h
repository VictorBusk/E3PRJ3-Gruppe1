/*!
 *  @file        LumenSensor.h
 *  @class       LumenSensor
 *  @brief       Handles the light sensor. Both initialization and data extraction
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
#ifndef LUMEN_SENSOR_H
#define LUMEN_SENSOR_H

#include <project.h>

/*!
 *  @brief      Initialize the light sensor
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
void initLumenSensor();

/*!
 *  @brief      Read sensor data from the light sensor
 *  @return The lux value of the perceived light
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
unsigned int readLumenSensor();

/*!
 *  @brief      Scale a lux value into a 0-255 range value
 *  Due to the limited range to scale into, lux over 1530 is scaled to 255.
 *      The top 1530 vas chosen because 1530/255 = 6.
 *
 *  @return The lux value scaled down into a single uint8
 *  @param[in]  val The lux value to scale down
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
uint8 scaleLuxToFF(unsigned int val);

/*!
 *  @brief      Scale a 0-255 range value into lux
 *  Due to the limited input range 1530 has been chosen as max value for lux.
 *      The top 1530 vas chosen because 1530/255 = 6.
 *
 *  @return The an upscaled lux value
 *  @param[in]  val uint8 containing a value to scale up
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
unsigned int scaleFFtoLux(uint8 val);

#endif  // ifndef LUMEN_SENSOR_H
