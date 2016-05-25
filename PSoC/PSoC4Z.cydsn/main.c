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
#include "z.h"

int main()
{
  CyGlobalIntEnable;
  
  data_init();
  queue_init(6u);
  z_init();
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
        calibrateZ();
      }
      while(SW2_Read() == 0u)
      {
        ; /* Wait till button released */
      }
    }
    
    i2c_rx();
    
    if(isEmptyQueue() != 1)
    {
      struct Action action;
      action = frontQueue();
      handler(action.cmd, action.val);
      popQueue();
    }
    
    i2c_tx();
  }
}

/* [] END OF FILE */
