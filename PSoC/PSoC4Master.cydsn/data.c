/*!
 *  @file       data.c
 *  @brief      Data modul
 *  @details    Indeholder data hentet fra PSoC-XY, -Z og -Sensor.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "data.h"

/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Initialiser data modulet
 *  @details    Initialiser data structen med 0 værdier.
 *  @public
 *  @memberof   Data
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void data_init()
{
  dataMaster.xVal = 0;
  dataMaster.yVal = 0;
  dataMaster.zVal = 0;
  dataMaster.rVal = 0;
  dataMaster.gVal = 0;
  dataMaster.bVal = 0;
}


/* [] END OF FILE */
