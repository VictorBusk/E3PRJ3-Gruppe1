/* ========================================
 *
 * File: xy.h
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

#ifndef XY_H
#define XY_H
    
#include <project.h>
#include "capsense.h"
#include "handler.h"
#include "i2c.h"
#include "led.h"
#include "queue.h"

#define stepDelay (3u)
#define interruptSteps (50u)
#define resolution (255u) 
    
void xy_init(void);
CY_ISR_PROTO(isr_X);
CY_ISR_PROTO(isr_Y);
void calibrateX(void);
void calibrateY(void);
void setXPos(uint8 xVal);
void setYPos(uint8 yVal);
uint8 getXPos(void);
uint8 getYPos(void);
uint8 getXMax(void);
uint8 getYMax(void);
void stepXForwards(void);
void stepXBackwards(void);
void stopX(void);
void stepYForwards(void);
void stepYBackwards(void);
void stopY(void);

#endif  // ifndef XY_H
/* [] END OF FILE */
