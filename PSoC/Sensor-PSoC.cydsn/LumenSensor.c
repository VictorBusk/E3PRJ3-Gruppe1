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

#include "LumenSensor.h"
#include "lux.h"

// Lumen sensor
#define LUMEN_ADDR 0b0101001

void initLumenSensor()
{
    uint8 writeBuf[2];
    
    // Add internal pull-up resistors on the SCL and SDA lines
    LumenCom_scl_SetDriveMode(LumenCom_scl_DM_RES_UP);
    LumenCom_sda_SetDriveMode(LumenCom_sda_DM_RES_UP);

    LumenCom_Start();
    // Send command to sensor:
    writeBuf[0] = 0x80;
    writeBuf[1] = 0x03;
    LumenCom_I2CMasterWriteBuf(LUMEN_ADDR, writeBuf, 2, LumenCom_I2C_MODE_COMPLETE_XFER);
    // Wait for the I2C command to finish transferring:
    while(LumenCom_I2CMasterStatus() & LumenCom_I2C_MSTAT_XFER_INP) {}
}

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

/* [] END OF FILE */
