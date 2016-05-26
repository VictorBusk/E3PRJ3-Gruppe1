/*!
 *  @file       data.h
 *  @brief      Data modul
 *  @details    Indeholder data hentet fra PSoC-XY, -Z og -Sensor.
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
 *  @details    Indeholder data hentet fra PSoC-XY, -Z og -Sensor.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
    
/***************************************
 *       Public data types
 ***************************************/

/*!
 *  @brief      Data struct
 *  @details    En data struct der indeholder de sidst kendte værdier fra PSoC-XY -Z og -Sensor.
 *  @public
 *  @memberof   Data
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
struct DataMaster
{
  uint8 xVal; /**< Værdi for sidst kendte X position */
  uint8 yVal; /**< Værdi for sidst kendte Y position */
  uint8 zVal; /**< Værdi for sidst kendte Z position */
  uint8 rVal; /**< Værdi for sidst kendte R niveau */
  uint8 gVal; /**< Værdi for sidst kendte G niveau */
  uint8 bVal; /**< Værdi for sidst kendte B niveau */
}dataMaster;


/***************************************
 *       Public methods
 ***************************************/

extern void data_init(void);


#endif  // ifndef DATA_H
/* [] END OF FILE */
