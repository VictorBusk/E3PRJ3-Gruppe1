/*!
 *  @file        main.c
 *  @brief       Main file for Sensor-PSoC
 *
 *  Contains the main loop and control structure for the Sensor-PSoC.
 *  The main control is the Metronome timer which generates an interrupt every
 *      half second. This interrupt then increases a set of counters which, in
 *      turn, set flags when the counters overflow. This allows us to define
 *      periodic events that trigger on integer multiple of half seconds.
 *
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
#include <project.h>
#include <stdio.h>
#include "SensorData.h"
#include "LumenSensor.h"
#include "handler.h"
#include "i2c.h"
#include "queue.h"

/*! Debug define. Comment out to suppress debug prints */
#define DEBUG_ON
char bla[150];

void scaleLedPWM();

// Main loop control stuff
/*! List of event names */
enum sensor {DIST, LUMEN, PIR, DIST_ALERT, MOVE_ALERT};
/*! Flag names */
enum ctrl {COUNT, RATE, FLAG};
/*! Control matrix: flags x event_names */
char controlFlags[5][3] = {
    {1,-1, 0},
    {1,-1, 0},
    {1,-1, 0},
    {1,-1, 0},
    {1,-1, 0}
};
/*! Initializer for control structure */
void initCtrlFlags()
{
    controlFlags[DIST][RATE] = 3;
    controlFlags[LUMEN][RATE] = 2;
    controlFlags[PIR][RATE] = 1;

    controlFlags[MOVE_ALERT][RATE] = 1;
}
/*! Helper function: Increase count, check for overflow, and raise flag if needed */
void incrCtrlFlag(enum sensor se)
{
    controlFlags[se][COUNT] = (controlFlags[se][COUNT] + 1) % controlFlags[se][RATE];
    if (controlFlags[se][COUNT] == 0) {
        controlFlags[se][FLAG] = 1;
    }
}
/*! Metronome timer interrupt handler */
CY_ISR(Metronome_Interrupt)
{
    // Clear interrupt
    MetronomeTimer_ReadStatusRegister();

    incrCtrlFlag(DIST);
    incrCtrlFlag(LUMEN);
    incrCtrlFlag(PIR);
    // Not DIST_ALERT
    incrCtrlFlag(MOVE_ALERT);

#ifdef DEBUG_ON
//    DEBUG_PutString("Beat\r\n");
#endif
}

/*! Flag: Have we already triggered a "too close" alert? */
uint8 distAlertTriggered = 0;
// Afstandssensor
/*! Timer interrupt for ultrasonic distance sensor */
CY_ISR(DistTimer_Interrupt)
{
    //  Calculate distance from delay. Basic formula: cm = micro-seconds / 58
    //      Timer counts down from 2^16, so start at 2^16 and subtract timer.
    int echoDelay = (1<<16) - DistTimer_ReadCapture();

    //  Integer calculations means everything gets rounded down, so add
    //      half a cm (58/2) to make 3.5 round up instead.
    sensorData.distance = (echoDelay + 58/2) / 58;

    // Check if we are too close - check done in time domain due to greater resolution
    if (echoDelay < sensorData.desiredTimeDistance) {
        controlFlags[DIST_ALERT][FLAG] = 1;
    } else {
        distAlertTriggered = 0;
        DistInterruptPin_Write(0);
        controlFlags[DIST_ALERT][COUNT] = 0;
    }

    // Reset the timer
    DistReset_Write(1);

#ifdef DEBUG_ON
//    sprintf(bla, "Dist: %i\n\r", sensorData.distance);
//    DEBUG_PutString(bla);
#endif
}

