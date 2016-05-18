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
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "z.h"
    
extern void handler(uint8 cmd, uint8 val);

/* Commands set */
#define cmdSetZPos (0x20u)
#define cmdGetZPos (0x21u)
#define cmdGetZMax (0x22u)
#define cmdStopZ (0x23u)
#define cmdCalibrateZ (0x24u)
    
#endif  // ifndef HANDLER_H
/* [] END OF FILE */
