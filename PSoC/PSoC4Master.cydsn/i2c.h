/*!
 *  @file       i2c.h
 *  @brief      I2C modul
 *  @details    Håndter kommunikation via I2C-busset
 *  @ingroup    PSoC-Master
 *  @class      I2C i2c.h
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef I2C_H
#define I2C_H

#include <project.h>

/***************************************
 *       Public methods
 ***************************************/

extern void i2c_init(void);
extern void i2c_setPacket(uint8 i2cAddr, uint8 i2cCmd, uint8 i2cVal);
extern void i2c_getPacket(uint8 i2cAddr, uint8 i2cCmd, uint8* i2cVal);


/***************************************
 *       Public constants
 ***************************************/

/* I2C slave adresser */
#define PSoC_XY             (0x08u)
#define PSoC_Z              (0x09u)
#define PSoC_Sensor         (0x10u)

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


#endif  // ifndef I2C_H
/* [] END OF FILE */