/* ========================================
 *
 * File: capsense.h
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

#ifndef CAPSENSE_H
#define CAPSENSE_H
    
#include <project.h>
#include "handler.h"
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "xy.h"

extern void capsense_init(void);
extern void capsense(void);
void CapSense_DisplayState(void);
    
#endif  // ifndef CAPSENSE_H
/* [] END OF FILE */
