/*!
 * @file        spi.h
 * @brief       SPI comunication
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */

#ifndef SPI_H
#define SPI_H
    
#include <project.h>
#include "led.h"
#include "queue.h"
    
/***************************************
*         Function Prototypes
****************************************/

/*!
 *  @brief      Initialize SPI slave
 */
extern void spi_init(void);

/*!
 *  @brief      ISR for SPI slave rx
 */
CY_ISR_PROTO(isr_spi_rx);

/*!
 *  @brief      Update tx buffer for SPI slave.
 *  @param      data Data to bre sent.
 */
extern void spi_tx(uint8 data);


/***************************************
*            Constants
****************************************/

/*!
 *  @defgroup SPI SPI constants
 */

#define SPI_BUFFER_SIZE     (1u)    /*!< SPI buffer size. @ingroup SPI */      
#define SPI_PACKET_SIZE     (1u)    /*!< SPI packet size. @ingroup SPI */ 
#define SPI_PACKET_SOP_POS  (0u)    /*!< SPI start of packet position. @ingroup SPI */ 
#define SPI_PACKET_DATA_POS (0u)    /*!< SPI data position. @ingroup SPI */
#define SPI_PACKET_EOP_POS  (2u)    /*!< SPI end of packet position. @ingroup SPI */ 
#define SPI_PACKET_SOP      (0x01u) /*!< SPI start of packet value. @ingroup SPI */ 
#define SPI_PACKET_EOP      (0x17u) /*!< SPI end of packet value. @ingroup SPI */
#define SPI_STS_CMD_DONE    (0xAAu) /*!< SPI status command done. @ingroup SPI */
#define SPI_STS_CMD_FAIL    (0xEEu) /*!< SPI status command fail. @ingroup SPI */

#endif  // ifndef SPI_H
/* [] END OF FILE */
