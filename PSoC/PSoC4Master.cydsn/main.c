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
  DEBUG_Start();

  lcd_newline("------------");
  lcd_newline("<          >");
  lcd_newline("< L.A.M.P! >");
  lcd_newline("< Prj3Gpr1 >");
  lcd_newline("<          >");
  lcd_newline("------------");
  
  setLed(1,0,0,150);
  setLed(0,1,0,150);
  setLed(0,0,1,150);
  
  DEBUG_PutCRLF();
  DEBUG_PutString("===== Initializing PSoC Master =====");
  DEBUG_PutCRLF();
  CyGlobalIntEnable; /* Enable global interrupts. */
  
  for(;;)
  {
    setLed(0,0,0,0);
    
    while(isEmptyQueue() != 1)
    {
      struct Action action;
      action = frontQueue();
      if(action.cmd != 0)
      {
        handler(action.cmd, action.val);
      }
      popQueue();
    }
  }
}

/* [] END OF FILE */
