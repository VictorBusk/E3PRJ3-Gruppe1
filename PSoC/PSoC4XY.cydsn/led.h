/*!
 *  @file       led.h
 *  @brief      LED modul
 *  @details    Håndtere PSoC'ens røde, grønne og blå led.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef LED_H
#define LED_H

#include <project.h>

/***************************************
 *       Class
 ***************************************/

/*!
 *  @class      LED led.h
 *  @brief      LED class
 *  @details    Håndtere PSoC'ens røde, grønne og blå led
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */


/***************************************
 *       Public methods
 ***************************************/

extern void setLed(uint8 red, uint8 green, uint8 blue, uint8 delay);


/***************************************
 *       Public constants
 ***************************************/

/* Ledens status */
#define LED_ON       (0u)
#define LED_OFF      (1u)


#endif  // ifndef LED_H
/* [] END OF FILE */
