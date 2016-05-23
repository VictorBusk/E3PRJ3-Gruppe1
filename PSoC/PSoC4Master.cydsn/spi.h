/*!
 *  @file        spi.h
 *  @brief       SPI comunication
 *  @class       Spi
 *  @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#ifndef SPI_H
#define SPI_H
    
#include <project.h>
    
/***************************************
 *       Public methods
 ***************************************/

extern void spi_init(void);
extern void spi_rx(void);
CY_ISR_PROTO(isr_spi_rx);
extern void spi_tx(uint8 data);


/***************************************
 *       Public constants
 ***************************************/

/*!
 *  @defgroup   SPI SPI constants
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
#define SPI_BUFFER_SIZE     (1u)    /*!< SPI buffer size. @ingroup SPI */      
#define SPI_PACKET_SIZE     (1u)    /*!< SPI packet size. @ingroup SPI */ 
#define SPI_PACKET_DATA_POS (0u)    /*!< SPI data position. @ingroup SPI */
#define SPI_STS_CMD_DONE    (0xAAAAu) /*!< SPI status command done. @ingroup SPI */
#define SPI_STS_CMD_FAIL    (0xEEEEu) /*!< SPI status command fail. @ingroup SPI */

#endif  // ifndef SPI_H
/* [] END OF FILE */