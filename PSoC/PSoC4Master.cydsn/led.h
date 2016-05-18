/* ========================================
 *
 * File: led.h
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: Jeppe Stærk
 * Matriculation number: 201271201
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

#ifndef LED_H
#define LED_H

#include <project.h>
#include "handler.h"
#include "queue.h"

extern void setLed(uint8 red, uint8 green, uint8 blue, uint8 time);
extern void queueLed(uint8 red, uint8 green, uint8 blue, uint8 time);

#define LED_ON       (0u)
#define LED_OFF      (1u)
    
#endif  // ifndef LED_H
/* [] END OF FILE */
