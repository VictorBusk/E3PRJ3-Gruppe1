/*!
 *  @file       z.h
 *  @brief      Z modul
 *  @details    Styre Z modulets funktioner.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef Z_H
#define Z_H

#include <project.h>


/***************************************
 *       Class
 ***************************************/

/*!
 *  @class      Z z.h
 *  @brief      Z class
 *  @details    Styre Z modulets funktioner.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */


/***************************************
 *       Public methods
 ***************************************/

extern void z_init(void);
extern void z_start(void);
CY_ISR_PROTO(isr_Z);
CY_ISR_PROTO(isr_S);
extern void calibrateZ(void);
extern void setZPos(uint8 zVal);


/***************************************
 *       Public constants
 ***************************************/

/* Konstanter til styring af Z modul */
#define stepDelay (3u)
#define interruptSteps (50u)
#define resolution (255u)


#endif  // ifndef Z_H
/* [] END OF FILE */