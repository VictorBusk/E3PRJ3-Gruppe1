/*!
 *  @file       data.h
 *  @brief      Data modul
 *  @details    Indeholder data vedr. Z modulet.
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
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */


/***************************************
 *       Public data types
 ***************************************/

struct DataZ {
  uint8 calibratedZ;
  uint8 interruptZ;
  uint8 isrStopZ;
  uint8 zFlag;
  uint32 zMax;
  uint32 zPos;
}dataZ;


/***************************************
 *       Public methods
 ***************************************/

extern void data_init(void);


#endif  // ifndef DATA_H
/* [] END OF FILE */