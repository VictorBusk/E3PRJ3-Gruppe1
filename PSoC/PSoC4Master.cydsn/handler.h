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
#define CMD_SET_X_POS (0x10u)
#define CMD_SET_Y_POS (0x11u)
#define CMD_GET_X_POS (0x12u)
#define CMD_GET_Y_POS (0x13u)
#define CMD_GET_X_MAX (0x14u)
#define CMD_GET_Y_MAX (0x15u)
#define CMD_X_STP (0x16u)
#define CMD_Y_STP (0x17u)
#define CMD_X_CAL (0x18u)
#define CMD_Y_CAL (0x19u)
#define CMD_SET_Z_POS (0x20u)
#define CMD_GET_Z_POS (0x21u)
#define CMD_GET_Z_MAX (0x22u)
#define CMD_Z_STP (0x23u)
#define CMD_Z_CAL (0x24u)
#define CMD_SET_RED_VAL (0x30u)
#define CMD_SET_GREEN_VAL (0x31u)
#define CMD_SET_BLUE_VAL (0x32u)
#define CMD_SET_LUMEN_VAL (0x33u)
#define CMD_SET_POWER_STS (0x34u)
#define CMD_GET_RED_VAL (0x35u)
#define CMD_GET_GREEN_VAL (0x36u)
#define CMD_GET_BLUE_VAL (0x37u)
#define CMD_GET_LUMEN_VAL (0x38u)
#define CMD_GET_POWER_STS (0x39u)
#define CMD_SET_DISTANCE_STS (0x40u)
#define CMD_SET_MOVEMENT_STS (0x41u)
#define CMD_GET_DISTANCE_STS (0x42u)
#define CMD_GET_MOVEMENT_STS (0x43u)
#define CMD_DISTANCE_ALRT (0x44u)
#define CMD_MOVEMENT_ALRT (0x45u)


#endif  // ifndef HANDLER_H
/* [] END OF FILE */
