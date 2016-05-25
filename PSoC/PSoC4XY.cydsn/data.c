/*!
 *  @file       data.c
 *  @brief      Data modul
 *  @details    Indeholder data vedr. XY modulet.
 *  @ingroup    PSoC-XY
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "data.h"

/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Initialiser data modulet
 *  @details    Initialiser dataXY structen med start værdier.
 *  @ingroup    PSoC-XY
 *  @public
 *  @memberof   Data
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
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
