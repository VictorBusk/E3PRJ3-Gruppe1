/*!
 * @file        lcd.c
 * @brief       Controls the LCD on PSoC Master
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "data.h"
#include "Nokia5110LCD.h"
/***************************************
 *       Public methods
 ***************************************/

char lineStr[6][12];

/**
 *  @brief      Write new line.
 *  @public
 *  @memberof   Lcd
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void lcd_newline(char* characters)
{
    int i;
    
    for(i = 0; i < 5; i++)
    {
        strncpy(lineStr[i],lineStr[i+1],12);
    }
    
    strcpy(lineStr[5], characters);
    
    for(i = 0; i < 6; i++)
    {
       LCD_gotoXY(0,i);
       LCD_String(lineStr[i]);
    }
}
    
/* [] END OF FILE */