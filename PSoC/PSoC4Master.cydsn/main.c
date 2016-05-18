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
#include "handler.h"
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "spi.h"

int main()
{
    queue_init();
    spi_init();
    i2c_init();   
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    queueLed(1,0,0,150);
    queueLed(0,1,0,150);
    queueLed(0,0,1,150);

    for(;;)
    {
        setLed(0,0,0,0);
        spi_rx();
        
        if(Knap_Read() == 0u)
        {
            CyDelay(5u);
            if(Knap_Read() == 0u)
            {
                struct Data test;
                test.cmd_ = 0x20;
                test.val_ = 0xAA;
                pushQueue(test);
            }
            while(Knap_Read() == 0u)
            {
            }
        }
        
        i2c_slave();
        
        while(isEmptyQueue() != 1)
        {
            struct Data action;
            action = frontQueue();
            handler(action.cmd_, action.val_);
            popQueue();
        }
        
//        spi_cleanup();
        
        CyDelay(50);
    }
}

/* [] END OF FILE */
