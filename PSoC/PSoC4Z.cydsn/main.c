/*!
 *  @file       main.c
 *  @brief      Hovedprogram
 *  @details    Intilizere modulerne og køre derefter i loop hvor der bliver kontrolieret om der er nogle actions i køen der skal håndteres af handleren.
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
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
  
  DEBUG_PutCRLF();
  DEBUG_PutString("===== Initializing PSoC Z =====");
  DEBUG_PutCRLF();
  
  setLed(0,1,0,0);
  CyDelay(100);
  setLed(0,0,0,0);
  
  z_start();
  
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
    
    while(isEmptyQueue() != 1)
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