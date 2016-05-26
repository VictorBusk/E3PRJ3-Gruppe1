/*!
 *  @file       led.c
 *  @brief      LED modul
 *  @details    Håndtere PSoC'ens røde, grønne og blå led.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "led.h"

/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Sætter den defineret farve og angivet delay.
 *  @details    Metoden sætter den/de valgte farver og venter i det angivet delay.
 *  @param[in]  red     Tænder/slukker den røde led.
 *  @param[in]  green   Tænder/slukker den grønne led.
 *  @param[in]  blue    Tænder/slukker den blå led.
 *  @param[in]  delay   Tid i microsekunder til delay.
 *  @public
 *  @memberof   LED
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
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
