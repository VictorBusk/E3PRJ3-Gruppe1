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

struct DataXY_T {
  uint8 calibratedX;
  uint8 calibratedY;
  uint8 interruptX;
  uint8 interruptY;
  uint8 isrStopX;
  uint8 isrStopY;
  uint8 xFlag;
  uint8 yFlag;
  uint32 xMax;
  uint32 xPos;
  uint32 yMax;
  uint32 yPos;
}dataXY;

extern void data_init(void);



#endif  // ifndef DATA_H
/* [] END OF FILE */
