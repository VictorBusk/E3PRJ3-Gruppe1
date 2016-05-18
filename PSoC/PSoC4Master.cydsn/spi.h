/* ========================================
 *
 * File: spi.h
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

#ifndef SPI_H
#define SPI_H
    
#include <project.h>
#include "led.h"
#include "queue.h"
    
 /***************************************
*         Function Prototypes
****************************************/
    
void spi_init();
void spi_rx();
void spi_tx(uint8 data);

/***************************************
*            Constants
****************************************/

/* Packet size */
#define SPI_PACKET_SIZE      (1u)

/* Packet positions */
#define SPI_PACKET_SOP_POS  (0u)
#define SPI_PACKET_DATA_POS  (0u)
#define SPI_PACKET_EOP_POS  (2u)

/* Start and end of the packet markers */
#define SPI_PACKET_SOP      (0x01u)
#define SPI_PACKET_EOP      (0x17u)

/* Command execution status */
#define SPI_STS_CMD_DONE    (0xAAu)
#define SPI_STS_CMD_FAIL    (0xEEu)

#endif  // ifndef SPI_H
/* [] END OF FILE */
