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

#ifndef HANDLER_H
#define HANDLER_H
    
#include <project.h>
#include "capsense.h"
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "xy.h"
    
extern void handler(uint8 cmd, uint8 val);

/* Commands set */
#define cmdSetXPos (0x10u)
#define cmdSetYPos (0x11u)
#define cmdGetXPos (0x12u)
#define cmdGetYPos (0x13u)
#define cmdGetXMax (0x14u)
#define cmdGetYMax (0x15u)
#define cmdStopX (0x16u)
#define cmdStopY (0x17u)
#define cmdCalibrateX (0x18u)
#define cmdCalibrateY (0x19u)
    
#endif  // ifndef HANDLER_H
/* [] END OF FILE */
