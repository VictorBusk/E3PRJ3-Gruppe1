/*!
 * @file        data.h
 * @brief       
 * @class       Data
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#ifndef DATA_H
#define DATA_H

#include <project.h>

/***************************************
*       Public data types
***************************************/

/*!
 *  @brief      Struct to contain a data
 *  @public
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
struct DataMaster_T
{
    uint8 xVal; /**< Value of the X position. */
    uint8 yVal; /**< Value of the Y position. */
    uint8 zVal; /**< Value of the Z position. */
    uint8 rVal; /**< Value of the red led. */
    uint8 gVal; /**< Value of the green led. */
    uint8 bVal; /**< Value of the blue led. */
    uint8 lumenVal; /**< Value of the lumen. */
    uint8 powerVal; /**< Value of the power. */
    uint8 distanceVal; /**< Value of the distance. */
    uint8 movementVal; /**< Value of the movememt. */
}dataMaster;

/***************************************
 *       Public methods
 ***************************************/

extern void data_init(void);

#endif  // ifndef DATA_H
/* [] END OF FILE */