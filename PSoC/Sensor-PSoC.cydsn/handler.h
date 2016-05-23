/* ========================================
 *
 * File: handler.h
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: 
 * Matriculation number: 
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

/*!
 *  @file        Handler.h
 *  @class       Handler
 *  @brief       Communication handler for the Sensor-PSoC
 *  @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#ifndef HANDLER_H
#define HANDLER_H
    
#include <project.h>
#include "i2c.h"
#include "queue.h"
    
extern void handler(uint8 cmd, uint8 val);

/* Commands set */
#define cmdSetRed (0x30u)
#define cmdSetGreen (0x31u)
#define cmdSetBlue (0x32u)
#define cmdSetLumen (0x33u)
#define cmdSetPower (0x34u)
#define cmdGetRed (0x35u)
#define cmdGetGreen (0x36u)
#define cmdGetBlue (0x37u)
#define cmdGetLumen (0x38u)
#define cmdGetPower (0x39u)
#define cmdSetDistance (0x40u)
#define cmdSetMovement (0x41u)
#define cmdGetDistance (0x42u)
#define cmdGetMovement (0x43u)
#define cmdDistanceAlert (0x44u)
#define cmdMovementAlert (0x45u)
    
#endif  // ifndef HANDLER_H
/* [] END OF FILE */
