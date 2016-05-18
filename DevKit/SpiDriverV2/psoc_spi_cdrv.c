#include <linux/err.h>
#include <linux/ctype.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/input.h>
#include <linux/module.h>
#include "psoc_spi_dev.h"

MODULE_AUTHOR("Jeppe Stærk");
MODULE_LICENSE("Dual BSD/GPL");

#define psoc4_MAJOR         64
#define psoc4_MINOR          0
#define psoc4_DEVICE         1
#define MAXLEN              16

#define MODULE_DEBUG 1

/* Char Driver Globals */
static struct cdev psoc4Dev;
struct file_operations psoc4_Fops;
static int devno;

/* Pointer to SPI Device */
static struct spi_device *psoc4_spi_device = NULL;

/* Macro to handle Errors */
#define ERRGOTO(label, ...)                   \
{                                             \
    printk (__VA_ARGS__);                     \
    goto label;                               \
} while(0)

/*
 * PUBLIC METHODS
 */

static int __init psoc4_cdrv_init(void)
{
    int err;
    
    printk("psoc4 driver initializing\n");
    
    /* Register SPI Driver */
    err=psoc4_spi_init();
    if(err)
        ERRGOTO(error, "Failed SPI Initialization\n");
    
    /* Allocate chrdev region */
    devno = MKDEV(psoc4_MAJOR, psoc4_MINOR);
    err = register_chrdev_region(devno, psoc4_DEVICE, "psoc4");
    if(err)
        ERRGOTO(err_spi_init, "Failed registering char region (%d,%d) +%d, error %d\n",
                psoc4_MAJOR, psoc4_MINOR, psoc4_DEVICE, err);
    
    /* Register Char Device */
    cdev_init(&psoc4Dev, &psoc4_Fops);
    err = cdev_add(&psoc4Dev, devno, psoc4_DEVICE);
    if (err)
        ERRGOTO(err_register, "Error %d adding psoc4 device\n", err);
    
    return 0;
    
err_register:
    unregister_chrdev_region(devno, psoc4_DEVICE);
    
err_spi_init:
    psoc4_spi_exit();
    
error:
    return err;
}

static void __exit psoc4_cdrv_exit(void)
{
    printk("psoc4 driver Exit\n");
    cdev_del(&psoc4Dev);
    
    unregister_chrdev_region(devno, psoc4_DEVICE);
    
    psoc4_spi_exit();
}

int psoc4_cdrv_open(struct inode *inode, struct file *filep)
{
    int major = imajor(inode);
    int minor = iminor(inode);
    
    printk("cdrv_open: Opening psoc4 Device [major], [minor]: %i, %i\n", major, minor);
    
    /* Check if minor number is within range */
    if (minor > psoc4_DEVICE-1)
    {
        printk("Minor no out of range (0-%i): %i\n", psoc4_DEVICE, minor);
        return -ENODEV;
    }
    
    /* Check if a psoc4 device is registered */
    if(!(psoc4_spi_device=psoc4_get_device()))
        return -ENODEV;
    
    return 0;
}

int psoc4_cdrv_release(struct inode *inode, struct file *filep)
{
    int major = imajor(inode);
    int minor = iminor(inode);
    
    printk("cdrv_release: Closing psoc4 Device [major], [minor]: %i, %i\n", major, minor);
    
    if ((minor > psoc4_DEVICE-1) || !(psoc4_spi_device=psoc4_get_device()))
        return -ENODEV;
    
    return 0;
}


ssize_t psoc4_cdrv_write(struct file *filep, const char __user *ubuf, size_t count, loff_t *f_pos)
{
    int err, minor, txLen;
    char txBuffer[MAXLEN];
    u16 txData;
    
    minor = iminor(filep->f_inode);
    
    printk(KERN_ALERT "cdrv_write: Writing to psoc4 [Minor] %i \n", minor);
    
    /* Limit copy length to MAXLEN allocated andCopy from user */
    txLen = count < MAXLEN ? count : MAXLEN;
    err = copy_from_user(txBuffer, ubuf, txLen);
    if(err) {return -err;}
    
    /* Pad null termination to string */
    txBuffer[txLen] = '\0';
    
    if(MODULE_DEBUG)
        printk("cdrv_write: string from user: %s lenth: %i\n", txBuffer, txLen);
    
    /* Convert sting to int */
    sscanf(txBuffer, "%hu", &txData);
    
    if(MODULE_DEBUG)
        printk("cdrv_write: data from user: 0x%x\n", txData);
    
    psoc4_spi_write(psoc4_spi_device, txData);
    
    /* Legacy file ptr f_pos. Used to support
     * random access but in char drv we dont!
     * Move it the length actually  written
     * for compability */
    *f_pos += txLen;
    
    /* return length actually written */
    return txLen;
}

ssize_t psoc4_cdrv_read(struct file *filep, char __user *ubuf, size_t count, loff_t *f_pos)
{
    int minor, rxLen;
    u16 rxData;
    char rxBuffer[5];
    
    minor = iminor(filep->f_inode);
    
    if(MODULE_DEBUG)
        printk(KERN_ALERT "cdrv_read: Reading from psoc4 [Minor] %i \n", minor);
    
    psoc4_spi_read(psoc4_spi_device, &rxData);
    
    if(MODULE_DEBUG)
        printk(KERN_DEBUG "cdrv_read: Reading from psoc4 result: 0x%02x\n", rxData);
        
    // Laver en int om til en string
    /* Convert to string and copy to user space */
    //  len = snprintf(resultBuf, sizeof resultBuf, "%d\n", result);
    /* Convert integer to string limited to "count" size. Returns
    * length excluding NULL termination */
    rxLen = sprintf(rxBuffer, "%hu", rxData);
    rxLen++;

    if(MODULE_DEBUG)
        printk(KERN_DEBUG "cdrv_read: Convert from psoc4 result: %s \n", rxBuffer);

    /* Copy data to user space */
    if(copy_to_user(ubuf, rxBuffer, rxLen))
        return -EFAULT;

    /* Move fileptr */
    *f_pos += rxLen;
    
    return rxLen;
}

struct file_operations psoc4_Fops =
{
    .owner   = THIS_MODULE,
    .open    = psoc4_cdrv_open,
    .release = psoc4_cdrv_release,
    .write   = psoc4_cdrv_write,
    .read    = psoc4_cdrv_read,
};

module_init(psoc4_cdrv_init);
module_exit(psoc4_cdrv_exit);