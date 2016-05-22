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
#include "handler.h"
#include "queue.h"

extern void i2c_init(void);
extern void i2c_rx(void);
// CY_ISR_PROTO(isr_i2c_rx);
extern void i2c_tx(void);

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

uint8 i2cTxBuffer[I2C_BUFFER_SIZE];
uint8 i2cRxBuffer[I2C_BUFFER_SIZE];
    
#endif  // ifndef I2C_H
/* [] END OF FILE */
