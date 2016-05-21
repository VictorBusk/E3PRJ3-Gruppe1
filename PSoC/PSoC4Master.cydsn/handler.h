/*!
 * @file        handler.h
 * @brief       Handels incoming commands
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */

#ifndef HANDLER_H
#define HANDLER_H
    
#include <project.h>
#include "i2c.h"
#include "spi.h"

uint8 xPos;
uint8 xMax;
uint8 yPos;
uint8 yMax;
uint8 zPos;
uint8 zMax;
    
/***************************************
*         Function Prototypes
****************************************/
    
extern void handler(uint8 cmd, uint8 val);

/***************************************
*            Constants
****************************************/

/* Commands set */
#define setXPos (0x10u)
#define setYPos (0x11u)
#define getXPos (0x12u)
#define getYPos (0x13u)
#define getXMax (0x14u)
#define getYMax (0x15u)
#define cmdStopX (0x16u)
#define cmdStopY (0x17u)
#define cmdCalibrateX (0x18u)
#define cmdCalibrateY (0x19u)
#define setZPos (0x20u)
#define getZPos (0x21u)
#define getZMax (0x22u)
#define cmdStopZ (0x23u)
#define cmdCalibrateZ (0x24u)
#define setRed (0x30u)
#define setGreen (0x31u)
#define setBlue (0x32u)
#define setLumen (0x33u)
#define setPower (0x34u)
#define getRed (0x35u)
#define getGreen (0x36u)
#define getBlue (0x37u)
#define getLumen (0x38u)
#define getPower (0x39u)
#define setDistance (0x40u)
#define setMovement (0x41u)
#define getDistance (0x42u)
#define getMovement (0x43u)
#define cmdDistanceAlert (0x44u)
#define cmdMovementAlert (0x45u)
#define setMasterLedOff (0x70)
#define setMasterLedRed (0x71)
#define setMasterLedGreen (0x72)
#define setMasterLedBlue (0x73)

#endif  // ifndef HANDLER_H
/* [] END OF FILE */
