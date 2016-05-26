/*!
 *  @file       xy.h
 *  @brief      XY modul
 *  @details    Styre XY modulets funktioner.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 */
#ifndef XY_H
#define XY_H

#include <project.h>


/***************************************
 *       Class
 ***************************************/

/*!
 *  @class      XY xy.h
 *  @brief      XY class
 *  @details    Styre XY modulets funktioner.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 */


/***************************************
 *       Public methods
 ***************************************/

extern void xy_init(void);
extern void xy_start(void);
CY_ISR_PROTO(isr_X);
CY_ISR_PROTO(isr_Y);
extern void calibrateX(void);
extern void calibrateY(void);
extern void setXPos(uint8 xVal);
extern void setYPos(uint8 yVal);


/***************************************
 *       Public constants
 ***************************************/

/* Konstanter til styring af XY modul */
#define stepDelay (3u)
#define interruptSteps (50u)
#define resolution (255u)


#endif  // ifndef XY_H
/* [] END OF FILE */