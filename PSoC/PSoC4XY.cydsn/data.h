/*!
 *  @file       data.h
 *  @brief      Data modul
 *  @details    Indeholder data vedr. XY modulet.
 *  @ingroup    PSoC-XY
 *  @class      Data data.h
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef DATA_H
#define DATA_H

#include <project.h>

/***************************************
 *       Public data types
 ***************************************/

struct DataXY {
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


/***************************************
 *       Public methods
 ***************************************/

extern void data_init(void);


#endif  // ifndef DATA_H
/* [] END OF FILE */
