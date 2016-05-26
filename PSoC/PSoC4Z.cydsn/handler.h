/*!
 *  @file       handler.h
 *  @brief      Handler modul
 *  @details    Håndtere indkommende kommandoer med tilhørende værdier.
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
#define CMD_SET_Z_POS (0x20u)
#define CMD_GET_Z_POS (0x21u)
#define CMD_Z_STP (0x23u)
#define CMD_Z_CAL (0x24u)


#endif  // ifndef HANDLER_H
/* [] END OF FILE */