/*!
 *  @brief      Main function
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Data collection
    initSensorData();
    
    // Afstandssensor
    DistTimer_Start();
    DistTimerInt_StartEx(DistTimer_Interrupt);
    
    // Lumen sensor
    initLumenSensor();

    // LED PWM
    GreenPWM_Start();
    RedPWM_Start();
    BluePWM_Start();
    
    // Main command loop
    initCtrlFlags();
    MetronomeTimer_Start();
    MetronomeISR_StartEx(Metronome_Interrupt);
    queue_init(6u);
    i2c_init();

    for(;;)
    {
        // Handle communication with PSoC4Master
        i2c_rx();
        if(isEmptyQueue() != 1)
        {   char queue[25];
            struct Data action;
            action = frontQueue();
            handler(action.cmd_, action.val_);
            sprintf(queue, "Queue: %i Cmd: %i Cal: %i\n\r", queueCount_,action.cmd_, action.val_);
            DEBUG_PutString(queue);
            popQueue();
        }
        i2c_tx();
        
        // Afstandssensor
        if (controlFlags[DIST][FLAG]) {
            controlFlags[DIST][FLAG] = 0;
            // Start the distance sensor by holding the trigger pin high for 10us
            DistReset_Write(0);
            DistTrigger_Write(1);
            CyDelayUs(10);
            DistTrigger_Write(0);
        }

        if (controlFlags[DIST_ALERT][FLAG]) {
            controlFlags[DIST_ALERT][FLAG] = 0;
            
            // Have to get two "too close" readings in a row to trigger alert
            ++(controlFlags[DIST_ALERT][COUNT]);
            if (!distAlertTriggered && controlFlags[DIST_ALERT][COUNT] >= 1) {
                // Set counter to fixed value - keeps it high but prevents overflow
                controlFlags[DIST_ALERT][COUNT] = 10;
                distAlertTriggered = 1;
                DistInterruptPin_Write(1);
                handler(cmdDistanceAlert, 0xff);
            }
        }
        
        // PIR sensor
        if (controlFlags[PIR][FLAG]) {
            controlFlags[PIR][FLAG] = 0;

            if (sensorData.movementAlertOn) {
                // Read the PIR sensor output
                int tmp = PIR_Trig_Read();
                // If there is movement now but not before
                if (tmp) {
                    // Movement detected - set movement high
                    sensorData.movement = 10;

                    if (!sensorData.movement) {
                        // Did it just happen?
                        handler(cmdMovementAlert, 0xff);
                    }
                } else {
                    // No movement
                    if (sensorData.movement) {
                        // But there were movement before - so slowly decay the indicator
                        --(sensorData.movement);
                    }
                }
            } else {
                // Movement alert is off
                sensorData.movement = 0;
            }
        }

        if (controlFlags[MOVE_ALERT][FLAG]) {
            controlFlags[MOVE_ALERT][FLAG] = 0;

            if (sensorData.movementAlertOn) {
                if (sensorData.movement) {
                    sensorData.ledPower = 1;
                    RedPWM_Start();
                    GreenPWM_Start();
                    BluePWM_Start();
                    RedPWM_WriteCompare(sensorData.redPWMPct);
                    GreenPWM_WriteCompare(sensorData.greenPWMPct);
                    BluePWM_WriteCompare(sensorData.bluePWMPct);
                } else {
                    sensorData.ledPower = 0;
                    RedPWM_Stop();
                    GreenPWM_Stop();
                    BluePWM_Stop();
                }
            }
        }

        // Lumen sensor
        if (controlFlags[LUMEN][FLAG]) {
            controlFlags[LUMEN][FLAG] = 0;
            // Read the lux value from the sensor
            unsigned int luxValue = readLumenSensor();
            // Add lux value to history
            insertValue(&sensorData.LumenMean, luxValue);
            sensorData.lux = getMeanValue(&sensorData.LumenMean);

            if (sensorData.ledPower && sensorData.desiredLux != 0) {
                scaleLedPWM();
            }
            
#ifdef DEBUG_ON
            sprintf(bla, "Lux: %u, mean: %i\n\r", luxValue, sensorData.lux);
            DEBUG_PutString(bla);
#endif
        }
    }
}

/*!
 *  @brief      Should control LED output according to measured and desired lux
 *  Does not currently work: LEDs cannot produce enough light to affect the
 *      measured lux in a meaningful way.
 *      Should have implemented a primitive PID controller (so far only P-part
 *      has been attempted implemented).
 *  @public
 *  @author      Simon Nejmann (19981127@uni.au.dk)
 */
void scaleLedPWM()
{
    // Work in scaled units since the LedPWMs also use the 0-255 range
    uint8 luxFF = scaleLuxToFF(sensorData.lux);
    uint8 luxDesFF = scaleLuxToFF(sensorData.desiredLux);
    int16 delta = luxDesFF - luxFF;

    // Keep delta in check - don't want light-levels jumping too much
    delta = (delta > 10) ? 10 : delta;
    delta = (delta < -10) ? -10 : delta;
    
#ifdef DEBUG_ON
    sprintf(bla, "Delta: %i, RGB: %i, %i, %i\n\r", delta,
        sensorData.redPWMPct, sensorData.greenPWMPct, sensorData.bluePWMPct);
    DEBUG_PutString(bla);
#endif

// Scale LEDs by delta
    sensorData.redPWMPct += delta;
    sensorData.greenPWMPct += delta;
    sensorData.bluePWMPct += delta;

    RedPWM_WriteCompare(sensorData.redPWMPct);
    GreenPWM_WriteCompare(sensorData.greenPWMPct);
    BluePWM_WriteCompare(sensorData.bluePWMPct);
}
