/* ========================================
 *
 * File: handler.c
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

#include "led.h"

void setLed(uint8 red, uint8 green, uint8 blue)
{
    red ? LED_Red_Write(0u) : LED_Red_Write(1u);
    green ? LED_Green_Write(0u) : LED_Green_Write(1u);
    blue ? LED_Blue_Write(0u) : LED_Blue_Write(1u);
}

/* [] END OF FILE */
