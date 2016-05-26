/*!
 *  @file       lcd.c
 *  @brief      LCD modul
 *  @details    Sender tekst til Nokia5110LCD skærmen via dens eksterne kode.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "data.h"
#include "Nokia5110LCD.h"


/***************************************
 *       Private attributes
 ***************************************/

/*!
 *  @brief      Char array der indholder tekst
 *  @details    Arrayet er et matrix array med 6 arryes med 12 pladser, det bruges til at indeholde de 6 linjer tekst der kan udskrives på Nokia 5110 LCD skærmen.
 *  @private
 *  @memberof   LCD
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
char lineStr[6][12];


/***************************************
 *       Public methods
 ***************************************/

/*!
 *  @brief      Udskriver tekst på Nokia 5110 LCD
 *  @details    Metoden bruges til at skrive en ny linje nederst på Nokia 5110 LCD skærmen, den husker på- og flytter de forhenværende linjer en linje op, når der indættes en ny.
 *  @public
 *  @memberof   LCD
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
  
  LCD_Clear();
  for(i = 0; i < 6; i++)
  {
    LCD_gotoXY(0,i);
    LCD_String(lineStr[i]);
  }
}


/* [] END OF FILE */
