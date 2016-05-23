/* ========================================
 *
 * File: main.c
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

#include <project.h>
#include "data.h"
#include "handler.h"
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "spi.h"
#include "Nokia5110LCD.h"
#include "lcd.h"

int main()
{
    data_init();
    queue_init(6u);
    spi_init();
    i2c_init();
    LCD_Init();
    
    setLed(1,0,0,150);
    setLed(0,1,0,150);
    setLed(0,0,1,150);
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    for(;;)
    {
        setLed(0,0,0,0);
        
        while(isEmptyQueue() != 1)
        {
            struct Data action;
            action = frontQueue();
            if(action.cmd_ != 0)
            {
                handler(action.cmd_, action.val_);
            }
            popQueue();
        }
    }
}

/* [] END OF FILE */
