/*!
 * @file        i2c.h
 * @brief       I2C comunication
 * @class       I2c
 * @author      Jeppe Stærk (201271201@uni.au.dk)
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
uint8 i2c_tx(uint8 i2cTxAddr, uint8 i2cTxCmd, uint8 i2cTxVal);
uint8 i2c_rx(uint8 i2cRxAddr, uint8* i2cRxCmd, uint8* i2cRxVal);
extern void i2c_slave(void);


/***************************************
*       Public constants
****************************************/

/*!
 *  @defgroup I2C I2C constants
 */

/* I2C slave address to communicate with */
#define PSoC_XY             (0x08u) /*!< I2C address on PSoC XY. @ingroup I2C */
#define PSoC_Z              (0x09u) /*!< I2C address on PSoC Z. @ingroup I2C */
#define PSoC_Sensor         (0x10u) /*!< I2C address on PSoC Sensor. @ingroup I2C */

/* Buffer and packet size */
#define I2C_BUFFER_SIZE     (4u)    /*!< I2C buffer size. @ingroup I2C */
#define I2C_PACKET_SIZE     (4u)    /*!< I2C packet size. @ingroup I2C */

/* Packet positions */
#define I2C_PACKET_SOP_POS  (0u)    /*!< I2C start of packet position. @ingroup I2C */
#define I2C_PACKET_CMD_POS  (1u)    /*!< I2C comand position. @ingroup I2C */
#define I2C_PACKET_VAL_POS  (2u)    /*!< I2C value position. @ingroup I2C */
#define I2C_PACKET_EOP_POS  (3u)    /*!< I2C end of packet position. @ingroup I2C */

/* Start and end of packet markers */
#define I2C_PACKET_SOP      (0x01u) /*!< I2C start of packet value. @ingroup I2C */
#define I2C_PACKET_EOP      (0x17u) /*!< I2C end of packet value. @ingroup I2C */

/* Command valid status */
#define I2C_STS_CMD_DONE    (0xAAu) /*!< I2C status command done. @ingroup I2C */
#define I2C_STS_CMD_FAIL    (0xEEu) /*!< I2C status command fail. @ingroup I2C */


#endif  // ifndef I2C_H
/* [] END OF FILE */