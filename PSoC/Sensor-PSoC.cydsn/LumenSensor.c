/*!
 *  @file        LumenSensor.c
 *  @brief       Handles the light sensor. Both initialization and data extraction
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
#include "LumenSensor.h"
#include "lux.h"
#include "SensorData.h"

/*! The I2C address of the light sensor */
#define LUMEN_ADDR 0b0101001

/*!
 *  @brief      Initialize the light sensor
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
void initLumenSensor()
{
    uint8 writeBuf[2];
    
    // Add internal pull-up resistors on the SCL and SDA lines
    LumenCom_scl_SetDriveMode(LumenCom_scl_DM_RES_UP);
    LumenCom_sda_SetDriveMode(LumenCom_sda_DM_RES_UP);

    LumenCom_Start();
    // Send command to sensor:
    writeBuf[0] = 0x80; // Highest bit set = command, low bits 0000 = control register
    writeBuf[1] = 0x03; // Power up sensor
    LumenCom_I2CMasterWriteBuf(LUMEN_ADDR, writeBuf, 2, LumenCom_I2C_MODE_COMPLETE_XFER);

    // Wait for the I2C command to finish transferring:
    while(LumenCom_I2CMasterStatus() & LumenCom_I2C_MSTAT_XFER_INP) {}
}

/*!
 *  @brief      Read sensor data from the light sensor
 *  @param[out] The lux value of the perceived light
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
unsigned int readLumenSensor()
{
    uint8 readBuf[2];
    uint8 writeBuf[1];
    unsigned int channel0 = 0;
    unsigned int channel1 = 0;

    // Send "read channel 0" command
    writeBuf[0] = 0xAC;
    LumenCom_I2CMasterWriteBuf(LUMEN_ADDR, writeBuf, 1, LumenCom_I2C_MODE_NO_STOP);

    // Wait for the I2C command to finish transferring
    while(!(LumenCom_I2CMasterStatus() & LumenCom_I2C_MSTAT_XFER_HALT)) {}
    // Read two bytes of data
    LumenCom_I2CMasterReadBuf(LUMEN_ADDR, readBuf, 2,
        LumenCom_I2C_MODE_REPEAT_START | LumenCom_I2C_MODE_NO_STOP);

    // Wait for the I2C command to finish transferring
    while(!(LumenCom_I2CMasterStatus() & LumenCom_I2C_MSTAT_XFER_HALT)) {}

    channel0 = readBuf[0] + readBuf[1] * 256;

    // Send "read channel 1" command
    writeBuf[0] = 0xAE;
    LumenCom_I2CMasterWriteBuf(LUMEN_ADDR, writeBuf, 1,
        LumenCom_I2C_MODE_REPEAT_START | LumenCom_I2C_MODE_NO_STOP);

    // Wait for the I2C command to finish transferring
    while(!(LumenCom_I2CMasterStatus() & LumenCom_I2C_MSTAT_XFER_HALT)) {}
    // Read two bytes of data
    LumenCom_I2CMasterReadBuf(LUMEN_ADDR, readBuf, 2, LumenCom_I2C_MODE_REPEAT_START);

    // Wait for the I2C command to finish transferring
    while(LumenCom_I2CMasterStatus() & LumenCom_I2C_MSTAT_XFER_INP) {}

    channel1 = readBuf[0] + readBuf[1] * 256;

    // Use Datasheet function to calculate lux value from read values
    return CalculateLux(0, 2, channel0, channel1, 0);
}

/*!
 *  @brief      Scale a lux value into a 0-255 range value
 *  Due to the limited range to scale into, lux over 1530 is scaled to 255.
 *      The top 1530 vas chosen because 1530/255 = 6.
 *
 *  @param[out] The lux value scaled down into a single uint8
 *  @param[in]  The lux value to scale down
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
uint8 scaleLuxToFF(unsigned int val)
{
//    int tmp = (val * 255) / 1530;
    int tmp = val / 6;
    return (uint8)((tmp < 255) ? tmp : 255);
}

/*!
 *  @brief      Scale a 0-255 range value into lux
 *  Due to the limited input range 1530 has been chosen as max value for lux.
 *      The top 1530 vas chosen because 1530/255 = 6.
 *
 *  @param[out] The an upscaled lux value
 *  @param[in]  val uint8 containing a value to scale up
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
unsigned int scaleFFtoLux(uint8 val)
{
//    return  (val * 1530) / 255;
    return  val * 6;
}
