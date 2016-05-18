#include <linux/err.h>
#include <linux/spi/spi.h>
#include <linux/module.h>
#include "psoc_spi_dev.h"

MODULE_AUTHOR("Jeppe Stærk");
MODULE_LICENSE("Dual BSD/GPL");

#define MODULE_DEBUG 1


/* We are only using ONE SPI device so far */
static struct spi_device *psoc4_spi_device = NULL;

/* Method to retrieve SPI device pointer */
struct spi_device* psoc4_get_device(void){
    return psoc4_spi_device;
}

/*
 * psoc4 SPI Read 16-bit Register
 * Reads 16-bit content of register at 
 * the provided psoc4 address
 */
int psoc4_spi_read(struct spi_device *spi, u16 txData, u16* rxData)
{
    struct spi_transfer t[2];
    struct spi_message m;
    u16 rxBuffer = 0;
    
    /* Check for valid spi device */
    if(!spi)
        return -ENODEV;
    
    /* Init Message */
    memset(t, 0, sizeof(t));
    spi_message_init(&m);
    m.spi = spi;
    
    t[0].tx_buf = &txData;
    t[0].rx_buf = NULL;
    t[0].len = 2;
    t[0].delay_usecs = 150;
    spi_message_add_tail(&t[0], &m);
    
    t[1].tx_buf = NULL;
    t[1].rx_buf = &rxBuffer;
    t[1].len = 2;
    spi_message_add_tail(&t[1], &m);
    
    /* Transmit SPI Data (blocking) */
    spi_sync(m.spi, &m);
    
    if(MODULE_DEBUG)
        printk(KERN_DEBUG "dev_read: Read data 0x%hx\n", rxBuffer);
      
    *rxData = rxBuffer;
    return 0;
}

/*
 * psoc4 SPI Write 16-bit Register
 * Writes 16-bit content to register at 
 * the provided psoc4 address
 */
int psoc4_spi_write(struct spi_device *spi, u16 txData)
{
    struct spi_transfer t[1];
    struct spi_message m;
        
    /* Check for valid spi device */
    if(!spi)
        return -ENODEV;
    
    /* Init Message */
    memset(&t, 0, sizeof(t)); 
    spi_message_init(&m);
    m.spi = spi;
    
    if(MODULE_DEBUG)
        printk(KERN_DEBUG "dev_write: Write data 0x%x\n", txData);

    /* Configure tx/rx buffers */
    t[0].tx_buf = &txData;
    t[0].rx_buf = NULL;
    t[0].len = 2;
//    t[0].delay_usecs = 60;
    spi_message_add_tail(&t[0], &m);

    /* Transmit SPI Data (blocking) */
    spi_sync(m.spi, &m);
    
    return 0;
}

/*
 * psoc4 Probe
 * Used by the SPI Master to probe the device
 * when an SPI device is registered.
 */
//static int __devinit psoc4_spi_probe(struct spi_device *spi)
static int psoc4_spi_probe(struct spi_device *spi)
{    
    int err = 0;
    printk(KERN_DEBUG "dev_probe: New SPI device: %s using chip select: %i\n",
           spi->modalias, spi->chip_select);
    
    spi->bits_per_word = 16;
    
    spi_setup(spi);
    
    /* In this case we assume just one device */
    psoc4_spi_device = spi;
    
    return err;
}

/*
 * psoc4 Remove
 * Called when the SPI device is removed
 */
static int psoc4_remove(struct spi_device *spi)
{
    psoc4_spi_device = 0;
    
    printk (KERN_ALERT "dev_remove: Removing SPI device %s on chip select %i\n",
            spi->modalias, spi->chip_select);
    
    return 0;
}

/*
 * psoc4 SPI Driver Struct
 * Holds function pointers to probe/release
 * methods and the name under which it is registered
 *
 */
static struct spi_driver psoc4_spi_driver = {
    .driver = {
        .name = "psoc4",
        .bus = &spi_bus_type,
        .owner = THIS_MODULE,
    },
    .probe = psoc4_spi_probe,
    .remove = psoc4_remove,
};


/*
 * psoc4 SPI Init
 * Registers the spi driver with the SPI host
 */
int psoc4_spi_init(void)
{
    int err;
    
    err = spi_register_driver(&psoc4_spi_driver);
    
    if(err<0)
        printk (KERN_ALERT "Error %d registering the psoc4 SPI driver\n", err);
    
    return err;
}

/*
 * psoc4 SPI Exit
 * Exit routine called from character driver.
 * Unregisters the driver from the SPI host
 */
void psoc4_spi_exit(void)
{
    spi_unregister_driver(&psoc4_spi_driver);
}