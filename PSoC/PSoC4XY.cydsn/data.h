/*!
 *  @file       data.h
 *  @brief      Data modul
 *  @details    Indeholder data vedr. XY modulet.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef DATA_H
#define DATA_H

#include <project.h>

/***************************************
 *       Class
 ***************************************/

/*!
 *  @class      Data data.h
 *  @brief      Data class
 *  @details    Indeholder data vedr. XY modulet.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */


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
