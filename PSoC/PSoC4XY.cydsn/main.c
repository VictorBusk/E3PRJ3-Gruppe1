/* ========================================
 *
 * File: main.c
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

#include <project.h>
#include "data.h"
#include "handler.h"
#include "i2c.h"
#include "led.h"
#include "queue.h"
#include "xy.h"

int main()
{
    CyGlobalIntEnable;

    data_init();
    queue_init(6u);
    xy_init();
    i2c_init();
    
    setLed(0,1,0);
    CyDelay(100);
    setLed(0,0,0);
    
    for(;;)
    {
        if(SW2_Read() == 0u)
        {
            CyDelay(5u);
            if(SW2_Read() == 0u)
            {
                calibrateX();
                calibrateY();
            }
            while(SW2_Read() == 0u)
            {
                ; /* Wait till button released */
            }
        }
        
        i2c_rx();
        
        while(isEmptyQueue() != 1)
        {
            struct Data action;
            action = frontQueue();
            handler(action.cmd_, action.val_);
            popQueue();
        }
        i2c_tx();
    }
}

/* [] END OF FILE */
