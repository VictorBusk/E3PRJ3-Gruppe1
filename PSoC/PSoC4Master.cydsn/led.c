/* ========================================
 *
 * File: led.c
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: Jeppe Stærk
 * Matriculation number: 201271201
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

#include "led.h"

void setLed(uint8 red, uint8 green, uint8 blue, uint8 time) 
{
    red ? LED_RED_Write(LED_ON) : LED_RED_Write(LED_OFF);
    green ? LED_GREEN_Write(LED_ON) : LED_GREEN_Write(LED_OFF);
    blue ? LED_BLUE_Write(LED_ON) : LED_BLUE_Write(LED_OFF);
    
    CyDelay(time);
}

void queueLed(uint8 red, uint8 green, uint8 blue, uint8 time) 
{
    struct Data ledAction;
    
    if(red)
    {
        ledAction.cmd_ = setMasterLedRed;
        ledAction.val_ = time;
    }
    else if(green)
    {
        ledAction.cmd_ = setMasterLedGreen;
        ledAction.val_ = time;
    }
    else if(blue)
    {
        ledAction.cmd_ = setMasterLedBlue;
        ledAction.val_ = time;
    }
    else
    {
        ledAction.cmd_ = setMasterLedOff;
        ledAction.val_ = time;
    }
    
    pushQueue(ledAction);
}
    
/* [] END OF FILE */
