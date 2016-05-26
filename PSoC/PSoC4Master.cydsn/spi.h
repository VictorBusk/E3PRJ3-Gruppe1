/*!
 *  @file       spi.h
 *  @brief      SPI modul
 *  @details    Håndter kommunikation via SPI-busset.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#ifndef SPI_H
#define SPI_H

#include <project.h>

/***************************************
 *       Class
 ***************************************/
    
/*!
 *  @class      SPI spi.h
 *  @brief      SPI class
 *  @details    Håndter kommunikation via SPI-busset.
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
    
    
/***************************************
 *       Public methods
 ***************************************/

extern void spi_init(void);
CY_ISR_PROTO(isr_spi_rx);


/***************************************
 *       Public constants
 ***************************************/

/* Buffer and pakke størelse */
#define SPI_BUFFER_SIZE     (1u)
#define SPI_PACKET_SIZE     (1u)

/* Pakke positioner */
#define SPI_PACKET_DATA_POS (0u)

/* Status */
#define SPI_STS_CMD_DONE    (0xAAAAu)
#define SPI_STS_CMD_FAIL    (0xEEEEu)


#endif  // ifndef SPI_H
/* [] END OF FILE */
