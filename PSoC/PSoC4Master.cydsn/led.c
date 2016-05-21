/*!
 * @file        led.c
 * @brief       Controls the LED on PSoC Master
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "led.h"

/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Set LED color on PSoC Master for given time.
 *  @param[in]  red     Sets the red led.
 *  @param[in]  green   Sets the green led.
 *  @param[in]  blue    Sets the blue led.
 *  @param[in]  delay   Sets the delay before moving on.
 *  @public
 *  @memberof   Led
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void setLed(uint8 red, uint8 green, uint8 blue, uint8 delay) 
{
    red ? LED_RED_Write(LED_ON) : LED_RED_Write(LED_OFF);
    green ? LED_GREEN_Write(LED_ON) : LED_GREEN_Write(LED_OFF);
    blue ? LED_BLUE_Write(LED_ON) : LED_BLUE_Write(LED_OFF);
    
    CyDelay(delay);
}

    
/* [] END OF FILE */