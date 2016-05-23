/* ========================================
 *
 * File: data.h
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

#ifndef DATA_H
#define DATA_H
    
#include <project.h>
    
struct DataZ_T {
    uint8 calibratedZ;
    uint8 interruptZ;
    uint8 isrStopZ;
    uint8 zFlag;
    uint32 zMax;
    uint32 zPos;
}dataZ;

extern void data_init(void);
    

    
#endif  // ifndef DATA_H
/* [] END OF FILE */
