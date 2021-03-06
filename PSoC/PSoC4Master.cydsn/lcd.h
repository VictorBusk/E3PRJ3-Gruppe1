/*!
 *  @file       lcd.h
 *  @brief      LCD modul
 *  @details    Sender tekst til Nokia5110LCD skærmen via dens eksterne kode.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef LCD_H
#define LCD_H

#include <project.h>
    
    
/***************************************
 *       Class
 ***************************************/
    
/*!
 *  @class      LCD lcd.h
 *  @brief      LCD class
 *  @details    Sender tekst til Nokia5110LCD skærmen via dens eksterne kode.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
    
/***************************************
 *       Public methods
 ***************************************/

extern void lcd_newline(char* characters);


#endif  // ifndef LCD_H
/* [] END OF FILE */
