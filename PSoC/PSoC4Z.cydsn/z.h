/* ========================================
 *
 * File: z.h
 * Description:
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 *
 * Author:
 * Matriculation number:
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
 */

#ifndef Z_H
#define Z_H

#include <project.h>

#define stepDelay (3u)
#define interruptSteps (50u)
#define resolution (255u)

void z_init(void);
CY_ISR_PROTO(isr_Z);
CY_ISR_PROTO(isr_S);
void calibrateZ(void);
void setZPos(uint8 zVal);
void stepZForwards(void);
void stepZBackwards(void);
void stopZ(void);

#endif  // ifndef Z_H
/* [] END OF FILE */
