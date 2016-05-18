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
#include <project.h>
#include <stdio.h>
#include "CircularMean.h"
#include "lux.h"
#include "handler.h"
#include "i2c.h"
#include "queue.h"

//#define DEBUG_ON

// Debug
#ifdef DEBUG_ON
char uartStr[150];
#endif

// Data collection:
struct {
    unsigned int lux;
    char movement;
    int distance;
} sensorData;

struct CircularMean LumenMean;

// Main loop control stuff
enum sensor {DIST, LUMEN, PIR, PWM};
enum ctrl {COUNT, RATE, FLAG};
char controlFlags[4][3] = {
    {1,-1, 0},
    {1,-1, 0},
    {1,-1, 0},
    {1,-1, 0}
};
void initCtrlFlags()
{
    controlFlags[DIST][RATE] = 3;
    controlFlags[LUMEN][RATE] = 2;
    controlFlags[PIR][RATE] = 10;
    controlFlags[PWM][RATE] = 1;
}
void incrCtrlFlag(enum sensor se)
{
    controlFlags[se][COUNT] = (controlFlags[se][COUNT] + 1) % controlFlags[se][RATE];
    if (controlFlags[se][COUNT] == 0) {
        controlFlags[se][FLAG] = 1;
    }
}
CY_ISR(Metronome_Interrupt)
{
    incrCtrlFlag(DIST);
    incrCtrlFlag(LUMEN);
    incrCtrlFlag(PIR);
    incrCtrlFlag(PWM);

    // Clear interrupt
    MetronomeTimer_ReadStatusRegister();
}

// Afstandssensor
CY_ISR(DistTimer_Interrupt)
{
    // Calculate distance from delay. Basic formula: cm = micro-seconds / 58
    //  Timer counts down from 2^16, so start at 2^16 and subtract timer.
    //  Integer calculations means everything gets rounded down, so add
    //      half a cm (58/2) to make 3.5 round up instead.
    sensorData.distance = ((1<<16) +58/2 - DistTimer_ReadCapture()) / 58;

    // Reset the timer
    DistReset_Write(1);

    // Debug
#ifdef DEBUG_ON
    sprintf(uartStr, "Distance: %i cm\n\r", sensorData.distance);
    Debug_UartPutString(uartStr);
#endif
}

// Lumen sensor
#define LUMEN_ADDR 0b0101001
unsigned char readBuf[5];
unsigned char writeBuf[5];
unsigned int readLumenSensor();

// LED PWM
unsigned int greenPWMPct;
unsigned int redPWMPct;
unsigned int bluePWMPct;

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Data collection
    initCircularMean(&LumenMean);
    queue_init();
    i2c_init();
    
    // Debug
#ifdef DEBUG_ON
    Debug_Start();
#endif

    // Afstandssensor
    DistTimer_Start();
    DistTimerInt_StartEx(DistTimer_Interrupt);

    // Lumen sensor
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

    // LED PWM
    GreenPWM_Start();
    RedPWM_Start();
    BluePWM_Start();
    
    // Main command loop
    initCtrlFlags();
    MetronomeTimer_Start();
    MetronomeISR_StartEx(Metronome_Interrupt);

    for(;;)
    {
        i2c_rx();
        while(isEmptyQueue() != 1)
        {
            struct Data action;
            action = frontQueue();
            handler(action.cmd_, action.val_);
            popQueue();
        }
        CyDelay(50);
        i2c_tx();
        
        // LED PWM
        if (controlFlags[PWM][FLAG]) {
            controlFlags[PWM][FLAG] = 0;
            greenPWMPct = (greenPWMPct +10) % 255;
            redPWMPct = (redPWMPct +10) % 255;
            bluePWMPct = (bluePWMPct +10) % 255;
            
            GreenPWM_WriteCompare(greenPWMPct);
            RedPWM_WriteCompare(redPWMPct);
            BluePWM_WriteCompare(bluePWMPct);
        }
        
        // Afstandssensor
        if (controlFlags[DIST][FLAG]) {
            controlFlags[DIST][FLAG] = 0;
            // Start the distance sensor by holding the trigger pin high for 10us
            DistReset_Write(0);
            DistTrigger_Write(1);
            CyDelayUs(10);
            DistTrigger_Write(0);
        }

        // PIR sensor
        if (controlFlags[PIR][FLAG]) {
            controlFlags[PIR][FLAG] = 0;
            // Read the PIR sensor output
            sensorData.movement = PIR_Trig_Read();

            // Debug
#ifdef DEBUG_ON
            Debug_UartPutString("PIR detekterer ");
            if (sensorData.movement) {
                Debug_UartPutString("bevaegelse\n\r");
            } else {
                Debug_UartPutString("ikke noget\n\r");
            }
#endif
        }

        // Lumen sensor
        if (controlFlags[LUMEN][FLAG]) {
            controlFlags[LUMEN][FLAG] = 0;
            // Read the lux value from the sensor
            unsigned int luxValue = readLumenSensor();
            // Add lux value to history
            insertValue(&LumenMean, luxValue);
            sensorData.lux = getMeanValue(&LumenMean);

            // Debug
#ifdef DEBUG_ON
            sprintf(uartStr, "Lux: %i\n\r", luxValue);
            Debug_UartPutString(uartStr);
            sprintf(uartStr, "Mean: %i\n\r", getMeanValue(&LumenMean));
            Debug_UartPutString(uartStr);
#endif
        }
    }
}

unsigned int readLumenSensor()
{
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
