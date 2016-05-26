/*!
 *  @file       i2c.h
 *  @brief      I2C modul
 *  @details    Håndter kommunikation via I2C-busset.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef I2C_H
#define I2C_H

#include <project.h>


/***************************************
 *       Class
 ***************************************/

/*!
 *  @class      I2C i2c.h
 *  @brief      I2C class
 *  @details    Håndter kommunikation via I2C-busset.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */


/***************************************
 *       Public methods
 ***************************************/

extern void i2c_init(void);
extern void i2c_tx(void);


/***************************************
 *       Public constants
 ***************************************/

/* Buffer and pakke størelse */
#define I2C_BUFFER_SIZE     (4u)
#define I2C_PACKET_SIZE     (4u)

/* Pakke positioner */
#define I2C_PACKET_SOP_POS  (0u)
#define I2C_PACKET_CMD_POS  (1u)
#define I2C_PACKET_VAL_POS  (2u)
#define I2C_PACKET_EOP_POS  (3u)

/* Start og slut pakker */
#define I2C_PACKET_SOP      (0xBEu)
#define I2C_PACKET_EOP      (0xEFu)

/* Status */
#define I2C_STS_CMD_DONE    (0xAAu)
#define I2C_STS_CMD_FAIL    (0xEEu)


/***************************************
 *       Public attributes
 ***************************************/

/*!
 *  @brief      Buffer til afsendelse af data.
 *  @details    En buffer der indeholder de data pakker der skal sende over I2C-busset.
 *  @public
 *  @memberof   I2C
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
extern uint8 i2cTxBuffer[I2C_BUFFER_SIZE];

/*!
 *  @brief      Buffer til modtagelse af data.
 *  @details    En buffer der indeholder de data pakker der skal modtagelse over I2C-busset.
 *  @public
 *  @memberof   I2C
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
extern uint8 i2cRxBuffer[I2C_BUFFER_SIZE];


#endif  // ifndef I2C_H
/* [] END OF FILE */