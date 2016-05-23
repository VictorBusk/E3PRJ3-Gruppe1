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
    dataZ.calibratedZ = 1;
    dataZ.interruptZ = 0;
    dataZ.isrStopZ = 0;
    dataZ.zFlag = 0;
    dataZ.zMax = 3000;
    dataZ.zPos = 0;
}

/* [] END OF FILE */
