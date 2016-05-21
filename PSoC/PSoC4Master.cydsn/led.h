/*!
 * @file        led.h
 * @brief       Controls the LED on PSoC Master
 * @class       Led
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#ifndef LED_H
#define LED_H

#include <project.h>

/***************************************
 *       Public methods
 ***************************************/

extern void setLed(uint8 red, uint8 green, uint8 blue, uint8 delay);

/***************************************
 *       Public constants
 ***************************************/

/*!
 *  @defgroup   LED LED constants
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
#define LED_ON       (0u) /*!< LED on value. @ingroup LED */
#define LED_OFF      (1u) /*!< SPI off value. @ingroup LED */
    
#endif  // ifndef LED_H
/* [] END OF FILE */