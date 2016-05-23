/* ========================================
 *
 * File: data.c
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

#include "data.h"

void data_init(void)
{
    dataXY.calibratedX = 1;
    dataXY.calibratedY = 1;
    dataXY.interruptX = 0;
    dataXY.interruptY = 0;
    dataXY.isrStopX = 0;
    dataXY.isrStopY = 0;
    dataXY.xFlag = 0;
    dataXY.yFlag = 0;
    dataXY.xMax = 3460;
    dataXY.xPos = 0;
    dataXY.yMax = 1475;
    dataXY.yPos = 0; 
}

/* [] END OF FILE */
