/*!
 *  @file       handler.h
 *  @brief      Handler modul
 *  @details    Håndtere indkommende kommandoer med tilhørende værdier.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef HANDLER_H
#define HANDLER_H

#include <project.h>

/***************************************
 *       Class
 ***************************************/

/*!
 *  @class      Handler handler.h
 *  @brief      Handler class
 *  @details    Håndtere indkommende kommandoer med tilhørende værdier.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */

/***************************************
 *       Public methods
 ***************************************/

extern void handler(uint8 cmd, uint8 val);


/***************************************
 *       Public constants
 ***************************************/

/* Kommando liste */
#define CMD_SET_X_POS (0x10u)
#define CMD_SET_Y_POS (0x11u)
#define CMD_GET_X_POS (0x12u)
#define CMD_GET_Y_POS (0x13u)
#define CMD_X_STP (0x16u)
#define CMD_Y_STP (0x17u)
#define CMD_X_CAL (0x18u)
#define CMD_Y_CAL (0x19u)


#endif  // ifndef HANDLER_H
/* [] END OF FILE */
