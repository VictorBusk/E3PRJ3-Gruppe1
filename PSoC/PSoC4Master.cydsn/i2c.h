/* ========================================
 *
 * File: i2c.h
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: Jeppe Stærk
 * Matriculation number: 201271201
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

#ifndef I2C_H
#define I2C_H
    
#include <project.h>
#include "led.h"
#include "queue.h"

/***************************************
*         Function Prototypes
****************************************/
    
void i2c_init();
extern void i2c_tx(uint8 i2cTxAddr, uint8 i2cTxCmd, uint8 i2cTxVal);
extern void i2c_rx(uint8 i2cRxAddr, uint8 i2cRxCmd, uint8* i2cRxVal);
extern void i2c_slave();

/***************************************
*            Constants
****************************************/

/* Buffer and packet size */
#define I2C_BUFFER_SIZE         (4u)
#define I2C_PACKET_SIZE         (I2C_BUFFER_SIZE)

/* Packet positions */
#define I2C_PACKET_SOP_POS      (0u)
#define I2C_PACKET_CMD_POS      (1u)
#define I2C_PACKET_VAL_POS      (2u)
#define I2C_PACKET_EOP_POS      (3u)

/* Start and end of packet markers */
#define I2C_PACKET_SOP          (0x01u)
#define I2C_PACKET_EOP          (0x17u)

/* Command valid status */
#define I2C_STS_CMD_DONE        (0xAAu)
#define I2C_STS_CMD_FAIL        (0xEEu)

#endif  // ifndef I2C_H
/* [] END OF FILE */
