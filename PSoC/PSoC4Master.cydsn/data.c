/*!
 *  @file       data.c
 *  @brief      Data modul
 *  @details    Indeholder data hentet fra PSoC-XY, -Z og -Sensor.
 *  @ingroup    PSoC-Master
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "data.h"

/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Initialiser data modulet
 *  @details    Initialiser dataMaster structen med 0 værdier.
 *  @ingroup    PSoC-Master
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
  dataMaster.lumenVal = 0;
  dataMaster.powerVal = 0;
  dataMaster.distanceVal = 0;
  dataMaster.movementVal = 0;
}


/* [] END OF FILE */