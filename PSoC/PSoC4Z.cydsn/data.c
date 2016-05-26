/*!
 *  @file       data.c
 *  @brief      Data modul
 *  @details    Indeholder data vedr. Z modulet.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "data.h"


/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Initialiser data modulet
 *  @details    Initialiser dataZ structen med start værdier.
 *  @public
 *  @memberof   Data
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
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