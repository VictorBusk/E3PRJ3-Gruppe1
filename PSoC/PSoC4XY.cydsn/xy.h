/*!
 * @todo  Dokumenter! xy.h
 */
#ifndef XY_H
#define XY_H

#include <project.h>

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

#define stepDelay (3u)
#define interruptSteps (50u)
#define resolution (255u)

#endif  // ifndef XY_H
/* [] END OF FILE */
